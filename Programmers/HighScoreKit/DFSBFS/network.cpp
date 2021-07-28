/*
컴퓨터의 개수 n은 1 이상 200 이하인 자연수입니다.
각 컴퓨터는 0부터 n-1인 정수로 표현합니다.
i번 컴퓨터와 j번 컴퓨터가 연결되어 있으면 computers[i][j]를 1로 표현합니다.
computer[i][i]는 항상 1입니다.

문제: https://programmers.co.kr/learn/courses/30/lessons/43162
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int N;
vector<bool> visited;

void DFS(vector<vector<int>>& coms, int start)
{
    if(visited[start])
        return;

    visited[start] = true;

    for(int i=0; i<N; ++i)
    {    
        if(i == start || visited[i])
            continue;

        if(coms[start][i] == 1)
        {
            DFS(coms, i);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;

    // 각 정점에서 DFS로 갈 수 있는 모든 정점을 가본다
    // 방문 표시를 한다.
    // DFS가 종료 될 때 마다 네트워크 수를 센다.
    N = computers.size();
    visited = vector<bool>(N, false);
    for(int i=0; i<N; ++i)
    {
        if(!visited[i])
        {
            DFS(computers, i);
            answer++;
        }            
    }

    return answer;
}

int main()
{
    vector<vector<int>> computers = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    //vector<vector<int>> computers = {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}};
    int n = 3;

    cout << solution(n, computers) << endl;

    return 0;
}