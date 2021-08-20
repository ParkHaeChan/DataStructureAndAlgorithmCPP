/*
약수의 개수와 덧셈
https://programmers.co.kr/learn/courses/30/lessons/77884
두 정수 left와 right가 매개변수로 주어집니다. 
left부터 right까지의 모든 수들 중에서, 약수의 개수가 짝수인 수는 더하고, 
약수의 개수가 홀수인 수는 뺀 수를 return 하도록 solution 함수를 완성해주세요.
!!!:
1 ≤ left ≤ right ≤ 1,000
*/

#include <string>
#include <vector>

using namespace std;

int divisor_counts(int n)
{   
    int ret = 2;    // 최소 2개는 존재한다
    for(int i=2; i*i<=n; ++i)
    {
        if(n%i == 0)
        {
            if(i*i == n)    // 같은 수를 제곱하는 경우로 1개만 추가
                ret++;
            else    // 약수는 두 쌍으로 존재
                ret += 2;
        }
    }
    return ret;
}

int solution(int left, int right) {
    int answer = 0;

    if(left == 1)
    {   // 위 함수는 2이상의 경우에만 적용가능하다
        answer = -1;
        left++;
    }

    for(int i=left; i<=right; ++i)
    {
        int divs = divisor_counts(i);
        if(divs % 2 == 0)
            answer += i;
        else
            answer -= i;
    }
    return answer;
}