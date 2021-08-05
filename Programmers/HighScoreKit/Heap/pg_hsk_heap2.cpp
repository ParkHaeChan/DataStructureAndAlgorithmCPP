/*
디스크 컨트롤러
https://programmers.co.kr/learn/courses/30/lessons/42627

?:
각 작업에 대해 [작업이 요청되는 시점, 작업의 소요시간]을 담은 2차원 배열 jobs가 매개변수로 주어질 때, 
작업의 요청부터 종료까지 걸린 시간의 평균을 가장 줄이는 방법으로 처리하면
평균이 얼마가 되는지 return 하도록 solution 함수를 작성해주세요. (단, 소수점 이하의 수는 버립니다)

!!!:
jobs의 길이는 1 이상 500 이하입니다.
jobs의 각 행은 하나의 작업에 대한 [작업이 요청되는 시점, 작업의 소요시간] 입니다.
각 작업에 대해 작업이 요청되는 시간은 0 이상 1,000 이하입니다.
각 작업에 대해 작업의 소요시간은 1 이상 1,000 이하입니다.
하드디스크가 작업을 수행하고 있지 않을 때에는 먼저 요청이 들어온 작업부터 처리합니다.

문제에서 작업이 소요시간이 짧은 순으로 작업을 진행하면 요청부터 종료까지 걸린 평균이 줄어듦을 알 수 있다.
즉, heap에서 작업 소요시간 기준으로 적은게 먼저 나오게 하면된다.
단, 이때 주의할 점은 모든 작업을 heap에 넣고 시작하는게 아니라
현재 요청이 온 작업에 한해서만 heap에 넣고 그 중 최단 작업 소요 시간을 사용하는 식으로 구현해야한다.

시작을 jobs를 정렬한 다음 맨 처음 job만 적용후 시작하려 했는데 코드가 지저분한것 같아서
정렬 후 처음 값 하나만 힙에 넣고 시작하는 식으로 변경하였다.

시도1) 처음 작업 수행후 다음 작업 요청시간이 현재 시간보다 큰 경우
힙이 비었을 때 접근하는 문제가 있어서 수정하였다.
시도2) 안에서 cnt++를 해줘야 다음에 같은 값 접근하지 않는다...
그리고 cnt++을 if(empty())문 안에 써줘야 한다. 실수로 밖에 뒀다가 실패함.
시도3) 통과...
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> jobs) {
    int answer = 0;

    using job = pair<int, int>;
    vector<job> jobvect(jobs.size());
    for(int i=0; i<jobs.size(); ++i)
    {
        jobvect[i] = {jobs[i][0], jobs[i][1]};
    }
    sort(jobvect.begin(), jobvect.end());   // 요청 시간순, 그 다음은 수행시간 적은 순으로 정렬됨
    priority_queue<job, vector<job>, greater<job>> jobPQ;   // minheap(수행 시간 적은게 먼저오려면 뒤집어서 넣어야한다)
    jobPQ.push({jobvect[0].second, jobvect[0].first});   // 순서 주의! 수행시간 순으로 뽑혀야한다.

    int curtime=0, endtime=0, sum = 0, cnt = 1;
    
    while(!jobPQ.empty())
    {
        job cur = jobPQ.top(); jobPQ.pop();

        if(curtime < cur.second)
            curtime = cur.second;
        endtime = curtime + cur.first;
        sum += (endtime - cur.second);
        curtime = endtime;
        for(; cnt<jobs.size(); ++cnt)
        {
            job temp = jobvect[cnt];
            if(curtime >= temp.first)
            {
                jobPQ.push({temp.second, temp.first});
                continue;
            }
            else
            {   // 시도2) 힙이 비면 다음값 하나 넣기
                if(jobPQ.empty())
                {
                    jobPQ.push({temp.second, temp.first});
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