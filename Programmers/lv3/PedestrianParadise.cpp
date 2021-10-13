/*
보행자 천국
https://programmers.co.kr/learn/courses/30/lessons/1832

도시 중심가의 지도는 m × n 크기의 격자 모양 배열 city_map으로 주어진다. 자동차는 오른쪽 또는 아래 방향으로 한 칸씩 이동 가능하다.

city_map[i][j]에는 도로의 상황을 나타내는 값이 저장되어 있다.

0인 경우에는 자동차가 자유롭게 지나갈 수 있다.
1인 경우에는 자동차 통행이 금지되어 지나갈 수 없다.
2인 경우는 보행자 안전을 위해 좌회전이나 우회전이 금지된다. (왼쪽에서 오던 차는 오른쪽으로만, 위에서 오던 차는 아래쪽으로만 진행 가능하다)

?:
도시의 도로 상태가 입력으로 주어졌을 때, 왼쪽 위의 출발점에서 오른쪽 아래 도착점까지 
자동차로 이동 가능한 전체 가능한 경로 수를 출력하는 프로그램을 작성하라
가능한 경로 수를 20170805로 나눈 나머지 값을 출력하라.

!!!:
1 <= m, n <= 500
city_map의 크기는 m × n이다.
배열의 모든 원소의 값은 0, 1, 2 중 하나이다.
출발점의 좌표는 (0, 0), 도착점의 좌표는 (m - 1, n - 1)이다.
출발점과 도착점의 city_map[i][j] 값은 0이다.

시도1)
모든 위치에서 분기하는 방식으로는 (재귀) 매우 느릴 수 있다.
각 지점까지의 경우의 수를 구하여 누적해 계산하는 방식을 사용해야한다.
동적 계획법 문제로 볼 수 있다.
재귀를 사용하지 않는 동적계획법의 경우는
다음 위치를 계산하기 위한 이전 위치들을 얻을 수 있도록, DP table을 채워나가야 한다.

시도2)
현위치를 계산하기 위해 이전 옆과 위를 확인 했는데 회전 불가능인 경우는 재귀적으로 타고 올라가서 경우의 수를 구해야 되는 문제가 있다.
이 표지판을 만나면 즉시 다음 위치(직진한 위치)에 경우의 수를 계산해주면 이런 처리를 따로 안해도 될 것 같다.
행렬 범위 주의

시도3)
이 방법은 덮어쓰면서 문제가 생기는 것 같다.
DP구성을 DP[m][n][2]로 세분화하여 가로로 온 경우와 세로로 온 경우를 따로 저장하는 방식을 쓰는게 나을 것 같다.
3차원 행렬이므로 자료형을 int로 바꿔 최적화. (이땐 모듈러 연산을 해주면서 계산해야함)
코드가 복잡해져서 이전 시도1,2 코드는 폐기함
통과
*/

#include <vector>

using namespace std;

int MOD = 20170805;

bool InRange(int r, int c, int m, int n)
{
    if(0<=r && r<m && 0<=c && c < n)
        return true;
    return false;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    int answer = 0;

    vector<vector<vector<int>>> DP(m, vector<vector<int>>(n, vector<int>(2, 0)));
    // 초기 상태: 맨 위쪽 행의 경우를 계산한다
    for(int i=0; i<n; ++i)
    {
        if(city_map[0][i] == 1)
            break;  // 통행금지라 더 이상 진행X (뒤는 더 볼 필요 없이 다 0)
        
        DP[0][i][0] = 1;   // 옆
        DP[0][i][1] = 0;   // 위
    }
    // DP테이블 채우기
    for(int r=1; r<m; ++r)
    {
        for(int c=0; c<n; ++c)
        {
            if(city_map[r][c] == 1)
                continue;   // 통행금지
            // DP[r][c] = DP[r-1][c] + DP[r][c-1]
            // 위에서 온 경우
            if(city_map[r-1][c] == 2)
            {   // 위에서 내려온 경우만 포함
                DP[r][c][1] = DP[r-1][c][1];
            }
            else
                DP[r][c][1] = (DP[r-1][c][0]%MOD + DP[r-1][c][1]%MOD)%MOD;
            // 옆에서 온 경우
            if(InRange(r,c-1,m,n))
            {
                if(city_map[r][c-1] == 2)
                {   // 옆에서 온 경우만 포함
                    DP[r][c][0] = DP[r][c-1][0];
                }
                else
                    DP[r][c][0] = (DP[r][c-1][0]%MOD + DP[r][c-1][1]%MOD)%MOD;
            }
        }
    }
    answer = (DP[m-1][n-1][0]%MOD + DP[m-1][n-1][1]%MOD)%MOD;

    return answer;
}

int main()
{
    int m = 3;
    int n = 6;
    vector<vector<int>> city_map = {{0, 2, 0, 0, 0, 2}, {0, 0, 2, 0, 1, 0}, {1, 0, 0, 2, 2, 0}};
    solution(m, n, city_map);

    return 0;
}