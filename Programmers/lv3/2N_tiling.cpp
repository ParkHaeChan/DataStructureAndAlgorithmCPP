/*
2 x n 타일링
https://programmers.co.kr/learn/courses/30/lessons/12900

가로 길이가 2이고 세로의 길이가 1인 직사각형모양의 타일이 있습니다. 
이 직사각형 타일을 이용하여 세로의 길이가 2이고 가로의 길이가 n인 바닥을 가득 채우려고 합니다. 
타일을 채울 때는 다음과 같이 2가지 방법이 있습니다.

타일을 가로로 배치 하는 경우
타일을 세로로 배치 하는 경우
예를들어서 n이 7인 직사각형은 다음과 같이 채울 수 있습니다.

직사각형의 가로의 길이 n이 매개변수로 주어질 때, 이 직사각형을 채우는 방법의 수를 return 하는 solution 함수를 완성해주세요.

제한사항
가로의 길이 n은 60,000이하의 자연수 입니다.
경우의 수가 많아 질 수 있으므로, 경우의 수를 1,000,000,007으로 나눈 나머지를 return해주세요.

해설
유명한? 동적계획법 문제이다.
마지막 칸을 어떤 방식으로 채우냐에 따라 가지수가 분기된다.

n = 1 -> 1가지
n = 2 -> 2가지
n = 3 -> 마지막 한칸 세우고 나머지 2칸은 위에서 2가지이므로 2*1 = 2가지
      -> 마지막칸 눕혀서 둘 경우 처음은 1칸 세워둬야하므로 1가지 총: 3가지
n = 4 -> 마지막을 세우는 경우는 남은 3칸은 n=3인 경우와 같으므로 3가지
      -> 마지막을 눕히는 경우 남은 2칸은 n=2인 경우와 같으므로 2가지 총: 5가지
n = 5 -> 세우는 경우 n=4 -> 5가지, 눕 -> n=3 3가지 총: 8가지
피보나치 수열과 같음을 확인할 수 있다.
추가로 DIV로 나눠주는 것을 잊지 말 것
*/

#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    const int DIV = 1000000007;

    vector<int> DP(n+1, 0);

    DP[1] = 1;
    DP[2] = 2;
    for(int i=3; i<=n; ++i)
    {
        DP[i] = (DP[i-1]%DIV + DP[i-2]%DIV)%DIV;
    }
    answer = DP[n];

    return answer;
}

int main()
{
    int n = 4;
    solution(n);

    return 0;
}
