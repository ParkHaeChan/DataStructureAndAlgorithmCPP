#include <string>
#include <vector>
#include <iostream>

using namespace std;

void PrintBoard(vector<vector<int>>& board)
{
    for(int i=0; i<board.size(); ++i)
    {
        for(int j=0; j<board[i].size(); ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool InRange(int row, int col, int N)
{
    if(0<= row && row < N && 0 <= col && col < N)
        return true;
    return false;
}

void check_board(vector<vector<int>>& board, int row, int col)
{   // 퀸이 갈 수 있는 영역 표시
    // 행, 열 표시
    for(int r=0; r<board.size(); ++r)
        board[r][col] = 1;
    for(int c=0; c<board.size(); ++c)
        board[row][c] = 1;
    // 대각선 표시
    int rc = 1, lc = 1;
    // 왼쪽 위 방향
    while(InRange(row-rc, col-lc, board.size()))
    {
        board[row-rc][col-lc] = 1;
        rc++; lc++;
    }
    rc = 1, lc = 1;
    // 오른쪽 위 방향
    while(InRange(row-rc, col+lc, board.size()))
    {
        board[row-rc][col+lc] = 1;  // board[row-rc][col-lc] = 1;로 InRanege에서 검사한 값이랑 다르게 잘 못 써놓고 못찾아서 범위 터지는 에러 발생한 것
        rc++; lc++;
    }
    rc = 1, lc = 1;
    // 왼쪽 아래 방향
    while(InRange(row+rc, col-lc, board.size()))
    {
        board[row+rc][col-lc] = 1;
        rc++; lc++;
    }
    rc = 1, lc = 1;
    // 오른쪽 아래 방향
    while(InRange(row+rc, col+lc, board.size()))
    {
        board[row+rc][col+lc] = 1;
        rc++; lc++;
    }
}

// 매 행을 depth로 퀸을 놓는 열을 select로 정의
int recur(vector<vector<int>> board, int depth)
{
    if(depth == board.size()-1)
    {   
        int cnt = 0;
        for(int col=0; col < board.size(); ++col)
            if(board[depth][col] == 0)
                cnt++;
        return cnt;
    }
    int ret = 0;
    vector<vector<int>> origin;
    copy(board.begin(), board.end(), back_inserter(origin));
    for(int col=0; col <board.size(); ++col)
    {
        if(board[depth][col] == 1)
            continue;
        check_board(board, depth, col); // solution 함수에서는 문제 없는데 여기서는 실행시키면 알기 힘든 런타임 에러가 발생한다.
        // 일종의 메모리 침범현상이 발생하는 듯 하다 --> check_board 내부에서 InRange와 동일하게 써야되는데 다르게 쓴 부분 있었음.
        ret += recur(board, depth+1);
        // board = vector<vector<int>>(board.size(), vector<int>(board.size(), 0)); 보드를 다 날리지 않고 이전 상태로만 돌아간다
        board.clear();
        copy(origin.begin(), origin.end(), back_inserter(board));
    }
    return ret;
}

int solution(int n) {
    int answer = 0;
    if(n == 1)
        return 1;

    vector<vector<int>> board = vector<vector<int>>(n, vector<int>(n, 0));
    for(int col = 0; col < board.size(); ++col)
    {
        check_board(board, 0, col);
        answer += recur(board, 1);
        board = vector<vector<int>>(n, vector<int>(n, 0));
    }
    return answer;
}

int main()
{
    int n = 5;
    solution(n);

    return 0;
}