#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

bool InRange(int x, int y)
{
    if(x <= 5 && x >= -5 && y <= 5 && y >= -5)
        return true;
    else
        return false;
}

int solution(string dirs) {
    int answer = 0;

    // save edges
    using point = pair<int,int>;
    using line = pair<point, point>;

    vector<point> dir = {{-1, 0}, {1,0}, {0,1}, {0,-1}};   // L, R, U, D

    map<line, bool> usedEdges;
    point cur = {0,0};
    int dx, dy;
    for(int i=0; i<dirs.size(); ++i)
    {
        switch(dirs[i])
        {
            case 'L':
                dx = dir[0].first;
                dy = dir[0].second;
                break;
            case 'R':
                dx = dir[1].first;
                dy = dir[1].second;
                break;
            case 'U':
                dx = dir[2].first;
                dy = dir[2].second;
                break;
            case 'D':
                dx = dir[3].first;
                dy = dir[3].second;
                break;
        }
        point next_pos = {cur.first+dx, cur.second+dy};
        if(!InRange(next_pos.first, next_pos.second))
        {
            continue;
        }
        // 추가로 cur == next_pos 인 경우 걸러주는 작업이 필요할 수 있다. (이 경우 edge가 아닌 vertex를 저장한 것이 된다)
        usedEdges[{cur, next_pos}] = true;
        usedEdges[{next_pos, cur}] = true;
        cur = next_pos;
    }
    // 양방향이 저장되어있으므로 반으로 줄여서 출력
    answer = usedEdges.size()/2;
    
    return answer;
}

int main()
{
    string dirs = "UUUDDDDDDDDDUUUU";

    cout << solution(dirs) << endl;

    return 0;
}