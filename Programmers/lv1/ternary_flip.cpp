/*
3진법 뒤집기
https://programmers.co.kr/learn/courses/30/lessons/68935

자연수 n이 매개변수로 주어집니다. n을 3진법 상에서 앞뒤로 뒤집은 후, 
이를 다시 10진법으로 표현한 수를 return 하도록 solution 함수를 완성해주세요.

n은 1 이상 100,000,000 이하인 자연수입니다.

x진법으로 바꾸기:
x로 나눈 몫과 나머지를 구한뒤,
나머지는 끝자리 수에 넣고,
다시 몫을 x로 나눈 뒤 나머지는 다음 자리 수에 넣고, 몫이 0이 될 때까지 반복한다.
x진법 --> 10진법:
끝자리 수 + 그 다음 자리수 * x + 그 다음 다음 자리수 * x^2 + ... 하면 된다.
*/

#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(int n) {
    int answer = 0;

    string flipped_ternary;
    // n을 3진법으로 바꾼다
    while(n/3 != 0)
    {   // string 형이므로 ascii 문자로 변환하여 넣는다
        flipped_ternary.push_back(n%3+'0');
        n /= 3;
    }
    flipped_ternary.push_back(n%3+'0');
    // 이 상태는 이미 뒤집힌 상태이다(뒷자리 부터 구해서 뒤에서 부터 추가했으므로)
    // 다시 10진법으로 바꾼다 (그리고 문자열을 숫자로 변경한다)
    int N = flipped_ternary.size();
    answer += flipped_ternary[N-1] - '0';
    int cnt =1;
    for(int i=N-2; i>=0; --i, ++cnt)
    {
        answer += pow(3, cnt) * (flipped_ternary[i]-'0');
    }

    return answer;
}

int main()
{
    int n = 45;
    solution(n);

    return 0;
}