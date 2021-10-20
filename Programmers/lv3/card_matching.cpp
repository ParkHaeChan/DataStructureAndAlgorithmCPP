/*
카드 짝 맞추기
https://programmers.co.kr/learn/courses/30/lessons/72415

게임 개발자인 베로니는 개발 연습을 위해 다음과 같은 간단한 카드 짝맞추기 보드 게임을 개발해 보려고 합니다.
게임이 시작되면 화면에는 카드 16장이 뒷면을 위로하여 4 x 4 크기의 격자 형태로 표시되어 있습니다. 
각 카드의 앞면에는 카카오프렌즈 캐릭터 그림이 그려져 있으며, 8가지의 캐릭터 그림이 그려진 카드가 각기 2장씩 화면에 무작위로 배치되어 있습니다.
유저가 카드를 2장 선택하여 앞면으로 뒤집었을 때 같은 그림이 그려진 카드면 해당 카드는 게임 화면에서 사라지며, 
같은 그림이 아니라면 원래 상태로 뒷면이 보이도록 뒤집힙니다. 이와 같은 방법으로 모든 카드를 화면에서 사라지게 하면 게임이 종료됩니다.

게임에서 카드를 선택하는 방법은 다음과 같습니다.

카드는 커서를 이용해서 선택할 수 있습니다.
커서는 4 x 4 화면에서 유저가 선택한 현재 위치를 표시하는 "굵고 빨간 테두리 상자"를 의미합니다.
커서는 [Ctrl] 키와 방향키에 의해 이동되며 키 조작법은 다음과 같습니다.
방향키 ←, ↑, ↓, → 중 하나를 누르면, 커서가 누른 키 방향으로 1칸 이동합니다.
[Ctrl] 키를 누른 상태에서 방향키 ←, ↑, ↓, → 중 하나를 누르면, 누른 키 방향에 있는 가장 가까운 카드로 한번에 이동합니다.
만약, 해당 방향에 카드가 하나도 없다면 그 방향의 가장 마지막 칸으로 이동합니다.
만약, 누른 키 방향으로 이동 가능한 카드 또는 빈 공간이 없어 이동할 수 없다면 커서는 움직이지 않습니다.
커서가 위치한 카드를 뒤집기 위해서는 [Enter] 키를 입력합니다.
[Enter] 키를 입력해서 카드를 뒤집었을 때
앞면이 보이는 카드가 1장 뿐이라면 그림을 맞출 수 없으므로 두번째 카드를 뒤집을 때 까지 앞면을 유지합니다.
앞면이 보이는 카드가 2장이 된 경우, 두개의 카드에 그려진 그림이 같으면 해당 카드들이 화면에서 사라지며, 
그림이 다르다면 두 카드 모두 뒷면이 보이도록 다시 뒤집힙니다.
"베로니"는 게임 진행 중 카드의 짝을 맞춰 몇 장 제거된 상태에서 카드 앞면의 그림을 알고 있다면, 
남은 카드를 모두 제거하는데 필요한 키 조작 횟수의 최솟값을 구해 보려고 합니다. 
키 조작 횟수는 방향키와 [Enter] 키를 누르는 동작을 각각 조작 횟수 1로 계산하며, 
[Ctrl] 키와 방향키를 함께 누르는 동작 또한 조작 횟수 1로 계산합니다.

다음은 카드가 몇 장 제거된 상태의 게임 화면에서 커서를 이동하는 예시입니다.
아래 그림에서 빈 칸은 이미 카드가 제거되어 없어진 칸을 의미하며, 
그림이 그려진 칸은 카드 앞 면에 그려진 그림을 나타냅니다.

?:
현재 카드가 놓인 상태를 나타내는 2차원 배열 board와 커서의 처음 위치 r, c가 매개변수로 주어질 때, 
모든 카드를 제거하기 위한 키 조작 횟수의 최솟값을 return 하도록 solution 함수를 완성해 주세요.

!!!:
board는 4 x 4 크기의 2차원 배열입니다.
board 배열의 각 원소는 0 이상 6 이하인 자연수입니다.
0은 카드가 제거된 빈 칸을 나타냅니다.
1 부터 6까지의 자연수는 2개씩 들어있으며 같은 숫자는 같은 그림의 카드를 의미합니다.
뒤집을 카드가 없는 경우(board의 모든 원소가 0인 경우)는 입력으로 주어지지 않습니다.
r은 커서의 최초 세로(행) 위치를 의미합니다.
c는 커서의 최초 가로(열) 위치를 의미합니다.
r과 c는 0 이상 3 이하인 정수입니다.
게임 화면의 좌측 상단이 (0, 0), 우측 하단이 (3, 3) 입니다.

시도1) 보드의 크기가 매우 작은 편이다.
완전 탐색 방식으로 모든 경우를 확인하여 최단 방법을 찾아도 될 것 같다.
어느 카드를 뒤집을지 결정하고 그 카드까지 이동하고 뒤집는데 쓰이는 키 횟수를 저장한 뒤
모든 카드가 뒤집어 졌을 떄 누적된 키입력 횟수의 최소값으로 갱신

어느 카드 하나를 선택(Enter)했으면, 똑같은 카드를 찾는데는 최대 방향키 2회로 이동할 수 있다.
같은 열이나 행에 있는 경우는 1회로 이동할 수 있다.
처음 시작하거나 한 쌍을 처리 후 다음 카드를 찾는데 최소로 찾아야 한다.
이 때는 같은 열이나 행인 경우 1회 
다른 경우 2회의 키입력으로 다음 카드를 찾을 수 있다.
Enter는 카드 수만큼 발생한다.
board는 복사로 넘겨주는게 편함
고려할게 많다...
단순히 문제에서 사용하는 그대로 시뮬레이션하는 방법이 나을 것 같다.
1칸 이동하는 모든 경우와 ctrl 누르고 이동하는 모든 경우를 고려하여 본뒤,
해당 위치가 0이 아니면 지금 뒤집는 경우와 다음에 뒤집는 경우로 나눠 수행

void recur(vector<vector<int>> board, pos cur, int face, int keyCnt)
{
    int ret = INF;
    bool done = true;
    for(int r=0; r<4; ++r)
    {
        if(!done)
            break;
        for(int c=0; c<4; ++c)
            if(board[r][c] != 0)
            {
                done = false;
                break;
            }
    }
    if(done)
    {
        MINMOVE = min(MINMOVE, keyCnt);
        return;
    }
    // 현재 위치가 0이 아니면 선택 여부 결정
    if(face != 0)
    {
        // 선택하는 경우
        board[cur.first][cur.second] = 0;   // 선택 했으므로 보드에서 뺌
        recur(board, cur, face, keyCnt+1);  // enter
        // 선택 안하는 경우
        board[cur.first][cur.second] = 1;
        recur(board, cur, 0, keyCnt);
    }

    for(int d=0;d<DIRS.size(); ++d)
    {   // 1칸 이동
        pos next = {cur.first+DIRS[d].first, cur.second+DIRS[d].second};
        if(InRange(next.first, next.second))
        {
            
        }
        bool moved = false;
        while(InRange(next.first, next.second))
        {   // ctrl + 이동
            if(board[next.first][next.second] != 0)
            {   // 다른 카드 만나는 경우
                moved = true;

                break;
            }
            else
                next = {next.first+DIRS[d].first, next.second+DIRS[d].second};
        }
        if(!moved)
        {
            next = {next.first-DIRS[d].first, next.second-DIRS[d].second};
            recur(board, next, board[next.first][next.second], moveCnt+1);   // 가능한 끝까지 이동
        }
    }
}

시도2)
완전탐색인데 구성이 까다롭다...
해설 참고
몇번 카드를 먼저 뒤집을 것인지 정해서(1~6)
그 카드를 먼저 해결한 경우 최소 키입력 횟수를 구하고,
그 다음에 뒤집을 카드를 정하고 하는 방식으로 진행한다.
1번 카드를 삭제한다고 하더라도 2개중 어떤 카드를 먼저 삭제하느냐에 따라서도 횟수가 다를 것이다.
즉, 순열을 사용해야 한다.

board 복원할 떄 n으로 복원해야 하는데 1로 씀.
tc: 22, 25~30 실패
시도3)
BFS에서 ctrl 이동하는 경우 처리 고침
tc: 22, 29, 30 실패

if(visited[...][...])
    continue;

visited[...][...] = true;
bfs.push(...)
을

if(!visited[next.first][next.second])
{   // 1칸 이동
    visited[next.first][next.second] = true;
    bfsQ.push({next, cur.n+1});
}
식으로 고쳐주니 통과되었다...

1칸 이동한 경우가 이미 방문했다고 다른 방향으로 가는 경우로 넘겨버리면(continue)
ctrl+이동으로 이동한 경우를 처리하지 않고 넘어가 버려서 발생한 문제이다.
주의해야 겠다.

*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using pos = pair<int, int>;

struct Point
{
    pos p;
    int n;    // 이동 키 입력 횟수
};

vector<pos> DIRS = {{-1, 0}, {0,-1}, {1,0}, {0,1}};

bool InRange(int r, int c)
{
    if(0<=r && r<4 && 0<=c && c<4)
        return true;
    return false;
}

const int INF = 987654321;

int BFS(Point src, Point dst, vector<vector<int>>& board)
{   // src에서 dst까지의 최단으로 가는 이동 key입력 횟수
    vector<vector<bool>> visited(4, vector<bool>(4, false));
    queue<Point> bfsQ;
    visited[src.p.first][src.p.second] = true;
    bfsQ.push(src);

    while(!bfsQ.empty())
    {
        auto cur = bfsQ.front(); bfsQ.pop();
        if(cur.p.first == dst.p.first && cur.p.second == dst.p.second)
        {
            return cur.n;
        }
        for(int d=0; d<4; ++d)
        {
            pos next = {cur.p.first + DIRS[d].first, cur.p.second + DIRS[d].second};
            if(InRange(next.first, next.second))
            {   
                if(!visited[next.first][next.second])
                {   // 1칸 이동
                    visited[next.first][next.second] = true;
                    bfsQ.push({next, cur.n+1});
                }
                for(int i=0; i<2; ++i)
                {   // 최대 2칸 더 추가로 이동할 수 있음(ctrl 이동)
                    if(board[next.first][next.second] != 0)
                        break;  // 카드가 있는 경우 거기서 멈춤
                    if(InRange(next.first+DIRS[d].first, next.second+DIRS[d].second))
                    {
                        next = {next.first+DIRS[d].first, next.second+DIRS[d].second};
                        // if(visited[next.first][next.second])
                        //     continue; // 무시하고 가는 경우라 체크 X
                        // if(board[next.first][next.second] != 0)
                        //     break;  // 카드가 있는 경우 거기서 멈춤 (반복문 시작시 처음에 검사해야함)
                    }
                    else
                        break;
                }
                if(!visited[next.first][next.second])
                {
                    visited[next.first][next.second] = true;
                    bfsQ.push({{next}, cur.n+1});
                }
            }
        }
    }
    return INF; // 정상적으로 작동했으면 실행되지 않음
}

int permutate(vector<vector<int>>& board, Point src)
{   // 모든 카드를 뒤집어보는 순열을 수행
    int ret = INF;
    for(int n=1; n<=6; ++n)
    {   // 카드는 1번부터 6번까지 사용
        vector<Point> points;
        for(int r=0; r<4; ++r)
        {
            for(int c=0; c<4; ++c)
            {
                if(board[r][c] == n)
                {
                    points.push_back({{r,c},0});    // bfs에서 이동수 넣을 것이므로 0으로 둠
                }
            }
        }
        if(points.empty())
            continue; // 짝 맞춘 카드 거나 없는 카드

        // 어떤 카드를 먼저 뒤집을지에 따라 키입력 횟수가 다름(순, 역순 시도)
        int forward = BFS(src, points[0], board) + BFS(points[0], points[1], board) + 2; // 2: enter 누르는 횟수
        int backward = BFS(src, points[1], board) + BFS(points[1], points[0], board) + 2;

        // 보드에서 삭제
        for(int i=0; i<2; ++i)
            board[points[i].p.first][points[i].p.second] = 0;

        ret = min(ret, permutate(board, points[0])+backward);
        ret = min(ret, permutate(board, points[1])+forward);

        // 복원
        for(int i=0; i<2; ++i)
            board[points[i].p.first][points[i].p.second] = n;   // n인데 1적는 실수 주의...
    }
    if(ret == INF)
        return 0;
    return ret;
}

int solution(vector<vector<int>> board, int r, int c) {
    int answer = 0;

    answer = permutate(board, {{r,c},0});

    return answer;
}

int main()
{
    vector<vector<int>> board = {{1,0,0,3},{2,0,0,0},{0,0,0,2},{3,0,1,0}};
    int r = 1;
    int c = 0;
    solution(board, r, c);

    return 0;
}