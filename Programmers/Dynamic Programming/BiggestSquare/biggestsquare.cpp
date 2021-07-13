#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[1001][1001] = {0};

int solution(vector<vector<int>> board)
{
    int answer = 0;

    // 2차원 배열 순회용
    int row = board.size();
    int col = board[0].size();
	
	/* 2차원 벡터로 초기화 하고 싶으면 이렇게 한다.
	vector<int> colvect(col+1, 0);
    vector<vector<int>> dp(row+1, colvect);
	*/
    
    // 일반적인 순서로 순회해도 dp table을 구성할 수 있음
    // dp정의: dp[i][j] = 현재 위치(i,j)를 구성할 최대 정사각형 오른쪽 최하단으로 봤을 때
    // 그 정사각형의 한 변 길이를 dp 테이블에 저장
    // 현재 위치(board[i][j])가 0이면 정사각형 구성 불가하고,
    // 1이면, 인접한 위치(3군데)에서 dp테이블에 저장된 값 중 최소 값을 가지고 정사각형을 구성할 수 있다
    // 즉, dp[i][j] = min(dp[i-1][j], dp[i-1][j-1], dp[i][j-1]) + 1(현 위치 크기);
    for(int i=1; i<=row; ++i)
    {
        for(int j=1; j<=col; ++j)
        {
            if(board[i-1][j-1] != 0)    // 이 조건으로 미리 걸러내지 않으면 시간초과가 발생하므로 주의
            {
                dp[i][j] = min(dp[i-1][j], min(dp[i-1][j-1], dp[i][j-1])) + 1;
            }
            answer = max(answer, dp[i][j]);
        }
    }

    // dp 테이블에 저장된 값은 한 변 길이이므로 넓이를 반환하기 위해 제곱한다.
    return answer*answer;
}