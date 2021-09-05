/*
가장 큰 정사각형 찾기
https://programmers.co.kr/learn/courses/30/lessons/12905

1와 0로 채워진 표(board)가 있습니다. 표 1칸은 1 x 1 의 정사각형으로 이루어져 있습니다. 
표에서 1로 이루어진 가장 큰 정사각형을 찾아 넓이를 return 하는 solution 함수를 완성해 주세요. 
(단, 정사각형이란 축에 평행한 정사각형을 말합니다.)

시도1)
대표적인 DP문제이다.
자세한 해설은 https://github.com/ParkHaeChan/DataStructureAndAlgorithmCPP/blob/main/Programmers/Dynamic%20Programming/BiggestSquare/biggestsquare.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> board)
{
    int answer = 0;

    int R = board.size();
    int C = board[0].size();
    int max_length = 0;
    // DP table 초기화
    vector<vector<int>> DP(R, vector<int>(C, 0));
    // DP[i][j] 정의 : i,j 위치를 정사각형 오른족 하단 위치로 봤을 떄 구성가능한 최대 정사각형 한변 길이 저장
    // 점화식: DP[i][j] = min( DP[i][j-1], DP[i-1][j], DP[i-1][j-1]) + 1 (단, [i][j] 위치가 1로 채워져 있는 경우만)

    // 첫 행(0번)과 열(0번)은 DP table과 보드 상태가 동일할 것이다.
    for(int b=0; b<DP[0].size(); b++)
    {
        DP[0][b] = board[0][b];
        max_length = max(max_length, DP[0][b]);
    }
    for(int b=0; b<DP.size(); b++)
    {
        DP[b][0] = board[b][0];
        max_length = max(max_length, DP[b][0]);
    }

    for(int i=1; i<R; ++i)
    {
        for(int j=1; j<C; ++j)
        {
            if(board[i][j] == 0)
                continue; // 이 위치에서는 정사각형을 구성할 수 없다
            
            DP[i][j] = min(min(DP[i][j-1], DP[i-1][j]), DP[i-1][j-1]) + 1;
            max_length = max(max_length, DP[i][j]);
        }
    }

    return answer = max_length*max_length;
}

int main()
{
    //vector<vector<int>> board = {{0,1,1,1},{1,1,1,1},{1,1,1,1},{0,0,1,0}};
    vector<vector<int>> board = {{0,0,1,1},{1,1,1,1}};

    solution(board);

    return 0;
}