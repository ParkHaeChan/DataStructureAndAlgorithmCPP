/*
순위 검색
https://programmers.co.kr/learn/courses/30/lessons/72412

시도2)
조건에 부합하는 사람 인원수만 알면되므로 구조체가 아닌 hash로 관리한다.
테케 통과 X, 효율성 통과 X
시도3)
멀티맵으로는 시간초과난다. map으로 좀 더 효율적으로 작성해야한다.

<풀이 참고>
파싱한 string을 모두 이어붙여서 모든 경우(각각이 - 들어갈 때의 경우까지 포함)를 처리하게 하면 된다.
ex) map<pair<string, int>, int> key: <javabackendjuniorpizza, 점수> val: 해당하는 인원수
이 방법 생각 못하면 못푸는 문제인것 같다...
추가로 map<string, vector<int>> 에서 vector 정렬을 query 반복문 내에서 수행하면 시간초과 발생한다.
아마 메모리 캐시성능 높이는 쪽으로 수행하도록 하는 목적인거 같은데
이게 난이도 2짜리가 맞나???
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

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

int G_SCORE;
void recur(map<string, vector<int>>& hashMap, int depth, vector<string>& options, string selected)
{
    if(depth == options.size())
    {
        hashMap[{selected}].push_back(G_SCORE);
        //cout << selected << endl;
        return;
    }

    // "-" 처리
    selected += "-";
    recur(hashMap, depth+1, options, selected);
    selected = selected.substr(0, selected.size()-1);
    // 이번 depth에 추가되는 option 추가
    selected += options[depth];
    recur(hashMap, depth+1, options, selected);
    selected = selected.substr(0, selected.size()-options[depth].size());
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;

    map<string, vector<int>> hashMap; // KEY: <sumstring, score>, VAL: 해당 인원수

    for(int i=0; i<info.size(); ++i)
    {
        vector<string> parse_i = parse_input(info[i]);
        int score = stoi(parse_i[4]);
        parse_i.pop_back();
        string temp = "";
        G_SCORE = score;
        // 각 경우가 "-" 인 경우도 모두 hash에 넣는다.
        recur(hashMap, 0, parse_i, temp);
    }

    // 모든 hashMap에 대해 정렬 수행
    for(auto& p : hashMap)  // 참조 주의
    {   // 같은 hashMap에 반복 접근하므로 캐시 성능 높여서 정렬 수행하여 시간초과 피한듯
        sort(p.second.begin(), p.second.end());
    }
    
    for(int i=0; i<query.size(); ++i)
    {
        vector<string> parse_q = parse_input(query[i]);
        int score = stoi(parse_q[4]);
        parse_q.pop_back();
        string temp = "";
        for(auto s: parse_q)
            temp += s;
        vector<int> rangevect = hashMap[temp];
        // 여기서 정렬하면 시간초과 발생한다 sort(rangevect.begin(), rangevect.end());
        // 이분 탐색
        auto it = lower_bound(rangevect.begin(), rangevect.end(), score);   //  score 이상
        int cnt = distance(rangevect.begin(), it);
        answer.push_back(rangevect.size() - cnt);
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