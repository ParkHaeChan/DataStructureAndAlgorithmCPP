/*
블록 이동하기
https://programmers.co.kr/learn/courses/30/lessons/60063

준비 중인 로봇은 2 x 1 크기의 로봇으로 "무지"는 "0"과 "1"로 이루어진 N x N 크기의 지도에서 
2 x 1 크기인 로봇을 움직여 (N, N) 위치까지 이동
봇은 90도씩 회전할 수 있습니다. 단, 로봇이 차지하는 두 칸 중, 어느 칸이든 축이 될 수 있지만, 
회전하는 방향(축이 되는 칸으로부터 대각선 방향에 있는 칸)에는 벽이 없어야 합니다.

?:
0"과 "1"로 이루어진 지도인 board가 주어질 때, 
로봇이 (N, N) 위치까지 이동하는데 필요한 최소 시간을 return 하도록 solution 함수를 완성해주세요.

!!!:
board의 한 변의 길이는 5 이상 100 이하입니다.
board의 원소는 0 또는 1입니다.
로봇이 처음에 놓여 있는 칸 (1, 1), (1, 2)는 항상 0으로 주어집니다.
로봇이 항상 목적지에 도착할 수 있는 경우만 입력으로 주어집니다.

시도1)
로봇의 방향 상태에 따라 이동시 확인해야할 벽의 위치가 달라진다.
그리고 회전할 때 조건을 지켜야 한다.
그리고 매번 1칸을 1초씩 움직이는데 최소 시간을 구해야 하므로 BFS방식이 적절해 보인다.
초기 방향은 가로로 있는 상태인데 이 상태를 0이라하고, 세로로 있는 상태를 1이라 정하고,
각 경우에 따라 움직일 때 벽에 대한 처리를 해주도록 구현

시도2)
visited를 좀 더 세분화해야한다.
가로로 된 로봇이 아래로 내려간 경우
세로로 회전을 시키려할 때 이미 두 위치가 방문한 상태가 되는 문제가 있다.
2차원 bool 벡터대신 set을 사용하여 사용 여부를 판단하도록 변경

통과는 했는데 회전쪽 중복로직 부분 코드 줄여봐야겠다...
*/

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;
using pos = pair<int, int>;

struct robot
{
    pos p1;  // 기준 위치
    pos p2;  // 추가 위치
    int rotation=0; // 0: 가로, 1: 세로
    int time;   // 걸린 시간
};

bool InRange(pos cur, int N)
{
    int r = cur.first;
    int c =cur.second;
    if(0<=r && r<N && 0<=c && c<N)
        return true;
    return false;
}

vector<pos> DIRS = {{-1,0},{0,-1},{1,0},{0,1}}; // ULDR

