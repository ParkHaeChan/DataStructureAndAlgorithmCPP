#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

/*
가장 멀리 떨어진 노드가 몇개인지를 구하는 문제이다.
입력으로 간선들이 주어지므로 입력을 통해 그래프를 구성하여 직접 그래프 연산을 통해 풀어내야 한다.
최단 경로로 이동했을 때 가장 멀리 떨어진 노드라하면 BFS로 직접 방문하면서 셀 수도 있지만,


제한사항:
노드의 개수 n은 2 이상 20,000 이하입니다.
간선은 양방향이며 총 1개 이상 50,000개 이하의 간선이 있습니다.
vertex 배열 각 행 [a, b]는 a번 노드와 b번 노드 사이에 간선이 있다는 의미입니다.
*/

int solution(int n, vector<vector<int>> edge) {
    
    // 인접리스트 형식으로 그래프 초기화
    vector<vector<int>> Graph(n+1);

    for(int i=0; i<edge.size(); ++i)
    {
        int node1 = edge[i][0];
        int node2 = edge[i][1];

        Graph[node1].push_back(node2);
        Graph[node2].push_back(node1);
    }

    // BFS 수행
    vector<bool> visited(n+1, false);
    vector<bool> selected(n+1, false);
    queue<pair<int, int>> nodeQ;
    priority_queue<int, vector<int>, less<int>> depthPQ;

    int start = 1;
    nodeQ.push({start, 0});

    while(!nodeQ.empty())
    {
        auto cur = nodeQ.front(); nodeQ.pop();
        visited[cur.first] = true;
        depthPQ.push(cur.second);
        for(auto e: Graph[cur.first])
        {
            if(!visited[e] && !selected[e])
            {
                selected[e] = true;
                nodeQ.push({e, cur.second+1});
            }
        }
    }
    int answer = 1;
    int farthest = depthPQ.top(); depthPQ.pop();
    while(!depthPQ.empty())
    {
        int cur = depthPQ.top(); depthPQ.pop();
        if(farthest != cur)
            break;
        else
            answer++;
    }
    
    return answer;
}

int main()
{
    int n = 6;

    vector<vector<int>> edge = {{3, 6}, {4, 3}, {3, 2}, {1, 3}, {1, 2}, {2, 4}, {5, 2}};

    cout << solution(n, edge) << endl;

    return 0;
}