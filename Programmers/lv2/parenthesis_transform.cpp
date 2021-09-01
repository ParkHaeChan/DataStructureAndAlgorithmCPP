/*
괄호 변환
https://programmers.co.kr/learn/courses/30/lessons/60058

'(' 와 ')' 로만 이루어진 문자열이 있을 경우, '(' 의 개수와 ')' 의 개수가 같다면 이를 
균형잡힌 괄호 문자열이라고 부릅니다.

그리고 여기에 '('와 ')'의 괄호의 짝도 모두 맞을 경우에는 이를 
올바른 괄호 문자열이라고 부릅니다.

예를 들어, "(()))("와 같은 문자열은 "균형잡힌 괄호 문자열" 이지만 "올바른 괄호 문자열"은 아닙니다.
반면에 "(())()"와 같은 문자열은 "균형잡힌 괄호 문자열" 이면서 동시에 "올바른 괄호 문자열" 입니다.
'(' 와 ')' 로만 이루어진 문자열 w가 "균형잡힌 괄호 문자열" 이라면 다음과 같은 과정을 통해 "올바른 괄호 문자열"로 변환할 수 있습니다.

1. 입력이 빈 문자열인 경우, 빈 문자열을 반환합니다. 
2. 문자열 w를 두 "균형잡힌 괄호 문자열" u, v로 분리합니다. 단, u는 "균형잡힌 괄호 문자열"로 더 이상 분리할 수 없어야 하며, v는 빈 문자열이 될 수 있습니다. 
3. 문자열 u가 "올바른 괄호 문자열" 이라면 문자열 v에 대해 1단계부터 다시 수행합니다. 
  3-1. 수행한 결과 문자열을 u에 이어 붙인 후 반환합니다. 
4. 문자열 u가 "올바른 괄호 문자열"이 아니라면 아래 과정을 수행합니다. 
  4-1. 빈 문자열에 첫 번째 문자로 '('를 붙입니다. 
  4-2. 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과 문자열을 이어 붙입니다. 
  4-3. ')'를 다시 붙입니다. 
  4-4. u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙입니다. 
  4-5. 생성된 문자열을 반환합니다.

?:
"균형잡힌 괄호 문자열" p가 매개변수로 주어질 때, 주어진 알고리즘을 수행해 
"올바른 괄호 문자열"로 변환한 결과를 return 하도록 solution 함수를 완성해 주세요.

!!!:
p는 '(' 와 ')' 로만 이루어진 문자열이며 길이는 2 이상 1,000 이하인 짝수입니다.
문자열 p를 이루는 '(' 와 ')' 의 개수는 항상 같습니다.
만약 p가 이미 "올바른 괄호 문자열"이라면 그대로 return 하면 됩니다.

시도1)
올바른 괄호 문자열인지 확인하는 함수를 작성. --> stack 활용
입력이 올바른 괄호 문자열이면 바로 종료,
아닐 경우는 변환 함수를 수행하도록 변환 함수 작성

시도2) 괄호Stack top이 (인 경우만 push해야 한다.
시도3)
문의란 확인한 결과
문자열을 역순으로 뒤집으란 얘기가 아닌 ')' -> '(' 와 '(' -> ')' 로 변환하라는 뜻이라 한다.
문제를 똑바로 읽어야 한다...
*/
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

bool isCorrectParen(const string& p)
{
    stack<char> pStack;

    for(char paren: p)
    {
        if(pStack.empty())
        {
            if(paren == '(')
                pStack.push(paren);
            else
                return false;
        }
        else
        {
            if(paren == ')')
                pStack.pop();
            else    // '(' 인 경우
                pStack.push(paren);
        }
    }

    if(pStack.empty())
        return true;
    return false;
}

string transform(string& p)
{
    // 1. 입력이 빈 문자열인 경우, 빈 문자열을 반환합니다.
    if(p.empty())
        return p;
    // 2. 문자열 w를 두 "균형잡힌 괄호 문자열" u, v로 분리합니다. 단, u는 "균형잡힌 괄호 문자열"로 더 이상 분리할 수 없어야 하며, v는 빈 문자열이 될 수 있습니다.
    int rp=0, lp=0, i=0;
    for(i=0; i<p.size(); ++i)
    {
        if(p[i] == '(')
            lp++;
        if(p[i] == ')')
            rp++;
        if(lp == rp)
            break;
    }
    string u = p.substr(0, i+1);
    string v = p.substr(i+1, p.size()-u.size());
    // 3. 문자열 u가 "올바른 괄호 문자열" 이라면 문자열 v에 대해 1단계부터 다시 수행합니다.
    if(isCorrectParen(u))
    {
        v = transform(v);
        //   3-1. 수행한 결과 문자열을 u에 이어 붙인 후 반환합니다.
        u += v;
        return u;
    }
    else
    {// 4. 문자열 u가 "올바른 괄호 문자열"이 아니라면 아래 과정을 수행합니다. 
        //   4-1. 빈 문자열에 첫 번째 문자로 '('를 붙입니다.
        string temp = "(";
        //   4-2. 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과 문자열을 이어 붙입니다.
        temp += transform(v);
        //   4-3. ')'를 다시 붙입니다.
        temp += ")"; 
        //   4-4. u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙입니다.
        u = u.substr(1, u.size()-2);
        
        // 시도3) ( --> ) 로 바꾸고, ) --> (로 바꿔서 붙이라는 뜻임...
        /*
        int front = 0, back = u.size()-1;
        while(front < back)
        {
            std::swap(u[front], u[back]);
            front++;
            back--;
        }*/
        for(char& c : u)
        {
            if(c == '(')
                c = ')';
            else
                c = '(';
        }
        temp += u;
        //   4-5. 생성된 문자열을 반환합니다.
        return temp;
    }
}

string solution(string p) {
    string answer = "";

    // 올바른 괄호 문자열이면 바로 종료
    if(isCorrectParen(p))
        return p;
    // 아닐 경우 변환 수행
    answer = transform(p);

    return answer;
}

int main()
{
    string p = 	"()))((()";

    cout << solution(p) << endl;

    return 0;
}