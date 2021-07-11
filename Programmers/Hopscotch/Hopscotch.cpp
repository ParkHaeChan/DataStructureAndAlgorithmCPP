#include <iostream>
#include <vector>

/*
동적계획법으로 풀이가 가능하다. 이때, 반복되는 부분문제와 최적 부분구조가 성립해야한다.
여기서 각 상태를 나타내는 방법은 현재까지 내려온 행과, 이전에 밟은 열의 정보가 필요하다.
이외의 정보는 DP 테이블을 구성하는데 필수적이지는 않다.

그럼 다음과 같이 점화식을 구할 수 있다.
DP[현재 행 번호][이전에 밟은 열 번호] = 현재 행까지 왔을 때 최대 값 저장

부분구조가 성립하는지 확인하기: r: 현재 행, C: 현재 열, c: C와 안겹치는 모든 열
DP[r][C] = DP[r-1][c] + CurrentRow[C] (c는 C와 안겹치는 모든 가능한 모든 최선의 값)
*/

using namespace std;

int solution(vector<vector<int> > land)
{
    int answer = 0;

    

    return answer;
}