int BFS(vector<vector<int>>& board)
{
    int N = board.size();
   set<pair<pos, pos>> visited;
    queue<robot> bfsQ;
    pos start1 = {0,0};
    pos start2 = {0,1};
    robot rb{start1, start2, 0, 0};
    bfsQ.push(rb);
    visited.insert({start1,start2});
    visited.insert({start2,start1});    // 방향 반대인 경우도 같음
    pos end = {N-1, N-1};
    int answer = 987654321;

    while(!bfsQ.empty())
    {
        auto cur = bfsQ.front(); bfsQ.pop();

        if(cur.p1 == end || cur.p2 == end)
        {
            answer = min(answer, cur.time);
        }
        // 상하좌우 이동 시도
        for(int d=0; d<DIRS.size(); ++d)
        {
            robot next;
            pos np1 = {cur.p1.first+DIRS[d].first, cur.p1.second+DIRS[d].second};    // 기준위치
            pos np2 = {cur.p2.first+DIRS[d].first, cur.p2.second+DIRS[d].second};
            // 보드 범위 확인
            if(InRange(np1, N) && InRange(np2, N))
            {
                if(visited.find({np1, np2}) != visited.end() || visited.find({np2, np1}) != visited.end())
                    continue;   // 방문여부
                if(board[np1.first][np1.second] == 1 || board[np2.first][np2.second] == 1)
                    continue;   // 벽인 경우

                visited.insert({np1, np2});
                visited.insert({np2, np1});
                next.p1 = np1;
                next.p2 = np2;
                next.rotation = cur.rotation;
                next.time = cur.time+1;
                bfsQ.push(next);
            }
        }
        //회전: 두 위치 각자 축인 경우 가능한 모든 회전 시도(4가지 가능)
        if(cur.rotation == 0)
        {   // 가로인 경우
            pos d1 = {cur.p1.first+1, cur.p1.second};
            pos d2 = {cur.p2.first+1, cur.p2.second};
            if(InRange(d1, N) && InRange(d2, N))
                if(board[d1.first][d1.second] == 0 && board[d2.first][d2.second] == 0)
                {
                    robot next1 = {cur.p1, d1, 1, cur.time+1};
                    robot next2 = {cur.p2, d2, 1, cur.time+1};
                    if(visited.find({cur.p1, d1}) == visited.end() && visited.find({d1, cur.p1}) == visited.end())
                        bfsQ.push(next1);
                    if(visited.find({cur.p2, d2}) == visited.end() && visited.find({d2, cur.p2}) == visited.end())
                        bfsQ.push(next2);
                }
            pos u1 = {cur.p1.first-1, cur.p1.second};
            pos u2 = {cur.p2.first-1, cur.p2.second};
            if(InRange(u1, N) && InRange(u2, N))
                if(board[u1.first][u1.second] == 0 && board[u2.first][u2.second] == 0)
                {
                    robot next1 = {cur.p1, u1, 1, cur.time+1};
                    robot next2 = {cur.p2, u2, 1, cur.time+1};
                    if(visited.find({cur.p1, u1}) == visited.end() && visited.find({u1, cur.p1}) == visited.end())
                        bfsQ.push(next1);
                    if(visited.find({cur.p2, u2}) == visited.end() && visited.find({u2, cur.p2}) == visited.end())
                        bfsQ.push(next2);
                }
        }
        else
        {   // 세로인 경우
            pos r1 = {cur.p1.first, cur.p1.second+1};
            pos r2 = {cur.p2.first, cur.p2.second+1};
            if(InRange(r1, N) && InRange(r2, N))
                if(board[r1.first][r1.second] == 0 && board[r2.first][r2.second] == 0)
                {
                    robot next1 = {cur.p1, r1, 0, cur.time+1};
                    robot next2 = {cur.p2, r2, 0, cur.time+1};
                    if(visited.find({cur.p1, r1}) == visited.end() && visited.find({r1, cur.p1}) == visited.end())
                        bfsQ.push(next1);
                    if(visited.find({cur.p2, r2}) == visited.end() && visited.find({r2, cur.p2}) == visited.end())
                        bfsQ.push(next2);
                }
            pos l1 = {cur.p1.first, cur.p1.second-1};
            pos l2 = {cur.p2.first, cur.p2.second-1};
            if(InRange(l1, N) && InRange(l2, N))
                if(board[l1.first][l1.second] == 0 && board[l2.first][l2.second] == 0)
                {
                    robot next1 = {cur.p1, l1, 0, cur.time+1};
                    robot next2 = {cur.p2, l2, 0, cur.time+1};
                    if(visited.find({cur.p1, l1}) == visited.end() && visited.find({l1, cur.p1}) == visited.end())
                        bfsQ.push(next1);
                    if(visited.find({cur.p2, l2}) == visited.end() && visited.find({l2, cur.p2}) == visited.end())
                        bfsQ.push(next2);
                }
        }
    }
    return answer;
}

int solution(vector<vector<int>> board) {
    int answer = 0;

    answer = BFS(board);

    return answer;
}

int main()
{
    vector<vector<int>> board = {{0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0}};
    solution(board);

    return 0;
}