/*
디스크 컨트롤러
https://programmers.co.kr/learn/courses/30/lessons/42627

?:
각 작업에 대해 [작업이 요청되는 시점, 작업의 소요시간]을 담은 2차원 배열 jobs가 매개변수로 주어질 때, 
작업의 요청부터 종료까지 걸린 시간의 평균을 가장 줄이는 방법으로 처리하면 평균이 얼마가 되는지 return 하도록 
solution 함수를 작성해주세요. (단, 소수점 이하의 수는 버립니다)

!!!:
jobs의 길이는 1 이상 500 이하입니다.
jobs의 각 행은 하나의 작업에 대한 [작업이 요청되는 시점, 작업의 소요시간] 입니다.
각 작업에 대해 작업이 요청되는 시간은 0 이상 1,000 이하입니다.
각 작업에 대해 작업의 소요시간은 1 이상 1,000 이하입니다.
하드디스크가 작업을 수행하고 있지 않을 때에는 먼저 요청이 들어온 작업부터 처리합니다.

풀이)
high score kit에서 풀었음
https://github.com/ParkHaeChan/DataStructureAndAlgorithmCPP/blob/main/Programmers/HighScoreKit/Heap/pg_hsk_heap2%20copy.cpp
*/

#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct job
{
    int arrived;
    int time_need;
    bool operator<(const job& lhs)  const   // const 안쓰면 빌드 에러 발생
    {   // lhs : back, rhs: front
        return lhs.time_need < this->time_need; // 짧게 걸리는게 앞으로
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;

    int N = jobs.size();
    vector<job> jobVect;
    priority_queue<job> PQ;
    // 먼저 도착한 요청을 먼저 수행하되, 소요 시간이 더 짧은 것을 먼저 처리하도록 하면 평균이 최소가 되도록 처리할 수 있다.
    for(auto e: jobs)
    {
        jobVect.push_back({e[0], e[1]});
    }
    sort(jobVect.begin(), jobVect.end(), [](job back, job front){
        if(back.arrived == front.arrived)
            return back.time_need < front.time_need;
        else
            return back.arrived < front.arrived;
    });   // 요청 도착 시간 순 정렬 (주의: struct에서 opearator<를 정의하면 그에 맞춰서 정렬한다(즉, 여기서 새로 정렬 함수를 써줘야 제대로 작동함))

    int start_time = 0; // 요청 수행 시작 시간(젤 일찍 도착한 요청)
    int avg_time = 0;
    PQ.push(jobVect[0]);
    int idx = 1;
    while(!PQ.empty())
    {
        // 제일 수행 시간 짧은 job 수행
        auto cur = PQ.top(); PQ.pop();
        int cur_time = max(start_time + cur.time_need, cur.arrived + cur.time_need);    // 중간에 요청 없는 시간이 길 경우 arrived가 더 커질 수 있음
        avg_time += cur_time-cur.arrived;   // 요청 도착 부터 수행 완료까지 걸린 시간
        start_time = cur_time;  // 시작 시간 갱신
        for( ; idx<jobVect.size(); ++idx)
        {   // 요청 수행 이내에 도착한 job PQ에 추가(PQ는 수행 시간 짧은 순으로 반환)
            if(jobVect[idx].arrived <= start_time)
            {
                PQ.push(jobVect[idx]);
            }
            else
            {   // 빼먹지 말것...
                if(PQ.empty())
                    PQ.push(jobVect[idx]);
                else
                    break;
            }
        }
    }

    answer = avg_time / N; // 소수점 이하는 버림

    return answer;
}

int main()
{
    vector<vector<int>> jobs = {{0, 3}, {4, 4}, {9, 2}};
    //vector<vector<int>> jobs = {{0, 3}, {1, 9}, {2, 6}};

    solution(jobs);

    return 0;
}