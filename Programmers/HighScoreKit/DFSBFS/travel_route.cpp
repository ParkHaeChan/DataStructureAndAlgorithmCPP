/*
문제: https://programmers.co.kr/learn/courses/30/lessons/43164

갈 수 있는 경로를 vector에 순차적으로 저장해야 하는 문제
주의: 갈 수 있는 곳이 2군데 이상이면 알파벳 순으로 빠른 곳을 먼저 간다
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

/*
주어진 항공권을 모두 이용하여 여행경로를 짜려고 합니다. 항상 "ICN" 공항에서 출발합니다.

모든 공항은 알파벳 대문자 3글자로 이루어집니다.
주어진 공항 수는 3개 이상 10,000개 이하입니다.
tickets의 각 행 [a, b]는 a 공항에서 b 공항으로 가는 항공권이 있다는 의미입니다.
주어진 항공권은 모두 사용해야 합니다.
만일 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 합니다.
모든 도시를 방문할 수 없는 경우는 주어지지 않습니다.

해설:
DFS로 가는데 갈수 있는 곳이 여러 곳일 경우 그중 알파벳 순으로 빠른데를 먼저간다.
*/
vector<bool> used;  // ticket 사용 여부
stack<string> route;
bool DFS(vector<vector<string>>& tickets, string& current)
{
    for(int i = 0; i<tickets.size(); ++i)
    {
        // current에서 출발하는 사용되지 않은 티켓을 찾는다.(정렬되어 있음)
        if(tickets[i][0] == current && !used[i])
        {
            used[i] = true; // 티켓 사용

            if(DFS(tickets, tickets[i][1]))
            {
                route.push(tickets[i][1]);
                return true;
            }
            else
            {
                used[i] = false;    // 다음에 시도한다
                continue;
            }
        }
    }

    // 안되는 case: 티켓이 남는데 더 이상 진행 할 수 없는 경우 -> 이전 티켓 무효로 돌리고 다음에 사용
    bool done = true;
    for(auto e: used)
        if(!e)
        {
            done = false;
            break;
        }
    if(done)
        return true;
    else
        return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    int N = tickets.size();
    used = vector<bool>(N, false);
    string begin = "ICN";
    
    // tickets를 (알파벳 순으로) 정렬해 둔다 (전부 3글자짜리 string임)
    sort(tickets.begin(), tickets.end(), [](auto& a, auto& b){
        // a,b의 원소는 string 두 개 뿐이다.
        if(a[0] == b[0])
        {
            for(int i=0; i<3; ++i)
            {
                if(a[1][i] == b[1][i])
                    continue;
                else
                    return a[1][i] < b[1][i];
            }
        }
        else
        {
            for(int i=0; i<3; ++i)
            {
                if(a[0][i] == b[0][i])
                    continue;
                else
                    return a[0][i] < b[0][i];
            }
        }
    });
    /* 정렬 테스트
    for(auto& vect : tickets)
        cout << vect[0] << " : " << vect[1] << endl;
    */
    DFS(tickets, begin);
    // 경로는 역순으로 저장되므로 stack에 넣었다가 꺼내면서 answer에 넣는다.
    answer.push_back(begin);
    while(!route.empty())
    {
        string top = route.top(); route.pop();
        answer.push_back(top);
    }

    return answer;
}

int main()
{
    //vector<vector<string>> tickets = {{"ICN", "JFK"}, {"HND", "IAD"}, {"JFK", "HND"}};
    vector<vector<string>> tickets = {{"ICN", "SFO"}, {"ICN", "ATL"}, {"SFO", "ATL"}, {"ATL", "ICN"}, {"ATL","SFO"}};

    vector<string> str_vect = solution(tickets);

    for(string& s: str_vect)
        cout << "[" << s << "], ";
    cout << endl;

    return 0;
}