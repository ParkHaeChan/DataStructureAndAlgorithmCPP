/*
벨만-포드 알고리즘

음수 가중치 사이클 있는 경우:
1회 더 추가로 시도해 보고 최단 경로가 갱신되는지 확인
*/

#include <vector>
#include <iostream>
#include <climits>  // INT_MAX
#include <algorithm> // reverse

const int UNKOWN = INT_MAX;

using namespace std;

struct node
{
    int next;
    int weight;
};

vector<int> print_path(vector<int>& parent, int end)
{
    vector<int> path;
    path.push_back(end);

    while(parent[end] != end)
    {
        end = parent[end];
        path.push_back(end);
    }

    reverse(path.begin(), path.end());
    cout << "path : ";
    for(int i=0; i<path.size(); ++i)
    {
        if(i == path.size()-1)
            cout << path[i] << endl;
        else
            cout << path[i] << " --> ";
    }
    return path;
}

pair<vector<int>,vector<int>> BellmanFord(vector<vector<node>>& Graph, int N, int start)
{
    // 1) distances + 시작 위치 초기화
    vector<int> distances(N+1, UNKOWN);
    distances[start] = 0;
    vector<int> parent(N+1, 0);
    parent[start] = start;

    // 2) N-1번 다익스트라 그리디 방식 반복
    for(int i=0; i<N-1; ++i)
    {
        // graph의 시작 정점 거리값이 UNKWON이면 skip
        for(int cur = 1; cur<=N; ++cur)
        {
            if(distances[cur] == UNKOWN)
                continue;

            // 인접한 정점의 거리 값이 새로운 경로에 의한 거리 값보다 크면 거리 값을 업데이트 한다
            int cur_weight = distances[cur];
            for(auto e: Graph[cur])
            {
                int next_weight = e.weight;
                if(distances[e.next] > cur_weight + next_weight)
                {
                    distances[e.next] = cur_weight + next_weight;
                    parent[e.next] = cur;
                }
            }
        }
    }

    return {distances, parent};
}

int main()
{
    int n = 5;  // 노드 수
    int start = 1;
    int target = 4;

    // {a, b, c}: a-b가 (양방향)연결되어 있고 가중치(거리)는 c
    vector<vector<int>> paths = {{1,5,1},{1,2,4},{1,3,3},{2,5,2},{2,4,2},{3,4,2}};
    vector<vector<node>> Graph(n+1);
    for(auto e : paths)
    {
        int a = e[0];
        int b = e[1];
        int c = e[2];
        Graph[a].push_back({b,c});
        Graph[b].push_back({a,c});
    }
    
    auto pair_vect = BellmanFord(Graph, n, start);

    vector<int> distances = pair_vect.first;
    vector<int> parent = pair_vect.second;

    cout << "target min distance: " << distances[target] << endl;
    print_path(parent, target);

    return 0;
}