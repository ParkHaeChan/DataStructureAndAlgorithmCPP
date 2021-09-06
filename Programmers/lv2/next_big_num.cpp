/*
다음 큰 숫자
https://programmers.co.kr/learn/courses/30/lessons/12911

자연수 n이 주어졌을 때, n의 다음 큰 숫자는 다음과 같이 정의 합니다.

조건 1. n의 다음 큰 숫자는 n보다 큰 자연수 입니다.
조건 2. n의 다음 큰 숫자와 n은 2진수로 변환했을 때 1의 갯수가 같습니다.
조건 3. n의 다음 큰 숫자는 조건 1, 2를 만족하는 수 중 가장 작은 수 입니다.
예를 들어서 78(1001110)의 다음 큰 숫자는 83(1010011)입니다.

자연수 n이 매개변수로 주어질 때, n의 다음 큰 숫자를 return 하는 solution 함수를 완성해주세요.

제한 사항
n은 1,000,000 이하의 자연수 입니다.
*/

#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

int to_10(deque<int> binary)
{
    int ret = 0;
    reverse(binary.begin(), binary.end());
    for(int i=0; i<binary.size(); ++i)
    {
        ret += binary[i] * pow(2, i);
    }
    return ret;
}

int solution(int n) {
    int answer = 0;
    deque<int> binary;
    int zeros = 0;
    int origin = n;
    // n을 2진수로 변환하여 1과 0의 개수를 센다
    while(n > 0)
    {
        if(n%2 == 0)
            zeros++;
        binary.push_front(n%2);
        n /= 2;
    }
    // 0을 붙여야 할 경우는 0붙이고 맨 앞 1 제외하고 다 뒤로 한칸씩 이동
    if(zeros == 0)
    {
        binary.push_back(0);
        for(int i=binary.size()-1; i>=1; --i)
        {
            binary[i] = binary[i-1];
        }
        binary[1] = 0;
    }
    else
        next_permutation(binary.begin(), binary.end());
    
    // 10진법으로 변환
    answer = to_10(binary);
    // 더 작아지는 경우: 현재가 110 처럼 0과 1의 순서를 바꾸는 것으로는 더 커질 수 없는 경우
    if(answer <= origin)
    {   // 젤 앞1을 제외한 제일 왼쪽 1을 0으로 고치고 맨 뒤에 1을 추가한다.
        prev_permutation(binary.begin(), binary.end());
        for(int i=1; i<binary.size(); ++i)
        {   if(binary[i] == 1)
            {
                binary[i] = 0;
                break;
            }
        }
        binary.push_back(1);
        answer = to_10(binary);
    }

    return answer;
}

int main()
{
    int n = 6;

    solution(n);

    return 0;
}