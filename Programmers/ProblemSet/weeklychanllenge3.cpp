/*
직업군 추천하기
문제: https://programmers.co.kr/learn/courses/30/lessons/84325

직업군 언어 점수를 정리한 문자열 배열 table, 개발자가 사용하는 언어를 담은 문자열 배열 languages, 
언어 선호도를 담은 정수 배열 preference가 매개변수로 주어집니다. 
개발자가 사용하는 언어의 언어 선호도 x 직업군 언어 점수의 총합이 가장 높은 직업군을 return 하도록 solution 함수를 완성해주세요. 
총합이 같은 직업군이 여러 개일 경우, 이름이 사전 순으로 가장 빠른 직업군을 return 해주세요.

!!!:
table의 길이 = 5
table의 원소는 "직업군 5점언어 4점언어 3점언어 2점언어 1점언어"형식의 문자열입니다. 직업군, 5점언어, 4언어, 3점언어, 2점언어, 1점언어는 하나의 공백으로 구분되어 있습니다.
table은 모든 테스트케이스에서 동일합니다.
1 ≤ languages의 길이 ≤ 9
languages의 원소는 "JAVA", "JAVASCRIPT", "C", "C++" ,"C#" , "SQL", "PYTHON", "KOTLIN", "PHP" 중 한 개 이상으로 이루어져 있습니다.
languages의 원소는 중복되지 않습니다.
preference의 길이 = languages의 길이
1 ≤ preference의 원소 ≤ 10
preference의 i번째 원소는 languages의 i번째 원소의 언어 선호도입니다.
return 할 문자열은 "SI", "CONTENTS", "HARDWARE", "PORTAL", "GAME" 중 하나입니다.
*/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>  // parse_string
#include <map>
#include <algorithm>

using namespace std;

vector<string> parse_string(string input)
{
    vector<string> parsed;

    istringstream iss(input);
    string buffer;
    while(getline(iss, buffer, ' '))    // 구분자는 공백
    {
        parsed.push_back(buffer);
    }
    return parsed;
}

string solution(vector<string> table, vector<string> languages, vector<int> preference) {
    string answer = "";

    // table을 저장할 중첩map[jobname] = map{language: score}
    map<string, map<string, int>> tableMap;
    vector<string> jobnames;

    // table 파싱 및 mapping
    for(auto e: table)
    {
        vector<string> parsed = parse_string(e);
        string jobname = parsed[0];
        int score = parsed.size()-1;
        for(int i=1; i<parsed.size(); ++i)
        {
            tableMap[jobname].insert({parsed[i], score-(i-1)});
        }
        jobnames.push_back(jobname);
    }
    // 모든 table에 대해 languages 가 존재하는지 확인하여 점수 계산
    vector<pair<string, int>> jobscorevect;
    for(string jobname: jobnames)
    {
        map<string, int> scoretable = tableMap[jobname];
        // 점수 계산
        int score_sum = 0;
        for(int i=0; i<languages.size(); ++i)
        {
            score_sum += preference[i] * scoretable[languages[i]];
        }
        jobscorevect.push_back({jobname, score_sum});
    }
    sort(jobscorevect.begin(), jobscorevect.end(), [](auto back, auto front){
        if(back.second == front.second)
        {   // string 사전순 (string형에 대한 사전순 비교는 c++에서 기본으로 지원한다!)
            return back.first < front.first;
        }
        else    // 점수 내림차순
            return back.second > front.second;
    });
    answer = jobscorevect[0].first;

    return answer;
}

int main()
{
    vector<string> table = {"SI JAVA JAVASCRIPT SQL PYTHON C#", "CONTENTS JAVASCRIPT JAVA PYTHON SQL C++", "HARDWARE C C++ PYTHON JAVA JAVASCRIPT", "PORTAL JAVA JAVASCRIPT PYTHON KOTLIN PHP", "GAME C++ C# JAVASCRIPT C JAVA"};
    vector<string> languages = {"PYTHON", "C++", "SQL"};
    vector<int> preference = {7, 5, 5};

    cout << solution(table, languages, preference) << endl;

    return 0;
}