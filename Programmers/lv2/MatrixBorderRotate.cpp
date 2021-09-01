/*
행렬 테두리 회전하기
https://programmers.co.kr/learn/courses/30/lessons/77485

rows x columns 크기인 행렬이 있습니다. 
행렬에는 1부터 rows x columns까지의 숫자가 한 줄씩 순서대로 적혀있습니다. 
이 행렬에서 직사각형 모양의 범위를 여러 번 선택해, 테두리 부분에 있는 숫자들을 시계방향으로 회전시키려 합니다.
각 회전은 (x1, y1, x2, y2)인 정수 4개로 표현하며, 그 의미는 다음과 같습니다.

x1 행 y1 열부터 x2 행 y2 열까지의 영역에 해당하는 직사각형에서 테두리에 있는 숫자들을 한 칸씩 시계방향으로 회전합니다.

?:
행렬의 세로 길이(행 개수) rows, 가로 길이(열 개수) columns, 그리고 회전들의 목록 queries가 주어질 때, 
각 회전들을 배열에 적용한 뒤, 그 회전에 의해 위치가 바뀐 숫자들 중 가장 작은 숫자들을 순서대로 배열에 담아 return 하도록 solution 함수를 완성해주세요.

!!!:
rows는 2 이상 100 이하인 자연수입니다.
columns는 2 이상 100 이하인 자연수입니다.
처음에 행렬에는 가로 방향으로 숫자가 1부터 하나씩 증가하면서 적혀있습니다.
즉, 아무 회전도 하지 않았을 때, i 행 j 열에 있는 숫자는 ((i-1) x columns + j)입니다.
queries의 행의 개수(회전의 개수)는 1 이상 10,000 이하입니다.
queries의 각 행은 4개의 정수 [x1, y1, x2, y2]입니다.
x1 행 y1 열부터 x2 행 y2 열까지 영역의 테두리를 시계방향으로 회전한다는 뜻입니다.
1 ≤ x1 < x2 ≤ rows, 1 ≤ y1 < y2 ≤ columns입니다.
모든 회전은 순서대로 이루어집니다.
예를 들어, 두 번째 회전에 대한 답은 첫 번째 회전을 실행한 다음, 그 상태에서 두 번째 회전을 실행했을 때 이동한 숫자 중 최솟값을 구하면 됩니다.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int rotate(int r1, int c1, int r2, int c2, vector<vector<int>>& board)
{
    const int INF = 987654321;
    int min_val = INF;

    vector<int> temp;
    // 테두리 값 접근 (코너 부분 값 안 겹치도록 주의: 반복문에서 <로 쓴다)
    // 윗변: r1, c1에서 시작-> r1, c2까지
    for(int c=c1; c<c2; ++c)
        temp.push_back(board[r1][c]);
    // 오른쪽변: r1, c2에서 시작 -> r2, c2까지
    for(int r=r1; r<r2; ++r)
        temp.push_back(board[r][c2]);
    // 아랫변: r2, c2에서 시작 -> r2, c1까지 (반대)
    for(int c=c2; c>c1; --c)
        temp.push_back(board[r2][c]);
    // 왼쪽변: r2, c1에서 시작 -> r1, c1까지 (반대)
    for(int r=r2; r>r1; --r)
        temp.push_back(board[r][c1]);

    // 한칸씩 이동할 것이므로 맨끝이 첨으로 가고 나머지는 한칸씩 옮긴다.
    int last = temp[temp.size()-1];
    temp.pop_back();
    temp.insert(temp.begin(), last);

    // 이동: temp에서 이미 옮겼으므로 순서대로 적용
    int idx = 0;
    // 윗변: r1, c1에서 시작-> r1, c2까지
    for(int c=c1; c<c2; ++c)
        board[r1][c] = temp[idx++];
    // 오른쪽변: r1, c2에서 시작 -> r2, c2까지
    for(int r=r1; r<r2; ++r)
        board[r][c2] = temp[idx++];
    // 아랫변: r2, c2에서 시작 -> r2, c1까지 (반대)
    for(int c=c2; c>c1; --c)
        board[r2][c] = temp[idx++];
    // 왼쪽변: r2, c1에서 시작 -> r1, c1까지 (반대)
    for(int r=r2; r>r1; --r)
        board[r][c1] = temp[idx++];

    // 최소값 찾기
    for(int v=0; v<temp.size(); ++v)
    {
        min_val = min(min_val, temp[v]);
    }

    return min_val;
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;

    // 원본 배열(비교용)
    vector<vector<int>> board(rows, vector<int>(columns, 0));
    for(int r=0; r<rows; ++r)
    {
        for(int c=0; c<columns; ++c)
        {
            board[r][c] = r*columns+c+1;
        }
    }

    // 쿼리 돌면서 회전 적용
    for(auto e: queries)
    {
        int r1 = e[0]-1, c1 = e[1]-1;
        int r2 = e[2]-1, c2 = e[3]-1;
        // 테두리 돌리고 이때 움직이는 최소값 저장
        answer.push_back(rotate(r1, c1, r2, c2, board));
    }

    return answer;
}

int main()
{
    // int rows = 6;
    // int columns = 6;
    // vector<vector<int>> queries = {{2,2,5,4},{3,3,6,6},{5,1,6,3}};

    int rows=3, columns=3;
    vector<vector<int>> queries = {{1,1,2,2},{1,2,2,3},{2,1,3,2},{2,2,3,3}};


    solution(rows, columns, queries);

    return 0;
}