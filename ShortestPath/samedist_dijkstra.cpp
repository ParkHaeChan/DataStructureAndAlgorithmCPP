/*
다익스트라 최단 경로 알고리즘
동일한 최단 거리로 가는 모든 서로 다른 경로를 찾도록 변경할 경우

1) 일반적인 다익스트라 알고리즘을 1회 수행하여 최단 거리를 찾는다.

2) 변형된 다익스트라 알고리즘을 수행하여 최단 거리를 찾을 때마다 경로를 저장한다.
*/

#include <vector>
#include <iostream>
#include <queue>    // priority_queue
#include <algorithm>    // reverse

using namespace std;

struct node
{
    int id; // 노드 번호
    int weight; // edge weight
    bool operator< (const node& lhs) const
    {
        return lhs.weight < this->weight;   // back < front : 뒤에가 앞에 보다 작으면 swap
    }
};

// 경로 저장 및 출력
vector<int> save_path(vector<int>& parent, int start, int target)
{
    // 실제 경로 출력: parent[target]에서 start까지 거슬러 올라간 후 뒤집어서 출력한다
    vector<int> path;
    while(target != start)
    {
        path.push_back(target);
        target = parent[target];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    for(int i=0; i<path.size(); ++i)
    {
        if(i == path.size()-1)
            cout << path[i] << endl;
        else
            cout << path[i] << " : ";
    }
    return path;
}

vector<int> normal_dijkstra(int n, int start, int target, vector<vector<node>>& Graph)
{
    const int INF = 98754321;
    vector<int> dist(n+1, INF);   // 1) dist배열 초기화(INF)
    dist[start] = 0;            // 2) 시작점 최단 거리는 0이다
    priority_queue<node> PQ;
    PQ.push({start, dist[start]});
    vector<bool> visited(n+1, false);   // 방문여부 저장
    vector<int> parent(n+1, INF);       // 실제 경로 저장
    parent[start] = start;

    while(!PQ.empty())
    {
        auto cur = PQ.top(); PQ.pop();
        int curdist = cur.weight;
        if(visited[cur.id])
            continue;
        if(cur.id == target)
            break;
        
        visited[cur.id] = true; // 이번에 확정되는 최단거리 방문표시
        
        // 현재 노드를 거쳐서 가는 경우를 모두 시도해서 dist 테이블 갱신
        for(auto next : Graph[cur.id])
        {   
            // 거쳐가는 경우가 기존 경우보다 짧으면 갱신하고 PQ에 삽입
            if(dist[next.id] > cur.weight + next.weight)
            {
                dist[next.id] = cur.weight + next.weight;
                parent[next.id] = cur.id;
                PQ.push({next.id, dist[next.id]});
            }
        }
    }
    return dist;
}

// 최단 경로로 가능한 모든 경로를 찾는 다익스트라 (최단 거리를 미리 알고 있어야 한다: MIN_DIST 필요)
vector<vector<int>> allpath_dijkstra(int n, int start, int target, vector<vector<node>>& Graph, int MIN_DIST)
{
    const int INF = 98754321;
    vector<int> dist(n+1, INF);   // 1) dist배열 초기화(INF)
    dist[start] = 0;            // 2) 시작점 최단 거리는 0이다
    priority_queue<node> PQ;
    PQ.push({start, dist[start]});
    vector<bool> visited(n+1, false);   // 방문여부 저장
    vector<int> parent(n+1, INF);       // 실제 경로 저장
    parent[start] = start;

    // 모든 경로를 찾아서 반환한다
    vector<vector<int>> allpath;

    while(!PQ.empty())
    {
        auto cur = PQ.top(); PQ.pop();
        int curdist = cur.weight;
        if(visited[cur.id])
            continue;
        if(cur.id == target)
            break;
        
        visited[cur.id] = true; // 이번에 확정되는 최단거리 방문표시
        
        // 현재 노드를 거쳐서 가는 경우를 모두 시도해서 dist 테이블 갱신
        for(auto next : Graph[cur.id])
        {   
            // 거쳐가는 경우가 기존 경우보다 짧으면 갱신하고 PQ에 삽입
            if(dist[next.id] > cur.weight + next.weight)
            {
                dist[next.id] = cur.weight + next.weight;
                parent[next.id] = cur.id;
                PQ.push({next.id, dist[next.id]});
            }
            // ####################< 추가된 부분 >############################
            // 모든 최단 경로를 찾을 것이므로 이번 연산으로 최단거리가 나오는 모든 경우에 경로를 저장한다
            if((next.id == target) && (cur.weight + next.weight == MIN_DIST))
            {   // 다음이 목적지이면서 최단거리 값인 경우 경로를 저장
                parent[next.id] = cur.id;
                allpath.push_back(save_path(parent, start, target));
            }
        }
    }

    return allpath;
}

void solution(int n, int start, int target, vector<vector<int>> paths)
{
    // 그래프 구성: paths는 {a,b,c}이고, 각각 a-b가 양방향 연결되어 있고, 가중치가 c이다
    // 인접리스트로 초기화한다
    vector<vector<node>> Graph(n+1); // 0번은 사용하지 않음
    for(auto e: paths)
    {
        int a = e[0];
        int b = e[1];
        int c = e[2];
        // 양방향 연결
        Graph[a].push_back({b,c});  // struct node형
        Graph[b].push_back({a,c});
    }

    vector<int> dist = normal_dijkstra(n, start, target, Graph);
    int min_dist = dist[target];
    vector<vector<int>> allpath = allpath_dijkstra(n, start, target, Graph, min_dist);
}

int main()
{
    int n = 5;  // 노드 수
    int start = 1;
    int target = 4;

    // {a, b, c, d}: a-b가 (양방향)연결되어 있고 가중치(거리)는 c이고, 보너스 점수 d(추가 데이터)
    vector<vector<int>> paths = {{1,5,1},{1,2,4},{1,3,3},{2,5,2},{2,4,2},{3,4,2}};
    solution(n, start, target, paths);

    return 0;
}