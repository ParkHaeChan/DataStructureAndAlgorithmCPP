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

    vector<pair<int,int>> dir = {{-1, 0}, {1,0}, {0,1}, {0,-1}};   // L, R, U, D

    // save edges
    using point = pair<int,int>;
    using line = pair<point, point>;

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
        point temp = {cur.first+dx, cur.second+dy};
        if(!InRange(temp.first, temp.second))
        {
            continue;
        }
        usedEdges[{cur, temp}] = true;
        usedEdges[{temp, cur}] = true;
        cur = temp;
    }
    answer = usedEdges.size()/2;
    
    return answer;
}

int main()
{
    string dirs = "UUUDDDDDDDDDUUUU";

    cout << solution(dirs) << endl;

    return 0;
}