#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
동적계획법으로 풀이가 가능하다. 이때, 반복되는 부분문제와 최적 부분구조가 성립해야한다.
여기서 각 상태를 나타내는 방법은 현재까지 내려온 행과, 이전에 밟은 열의 정보가 필요하다.
이외의 정보는 DP 테이블을 구성하는데 필수적이지는 않다.

그럼 다음과 같이 점화식을 구할 수 있다.
DP[현재 행 번호][이번에 밟은 열 번호] = 현재 행까지 왔을 때 최대 값 저장

부분구조가 성립하는지 확인하기: r: 현재 행, C: 현재 열, !C: C와 안겹치는 모든 열
DP[r][C] = max(DP[r-1][!C]) + CurrentRow[C] (c는 C와 안겹치는 모든 가능한 모든 최선의 값)

-제한사항-
행의 개수 N : 100,000 이하의 자연수
열의 개수는 4개이고, 땅(land)은 2차원 배열로 주어집니다.
점수 : 100 이하의 자연수
*/

using namespace std;

void printLand(vector<vector<int>>& land)
{
    for(int i=0; i<land.size(); i++)
    {
        for(int j=0; j<land[0].size(); ++j)
        {
            cout << land[i][j];
            if(j == land[0].size()-1)
                cout << endl;
            else
                cout << " ";
        }
    }
}

void inputParser(string& input, vector<vector<int>>& land)
{
    int colnum = 0;
    int row = 0;
    for(char c : input)
    {
        if(c == ']')
        {
            row++;
            continue;
        }
        if(c == '[')
        {
            colnum = 0;
            continue;
        }
        if(c == ',')
        {
            continue;
        }
        land[row][colnum++] = static_cast<int>(c-'0');
    }
}

int DP[100001][4];

int solution(vector<vector<int> > land)
{
    int answer = 0;

    //초기화: 0번 행은 그대로일 것임.
    for(int i=0; i<land[0].size(); ++i)
        DP[0][i] = land[0][i];

    for(int row=1; row < land.size(); ++row)
    {
        for(int col=0; col < 4; ++col)
        {
            int lastMax = 0;
            // DP[row][col] = max(DP[row-1][!col]) + current col
            for(int i=0; i<4; ++i)
            {
                if(col == i)
                    continue;
                lastMax = max(lastMax, DP[row-1][i]);
            }
            DP[row][col] = lastMax + land[row][col];
        }
    }
    
    for(int i=0; i<4; ++i)
    {
        answer = max(answer, DP[land.size()-1][i]);
    }

    return answer;
}

int main()
{
    vector<int> cols(4);
    vector<vector<int>> land(3, cols);

    string input = "[[1,2,3,5],[5,6,7,8],[4,3,2,1]]";
    inputParser(input, land);

    printLand(land);
    int answer = solution(land);

    cout << answer << endl;
    return 0;
}