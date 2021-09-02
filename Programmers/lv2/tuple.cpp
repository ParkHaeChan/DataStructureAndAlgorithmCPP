/*
튜플
https://programmers.co.kr/learn/courses/30/lessons/64065

튜플은 다음과 같은 성질을 가지고 있습니다.
중복된 원소가 있을 수 있습니다. ex : (2, 3, 1, 2)
원소에 정해진 순서가 있으며, 원소의 순서가 다르면 서로 다른 튜플입니다. ex : (1, 2, 3) ≠ (1, 3, 2)
튜플의 원소 개수는 유한합니다.
원소의 개수가 n개이고, 중복되는 원소가 없는 튜플 (a1, a2, a3, ..., an)이 주어질 때(단, a1, a2, ..., an은 자연수), 
이는 다음과 같이 집합 기호 '{', '}'를 이용해 표현할 수 있습니다.
{{a1}, {a1, a2}, {a1, a2, a3}, {a1, a2, a3, a4}, ... {a1, a2, a3, a4, ..., an}}
예를 들어 튜플이 (2, 1, 3, 4)인 경우 이는 {{2}, {2, 1}, {2, 1, 3}, {2, 1, 3, 4}}

이때, 집합은 원소의 순서가 바뀌어도 상관없으므로
{{2}, {2, 1}, {2, 1, 3}, {2, 1, 3, 4}}
{{2, 1, 3, 4}, {2}, {2, 1, 3}, {2, 1}}
{{1, 2, 3}, {2, 1}, {1, 2, 4, 3}, {2}}
는 모두 같은 튜플 (2, 1, 3, 4)를 나타냅니다.

?:
특정 튜플을 표현하는 집합이 담긴 문자열 s가 매개변수로 주어질 때, s가 표현하는 튜플을 배열에 담아 return 하도록 solution 함수를 완성해주세요.

!!!:
s의 길이는 5 이상 1,000,000 이하입니다.
s는 숫자와 '{', '}', ',' 로만 이루어져 있습니다.
숫자가 0으로 시작하는 경우는 없습니다.
s는 항상 중복되는 원소가 없는 튜플을 올바르게 표현하고 있습니다.
s가 표현하는 튜플의 원소는 1 이상 100,000 이하인 자연수입니다.
return 하는 배열의 길이가 1 이상 500 이하인 경우만 입력으로 주어집니다.

시도1)
parsing 한다.
제일 짧은(원소가 적은) 문자열이 접두어이다.
정렬된 순서를 따라 겹치는 부분 제외하고 붙여가면서 정답배열을 구성한다.
통과
*/

#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> parse_s(string s)
{
    vector<string> strvect;
    vector<vector<int>> ret;
    int start=0, end=0;
    s = s.substr(1, s.size()-2);    // 양 끝 {,} 삭제
    for(int i=0; i<s.size(); ++i)
    {
        if(s[i] == '{')
        {
            start = i+1;
        }
        else if(s[i] == '}')
        {
            strvect.push_back(s.substr(start, i-start));
        }
    }
    // 콤마 삭제 + 정수 배열로 변환
    for(string s: strvect)
    {
        vector<int> temp;
        string buff;
        istringstream iss(s);
        while(getline(iss, buff, ','))
        {
            temp.push_back(stoi(buff));
        }
        ret.push_back(temp);
    }
    return ret;
}

vector<int> solution(string s) {
    vector<int> answer;

    vector<vector<int>> parsed = parse_s(s);

    sort(parsed.begin(), parsed.end(), [](auto back, auto front){
        return back.size() < front.size();  // 벡터 크기 작은 순으로 정렬
    });
    answer.push_back(parsed[0][0]);
    for(int i=1; i<parsed.size(); ++i)
    {
        multiset<int> mset;
        for(auto e: parsed[i])
            mset.insert(e);

        // 겹치는 것 삭제
        for(auto e: answer)
        {
            mset.erase(e);
        }
        // 남은 것 추가
        int left = (*mset.begin());
        answer.push_back(left);
    }

    return answer;
}

int main()
{
    string s = "{{4,2,3},{3},{2,3,4,1},{2,3}}";

    solution(s);

    return 0;
}