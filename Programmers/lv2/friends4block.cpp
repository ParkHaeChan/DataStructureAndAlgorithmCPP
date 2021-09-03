/*
프렌즈4블록
https://programmers.co.kr/learn/courses/30/lessons/17679

같은 모양의 카카오프렌즈 블록이 2×2 형태로 4개가 붙어있을 경우 사라지면서 점수를 얻는 게임이다.
같은 블록은 여러 2×2에 포함될 수 있으며, 지워지는 조건에 만족하는 2×2 모양이 여러 개 있다면 한꺼번에 지워진다.
블록이 지워진 후에 위에 있는 블록이 아래로 떨어져 빈 공간을 채우게 된다.
만약 빈 공간을 채운 후에 다시 2×2 형태로 같은 모양의 블록이 모이면 다시 지워지고 떨어지고를 반복하게 된다.

?:
입력으로 블록의 첫 배치가 주어졌을 때, 지워지는 블록은 모두 몇 개인지 판단하는 프로그램을 제작하라.

!!!:
입력으로 판의 높이 m, 폭 n과 판의 배치 정보 board가 들어온다.
2 ≦ n, m ≦ 30
board는 길이 n인 문자열 m개의 배열로 주어진다. 블록을 나타내는 문자는 대문자 A에서 Z가 사용된다.

시도1)
보드를 순회하며 삭제 가능한 위치를 모두 찾아서 표시를 남긴다.
표시된곳을 삭제(0표시)후 이어붙인다. (보드를 새로 구성하는 식으로 구현)
삭제할게 없을 때 까지 반복한다. --> 삭제된 곳을 누적해서 계속 세므로 이전과 삭제된 수가 같으면 종료하도록 변경
*/

#include <string>
#include <vector>

using namespace std;

bool check_del(int r, int c, vector<string>& board)
{
    char cur = board[r][c];
    if(board[r+1][c] == cur && board[r][c+1] == cur && board[r+1][c+1] == cur)
        return true;
    return false;
}

void del_board(int r, int c, vector<string>& board)
{
    board[r][c] = '0';
    board[r+1][c] = '0';
    board[r][c+1] = '0';
    board[r+1][c+1] = '0';
}

int solution(int m, int n, vector<string> board) {
    int answer = 0;

    int deleted=0, last_deleted=0;
    do{
        last_deleted = deleted;
        deleted = 0;
        vector<string> temp;
        copy(board.begin(), board.end(), back_inserter(temp));
        for(int r=0; r<m-1; ++r)
        {
            for(int c=0; c<n; ++c)
            {   // 현 위치가 삭제될 2X2블록의 좌측 상단인지 확인한다
                if(check_del(r,c, board))
                    del_board(r,c, temp);   // 삭제 수행(사본)
            }
        }
        board.clear();
        copy(temp.begin(), temp.end(), back_inserter(board));
        temp = vector<string>(m, string(n, '0'));

        // 삭제된 빈칸을 위에서 채운다.
        for(int c=0; c<n; ++c)
        {   // 각 열을 돌면서
            string column = "";
            for(int r=m-1; r>=0; --r)   // 아래서 부터
                if(board[r][c] != '0')  // 삭제된 구간 제외하고 이어붙인다.
                    column += board[r][c];
                else    // 실제 삭제된 수 센다
                    deleted++;
            // 바닥부터 열을 보드에 채운다
            for(int r=m-1, cnt=0; cnt<column.size(); cnt++, --r)
            {
                temp[r][c] = column[cnt];
            }
        }
        board.clear();
        copy(temp.begin(), temp.end(), back_inserter(board));
    } while (deleted != last_deleted);

    answer = deleted;
    return answer;
}

int main()
{
    int m = 6;
    int n = 6;
    vector<string> board = {"TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ"};
    // int m = 4;
    // int n = 5;
    // vector<string> board = {"CCBDE", "AAADE", "AAABF", "CCBBF"};

    solution(m,n, board);

    return 0;
}