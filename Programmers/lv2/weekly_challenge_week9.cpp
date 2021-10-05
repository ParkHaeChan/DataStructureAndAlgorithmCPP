/*
전력망을 둘로 나누기
https://programmers.co.kr/learn/courses/30/lessons/86971

n개의 송전탑이 전선을 통해 하나의 트리 형태로 연결되어 있습니다. 
당신은 이 전선들 중 하나를 끊어서 현재의 전력망 네트워크를 2개로 분할하려고 합니다. 
이때, 두 전력망이 갖게 되는 송전탑의 개수를 최대한 비슷하게 맞추고자 합니다.

?:
송전탑의 개수 n, 그리고 전선 정보 wires가 매개변수로 주어집니다. 
전선들 중 하나를 끊어서 송전탑 개수가 가능한 비슷하도록 두 전력망으로 나누었을 때,
두 전력망이 가지고 있는 송전탑 개수의 차이(절대값)를 return 하도록 solution 함수를 완성해주세요.

!!!:
n은 2 이상 100 이하인 자연수입니다.
wires는 길이가 n-1인 정수형 2차원 배열입니다.
wires의 각 원소는 [v1, v2] 2개의 자연수로 이루어져 있으며, 이는 전력망의 v1번 송전탑과 v2번 송전탑이 전선으로 연결되어 있다는 것을 의미합니다.
1 ≤ v1 < v2 ≤ n 입니다.
전력망 네트워크가 하나의 트리 형태가 아닌 경우는 입력으로 주어지지 않습니다.

시도1)
트리의 형태에 대한 말이 없고(이진 트리인지 어떤지 등...) 
입력이 2~100으로 작은 편이다. 일단 완전탐색을 시도해본다.

트리: 그냥 2차원 배열로 그래프로 구현
트리의 노드 수 세기: DFS방식으로 연결된 노드 수를 센다.

*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int DFS(int start, vector<vector<int>>& GRAPH, vector<bool>& visited)
{
    int N = GRAPH.size()-1;
    int ret = 0;
    if(visited[start])
        return 0;
    visited[start] = true;
    ret += 1;

    for(int next = 1; next <= N; ++next)
    {
        if(GRAPH[start][next] == 1 && !visited[next])
        {
            ret += DFS(next, GRAPH, visited);
        }
    }
    return ret;
}

int solution(int n, vector<vector<int>> wires) {
    const int INF = 987654321;
    int answer = INF;

    vector<vector<int>> GRAPH(n+1, vector<int>(n+1));
    for(auto& e: wires)
    {
        GRAPH[e[0]][e[1]] = 1;
        GRAPH[e[1]][e[0]] = 1;
    }

    // 하나만 끊어보고 두 영역 차이를 계산
    for(auto& e: wires)
    {   // 끊기
        GRAPH[e[0]][e[1]] = 0;
        GRAPH[e[1]][e[0]] = 0;

        // 영역 개수 세기
        vector<bool> visited(n+1, false);
        // 시작 노드
        int val = DFS(1, GRAPH, visited);
        for(int i=1; i<=n; ++i)
        {
            if(visited[i])
                continue;
            int another = DFS(i, GRAPH, visited);
            answer = min(answer, abs(val-another));
            break;
        }
        // 복구
        GRAPH[e[0]][e[1]] = 1;
        GRAPH[e[1]][e[0]] = 1;
    }

    return answer;
}

int main()
{
    int n = 9;
    vector<vector<int>> wires = {{1,3},{2,3},{3,4},{4,5},{4,6},{4,7},{7,8},{7,9}};

    solution(n, wires);

    return 0;
}