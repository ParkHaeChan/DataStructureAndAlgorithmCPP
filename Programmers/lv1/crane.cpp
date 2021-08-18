/*
크레인 인형뽑기 게임
https://programmers.co.kr/learn/courses/30/lessons/64061

?:
게임 화면의 격자의 상태가 담긴 2차원 배열 board와 인형을 집기 위해 크레인을 작동시킨 위치가 담긴 배열 moves가 매개변수로 주어질 때,
크레인을 모두 작동시킨 후 터트려져 사라진 인형의 개수를 return 하도록 solution 함수를 완성해주세요.

!!!:
board 배열은 2차원 배열로 크기는 "5 x 5" 이상 "30 x 30" 이하입니다.
board의 각 칸에는 0 이상 100 이하인 정수가 담겨있습니다.
0은 빈 칸을 나타냅니다.
1 ~ 100의 각 숫자는 각기 다른 인형의 모양을 의미하며 같은 숫자는 같은 모양의 인형을 나타냅니다.
moves 배열의 크기는 1 이상 1,000 이하입니다.
moves 배열 각 원소들의 값은 1 이상이며 board 배열의 가로 크기 이하인 자연수입니다.

시도1)
moves가 가리키는 곳에서 값을 가져와서 stack에 넣는다.
stack에 넣을 때 top과 같으면 삭제가 발생한다. (카운트 센다)
*/

#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;

    int N = board.size();
    stack<int> bucket;
    // 모든 moves에 대해
    for(int cur : moves)
    {
        // 이번에 올릴 위치
        int dollnum = 0;
        int i;
        for(i = 0; i<N; ++i)    // 실제 index는 (0 ~ N-1)
        {
            if(board[i][cur-1] == 0)   // 빈칸
                continue;
            else
            {
                dollnum = board[i][cur-1];
                board[i][cur-1] = 0;    // 뽑았으므로 board에서 지운다
                break;
            }
        }
        // 빈칸에 시도한 경우
        if(dollnum == 0)
            continue;
        // 인형을 stack에 넣는다
        if(bucket.empty())
            bucket.push(dollnum);
        else
        {   // 같은 인형이 만나면
            if(bucket.top() == dollnum)
            {
                bucket.pop();
                answer += 2;
            }
            else
                bucket.push(dollnum);
        }
    }

    return answer;
}

int main()
{
    vector<vector<int>> board = {{0,0,0,0,0},{0,0,1,0,3},{0,2,5,0,1},{4,2,4,4,2},{3,5,1,3,1}};
    vector<int> moves = {1,5,3,5,1,2,1,4};

    solution(board, moves);

    return 0;
}