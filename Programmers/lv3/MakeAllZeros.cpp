/*
모두 0으로 만들기
https://programmers.co.kr/learn/courses/30/lessons/76503

각 점에 가중치가 부여된 트리가 주어집니다. 당신은 다음 연산을 통하여, 이 트리의 모든 점들의 가중치를 0으로 만들고자 합니다.

임의의 연결된 두 점을 골라서 한쪽은 1 증가시키고, 다른 한쪽은 1 감소시킵니다.
하지만, 모든 트리가 위의 행동을 통하여 모든 점들의 가중치를 0으로 만들 수 있는 것은 아닙니다. 
당신은 주어진 트리에 대해서 해당 사항이 가능한지 판별하고, 
만약 가능하다면 최소한의 행동을 통하여 모든 점들의 가중치를 0으로 만들고자 합니다.

?:
트리의 각 점의 가중치를 의미하는 1차원 정수 배열 a와 트리의 간선 정보를 의미하는 edges가 매개변수로 주어집니다. 
주어진 행동을 통해 트리의 모든 점들의 가중치를 0으로 만드는 것이 불가능하다면 -1을, 
가능하다면 최소 몇 번만에 가능한지를 찾아 return 하도록 solution 함수를 완성해주세요. 
(만약 처음부터 트리의 모든 정점의 가중치가 0이라면, 0을 return 해야 합니다.)

!!!:
a의 길이는 2 이상 300,000 이하입니다.
a의 모든 수는 각각 -1,000,000 이상 1,000,000 이하입니다.
a[i]는 i번 정점의 가중치를 의미합니다.
edges의 행의 개수는 (a의 길이 - 1)입니다.
edges의 각 행은 [u, v] 2개의 정수로 이루어져 있으며, 이는 u번 정점과 v번 정점이 간선으로 연결되어 있음을 의미합니다.
edges가 나타내는 그래프는 항상 트리로 주어집니다.

시도 1)
a의 길이가 최대 30만이고, 원소크기가 +-100만이나 된다.
edge의 개수는 a의 길이-1 이므로 약 30만
입력 크기로 봐선 완전탐색은 불가능해보인다.
직접 트리를 구성해서 처리하기도 애매한 크기이다.
"연결된 두 점을 골라서 한쪽은 1 증가시키고, 다른 한쪽은 1 감소시킵니다" --> 가중치가 이동하는 것으로 볼 수 있다.
한 정점의 가중치를 다른 정점으로 이동할 수 있다는 것이다.
그래프는 항상 트리로 주어진다하였고, edge개수가 a의 길이-1이기 때문에 끊어진 경우는 없다
즉, a의 모든 원소의 합이 0이면 구성할 수 있어서 최소 이동수를 구하면 되고,
이외의 경우는 구할 수 없으므로 -1을 반환한다.
최소 이동수를 구하는 방법은 트리라는 점을 생각하면
leaf에서 root까지 올라가는 횟수라 생각 할 수 있다.
이 방식으로 순회하려면, 트리 순회 방식에서 후위순회를 사용한다.
여기서 이미 root에 도달하기 전에 0이 된 경우도 0을 이동하는 것은 횟수에 안들어가므로 문제없이 구현가능하다.
하지만 root가 몇번이라는 말이 없다...
생각해보니 이진 트리가 아니기 때문에 아무데서나 시작해도 된다.
점수: 39
PostOrder할 떄 종료전에는 ret에 있는 값도 ANSWER에 반영해야하는데 그게 안된 것 같다.

시도2)
점수 그대로...
전역에 있는 int ANSWER를 long long 형으로 바꿔 주었다.
통과

*/

#include <string>
#include <vector>

using namespace std;

vector<int> A;

long long ANSWER = 0;   // 시도 3

long long PostOrder(vector<vector<int>>& Tree, vector<bool>& visited, int cur)
{
    // dfs방식으로 먼저 끝까지 들어간 다음 시작점으로 돌아온다.
    auto connected = Tree[cur];
    visited[cur] = true;
    long long ret = A[cur];
    long long temp = 0;
    for(auto next: connected)
    {
        if(visited[next])
            continue;
        long long movedval = PostOrder(Tree, visited, next);
        temp += abs(movedval);
        ret += movedval;
    }
    ANSWER += temp;
    return ret;
}

long long solution(vector<int> a, vector<vector<int>> edges) {
    long long answer = -1;
    A = a;

    long long sum = 0;
    for(auto e: a)
        sum += e;
    // a원소 합이 0이 아니면 0으로 만드는 것은 불가능함
    if(sum != 0)
        return -1;

    // 최소 이동 수: 트리(그래프)의 후위순회 방식으로 셈, 아무 정점에서 시작해도 가능
    // 그래프: 인접리스트 방식
    vector<vector<int>> Tree(a.size());
    vector<bool> visited(a.size(), false);
    for(auto& v: edges)
    {
        // 양방향 연결
        Tree[v[0]].push_back(v[1]);
        Tree[v[1]].push_back(v[0]);
    }
    answer = PostOrder(Tree, visited, 0);
    ANSWER += abs(answer);  // 시도 2

    return ANSWER;
}

int main()
{
    vector<int> a = {-5,0,2,1,2};
    vector<vector<int>> edges = {{0,1},{3,4},{2,3},{0,3}};

    solution(a, edges);

    return 0;
}