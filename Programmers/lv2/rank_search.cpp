/*
순위 검색
https://programmers.co.kr/learn/courses/30/lessons/72412

이번 채용에서 지원자는 지원서 작성 시 아래와 같이 4가지 항목을 반드시 선택하도록 하였습니다.
코딩테스트 참여 개발언어 항목에 cpp, java, python 중 하나를 선택해야 합니다.
지원 직군 항목에 backend와 frontend 중 하나를 선택해야 합니다.
지원 경력구분 항목에 junior와 senior 중 하나를 선택해야 합니다.
선호하는 소울푸드로 chicken과 pizza 중 하나를 선택해야 합니다.

개발팀에서 궁금해하는 내용은 다음과 같은 형태를 갖습니다.
* [조건]을 만족하는 사람 중 코딩테스트 점수를 X점 이상 받은 사람은 모두 몇 명인가?

?:
지원자가 지원서에 입력한 4가지의 정보와 획득한 코딩테스트 점수를 하나의 문자열로 구성한 값의 배열 info, 
개발팀이 궁금해하는 문의조건이 문자열 형태로 담긴 배열 query가 매개변수로 주어질 때,
각 문의조건에 해당하는 사람들의 숫자를 순서대로 배열에 담아 return 하도록 solution 함수를 완성해 주세요.

!!!:
info 배열의 크기는 1 이상 50,000 이하입니다.
info 배열 각 원소의 값은 지원자가 지원서에 입력한 4가지 값과 코딩테스트 점수를 합친 "개발언어 직군 경력 소울푸드 점수" 형식입니다.
개발언어는 cpp, java, python 중 하나입니다.
직군은 backend, frontend 중 하나입니다.
경력은 junior, senior 중 하나입니다.
소울푸드는 chicken, pizza 중 하나입니다.
점수는 코딩테스트 점수를 의미하며, 1 이상 100,000 이하인 자연수입니다.
각 단어는 공백문자(스페이스 바) 하나로 구분되어 있습니다.
query 배열의 크기는 1 이상 100,000 이하입니다.
query의 각 문자열은 "[조건] X" 형식입니다.
[조건]은 "개발언어 and 직군 and 경력 and 소울푸드" 형식의 문자열입니다.
언어는 cpp, java, python, - 중 하나입니다.
직군은 backend, frontend, - 중 하나입니다.
경력은 junior, senior, - 중 하나입니다.
소울푸드는 chicken, pizza, - 중 하나입니다.
'-' 표시는 해당 조건을 고려하지 않겠다는 의미입니다.
X는 코딩테스트 점수를 의미하며 조건을 만족하는 사람 중 X점 이상 받은 사람은 모두 몇 명인 지를 의미합니다.
각 단어는 공백문자(스페이스 바) 하나로 구분되어 있습니다.

예를 들면, "cpp and - and senior and pizza 500"은 
"cpp로 코딩테스트를 봤으며, 경력은 senior 이면서 소울푸드로 pizza를 선택한 지원자 중 
코딩테스트 점수를 500점 이상 받은 사람은 모두 몇 명인가?"를 의미합니다.

시도1)
DB랑 비슷한 느낌인데 이를 효율적으로 작동시키려면 해싱이 필요하다.
각 조건이 and로만 처리됨을 확인
효율성 테스트 실패
시도2)
조건에 부합하는 사람 인원수만 알면되므로 구조체가 아닌 hash로 관리한다.
(완전 다른 방식이므로 새로 구현 rank_search_new.cpp 참고)
*/

#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct applicant
{
    int id;
    string lang;
    string job;
    string career;
    string soulfood;
    int score;
};

vector<string> parse_input(string& input)
{
    string buff;
    istringstream iss(input);
    vector<string> ret;

    while(getline(iss, buff, ' '))
    {
        if(buff == "and")
            continue;
        ret.push_back(buff);
    }
    return ret;
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;

    vector<applicant> applicantVect;
    for(int i=0; i<info.size(); ++i)
    {
        vector<string> parse_i = parse_input(info[i]);
        applicant temp = {i, parse_i[0], parse_i[1], parse_i[2], parse_i[3], stoi(parse_i[4])};
        applicantVect.push_back(temp);
    }
    
    for(int i=0; i<query.size(); ++i)
    {
        vector<string> parse_q = parse_input(query[i]);
        string lang = parse_q[0];
        string job = parse_q[1];
        string career = parse_q[2];
        string soulfood = parse_q[3];
        int score = stoi(parse_q[4]);

        int cnt = 0;
        for(auto e: applicantVect)
        {
            if(lang == e.lang || lang == "-")
            {
                if(job == e.job || job == "-")
                {
                    if(career == e.career || career == "-")
                    {
                        if(soulfood == e.soulfood || soulfood == "-")
                        {
                            if(score <= e.score)
                            {
                                cnt++;
                            }
                        }
                    }
                }
            }
        }
        answer.push_back(cnt);
    }

    return answer;
}

int main()
{
    vector<string> info = {"java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50"};
    vector<string> query = {"java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"};

    solution(info, query);

    return 0;
}