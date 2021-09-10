/*
https://www.acmicpc.net/problem/3190
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using pos = pair<int, int>;

bool InRange(int row, int col, vector<vector<int>>& board)
{
    int N = board.size();
    if(0 <= row && row < N && 0 <= col && col < N && board[row][col] != 1)
        return true;
    return false;
}
// 오른족이나 왼쪽으로 방향을 바꾸는 경우
// 구현을 쉽게하려면 순환되는 구조로 처음 방향을 잡아준다
// 왼쪽으로 도는 경우 이전 방향이
// 위쪽일 때는 왼쪽 그대로가고,
// 왼쪽을 떄는 아래로 가고
// 아래쪽일 때는 오른쪽으로 가고,
// 오른족일 때는 위로 간다.
// U L D R 순으로 0123이라 하면 바뀌는 방향은
// L D R U (1230)으로 순환됨을 확인할 수 있다
// 반대로 오른쪽으로 도는 경우는
// R U L D (3012)이다.
int turn_dir(int last_dir, char C)
{   
    if(C == 'L')
    {
        return (last_dir+1)%4;
    }
    else if(C == 'D')
    {
        if(last_dir-1 < 0)
            return 3;
        else
            return last_dir-1;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    int N, K;
    cin >> N >> K;

    // 보드: N x N
    vector<vector<int>> Board(N, vector<int>(N, 0));

    // 사과의 위치
    int r, c;
    for(int k=0; k < K; ++k)
    {
        cin >> r >> c;
        Board[r-1][c-1] = 2; // 사과 표시
    }
    int L;
    cin >> L; // 뱀의 방향 전환 횟수
    int time;
    char direction;
    vector<pair<int, char>> turnInfo;
    for(int turn = 0; turn < L; ++turn)
    {
        cin >> time >> direction;
        turnInfo.push_back({time, direction});
    }

    // 게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1 이다. 뱀은 처음에 오른쪽을 향한다
    vector<pos> DIRS = {{-1, 0}, {0, -1}, {1,0}, {0, 1}};   // ULDR
    int last_dir = 3;   // R로 시작
    pos head = {0, 0};
    pos tail = {0, 0};
    Board[tail.first][tail.second] = 1; // 뱀 자리
    queue<pos> snake;
    snake.push(tail);
    int answer = 0;
    int idx = 0;
    while(true)
    {
        // time 만큼 last_dir 방향으로 진행
        answer++;
        pos new_head = {head.first + DIRS[last_dir].first, head.second + DIRS[last_dir].second};
        if(!InRange(new_head.first, new_head.second, Board)) // 벽 또는 자신
            break;
        if(Board[new_head.first][new_head.second] != 2) // 사과 먹은 경우가 아니면
        {   // 꼬리 위치 삭제 (이동)
            tail = snake.front(); snake.pop();
            Board[tail.first][tail.second] = 0;
        }
        // 머리 위치 갱신
        Board[new_head.first][new_head.second] = 1;
        snake.push(new_head);
        head = new_head;

        // time 이후 방향 전환
        if(answer == turnInfo[idx].first)
        {
            direction = turnInfo[idx].second;
            idx++;
            last_dir = turn_dir(last_dir, direction);
        }
    }
    cout << answer << endl;

    return 0;
}