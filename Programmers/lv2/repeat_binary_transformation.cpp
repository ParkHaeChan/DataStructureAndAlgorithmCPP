/*
이진 변환 반복하기
https://programmers.co.kr/learn/courses/30/lessons/70129

문제 설명
0과 1로 이루어진 어떤 문자열 x에 대한 이진 변환을 다음과 같이 정의합니다.

x의 모든 0을 제거합니다.
x의 길이를 c라고 하면, x를 "c를 2진법으로 표현한 문자열"로 바꿉니다.
예를 들어, x = "0111010"이라면, x에 이진 변환을 가하면 x = "0111010" -> "1111" -> "100" 이 됩니다.

?:
0과 1로 이루어진 문자열 s가 매개변수로 주어집니다. 
s가 "1"이 될 때까지 계속해서 s에 이진 변환을 가했을 때, 
이진 변환의 횟수와 변환 과정에서 제거된 모든 0의 개수를 각각 배열에 담아 return 하도록 solution 함수를 완성해주세요.

!!!:
s의 길이는 1 이상 150,000 이하입니다.
s에는 '1'이 최소 하나 이상 포함되어 있습니다.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(string s) {
    vector<int> answer;

    int deleted_zeros = 0;

    for(int t = 1; true; ++t)
    {
        int del_zero = 0;
        // x의 모든 0을 제거합니다.
        for(int i=0; i<s.size(); ++i)
            if(s[i] == '0')
                del_zero++;

        // x의 길이를 c라고 하면, x를 "c를 2진법으로 표현한 문자열"로 바꿉니다.
        int c = s.size() - del_zero;

        if(c == 1)
        {
            deleted_zeros += del_zero;
            answer = {t, deleted_zeros};
            break;
        }

        string temp = "";
        while(c != 0)
        {
            temp += to_string(c%2);
            c /= 2;
        }
        reverse(temp.begin(), temp.end());
        s = temp;
        deleted_zeros += del_zero;
    }

    return answer;
}

int main()
{
    string s = "110010101001";
    solution(s);

    return 0;
}