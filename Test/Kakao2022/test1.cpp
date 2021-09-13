// 구현 문제: 누가 누굴 신고했는지, 신고 횟수 충족되서 정지 먹은 사람 몇명인지, 결과적으로 누가 얼마나 통보 받는지
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

vector<string> parse_input(string& input)
{
    vector<string> ret;
    istringstream iss(input);
    string buff;
    while(getline(iss, buff, ' '))
    {
        ret.push_back(buff);
    }
    return ret;
}

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;

    map<string, int> userMap;
    multimap<string, string> sueMap;
    set<pair<string, string>> reported;
    for(auto e: report)
    {
        auto r = parse_input(e);
        pair<string, string> repo = {r[0], r[1]};

        if(reported.find(repo) != reported.end())
            continue;
        reported.insert(repo);
        sueMap.insert(repo);
    }
    for(auto e: reported)
    {
        userMap[e.second]++;
    }
    set<string> reportedSet;
    for(auto e: userMap)
    {
        if(e.second >= k)
            reportedSet.insert(e.first);
    }
    
    for(auto e: id_list)
    {
        auto piter = sueMap.equal_range(e);
        int cnt = 0;
        for(auto it = piter.first; it != piter.second; ++it)
        {
            string p = (*it).second;
            if(reportedSet.find(p) != reportedSet.end())
                cnt++;
        }
        answer.push_back(cnt);
    }

    return answer;
}

int main()
{
    vector<string> id_list = {"muzi", "frodo", "apeach", "neo"};
    vector<string> report = {"muzi frodo","apeach frodo","frodo neo","muzi neo","apeach muzi"};

    int k = 2;

    solution(id_list, report, k);

}