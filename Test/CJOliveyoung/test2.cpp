#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

vector<string> parse_string(string parseStr)
{
    vector<string> parsed;
    istringstream iss(parseStr);
    string buffer;
    while(getline(iss, buffer, ' '))
    {
        parsed.push_back(buffer);
    }
    return parsed;  // 반환형이 참조형이면 삭제된 벡터에 대한 접근으로 에러가 발생한다
}

int solution(vector<string> subway, int start, int end) {
    int answer = 0;

    set<int> temp;
    vector<set<int>> subwaylines(subway.size(), temp);  // 역명은 같은 호선 내에선 안겹칠 것이므로 set사용
    set<int> stations;  // 모든 역명 저장, 이후 환승역 찾을 때 사용
    for(int i=0; i<subway.size(); ++i)
    {
        vector<string> parsed = parse_string(subway[i]);
        for(auto e: parsed)
        {
            int station = stoi(e);
            subwaylines[i].insert(station);
            stations.insert(station);
        }
    }

    // 모든 환승역을 미리 찾아둔다(역명은 100만까지 가능하므로 배열대신 map으로 저장)
    multimap<int, int> station_lineMap; // (역명, ?호선) 멀티맵
    for(auto e: stations)
    {
        for(int i=0; i<subwaylines.size(); ++i)
        {
            if(subwaylines[i].find(e) != subwaylines[i].end())
            {
                station_lineMap.insert({e, i});
            }
        }
    }

    // start를 포함하고 있는 line을 모두 찾는다
    queue<pair<int, int>> lineQ;
    vector<bool> visited(1001, false);  // line은 최대 1000개
    for(int i=0; i<subwaylines.size(); ++i)
    {
        if(subwaylines[i].find(start) != subwaylines[i].end())
        {
            lineQ.push({i,0});   // (line 번호 + 환승횟수) 저장
        }
    }
    
    // 최소 환승수를 구하므로 BFS를 시도
    // 각각의 line을 확인하여 end로 갈 수 있는지 확인
    while(!lineQ.empty())
    {   
        auto cur = lineQ.front(); lineQ.pop();
        if(visited[cur.first])
            continue;
        visited[cur.first] = true;
        if(subwaylines[cur.first].find(end) != subwaylines[cur.first].end())
        {   // end역으로 갈 수 있으면 종료
            answer = cur.second;
            break;
        }
        else
        {   // 갈 수 있는 다른 라인들을 시도: 환승역 찾아서 큐에 line추가
            for(auto e: subwaylines[cur.first])
            {
                if(station_lineMap.find(e) != station_lineMap.end())
                {
                    auto pair_iter = station_lineMap.equal_range(e);
                    for(auto it = pair_iter.first; it != pair_iter.second; ++it)
                    {
                        int line = (*it).second;
                        int change = cur.second;  // 환승수
                        if(visited[line])
                            continue;
                        lineQ.push({line, change+1});
                    }
                }
            }
        }
    }
    return answer;
}

int main()
{
    vector<string> sub = {"1 2 3 4 5 6 7 8","2 11","0 11 10","3 17 19 12 13 9 14 15 10","20 2 21"};
    int start = 1;
    int end = 9;

    cout << solution(sub, start, end) << endl;

    return 0;
}