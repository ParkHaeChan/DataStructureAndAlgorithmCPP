#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
동적계획법으로 풀이가 가능하다. 이때, 반복되는 부분문제와 최적 부분구조가 성립해야한다.
여기서 각 상태를 나타내는 방법은 현재까지 내려온 행과, 이번에 밟은 열의 정보가 필요하다.
이외의 정보는 DP 테이블을 구성하는데 필수적이지 않다.

그럼 다음과 같이 점화식을 구할 수 있다.
DP[현재 행 번호][이번에 밟은 열 번호] = 현재 행까지 왔을 때 최대 값 저장

부분구조가 성립하는지 확인하기: r: 현재 행, C: 현재 열, !C: C와 안겹치는 모든 열
DP[r][C] = max(DP[r-1][!C]) + land[r][C]

-제한사항-
행의 개수 N : 100,000 이하의 자연수
열의 개수는 4개이고, 땅(land)은 2차원 배열로 주어집니다.
점수 : 100 이하의 자연수
즉, DP[100000][4]로 모든 경우를 처리할 수 있다. (행은 0번부터 시작한다고 가정)
*/

int DP[100000][4];

int solution(vector<vector<int> > land)
{
    int answer = 0;

    //초기화: 초기에는 land의 0행이 최대이므로
    for(int i=0; i<4; ++i)
        DP[0][i] = land[0][i];
    
    //이후 각 행과 열에 대해 DP 테이블을 채워야 하므로 반복문은 DP행렬의 차원 + 내부 조건 처리 만큼 필요
    for(int row=1; row<land.size(); ++row)  //0 행은 이미 처리하였음
    {
        for(int col=0; col<4; ++col)
        {
            //DP[row][col] = max(DP[row-1][!col]) + land[row][col]
            int lastMax = 0;       //max(DP[row-1][!col] 저장용 변수
            for(int i=0; i<4; ++i)
            {
                if(i==col)  // 같은 열 연속으로 못가는 조건(!col)
                    continue;
                lastMax = max(lastMax, DP[row-1][i]);
            }
            DP[row][col] = lastMax + land[row][col];
        }
    }
    
    //정답은 마지막 행중 가장 큰 값
    for(int i=0; i<4; ++i)
        answer = max(answer, DP[land.size()-1][i]);

    return answer;
}

int main()
{
    vector<vector<int>> land{{1,2,3,5},{5,6,7,8},{4,3,2,1}};

    cout << solution(land) << endl;
    
    return 0;
}