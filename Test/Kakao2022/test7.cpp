/*
부분점수 획득
---시험 후----
NQueen문제랑 비슷한 느낌인데 좀 더 조건이 까다로운 듯
아직 명확한 해법은 안떠오른다.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using pos = pair<int, int>;

vector<pos> DIRS = {{-1, 0}, {0,-1},{1,0},{0,1}};  // ULDR

int MOVED = 0;

bool InRange(int row, int col, int R, int C)
{
    if(0<=row && row<R && 0<=col && col <C)
        return true;

    return false;
}

bool try_game(vector<vector<int>> board, pos a, pos b, bool turn, int movecnt)
{
    // 갈 수 있는 선택지가 없는 경우 패배
    int r,c;
    if(turn == false)   // a 차례
    {
        r = a.first;
        c = a.second;
        if(board[r][c] == 0)    // 상대가 이동하면서 바닥 붕괴
        {
            MOVED = max(MOVED, movecnt);
            return 1;   // b가 이김
        }
        int cnt = 0;
        for(auto dir: DIRS)
        {
            if(!InRange(r+dir.first,c+dir.second, board.size(), board[0].size()))
                continue;
            if(board[r+dir.first][c+dir.second] == 0)
                cnt++;
        }
        if(cnt == 4)
        {
            MOVED = max(MOVED, movecnt);
            return 1;   // b가 이김
        }
    }
    else
    {
        r = b.first;
        c = b.second;
        if(board[r][c] == 0)    // 상대가 이동하면서 바닥 붕괴
        {
            MOVED = max(MOVED, movecnt);
            return 0;   // b가 이김
        }
        int cnt = 0;
        for(auto dir: DIRS)
        {
            if(!InRange(r+dir.first,c+dir.second, board.size(), board[0].size()))
                continue;
            if(board[r+dir.first][c+dir.second] == 0)
                cnt++;
        }
        if(cnt == 4)
        {
            MOVED = max(MOVED, movecnt);
            return 0;   // b가 이김
        }
    }

    // 아직 더 진행할 수 있는 경우
    for(auto dir: DIRS)
    {
        if(!InRange(r+dir.first,c+dir.second, board.size(), board[0].size()))
                continue;
        if(board[r+dir.first][c+dir.second] != 0)
        {
            board[r][c] = 0;   // 이동하면서 원래 위치 삭제
            if(turn)
            {
                if(try_game(board, a, {r+dir.first,c+dir.second}, !turn, movecnt+1) == turn)
                    return turn;
            }
            else
            {
                if(try_game(board, {r+dir.first,c+dir.second}, b, !turn, movecnt+1) == !turn)
                    return !turn;
            }
        }
    }
    // 진행 못하면 상대 승
    MOVED = max(MOVED, movecnt);
    return !turn;
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {

    pos a = {aloc[0], aloc[1]};
    pos b = {bloc[0], bloc[1]};
    try_game(board, a, b, false, 0);
    return MOVED;
}

int main()
{
    vector<vector<int>> board = {{1, 1, 1, 1, 1}};
    vector<int> aloc = {0, 0};
    vector<int> bloc = {0, 4};
    solution(board, aloc, bloc);
    return 0;
}