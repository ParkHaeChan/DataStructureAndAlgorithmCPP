/*
땅따먹기
https://programmers.co.kr/learn/courses/30/lessons/12913

풀었던 문제이다.
https://github.com/ParkHaeChan/DataStructureAndAlgorithmCPP/blob/main/Programmers/Dynamic%20Programming/Hopscotch/Hopscotch.cpp

!!!:
행의 개수 N : 100,000 이하의 자연수
열의 개수는 4개이고, 땅(land)은 2차원 배열로 주어집니다.
점수 : 100 이하의 자연수
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int> > land)
{
    int answer = 0;
    int R = land.size();
    int C = land[0].size();

    vector<vector<int>> DP(R, vector<int>(C, 0));
    // DP[i][j] 점화식: 이전에 j번째를 밟았을 떄 i번째에서 얻을 수 있는 최고점
    // 초기 상태: DP[0] = land[0]
    DP[0] = land[0];

    for(int i=1; i<R; ++i)
    {
        
        for(int j=0; j<C; ++j)
        {
            // DP[i][k] = DP[i-1][j] + land[i][k]; (k는 land[i]중 가장 크면서 j와 같지 않음)
            for(int k=0; k<C; ++k)
            {
                if(k == j)
                    continue;
                DP[i][k] = max(DP[i][k], DP[i-1][j] + land[i][k]);
            }
        }
    }
    for(int j=0; j<C; ++j)
    {
        answer = max(answer, DP[R-1][j]);
    }

    return answer;
}

int main()
{
    vector<vector<int>> land = {{1,2,3,5},{5,6,7,8},{4,3,2,1}};
    solution(land);

    return 0;
}