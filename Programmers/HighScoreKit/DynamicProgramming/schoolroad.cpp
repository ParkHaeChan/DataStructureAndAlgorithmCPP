#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
장애물이 있는 최단 경로 경우의 수 문제이다.
일단 맨 가쪽으로 가는 경우는 모두 1로 초기화하고 그 다음은
최단경로로 움직이므로 왼쪽에서 온 경우와 위쪽에서 온 경우를 더해 주면 된다.
장애물을 고려하지 않으면 지도[i][j] 위치 = 지도[i-1][j] + 지도[i][j-1] 이다.

맨 위 행부터 시작해서 오른쪽으로 진행하며 경우의 수를 채워나가는데,
장애물을 만나면 그 뒤로는 경우의 수를 0으로 지정한다.
그렇게 학교 위치까지 진행한다.

오답: 되는 경우가 1경우 뿐이다.

그래서 생각을 바꿔서
모든 경우를 구한 뒤 물 웅덩이를 거치는 경우만큼 빼주는 방식으로 바꿔서 생각해 보았다.
*/

int failed_solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    const long long INF = 987654321;  // 물웅덩이 표시용
    const long long DIV = 1000000007;
    
    // 지도 초기화 (문제 조건에 맞추기 위해 n,m 보다 1 더 크게 할 것)
    vector<long long> cols(m+1, 0);
    vector<vector<long long>> RoadMap(n+1, cols);
    
    // 지도에 웅덩이 표시
    for(auto pos : puddles)
    {
        RoadMap[pos[0]][pos[1]] = INF;  
    }
    
    // 제한사항: 집과 학교가 물에 잠긴 경우는 주어지지 않는다.
    RoadMap[1][1] = 1;
    
    // 지도 순회하며 각 위치에 도달하는 최단 경우의 수 채우기
    for(int row=1; row<=n; ++row)
    {
        for(int col=1; col<=m; ++col)
        {
            // 이미 계산함
            if(row == 1 && col == 1)
                continue;
            
            // 물 웅덩이 위치면
            if(RoadMap[row][col] == INF)
            {
                // 다음 위치 계산시 영향 미치지 않도록 0으로 초기화
                RoadMap[row][col] = 0;
                continue;
            }
            else
            {
                RoadMap[row][col] = (RoadMap[row-1][col]%DIV + RoadMap[row][col-1]%DIV)%DIV;
            }
        }
    }
    answer = static_cast<int>(RoadMap[n][m]);
    
    return answer;
}

//모든 경우를 구한 뒤 물 웅덩이를 거치는 경우만큼 빼주는 방식으로 바꿔서 생각해 보았다.
// 장애물 없을 때 전체 경우의 수 (m-1 + n-1)! / (m-1)! * (n-1)!
// 이는 int로 처리하기 너무 큰 수가 된다.
// 이항 계수를 덧셈으로 구하는 방법을 써서 DP[100][100]을 미리 채워 놓고
// 각 경우의 수를 DP테이블을 참조하는 식으로 구현한다.
// 이항계수 공식: nCr = n-1Cr-1 + n-1Cr
int failed_solution2(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    
    vector<long long> cols(101, 0);
    vector<vector<long long>> DP(101, cols);
    const int DIV = 1000000007;
    
    // DP 테이블 초기화 0번열: 1, 행,열 번호 같으면 = 1
    for(auto col : DP)
        col[0] = 1;
    for(int i=1; i<DP.size(); ++i)
        DP[i][i] = 1;
    
    // 이항계수 계산
    for(int row=2; row<=100; ++row)
    {
        for(int col=1; col<=100; ++col)
        {
            DP[row][col] = (DP[row-1][col-1]%DIV + DP[row-1][col]%DIV)%DIV;
        }
    }
    int h2s = DP[n+m-2][n-1];   // home-school
    
    // 웅덩이를 거쳐가는 경우]
    int hps; // home-puddle-school
    for(auto pos : puddles)
    {
        // 집에서 웅덩이로 가는 최단 경우
        int row = pos[0]-1;
        int col = pos[1]-1;
        int n1 = row+col;
        int r = n1 - row;
        int h2p = DP[n1][r];
        // 웅덩이에서 학교로 가는 최단 경우
        int n2 = n - row;
        r = m - col;
        int p2s = DP[n2][r];
        // 곱연산으로 이어준다 (나머지 연산의 곱셈 역원 필요할 듯)
        hps = h2p * p2s;
        h2s -= hps;
    }
    answer = h2s;
    
    return answer;
}

// 뭔가 말이 안되게 너무 어려운 듯하여 다시 잘 고민해 봤다가
// 처음에 했던 시도가 그나마 정상적인것 같아서 다시 살펴 봤는데
// 문제에서 주는 물웅덩이 좌표랑 MAP에서 사용하는 index가 바뀌어 들어가야 한다는 것을 간과함
// 즉, (X,Y) 좌표 순으로 표현해서 (3,2)를 주면 실제 MAP행렬에서는 [2][3]을 접근해야 함
// 그 문제만 고쳐주니 바로 통과됨...(내 2시간ㅠㅠ)
int solution(int m, int n, vector<vector<int>> puddles) {

    const int INF = 987654321;  // 물웅덩이 표시용
    const int DIV = 1000000007;
    
    // 지도 초기화 (문제 조건에 맞추기 위해 n,m 보다 1 더 크게 할 것)
    vector<int> cols(m+1, 0);
    vector<vector<int>> RoadMap(n+1, cols);
    
    // 지도에 웅덩이 표시
    for(auto pos : puddles)
    {
        //좌표(X,Y) => 행렬[Y][X]로 접근
        RoadMap[pos[1]][pos[0]] = INF;  
    }
    
    // 제한사항: 집과 학교가 물에 잠긴 경우는 주어지지 않는다.
    RoadMap[1][1] = 1;
    
    // 지도 순회하며 각 위치에 도달하는 최단 경우의 수 채우기
    for(int row=1; row<=n; ++row)
    {
        for(int col=1; col<=m; ++col)
        {
            // 이미 계산함
            if(row == 1 && col == 1)
                continue;
            
            // 물 웅덩이 위치면
            if(RoadMap[row][col] == INF)
            {
                // 다음 위치 계산시 영향 미치지 않도록 0으로 초기화
                RoadMap[row][col] = 0;
                continue;
            }
            else
            {
                RoadMap[row][col] = (RoadMap[row-1][col]%DIV + RoadMap[row][col-1]%DIV)%DIV;
            }
        }
    }
    return RoadMap[n][m];
}

int main()
{
    int m = 4, n = 3;
    vector<vector<int>> puddles{{2,2}};

    cout << solution(m, n, puddles);

    return 0;
}