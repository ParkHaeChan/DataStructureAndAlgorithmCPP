/*
가장 긴 팰린드롬
https://programmers.co.kr/learn/courses/30/lessons/12904

앞뒤를 뒤집어도 똑같은 문자열을 팰린드롬(palindrome)이라고 합니다.
문자열 s가 주어질 때, s의 부분문자열(Substring)중 가장 긴 팰린드롬의 길이를 return 하는 solution 함수를 완성해 주세요.

예를들면, 문자열 s가 "abcdcba"이면 7을 return하고 "abacde"이면 3을 return합니다.

!!!:
문자열 s의 길이 : 2,500 이하의 자연수
문자열 s는 알파벳 소문자로만 구성

시도1)
단순하게 생각하면 모든 위치에서 팰린드롬을 구성하여 가장 큰 팰린드롬을 찾으면된다.
하지만 이런 방식으로는 시간초과가 발생할 것이다.
2500이하라해도 가능한 모든 크기를 찾기 위해서는 길이가 n! 가지를 조사해야한다.
가장 큰 팰린드롬만 빠르게 찾는 방법으로 투포인터(또는 슬라이딩 윈도우) 방식이나 동적계획법 등이 필요해 보인다.
작은 팰린드롬을 찾으면 그 팰린드롬의 양 끝이 서로 같은지 확인하는 것으로 더 큰 팰린드롬이 되는지를 확인할 수 있다.
모든 위치에서 이방식을 적용하면, N^2가 걸리고 이는 가능성이 있다.

추가로 팰린드롬 길이가 홀수/짝수 이냐에 따라 검사 방식이 바뀌어야 함을 주의

시도2)
위 방식으로는 팰린드롬 길이가 홀수인 경우만 제대로 센다.
짝수인 경우로 세려면 일단 두개가 겹치는 구간에서 시작하는 방식으로 찾는 방법과
첨부터 재귀로 양끝에서 시작해서 서로 다른 경우 양끝을 줄여나가는 식으로 구성하는 방법도 가능하다.
우선은 짝수인 경우도 세는 방식을 시도해본다.
<통과했다>

시도3)
위 방식으로 통과 했지만 재귀 방식으로 시도해본다.(재귀 방식으로 효율성이 통과 되는지 궁금해서 시도)
재귀로 구성할 경우 양끝에서 시도해서 찾아가는 방식으로하면 시간초과가 발생한다.
가능한 모든 부분 문자열 길이에 대해 팰린드롬이 가능한지 검사하는것과 같기 때문이다.
일단 팰린드롬인 상태에서 더 크게 구성이 가능한지 확인하는 방식이 더 비용이 적을 수 밖에 없다.
<시간초과 발생>
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool InRange(int front, int back, int size)
{
    if(front < 0 || back >= size)
        return false;
    return true;
}

int recur(int length, int front, int back, string& s)
{
    // 탈출조건
    if(front >= back)
    {
        if(front == back)
            return length+1;
        else
            return length;
    }
    int ret = 0;
    // front, back은 s의 양 끝에서 시작
    if(s[front] == s[back]) // 양 끝이 같은 경우
    {
        ret = recur(length+2, front+1, back-1, s);
    }
    // 앞쪽을 한칸 앞으로 이동 또는 뒤쪽을 한칸 뒤로 이동한 상태로도 찾아본다
    int move_front = recur(0, front+1, back, s);
    int move_back = recur(0, front, back-1, s);
    
    int temp = max(move_front, move_back);  // 둘 중 더 긴쪽
    return max(ret, temp);
}

// 홀수 길이의 팰린드롬
int palin_size(string& s, int start)
{
    int front = start;
    int back = start;
    int ret = 1;    // start 하나인 경우도 1크기의 팰린드롬
    while(true)
    {
        if(InRange(front-1, back+1, s.size()))
        {
            if(s[front-1] == s[back+1])
            {
                front--;
                back++;
                ret+=2;
            }
            else
                break;  // 팰린드롬 X
        }
        else
            break;  // 범위 나간 경우 X
    }
    return ret;
}

// 짝수 길이 팰린드롬
int even_palin(string& s, int front, int back)
{
    if(s[front] != s[back] || back >= s.size())
        return 0;

    int ret = 2;
    while(true)
    {
        if(InRange(front-1, back+1, s.size()))
        {
            if(s[front-1] == s[back+1])
            {
                front--;
                back++;
                ret+=2;
            }
            else
                break;  // 팰린드롬 X
        }
        else
            break;  // 범위 나간 경우 X
    }
    return ret;
}
/*
int solution(string s)
{
    int answer=0;

    // 모든 위치에서 가능한 가장 큰 팰린드롬을 찾는다
    for(int i=0; i<s.size(); ++i)
    {
        answer = max(answer, palin_size(s, i)); // 홀수길이
        answer = max(answer , even_palin(s, i, i+1));   // 짝수 길이
    }

    return answer;
}
*/
int solution(string s)
{
    int answer=0;

    answer = recur(0, 0, s.size()-1, s);

    return answer;
}

int main()
{
    string s = "abacde";
    cout << solution(s) << endl;

    return 0;
}