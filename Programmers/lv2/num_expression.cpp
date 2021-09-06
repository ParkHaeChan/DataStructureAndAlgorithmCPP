/*
숫자의 표현
https://programmers.co.kr/learn/courses/30/lessons/12924

Finn은 요즘 수학공부에 빠져 있습니다. 
수학 공부를 하던 Finn은 자연수 n을 연속한 자연수들로 표현 하는 방법이 여러개라는 사실을 알게 되었습니다. 

예를들어 15는 다음과 같이 4가지로 표현 할 수 있습니다.
1 + 2 + 3 + 4 + 5 = 15
4 + 5 + 6 = 15
7 + 8 = 15
15 = 15
자연수 n이 매개변수로 주어질 때, 연속된 자연수들로 n을 표현하는 방법의 수를 return하는 solution를 완성해주세요.

제한사항
n은 10,000 이하의 자연수 입니다.

시도1)
n이 작고, 저런 경우는 모든 경우를 시도해 봐야 확인할 수 있다고 판단
연속된 합을 사용하므로, 부분합 배열을 사용하면 좋을 것 같음.
시간초과로 효율성 테스트 실패
10000개에서 2개 뽑는 경우를 모두 시도하는데서 시간초과가 발생한듯 함
불필요한 계산 줄이도록 수정

시도2)
합이 n을 넘어가는 경우 바로 종료하도록 조치 후 통과

*/

#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;

    // 부분합 배열
    vector<int> partsum(n+1, 0);
    for(int i=1; i<=n; ++i)
    {
        partsum[i] += partsum[i-1] + i;
    }
    // 시작과 끝을 정하는 경우(조합)
    for(int start = 0; start < n; ++start)
    {
        for(int end = start+1; end <= n; ++end)
        {
            if(partsum[end]-partsum[start] >= n)
            {
                if(partsum[end]-partsum[start] == n)
                    answer++;
                break;  // 이 이상으로는 발생x
            }
        }
    }

    return answer;
}

int main()
{
    int n = 15;
    solution(n);

    return 0;
}