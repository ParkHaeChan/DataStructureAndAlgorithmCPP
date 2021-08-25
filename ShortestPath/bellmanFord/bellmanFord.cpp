/*
벨만-포드 알고리즘

용도: 음수 가중치가 있는 그래프에서 최단 경로(거리) 구하기
(음수 가중치 사이클이 있는 경우도 판별가능: N-1 --> 추가로 1회 더 돌려서 더 짧은 경로가 나오면 음수 가중치 사이클 존재)

그래프의 모든 EDGE에 대해 다익스트라의 그리디 선택 방법을 (N-1)번 반복하여 점진적으로 최단 거리를 찾는다.

입력: ( 그래프(Edge List), 정점 개수: N, 출발 정점 번호: start )
출력: start-> 모든 정점까지의 최단 경로(거리)

구현:
1) distance 배열 + 시작 위치 초기화
2) N-1회 반복: 모든 거리가 알려진 정점(distance[cur] != UNKOWN)에 relaxing(distance 테이블 갱신) 시도

다익스트라와의 차이점:
1) 음수 가중치가 있어도 작동한다.
2) 다익스트라는 목적지를 찾으면 중간에 종료해도 된다. 하지만 벨만 포드는 N-1회 까지 돌아야 정확하게 나온다.
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
    // 사이클이 있으면 거리가 갱신된다는 점을 이용
    for(int cur = 1; cur<=N; ++cur)
    {
        if(distances[cur] == UNKOWN)
            continue;

        int cur_weight = distances[cur];
        for(auto e: Graph[cur])
        {
            int next_weight = e.weight;
            // 거리가 갱신되면 사이클 존재
            if(distances[e.next] > cur_weight + next_weight)
            {
                cout << "Negative Cycle exists!" << endl;
                break;
            }
        }
    }

    return {distances, parent};
}

int main()
{
    int n = 6;  // 노드 수
    int start = 1;
    int target = 4;

    // {a, b, c}: a-b가 (양방향)연결되어 있고 가중치(거리)는 c
    // 양방향 연결이므로 가중치 음수 존재하면 바로 싸이클 생김
    vector<vector<int>> paths = {{1,5,1},{1,2,4},{1,3,3},{2,5,2},{2,4,2},{3,4,2},{1,6,-1}};
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

    // 음수 사이클 존재할 때는 정상적인 값을 기대하긴 힘들다
    //cout << "target min distance: " << distances[target] << endl;
    //print_path(parent, target);

    return 0;
}