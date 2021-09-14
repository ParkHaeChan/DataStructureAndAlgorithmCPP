/*
멀리 뛰기
https://programmers.co.kr/learn/courses/30/lessons/12914

효진이는 멀리 뛰기를 연습하고 있습니다. 효진이는 한번에 1칸, 또는 2칸을 뛸 수 있습니다. 칸이 총 4개 있을 때, 효진이는
(1칸, 1칸, 1칸, 1칸)
(1칸, 2칸, 1칸)
(1칸, 1칸, 2칸)
(2칸, 1칸, 1칸)
(2칸, 2칸)
의 5가지 방법으로 맨 끝 칸에 도달할 수 있습니다. 
멀리뛰기에 사용될 칸의 수 n이 주어질 때, 효진이가 끝에 도달하는 방법이 몇 가지인지 알아내, 
여기에 1234567를 나눈 나머지를 리턴하는 함수, solution을 완성하세요. 
예를 들어 4가 입력된다면, 5를 return하면 됩니다.

!!!:
n은 1 이상, 2000 이하인 정수입니다.

시도1)
n이 2000까지 갈 수 있으므로 완전 탐색 방식으로는 시간 초과가 발생할 것이다.
즉, 동적계획법 방식을 사용하여야 한다.
효진이는 1칸 또는 2칸을 뛸 수 있으므로
n칸을 뛰어가는 가짓수는 n-1칸에서 1칸을 뛰는 가짓수와 n-2에서 2칸을 뛰는 가짓수로 구할 수 있다.
즉, 점화식 DP[N] = DP[N-1] + DP[N-2]이다.
이를 위해선 초기값 2개 이상이 필요하다.
DP[0] = 0;
DP[1] = 1 --> 1칸 점프
DP[2] = 2 --> 1칸씩 2회 점프, 2칸씩 1회 점프
*/

#include <string>
#include <vector>

using namespace std;

long long solution(int n) {
    long long answer = 0;
    const int DIV = 1234567;

    vector<long long> DP(n+1, 0);
    DP[1] = 1;
    DP[2] = 2;
    
    for(int i=3; i<=n; ++i)
        DP[i] = (DP[i-1]%DIV + DP[i-2]%DIV)%DIV;

    return answer = DP[n];
}

int main()
{
    int n = 4;
    solution(n);
}