#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

string solution(vector<string> research, int n, int k) {
    string answer = "";

    // 어떤 검색어가 연속된 n일 동안 매일 최소 k 번 이상 검색되고, 같은 연속된 n일 동안 총 2 x n x k번 이상 검색되었을 경우 이슈 검색어가 됩니다
    int days = research.size();
    vector<map<char, int>> searchMap(days);
    set<char> wordset;
    for(int i=0; i<days; ++i)
    {
        for(auto c: research[i])
        {
            searchMap[i][c]++;
            wordset.insert(c);
        }
    }

    // n일 연속으로 이슈인지 확인
    map<char, int> issueMap;
    for(int i=0; i<=days-n; ++i)
    {
        for(auto c: wordset)
        {   // 사용된 단어가 n일 연속으로 검색됨
            bool issue = true;
            int sum = 0;
            for(int j=0; j<n; ++j)
            {
                if(searchMap[i+j][c] < k)
                {
                    issue = false;
                    break;
                }
                else
                {
                    sum += searchMap[i+j][c];
                }
            }
            if(issue)
            {
                if(sum >= 2*n*k)
                    issueMap[c]++;
            }
        }
    }

    if(issueMap.empty())
        return "None";

    // issue 순으로 정렬
    vector<pair<char, int>> issueVect;
    for(auto e: issueMap)
        issueVect.push_back(e);

    sort(issueVect.begin(), issueVect.end(), [](auto back, auto front){
        if(back.second == front.second)
        {
            return back.first < front.first;
        }
        else
            return back.second > front.second;
    });
    answer += issueVect[0].first;

    return answer;
}

int main()
{
    vector<string> research = {"abaaaa","aaa","abaaaaaa","fzfffffffa"};
    int n = 2;
    int k = 2;
    solution(research, n, k);
    return 0;
}