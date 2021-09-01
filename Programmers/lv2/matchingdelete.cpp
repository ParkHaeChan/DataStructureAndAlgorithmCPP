/*
짝지어 제거하기
https://programmers.co.kr/learn/courses/30/lessons/12973#

짝지어 제거하기는, 알파벳 소문자로 이루어진 문자열을 가지고 시작합니다. 
먼저 문자열에서 같은 알파벳이 2개 붙어 있는 짝을 찾습니다. 그다음, 그 둘을 제거한 뒤, 앞뒤로 문자열을 이어 붙입니다.
이 과정을 반복해서 문자열을 모두 제거한다면 짝지어 제거하기가 종료됩니다. 

문자열 S가 주어졌을 때, 짝지어 제거하기를 성공적으로 수행할 수 있는지 반환하는 함수를 완성해 주세요. 
성공적으로 수행할 수 있으면 1을, 아닐 경우 0을 리턴해주면 됩니다.

예를 들어, 문자열 S = baabaa 라면
b aa baa → bb aa → aa →
의 순서로 문자열을 모두 제거할 수 있으므로 1을 반환합니다.

!!!:
문자열의 길이 : 1,000,000이하의 자연수
문자열은 모두 소문자로 이루어져 있습니다.

시도1) 문자열의 길이제한이 꽤 크다. 위의 방식으로 하나씩 하면 시간이 오래 걸릴 것이다.
그리고 실제로 삭제 연산을 여러번 시도하기에도 문자열 길이가 제법 크다.
한번 읽으면서 짝지어서 바로 풀 수 있는 방법을 찾아야 할 것 같다.
여기서 stack을 쓰면 될 것 같다고 바로 느낌이 왔다.
하나씩 넣으면서 같은 것 2개가 들어온 순간 pop하고
문자열 끝까지 읽었을 때, stack이 비면 모두 제거할 수 있다는 뜻이다.
*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

int solution(string s)
{
    int answer = 0;

    stack<char> charStack;

    for(auto c: s)
    {
        if(!charStack.empty())
        {
            char w = charStack.top();
            if(w == c)
                charStack.pop();
            else
                charStack.push(c);
        }
        else
            charStack.push(c);
    }
    if(charStack.empty())
        answer = 1;

    return answer;
}