/*
문제가 뭐였는지 기억이 안난다...
테스트 용으로 랜덤으로 나온 문제이다.
1시간 내에 못풀어서 정답체크를 못해봤다.
*/

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

bool RightPstr(string p)
{
    stack<char> charStack;

    if(p[0] == ')')
        return false;

    for(int i=0; i<p.size(); ++i)
    {
        if(p[i] == '(')
            charStack.push(p[i]);
        else
        {
            if(!charStack.empty())
                charStack.pop();
            else
                return false;
        }
    }
    if(charStack.empty())
        return true;
    else
        return false;
}

//입력 문자열을 분리하는 재귀함수
string recur(string& p, int start, int end)
{
    // 종료 조건: 올바른 괄호
    if(RightPstr(p))
    {
        return p;
    }

    int mid = 0;
    // 분리 기준: 최소 균형잡힌 괄호 문자열
    for(int i = 2; i<end; i+=2)
    {
        int r = 0, l = 0;
        for(int j=0; j<i; ++j)
        {
            if(p[j] == '(')
                l++;
            else
                r++;
        }
        if(r == l)
        {
            mid = i;
            break;
        }
    }
    string u = p.substr(start, mid);
    string v = p.substr(mid, end);
    if(RightPstr(u))
    {
        return u + recur(v, 0, v.size());
    }
    else
    { // 앞뒤 문자를 제거하고, 나머지 문자의 괄호 방향을 뒤집고 양끝에 ( ) 추가
        u[start] = '(';
        u[mid-1] = ')';
        int center = (start+(mid-1))/2;
        for(int i=start+1; i<=center; ++i)
        {
            swap(u[i], u[mid-1-i]);
        }
        return u + recur(v, 0, v.size());
    }
}


string solution(string p) {
    string answer = "";

    answer = recur(p, 0, p.size());

    return answer;
}

int main()
{
    string p = "()))((()";
    //string p = "(()())()";

    cout << RightPstr(p) << endl;

    cout << solution(p) << endl;

    return 0;
}