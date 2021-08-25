/*
다익스트라 최단 경로 알고리즘

1) 시작점 설정하고 dist 배열 초기화(INF)
2) dist[start] = 0으로 설정
3) 현재 방문하지 않은 노드 중에서 최단 거리가 가장 짧은 노드를 선택
4) 해당 노드를 거칠때 최단 거리 갱신되면 dist 테이블 갱신
5) 3,4를 반복

3,4) 수행시 PQ가 필요함. 가중치 기준으로 작동하도록 node의 operator< 연산자를 오버로딩한다
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
    {// lhs < this 인 상황 (lhs: left hand side로 비교 수직의 왼쪽항을 의미함, 반대쪽인 this는 당연히 rhs)
        // 여기서는 left, right 중 weight가 작은 쪽이 먼저 힙에서 나오게 하고 싶다 (minHeap)

        // 이때 주의해야 할 점은 lhs라고해서 container 내부에서도 비교 대상의 왼쪽에 존재하지는 않는다는 것이다.
        // sort의 비교함수에서 인자 a, b가 실제로는 back, front 순인것을 생각하면 여기서도 lhs가 back에 위치한다고 볼 수 있다.
        
        // lhs를 back으로 보고 this(rhs)를 front로 보고,
        // 조건식이 true일 때 swap이 발생한다는 점(국룰)을 숙지하면, 다음과 같은 조건식으로 minHeap으로 작동하도록 구성할 수 있다.

        // return front > back; --> return this.weight > lhs.weight;
        // 해설: 이 조건식이 true이면 뒤에 값이 더 작은 값이므로 먼저 나오게 하려면 앞으로 이동해야되므로 front와 swap이 발생해야한다.

        // operator< 와 같이 <로 일치시키고 싶다면, return back < front로 쓴다.
        // 주의: operator>는 PQ의 비교 조건식으로 작동하지 않는다... 굳이 오버로딩할 필요 없다

        cout << "this: (front)" << this->weight << " # " << "lhs: (back)" << lhs.weight;
        if(lhs.weight < this->weight)
            cout << " Swap 발생"<<endl;
        else
            cout << endl;
        return lhs.weight < this->weight;
    }
};

vector<int> solution(int n, int start, int target, vector<vector<int>> paths)
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
            break;  // 목적지 도달
        
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
    return dist;
}

int main()
{
    int n = 5;  // 노드 수
    int start = 1;
    int target = 4;

    // {a, b, c}: a-b가 (양방향)연결되어 있고 가중치(거리)는 c
    vector<vector<int>> paths = {{1,5,1},{1,2,4},{1,3,3},{2,5,2},{2,4,2},{3,4,2}};
    vector<int> shortest_distances = solution(n, start, target, paths);

    return 0;
}