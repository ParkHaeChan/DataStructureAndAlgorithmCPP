/*
배달
https://programmers.co.kr/learn/courses/30/lessons/12978

N개의 마을로 이루어진 나라가 있습니다. 이 나라의 각 마을에는 1부터 N까지의 번호가 각각 하나씩 부여되어 있습니다. 
각 마을은 양방향으로 통행할 수 있는 도로로 연결되어 있는데, 서로 다른 마을 간에 이동할 때는 이 도로를 지나야 합니다. 
도로를 지날 때 걸리는 시간은 도로별로 다릅니다. 현재 1번 마을에 있는 음식점에서 각 마을로 음식 배달을 하려고 합니다. 
각 마을로부터 음식 주문을 받으려고 하는데, N개의 마을 중에서 K 시간 이하로 배달이 가능한 마을에서만 주문을 받으려고 합니다. 

?:
마을의 개수 N, 각 마을을 연결하는 도로의 정보 road, 음식 배달이 가능한 시간 K가 매개변수로 주어질 때, 
음식 주문을 받을 수 있는 마을의 개수를 return 하도록 solution 함수를 완성해주세요.

!!!:
마을의 개수 N은 1 이상 50 이하의 자연수입니다.
road의 길이(도로 정보의 개수)는 1 이상 2,000 이하입니다.
road의 각 원소는 마을을 연결하고 있는 각 도로의 정보를 나타냅니다.
road는 길이가 3인 배열이며, 순서대로 (a, b, c)를 나타냅니다.
a, b(1 ≤ a, b ≤ N, a != b)는 도로가 연결하는 두 마을의 번호이며, c(1 ≤ c ≤ 10,000, c는 자연수)는 도로를 지나는데 걸리는 시간입니다.
두 마을 a, b를 연결하는 도로는 여러 개가 있을 수 있습니다.
한 도로의 정보가 여러 번 중복해서 주어지지 않습니다.
K는 음식 배달이 가능한 시간을 나타내며, 1 이상 500,000 이하입니다.
임의의 두 마을간에 항상 이동 가능한 경로가 존재합니다.
1번 마을에 있는 음식점이 K 이하의 시간에 배달이 가능한 마을의 개수를 return 하면 됩니다.

시도1)
최단 시간 경로수를 찾으므로 방법은 여러가지가 있다.
N이 작고 시간이므로 음수 가중치도 존재하지 않는다.
무난하게 SingleSourceShortestPath를 구하는 다익스트라를 써본다.
0점... 다익스타라 구성에 실수가 있었다.
visited 재방문 안막았고, PQ에 넣을 때 업데이트 된 가중치가 들어가야한다.

시도2)
통과
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node
{
    int id;
    int weight;

    bool operator<(const node& back) const
    {   // lhs: back rhs: front     minheap
        return this->weight > back.weight;
    }
};

vector<vector<node>> Graph;

vector<int> dijkstra(int start, int N)
{
    const int INF = 987654321;
    vector<int> dist(N+1, INF);
    vector<bool> visited(N+1, false);
    priority_queue<node> PQ;
    dist[start] = 0;
    PQ.push({start, dist[start]});

    while(!PQ.empty())
    {
        auto cur = PQ.top(); PQ.pop();
        if(visited[cur.id])
            continue;
        visited[cur.id] = true;

        int curdist = cur.weight;
        for(auto e: Graph[cur.id])
        {
            if(dist[e.id] > e.weight + curdist)
            {
                dist[e.id] = e.weight + curdist;
                PQ.push({e.id, dist[e.id]});
            }
        }
    }

    return dist;
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;

    // road로 그래프 구성(인접 리스트)
    Graph = vector<vector<node>>(N+1);
    for(auto e: road)
    {
        int a = e[0];
        int b = e[1];
        int c = e[2];
        // 양방향
        Graph[a].push_back({b,c});
        Graph[b].push_back({a,c});
    }

    // 1번 마을에서 시작
    vector<int> dist = dijkstra(1, N);
    
    for(int i=1; i<=N; ++i)
    {
        if(dist[i] <= K)
            answer++;
    }

    return answer;
}

int main()
{
    int N = 5;
    vector<vector<int>> road = {{1,2,1},{2,3,3},{5,2,2},{1,4,2},{5,3,1},{5,4,2}};
    int K = 3;

    solution(N, road, K);

    return 0;
}