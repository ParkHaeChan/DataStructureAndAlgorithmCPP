/*
최대값과 최소값
https://programmers.co.kr/learn/courses/30/lessons/12939

문자열 s에는 공백으로 구분된 숫자들이 저장되어 있습니다. 
str에 나타나는 숫자 중 최소값과 최대값을 찾아 이를 "(최소값) (최대값)"형태의 문자열을 반환하는 함수, solution을 완성하세요.
예를들어 s가 "1 2 3 4"라면 "1 4"를 리턴하고, "-1 -2 -3 -4"라면 "-4 -1"을 리턴하면 됩니다.

제한 조건
s에는 둘 이상의 정수가 공백으로 구분되어 있습니다.
*/

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>

using namespace std;

vector<int> parse(string& s)
{
    vector<int> ret;
    string buff;
    istringstream iss(s);
    while(getline(iss, buff, ' '))
    {
        ret.push_back(stoi(buff));
    }
    return ret;
}

string solution(string s) {
    string answer = "";

    vector<int> parsed = parse(s);
    int maxval = INT_MIN;
    for(auto e: parsed)
        maxval = max(maxval, e);
    int minval = INT_MAX;
    for(auto e: parsed)
        minval = min(minval, e);

    answer = to_string(minval) + " " + to_string(maxval);

    return answer;
}

int main()
{
    string s = "-1 -2 -3 -4";
    solution(s);
    return 0;
}