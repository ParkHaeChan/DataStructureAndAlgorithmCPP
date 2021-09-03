/*
괄호 회전하기
https://programmers.co.kr/learn/courses/30/lessons/76502

다음 규칙을 지키는 문자열을 올바른 괄호 문자열이라고 정의합니다.

(), [], {} 는 모두 올바른 괄호 문자열입니다.
만약 A가 올바른 괄호 문자열이라면, (A), [A], {A} 도 올바른 괄호 문자열입니다. 예를 들어, [] 가 올바른 괄호 문자열이므로, ([]) 도 올바른 괄호 문자열입니다.
만약 A, B가 올바른 괄호 문자열이라면, AB 도 올바른 괄호 문자열입니다. 예를 들어, {} 와 ([]) 가 올바른 괄호 문자열이므로, {}([]) 도 올바른 괄호 문자열입니다.

?:
대괄호, 중괄호, 그리고 소괄호로 이루어진 문자열 s가 매개변수로 주어집니다. 
이 s를 왼쪽으로 x (0 ≤ x < (s의 길이)) 칸만큼 회전시켰을 때 
s가 올바른 괄호 문자열이 되게 하는 x의 개수를 return 하도록 solution 함수를 완성해주세요.

!!!:
s의 길이는 1 이상 1,000 이하입니다.

시도1)
시뮬레이션으로 구현한다
앞에서 x칸 잘라서 뒤에 붙인게 올바른 문자열인지 확인
*/

#include <string>
#include <vector>
#include <stack>

using namespace std;

bool check_paren(string& s)
{
    stack<char> cStack;
    for(int i=0; i<s.size(); ++i)
    {
        switch(s[i])
        {
            case '(':
            case '{':
            case '[':
                cStack.push(s[i]);
                break;
            case ')':
                if(cStack.empty())
                    return false;
                else
                {
                    if(cStack.top() == '(')
                        cStack.pop();
                }
                break;
            case '}':
                if(cStack.empty())
                    return false;
                else
                {
                    if(cStack.top() == '{')
                        cStack.pop();
                }
                break;
            case ']':
                if(cStack.empty())
                    return false;
                else
                {
                    if(cStack.top() == '[')
                        cStack.pop();
                }
                break;
        }
    }
    if(cStack.empty())
        return true;
    return false;
}

int solution(string s) {
    int answer = 0;

    // 올바른 괄호 문자열인지 확인
    for(int i=0; i<s.size()-1; ++i)
    {
        if(check_paren(s))
            answer++;
        
        // s의 맨 앞을 잘라 맨 뒤로 보낸다
        string f = s.substr(0,1);
        s = s.substr(1, s.size()-1);
        s += f;
    }

    return answer;
}

int main()
{
    string s = "[](){}";

    solution(s);

    return 0;
}