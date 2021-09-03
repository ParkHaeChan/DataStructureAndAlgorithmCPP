/*
2개 이하로 다른 비트
https://programmers.co.kr/learn/courses/30/lessons/77885

양의 정수 x에 대한 함수 f(x)를 다음과 같이 정의합니다.
x보다 크고 x와 비트가 1~2개 다른 수들 중에서 제일 작은 수
f(2) = 3, f(7) = 11

?:
정수들이 담긴 배열 numbers가 매개변수로 주어집니다. 
numbers의 모든 수들에 대하여 각 수의 f 값을 배열에 차례대로 담아 return 하도록 solution 함수를 완성해주세요.

!!!:
1 ≤ numbers의 길이 ≤ 100,000
0 ≤ numbers의 모든 수 ≤ 1015

시도1)
적절한 비트연산을 수행하면된다.
몇몇 케이스에서 시간초과 발생
i 쪽 반복문의 자료형이 long long이어야 x와 적절히 비교할 수 있다...(습관적으로 int씀)
시도2)
케이스 10, 11에서 시간초과 발생
방법을 아예 변경해서 x보다 큰 수에서 비트수 차이를 직접세지 않고
x를 적절히 변경해서 바로 x보다 크면서 비트수 2이내로 차이나게 만든다.
x의 비트중 제일 빠른 0이 나온 부분을 1로 바꾸고 (x보다 커야하므로)
그리고 바꾼 부분에서 뒤로 가장 가까운 1을 0으로 바꾼다(크면서 최소여야 한다)
*/

#include <string>
#include <vector>

using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;

    for(long long x: numbers)
    {   
        // x보다 크고 비트가 2개 이하로 다른 최소 숫자를 찾으므로
        /* 시도 1: case 10, 11 시간 초과
        for(long long i=x+1; i<=LONG_LONG_MAX; ++i)
        {   // 비트 수 차이를 센다
            // x 와 i를 XOR 연산 후 비트가 1인게 몇 개 있는 확인
            unsigned long long XOR = x ^ i;
            unsigned long long bit1 = 1LL;
            int cnt = 0;
            for(int b=0; b<64; ++b)
            {
                if((XOR & bit1<<b) == 0)
                    continue;
                else
                    cnt++;
                // 시도 2
                if(cnt > 2)
                    break;
            }
            if(cnt <= 2)
            {
                answer.push_back(i);
                break;
            }
        }*/
        // 시도 2
        // x의 낮은 자리부터 가장 빠른 0을 찾는다
        long long bit1 = 1;
        int i;
        for(i=0; i<64; ++i)
        {
            if((x & (bit1<<i)) == 0)
            {   // 해당 자리를 1로 바꾼다
                x |= bit1<<i;
                break;
            }
        }
        // x뒤의 비트중 1이 있으면 0으로 바꾼다
        for(int b=i-1; b>=0; --b)
        {
            if(x & bit1<<b == bit1<<b)
            {
                long long notX = ~(bit1<<b);    // 비트를 뒤집는다(0->1, 1->0)
                x = x & notX; // 해당 위치만 0으로 바꾼다
                break;
            }
        }
        answer.push_back(x);
    }

    return answer;
}

int main()
{
    vector<long long> numbers = {2,7};
    solution(numbers);

    return 0;
}