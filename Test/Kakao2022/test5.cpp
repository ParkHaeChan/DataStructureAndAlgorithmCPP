/*
이진트리, 그래프 순회

당신이 모은 양의 수보다 늑대의 수가 같거나 더 많아지면 바로 모든 양을 잡아먹어 버립니다. 
당신은 중간에 양이 늑대에게 잡아먹히지 않도록 하면서 최대한 많은 수의 양을 모아서 다시 루트 노드로 돌아오려 합니다.

루트 노드에는 항상 양이 있습니다
0은 양, 1은 늑대를 의미합니다.

edges의 각 행은 [부모 노드 번호, 자식 노드 번호] 형태로, 서로 연결된 두 노드를 나타냅니다.

부분점수
----시험 후----
시도2
이진 트리인 점을 생각하면 트리의 후위 순회방식을 응용하면
좌우 자식 노드를 방문한 다음 원래 위치로 돌아오는 것을 구현할 수 있다.
다른 쪽에서 양을 찾으면 이전에 못가던 늑대쪽을 다시 시도해 봐야 하므로
후위순회를 2회 시켜주는 방식으로 구현하면 어떨지 생각이 든다.
ramb 수는 전역변수로 관리하고 wolf수는 재귀함수 인자로 사용하도록 변경
*/

#include <string>
#include <vector>

struct node
{
    int id;
    bool wolf;
    bool visited = false;
};

using namespace std;

vector<bool> visited;
int ramb = 1;
int wolfcnt = 0;
/* 시도1
int DFS(vector<vector<node>>& Graph, int start)
{
    for(auto& e: Graph[start])
    {
        if(visited[e.id])
            continue;

        if(e.wolf)
            wolfcnt++;
        else
            if(!e.visited)
            {
                e.visited = true;
                ramb++;
            }
        if(ramb <= wolfcnt)
        {
            wolfcnt--;
            continue;
        }
        visited[e.id];
        DFS(Graph, e.id);
        if(e.wolf)
            wolfcnt--;
    }

    return ramb;
}*/
// 시도2
int DFS(vector<vector<node>>& Graph, int start, int wolves)
{
    for(auto& e: Graph[start])
    {
        if(e.wolf)
        {
            if(ramb <= wolves+1)
                continue;
            else
                DFS(Graph, e.id, wolves+1);
        }
        else
        {
            if(!e.visited)
            {
                ramb++;
                e.visited = true;
            }
            DFS(Graph, e.id, wolves);
        }
    }
    for(auto& e: Graph[start])
    {
        if(e.wolf)
        {
            if(ramb <= wolves+1)
                continue;
            else
                DFS(Graph, e.id, wolves+1);
        }
        else
        {
            if(!e.visited)
            {
                ramb++;
                e.visited = true;
            }
            DFS(Graph, e.id, wolves);
        }
    }
    return ramb;
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;
    int N = info.size();
    vector<vector<node>> Graph(N);
    for(auto e: edges)
    {
        Graph[e[0]].push_back({e[1], (bool)info[e[1]]});
        //Graph[e[1]].push_back({e[0], (bool)info[e[0]]});
    }
    visited = vector<bool>(N, false);
    answer = DFS(Graph, 0, 0);

    return answer;
}

int main()
{
    vector<int> info = {0,0,1,1,1,0,1,0,1,0,1,1};
    vector<vector<int>> edges = {{0,1},{1,2},{1,4},{0,8},{8,7},{9,10},{9,11},{4,3},{6,5},{4,6},{8,9}};

    solution(info, edges);

    return 0;
}