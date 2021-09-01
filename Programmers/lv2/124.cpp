/*
124나라의 숫자
https://programmers.co.kr/learn/courses/30/lessons/12899

124 나라가 있습니다. 124 나라에서는 10진법이 아닌 다음과 같은 자신들만의 규칙으로 수를 표현합니다.

124 나라에는 자연수만 존재합니다.
124 나라에는 모든 수를 표현할 때 1, 2, 4만 사용합니다.
예를 들어서 124 나라에서 사용하는 숫자는 다음과 같이 변환됩니다.

10진법	124 나라	10진법	124 나라
1	1	6	14
2	2	7	21
3	4	8	22
4	11	9	24
5	12	10	41

?:
자연수 n이 매개변수로 주어질 때, n을 124 나라에서 사용하는 숫자로 바꾼 값을 return 하도록 solution 함수를 완성해 주세요.

!!!:
n은 500,000,000이하의 자연수 입니다.

시도1)
자리수 당 1,2,4가 사용되므로 3진법 처럼 작동한다.
단 1,2,3이 아닌 1,2,4가 사용된다.
즉, 3진법으로 바꾼뒤 3을 4로 바꾸면 된다 --> (X)
0도 있다, 그럼 0->1, 1->2, 2->4 로 대치한다? (X)
이 경우는 3,9,27 같은 경우 3진법으로는 자리수가 추가되지만 124로는 자리수가 늘어나지 않는다.
3은 3진법으로는 10이고, 124로는 4에 해당하기 때문에 그대로 대치하는 방식으로는 작동하지 않는다.
6은 3진법으로는 20이고, 124로는 14에 해당한다(여기부턴 대치가 통한다)
9는 3진법으로 100이고, 124로는 24에 해당한다(대치로 작동X)

시도2)
3진법을 만드는 것 처럼 3으로 나누되 나머지가 0이 되는 경우는 몫-1, 나머지:3 이 되도록 조치한다.
즉, 3진법의 0,1,2가 (124나라에선) 4,1,2로 대치되면 된다.
나머지만 스택에 넣었다가 꺼내면서 124로 치환한다.
통과
*/
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

string solution(int n) {
    string answer = "";

    string n124 = "0124";
    stack<int> numStack;

    int quotient = n;
    int remainder;
    while(quotient > 0)
    {
        remainder = quotient%3;
        quotient /= 3;
        if(remainder == 0)
        {
            quotient--;
            remainder = 3;
        }
        numStack.push(remainder);
    }
    while (!numStack.empty())
    {
        int t = numStack.top(); numStack.pop();
        answer += n124[t];
    }

    return answer;
}

int main()
{
    int n = 10;

    cout << solution(n) << endl;

    return 0;
}