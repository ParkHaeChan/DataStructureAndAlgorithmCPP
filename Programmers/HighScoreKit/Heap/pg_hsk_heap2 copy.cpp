/*
디스크 컨트롤러
https://programmers.co.kr/learn/courses/30/lessons/42627

pair<int, int> heap 사용시 거꾸로 넣는 다는 점이 거슬릴수 있다
이때는 struct형으로 만들고 비교함수를 넣어준다.
이때는 연산자 오버로딩을 사용하는데 좀 햇갈릴 수 있으므로 주의한다.
sort()에 사용하는 비교함수와 방향이 반대라 생각하면 된다...
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct job
{
    int arrived;
    int require;
    // operator< 사용하려면 생성자도 꼭 필요하다...
    job() : arrived(-1), require(-1)
    {}
    job(int arr, int req) : arrived(arr), require(req)
    {}

    // operator< 를 정의해 준다
    bool operator<(const job a) const
    {   // 작은 것이 먼저 나오게 하려면 >를 써준다.
        return this->require > a.require;
    }
};

// 방법2: comp 구조체를 만든다.
struct comp
{   // 이때는 operator()()를 사용한다
    bool operator()(job a, job b)
    {   // 작은게 먼저 나오도록 하려면 >를 써준다.
        return a.require > b.require;
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;

    vector<job> jobvect(jobs.size());
    for(int i=0; i<jobs.size(); ++i)
    {
        jobvect[i] = {jobs[i][0], jobs[i][1]};
    }
    // job 구조체의 operator< 를 기준으로 정렬하면 안되므로 람다 비교함수를 써준다
    sort(jobvect.begin(), jobvect.end(), [](auto a, auto b){
        if(a.arrived == b.arrived)
            return a.require < b.require;
        else
            return a.arrived < b.arrived;
    });
    priority_queue<job, vector<job>, comp> jobPQ;   // minheap(job 구조체의 operator< 기준으로 나온다)
    jobPQ.push(jobvect[0]);

    int curtime=0, endtime=0, sum = 0, cnt = 1;
    
    while(!jobPQ.empty())
    {
        job cur = jobPQ.top(); jobPQ.pop();

        if(curtime < cur.arrived)
            curtime = cur.arrived;
        endtime = curtime + cur.require;
        sum += (endtime - cur.arrived);
        curtime = endtime;
        for(; cnt<jobs.size(); ++cnt)
        {
            job temp = jobvect[cnt];
            if(curtime >= temp.arrived)
            {
                jobPQ.push(temp);
                continue;
            }
            else
            {   // 시도2) 힙이 비면 다음값 하나 넣기
                if(jobPQ.empty())
                {
                    jobPQ.push(temp);
                    cnt++;  // 중간에 break하면 안늘어 나므로 주의
                }
                break;
            }  
        }
    }
    answer = sum / jobs.size();

    return answer;
}

int main()
{
    vector<vector<int>> jobs = {{0, 3}, {1, 9}, {2, 6}, {0, 1}};

    cout << solution(jobs) << endl;

    return 0;
}