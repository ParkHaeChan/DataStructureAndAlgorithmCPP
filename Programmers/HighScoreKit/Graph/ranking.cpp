/*
문제: https://programmers.co.kr/learn/courses/30/lessons/49191

문제를 읽어보면 위상정렬을 문제임을 예상할 수 있다.
그래프를 구성하면 명백한 순서가 나타나는 그래프로 구성될 것이기 때문이다.
하지만, 위상정렬 자체로는 이 문제를 풀순 없다.
순위가 명확한 사람 수를 출력해야 하는 문제이기 때문에 이를 응용하여 풀어야 한다.

시도1) 만약 반대로 순위가 명확하지 않은 사람을 센다면,
위상정렬을 수행할 때 진입차수가 0이 아닌 노드가 여럿 큐에 삽입될 때가 순위가 불명확한 사람들의 수만큼 생길 것임을 알 수 있다.
위 인사이트를 통해 이번에 큐에 삽입되는 진입차수가 0인 노드가 1개 뿐이면 순위가 명확한 사람 수를 찾은 것으로 생각하고 수를 세면 된다는 것을 알 수 있다.
(오류: 진입차수 0인 노드가 1개 뿐인 경우도 순위가 불명확할 수 있다 -예시 입력에서 [4,3]이 남았을 때 3이 진입차수 0인 유일한 노드인 상태이나 둘 다 순위가 불분명하다)

시도2) 이번에는 순방향과 역방향을 저장하는 두개의 그래프를 만들어서 시도했다.
순방향으로는 위상정렬을 수행하면서 큐에 하나의 값만 삽입될 때가 순위가 확정되는 순간이라 여긴것 까진 위와 같고,
이때 순위가 확정된 노드의 번호와 순위를 따로 큐에 저장해 둔다.
저장해둔 번호와 순위를 꺼내서 역방향 그래프에서 시작점을 큐에서 꺼낸 번호로 하고, 여기서 BFS를 수행하여
순위만큼의 노드를 방문할 수 있는지를 확인한다.

시도3)...역방향 그래프를 사용할 필요가 없다. 위상 정렬을 시도하면 그래프가 훼손된다.
그래서 그냥 원본 그래프를 놔두고 저장해 두었던 위치에서 실제 순위만큼 노드 방문이 가능한지 확인하면 된다.


위상정렬은 BFS와 비슷하게 수행된다.
1) 진입차수가 0인 노드를 모두 찾아 큐에 넣는다.
2) 큐가 빌 때 까지 다음을 반복한다.
 - 큐에서 값을 하나 가져와서 그래프에서 이 노드와 연결된 간선을 제거한다.
 - 진입차수가 0이된 노드를 큐에 추가한다.
 (이때 진입차수가 0이된 노드가 없으면 사이클이 존재하는 그래프라 볼 수 있다)

제한사항:
선수의 수는 1명 이상 100명 이하입니다.
경기 결과는 1개 이상 4,500개 이하입니다.
results 배열 각 행 [A, B]는 A 선수가 B 선수를 이겼다는 의미입니다.
모든 경기 결과에는 모순이 없습니다.
*/
#include <string>
#include <vector>
#include <queue>
#include <algorithm>    // std::find
#include <iostream>

using namespace std;

int BFS(int current, vector<vector<int>>& Graph)
{
    vector<bool> visited(Graph.size(), false);

    queue<int> Q;
    Q.push(current);

    while(!Q.empty())
    {
        int cur = Q.front(); Q.pop();
        visited[cur] = true;

        for(int e : Graph[cur])
        {
            if(!visited[e])
            {
                Q.push(e);
            }
        }
    }
    int ret = 0;
    for(auto e : visited)
        if(e)
            ret++;

    return ret;
}

int solution(int n, vector<vector<int>> results) {
    int answer = 0;

    // 위상 정렬을 수행할 큐와 그래프(인접리스트) 생성
    queue<int> topologyQ;
    vector<vector<int>> Graph(n+1);
    vector<vector<int>> OriginalGraph(n+1);
    for(auto vect : results)
    {
        int Winner = vect[0];
        int Loser = vect[1];

        // 끝 순위 부터 큐에 추가되도록
        Graph[Winner].push_back(Loser);
        // 원본 배열
        OriginalGraph[Winner].push_back(Loser);
    }

    int rank = 0, temp = -1;   // 위상 정렬 처리 횟수, 임시 인덱스 저장
    vector<int> visited(n+1, -1);   // -1: 방문X, 0: 큐에 삽입, 1: 방문O
    queue<pair<int,int>> rankQ;
    // 위상 정렬 초기화: 진입차수가 0인 노드를 찾아 큐에 넣는다
    for(int i=1; i<=n; ++i)
    {
        if(Graph[i].empty())
        {
            visited[i] = 0;
            topologyQ.push(i);
            rank++;
            temp = i;
        }
    }
    // 이번에 진입차수 0인 노드가 하나 뿐이면 순위를 기록한다
    if(topologyQ.size() == 1)
    {   // 역순으로 보므로 n-(rank-1)으로 셈
        rankQ.push({temp, (n+1)-rank});
    }

    // 위상 정렬 수행
    while(!topologyQ.empty())
    {
        int cur = topologyQ.front(); topologyQ.pop();
        visited[cur] = 1;

        // 이 노드와 연결된 간선을 삭제한다
        for(int i = 1; i<=n; ++i)
        {
            if(visited[i] == 1)
                continue;

            auto iter = find(Graph[i].begin(), Graph[i].end(), cur);
            if(iter != Graph[i].end())
                Graph[i].erase(iter);
        }

        // 이번에 진입차수가 0이된 노드를 추가한다
        int cnt = 0;
        for(int i=1; i<=n; ++i)
        {
            if(visited[i] >= 0)
                continue;
            if(Graph[i].empty())
            {
                visited[i] = 0;
                topologyQ.push(i);
                cnt++;
                rank++;
                temp = i;
            }
        }
        // 이번에 진입차수 0인 노드가 하나 뿐이면 순위를 기록한다
        if(cnt == 1)
        {
            rankQ.push({temp, (n+1)-rank});
        }
    }
    // 기록한 위치에서 순위만큼 노드를 방문가능한지 확인한다.
    while(!rankQ.empty())
    {
        auto cur = rankQ.front(); rankQ.pop();
        if(BFS(cur.first, OriginalGraph) == n-cur.second+1)
            answer++;   // 방문가능하면 실제 위치가 맞다
    }

    return answer;
}

int main()
{
    int n = 5;
    vector<vector<int>> results = {{4, 3}, {4, 2}, {3, 2}, {1, 2}, {2, 5}};

    cout << solution(n, results) << endl;

    return 0;
}