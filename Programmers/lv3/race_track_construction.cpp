/*
경주로 건설
https://programmers.co.kr/learn/courses/30/lessons/67259

경주로의 출발점은 (0, 0) 칸(좌측 상단)이며, 도착점은 (N-1, N-1) 칸(우측 하단)
출발점인 (0, 0) 칸에서 출발한 자동차가 도착점인 (N-1, N-1) 칸까지 무사히 도달할 수 있게 중간에 끊기지 않도록 경주로를 건설
경주로는 상, 하, 좌, 우로 인접한 두 빈 칸을 연결하여 건설할 수 있으며, 벽이 있는 칸에는 경주로를 건설할 수 없습니다.
이때, 인접한 두 빈 칸을 상하 또는 좌우로 연결한 경주로를 직선 도로 라고 합니다.
또한 두 직선 도로가 서로 직각으로 만나는 지점을 코너 라고 부릅니다.
건설 비용을 계산해 보니 직선 도로 하나를 만들 때는 100원이 소요되며, 코너를 하나 만들 때는 500원이 추가로 듭니다.
죠르디는 견적서 작성을 위해 경주로를 건설하는 데 필요한 최소 비용을 계산해야 합니다.

?:
도면의 상태(0은 비어 있음, 1은 벽)을 나타내는 2차원 배열 board가 매개변수로 주어질 때, 
경주로를 건설하는데 필요한 최소 비용을 return 하도록 solution 함수를 완성해주세요.

!!!:
board는 2차원 정사각 배열로 배열의 크기는 3 이상 25 이하입니다.
board 배열의 각 원소의 값은 0 또는 1 입니다.
도면의 가장 왼쪽 상단 좌표는 (0, 0)이며, 가장 우측 하단 좌표는 (N-1, N-1) 입니다.
원소의 값 0은 칸이 비어 있어 도로 연결이 가능함을 1은 칸이 벽으로 채워져 있어 도로 연결이 불가능함을 나타냅니다.
board는 항상 출발점에서 도착점까지 경주로를 건설할 수 있는 형태로 주어집니다.
출발점과 도착점 칸의 원소의 값은 항상 0으로 주어집니다.

시도1)
보드의 크기가 작다. 한번에 한칸씩 이동하면서 최소값을 구하는 문제이다.
--> BFS 시도
코너와 직선을 구분해야 한다 --> 이전에 움직인 방향과 다른지로 판단(돌아가는 경우는 없다-visited check로 막을 것)
가능한 방법이 여러가지인 경우 비용 최소가 되는 것 선택(목적지 도달해도 바로 종료X--> 큐가 빌때 까지 시도)

시도2)
답이 이상하게 나와서 좀 생각해보니까 이미 방문했더라도, 더 싸게 가는 방법이 존재하면 그 방법이 우선되어야 한다.
visited를 bool에서 int로 바꿔서 이 위치까지 도달하는데 쓴 비용이 더적으면 업데이트하는 방식으로 변경
즉, DP처럼 풀어야 한다.
25번 케이스 하나 실패하고 통과함

시도3)
[0, 0, 0, 0, 0],
[0, 1, 1, 1, 0],
[0, 0, 1, 0, 0],
[1, 0, 0, 0, 1],
[0, 1, 1, 0, 0]
이 경우 3000이 정답인데 3300이 나온다.
BFS 방식으로 중간 까지의 계산을 저장하는 방식이 아닌
모든 경우를 다 시도하여 끝까지 도달한 모든 경우 중 최소값을 찾는 DFS방식으로 짜야될 것 같다.
시간초과 발생

시도4)
DP로 풀자니 초반에 커도 후반에 더 작아지는 경우가 발생하여 답이 틀리고,
DFS로 모든 경우 시도해보자니 시간초과가 발생한다.
BFS에서 비용의 결과값을 기준으로하는 것이 아닌 코너의 수를 기준으로하여
더 적은 코너를 사용하면서 목적지에 도달하였을 경우의 최소비용만 계산해주는 방식으로 바꿔주었다.
통과는 했는데 찝찝한 느낌...
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using pos = pair<int, int>;

struct node
{
    int last_dir;
    int cost;
    int st = 0;
    int cn = 0;
};

bool InRange(pos p, int N)
{
    int r = p.first;
    int c = p.second;
    if(0<=r && r<N && 0<=c && c<N)
        return true;
    return false;
}

int BFS(vector<vector<int>>& board)
{
    const int INF = 987654321;
    int N = board.size();
    pos start = {0,0};
    pos end = {N-1, N-1};
    queue<pair<pos, node>> bfsQ; // 위치 방향 함께 저장
    node temp = {-1, 0, 0, 0};
    bfsQ.push({start, temp});
    vector<vector<int>> visited(N, vector<int>(N, INF));
    visited[0][0] = 0;
    int corner = INF;   // 시도 4
    int answer = INF;

    vector<pos> DIRS = {{-1, 0},{0,-1},{1,0},{0,1}};

    while(!bfsQ.empty())
    {
        auto cur = bfsQ.front(); bfsQ.pop();
        pos curpos = cur.first;
        node curinfo = cur.second;
        if(curpos == end)
        {
            if(corner >= curinfo.cn)
            {
                answer = min(answer, curinfo.cn*500 + curinfo.st*100);
            }
            continue;
        }

        for(int d=0; d<DIRS.size(); ++d)
        {
            pos next = {curpos.first+DIRS[d].first, curpos.second+DIRS[d].second};
            if(InRange(next, N))
            {   // 보드 범위 내
                if(board[next.first][next.second] == 1)
                    continue;   // 벽

                node nextinfo;
                nextinfo.last_dir = d;
                if(curinfo.last_dir == -1 || curinfo.last_dir == d)
                {   // 첫 시작은 직선도로 건설로 간주 || 직선도로
                    nextinfo.cost = curinfo.cost + 100;
                    nextinfo.st = curinfo.st+1;
                    nextinfo.cn = curinfo.cn;
                }
                else
                {   // 코너
                    nextinfo.cost = curinfo.cost + 600;
                    nextinfo.st = curinfo.st+1;
                    nextinfo.cn = curinfo.cn+1;
                }
                if(visited[next.first][next.second] >= nextinfo.cn)   // 주의: 같은 경우도 포함시켜야 모든 경우 찾아짐
                {
                    visited[next.first][next.second] = nextinfo.cn;
                    bfsQ.push({next, nextinfo});
                }
            }
        }
    }

    return answer;
}

int ANSWER;
vector<pos> DIRS = {{-1, 0},{0,-1},{1,0},{0,1}};
pos END;
void DFS(vector<vector<int>>& board, pos start, int cost, int lastdir, vector<vector<bool>>& visited)
{
    if(start == END)
    {
        ANSWER = min(ANSWER, cost);
        return;
    }
    for(int d=0; d<DIRS.size(); ++d)
    {
        pos next = {start.first+DIRS[d].first, start.second+DIRS[d].second};
        if(InRange(next, board.size()))
        {
            if(visited[next.first][next.second])
                continue;
            if(board[next.first][next.second] == 1)
                continue;
            int add;
            if(lastdir == -1 ||  lastdir == d)
                add = 100;
            else
                add = 600;
            visited[next.first][next.second] = true;
            DFS(board, next, cost+add, d, visited);
            visited[next.first][next.second] = false;
        }
    }
}

int solution(vector<vector<int>> board) {
    /* 시도3
    const int INF = 987654321;
    ANSWER = INF;
    int N = board.size();
    vector<vector<bool>> visited(N, vector<bool>(N, false));;
    END = {N-1, N-1};
    visited[0][0] = true;
    DFS(board, {0,0}, 0, -1, visited);*/
    int answer = 0;

    answer = BFS(board);

    return answer;
}

int main()
{
    // vector<vector<int>> board = {
    //     {0,0,0,0,0,0,0,1},
    //     {0,0,0,0,0,0,0,0},
    //     {0,0,0,0,0,1,0,0},
    //     {0,0,0,0,1,0,0,0},
    //     {0,0,0,1,0,0,0,1},
    //     {0,0,1,0,0,0,1,0},
    //     {0,1,0,0,0,1,0,0},
    //     {1,0,0,0,0,0,0,0}
    //     };
    vector<vector<int>> board = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 0, 0}};
    solution(board);

    return 0;
}