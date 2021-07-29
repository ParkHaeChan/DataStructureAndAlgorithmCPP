// 문제: https://programmers.co.kr/learn/courses/30/lessons/42884

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

struct Point
{
    int id; // 구간 식별자
    int position;
    bool start;
};

int solution(vector<vector<int>> routes) {
    int answer = 0;
    int N = routes.size();
    
    vector<Point> positions;
    // 시작점과 끝점이 겹치는 구간이 있어서 이때는 방문처리해서 중복처리 방지
    vector<bool> visited(N, false);
    for(int i=0; i<N; ++i)
    {
        positions.push_back({i, routes[i][0], true});
        positions.push_back({i, routes[i][1], false});
    }

    // 위치 기준으로 정렬
    sort(positions.begin(), positions.end(), [](auto& a, auto&b){ return a.position < b.position; });
    
    queue<int> IDQ;
    for(auto e: positions)
    {
        if(!e.start && !visited[e.id])
        {
            answer++;   // 카메라 설치
            while(!IDQ.empty())
            {
                int id = IDQ.front(); IDQ.pop();
                visited[id] = true; // 카메라에 걸리는 구간들 표시
            }
        }
        else
        {   //시작점이면 이 구간을 큐에 저장
            IDQ.push(e.id);
        }
    }
    
    return answer;
}

int main()
{
    vector<vector<int>> routes = {{-20,15}, {-14,-5}, {-18,-13}, {-5,-3}};
    std::cout << solution(routes) << endl;

    return 0;
}