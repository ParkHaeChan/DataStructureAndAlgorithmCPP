/*
다익스트라 최단 경로 알고리즘 + 응용(최단 거리이면서 보너스 포인트는 최대로 하는 경로 찾기)

-용도: 단일시작점에서 다른 모든 노드까지의 최단 경로를 저장

-입력: 시작 위치 노드
-출력: 모든 위치까지의 최소 거리가 저장된 배열(dist) 또는 목적지까지의 거리값(dist[Target])
(문제가 단일 목적지까지의 거리라면 목적지에 도달하면 바로 종료하도록 구현)

-한계: 음수 가중치가 있는 경우 사용 불가능

-응용:
최단 거리를 출력하되, 여러 경로가 최단 거리로 가능한 경우, 최대 보너스 포인트를 챙기도록 구현

-구현:
1) 시작 노드 설정
2) 최단 거리 테이블(배열)을 초기화한다
3) 방문하지 않은 노드 중에서 최단 거리가 가장 짧은 노드를 선택한다
4) 해당 노드를 거쳐 다른 노드로 가는 비용을 계산하여 최단 거리 테이블을 갱신한다
    응용1) 최단 거리 테이블이 갱신되면 보너스 테이블도 갱신한다 (포인트 보단 최단 거리로 가는게 우선이다)
    응용2) 최단 거리가 같은 다른 경로가 발견되면 보너스가 더 커지는 경우만 보너스 테이블을 갱신한다
5) 위 과정에서 3,4를 반복한다
*/

#include <vector>
#include <queue>    // priority_queue
#include <iostream>

using namespace std;

int N, Target;  // 노드 수,  목적지 노드 번호

struct GRAPH_NODE
{
    int id;
    int weight;
    int bp; // bonus point
};
// GRAPH_NODE와 굳이 분리한 이유는
// PQ에 넣을 node로 사용할 때는 node 내부에 operator< (const node& lhs) 를 정의하여야한다
// 이는 PQ에 넣는 용도 외에 sort로 정렬을 수행하거나 할 경우 다르게 작동하여 문제가 생길 수 있다.
// 여기서는 그런 위험은 없지만 안전한 습관을 위해 분리하여 작성하였다
struct PQ_NODE
{
    int id;
    int weight;
    int bp;
 
    inline bool operator< (const PQ_NODE& left) const
    {// 거리가 짧은 순으로 먼저 시도하고
        // 거리가 같은 경우는 보너스 포인트 높은 순으로
        // if(this->weight == left.weight)
        // {
        //     return this->bp > left.bp;  // bp 내림차순(maxHeap)
        // }
        // else : 안써도 상관없었음... 어차피 거리 갱신되면 보너스 점수도 새로운 경로로 같이 갱신되야함
        return this->weight < left.weight;  // weight 오름차순(minHeap)
    }
};

using gnode = GRAPH_NODE;
using pqnode = PQ_NODE;

vector<vector<gnode>> GRAPH;

vector<int> dijkstra(int start)
{   // 1) 시작 위치 설정 (함수 인자로 받는다)
    const int INF = 987654321;
    vector<int> dist(N+1, INF);  // 2) 최단 거리 테이블 초기화
    vector<int> bonus(N+1, 0);   // bp 테이블 초기화
    vector<bool> visited(N+1, false);
    dist[start] = 0;         // 시작 위치는 초기 거리 0 이다   

    priority_queue<PQ_NODE> PQ;
    PQ.push({start, -dist[start], bonus[start]});   // minHeap으로 작동시키기 위해 weight에 -를 붙이는 것 주의

    while(!PQ.empty())
    {   // 3) 방문하지 않은 노드 중에서 최단거리 가장 짧은 노드 선택
        auto cur = PQ.top(); PQ.pop();
        if(visited[cur.id])
            continue;
        if(cur.id == Target)
            break;
        visited[cur.id] = true;

        int curdist = -cur.weight;

        // 4) 해당 노드를 거쳐 다른 노드로 가는 비용을 계산하여 최단 거리 테이블을 갱신
        for(gnode next: GRAPH[cur.id])
        {   // 최단 거리 갱신되는 경우
            if(dist[next.id] > curdist + next.weight)
            {   
                bonus[next.id] = cur.bp + next.bp;
                dist[next.id] = curdist + next.weight;
                PQ.push({next.id, -dist[next.id], bonus[next.id]});
            }
            // 최단 거리가 같은 다른 경로의 경우
            if(dist[next.id] == curdist + next.weight)
            {   // bonus가 커질때만 갱신한다
                if(bonus[next.id] < cur.bp + next.bp)
                {
                    bonus[next.id] = cur.bp + next.bp;
                    // 갱신된 보너스에 누적하도록 PQ에 삽입한다
                    PQ.push({next.id, -dist[next.id], bonus[next.id]});
                }
            }
        }
    }
    // 최단 거리와 최대 보너스를 return
    return {dist[Target], bonus[Target]};
}

vector<int> solution(int n, int k, vector<vector<int>> paths) {
    vector<int> answer;
    vector<gnode> temp;
    GRAPH = vector<vector<gnode>>(n+1, temp);
    // 인접리스트 그래프
    for(auto e: paths)
    {
        int s = e[0];
        int t = e[1];
        int weight = e[2];
        int bp = e[3];
        // 양방향
        GRAPH[s].push_back({t, weight, bp});
        GRAPH[t].push_back({s, weight, bp});
    }
    N = n;
    Target = k;  // target
    // 시작은 1번 위치 부터
    int start = 1;
    answer = dijkstra(start);

    return answer;
}

int main()
{
    int n = 5;
    int k = 4;

    // {a, b, c, d}: a-b가 (양방향)연결되어 있고 가중치(거리)는 c이고, 보너스 점수 d(추가 데이터)
    vector<vector<int>> paths = {{1,5,1,1},{1,2,4,3},{1,3,3,2},{2,5,2,1},{2,4,2,3},{3,4,2,2}};
    solution(n, k, paths);

    return 0;
}