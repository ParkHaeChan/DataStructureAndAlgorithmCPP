#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

struct job
{
    int arrived;
    int needed;
    int classnum;
    int importance;
};

vector<int> solution(vector<vector<int>> jobs) {
    vector<int> answer;

    queue<job> jobQ;
    for(int i=0; i<jobs.size(); ++i)
    {   // 요청 시간순 정렬된 입력
        jobQ.push({jobs[i][0],jobs[i][1],jobs[i][2],jobs[i][3]});
    }
    int cur_time = 0;
    int cur_class_num = 0;
    job first = jobQ.front(); jobQ.pop();
    cur_time = first.arrived+first.needed;
    cur_class_num = first.classnum;
    vector<job> arrived_jobs;
    vector<int> done;
    done.push_back(cur_class_num);
    while(!(jobQ.empty() && arrived_jobs.empty()))
    {
        while(!jobQ.empty() && cur_time >= jobQ.front().arrived)
        {
            arrived_jobs.push_back(jobQ.front());
            jobQ.pop();
        }
        // 이전과 같은 분류 작업 있는 경우
        int i;
        for(i=0; i<arrived_jobs.size(); ++i)
        {
            if(arrived_jobs[i].classnum == cur_class_num)
            {
                break;
            }
        }
        if(i != arrived_jobs.size())
        {   // 이 작업 처리
            cur_time = max(cur_time + arrived_jobs[i].needed, arrived_jobs[i].arrived+arrived_jobs[i].needed);
            cur_class_num = arrived_jobs[i].classnum;
            done.push_back(arrived_jobs[i].classnum);
            // arrived_job에서 삭제
            arrived_jobs.erase(arrived_jobs.begin()+i);
            continue;
        }
        if(arrived_jobs.empty())
        {   // 먼저 온 작업 처리
            if(jobQ.empty())
                break;
            job cur = jobQ.front(); jobQ.pop();
            cur_time = cur.arrived + cur.needed;
            cur_class_num = cur.classnum;
            done.push_back(cur.classnum);
            continue;
        }
        // 분류 번호와 중요도를 계산
        map<int, int> classnum_importanceMap;
        for(i=0; i<arrived_jobs.size(); ++i)
        {
            int cn = arrived_jobs[i].classnum;
            int imp = arrived_jobs[i].importance;
            classnum_importanceMap[cn] += imp;
        }
        vector<pair<int, int>> cn_impVect;
        for(auto e: classnum_importanceMap)
            cn_impVect.push_back(e);
        sort(cn_impVect.begin(), cn_impVect.end(), [](auto back, auto front){
            if(back.second == front.second)
            {
                return back.first < front.first;
            }
            else
                return back.second > front.second;
        });
        int selected_cn = cn_impVect[0].first;
        // 중요도 높은 작업중 먼저온 것 시작
        for(i=0; i<arrived_jobs.size(); ++i)
        {
            if(arrived_jobs[i].classnum == selected_cn)
            {
                break;
            }
        }
        // 이 작업 처리
        cur_time = max(cur_time + arrived_jobs[i].needed, arrived_jobs[i].arrived+arrived_jobs[i].needed);
        cur_class_num = arrived_jobs[i].classnum;
        done.push_back(arrived_jobs[i].classnum);
        // arrived_job에서 삭제
        arrived_jobs.erase(arrived_jobs.begin()+i);
    }
    answer.push_back(done[0]);
    int last = done[0];
    for(int i=1; i<done.size(); ++i)
    {
        if(last == done[i])
        {
            continue;
        }
        else
        {
            answer.push_back(done[i]);
            last = done[i];
        }
    }

    return answer;
}

int main()
{
    vector<vector<int>> jobs = {{0, 5, 1, 1}, {2, 4, 3, 3}, {3, 4, 4, 5}, {5, 2, 3, 2}};

    solution(jobs);

    return 0;
}