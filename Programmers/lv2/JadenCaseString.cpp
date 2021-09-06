/*
JadenCase 문자열 만들기
https://programmers.co.kr/learn/courses/30/lessons/12951

JadenCase란 모든 단어의 첫 문자가 대문자이고, 그 외의 알파벳은 소문자인 문자열입니다. 
문자열 s가 주어졌을 때, s를 JadenCase로 바꾼 문자열을 리턴하는 함수, solution을 완성해주세요.

제한 조건
s는 길이 1 이상인 문자열입니다.
s는 알파벳과 공백문자(" ")로 이루어져 있습니다.
첫 문자가 영문이 아닐때에는 이어지는 영문은 소문자로 씁니다. ( 첫번째 입출력 예 참고 )

시도 1)
8번 test case에 실패
이유는 입력 문자열에 공백있는 경우로 들어오면 끝에 공백으로 끝나는 경우도 발생함.

*/

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> parse(string& s)
{
    vector<string> ret;
    string buff;
    istringstream iss(s);
    while(getline(iss, buff, ' '))
    {
        ret.push_back(buff);
    }
    return ret;
}

string solution(string s) {
    string answer = "";
    
    // 소문자로 변환
    transform(s.begin(), s.end(), s.begin(), [](auto c){
        return tolower(c);
    });
    // 파싱
    vector<string> parsed = parse(s);
    for(string& s: parsed)
    {
        // 첫글자 대문자로 변환
        s[0] = toupper(s[0]);
        answer += s + " ";
    }
    // 원본 문자열 끝이 공백이 아닌데 공백이 있으면
    if(s[s.size()-1] != ' ')
        answer = answer.substr(0, answer.size()-1); // 끝에 공백 제거

    return answer;
}

int main()
{
    string s = "    3people   unFollowed    me    ";
    solution(s);

    return 0;
}