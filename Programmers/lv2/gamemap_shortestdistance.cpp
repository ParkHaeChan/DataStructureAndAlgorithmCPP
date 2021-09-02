/*
게임맵 최단거리
https://programmers.co.kr/learn/courses/30/lessons/1844

?:
게임 맵의 상태 maps가 매개변수로 주어질 때, 
캐릭터가 상대 팀 진영에 도착하기 위해서 지나가야 하는 칸의 개수의 최솟값을 return 하도록 solution 함수를 완성해주세요. 
단, 상대 팀 진영에 도착할 수 없을 때는 -1을 return 해주세요.

!!!:
maps는 n x m 크기의 게임 맵의 상태가 들어있는 2차원 배열로, n과 m은 각각 1 이상 100 이하의 자연수입니다.
n과 m은 서로 같을 수도, 다를 수도 있지만, n과 m이 모두 1인 경우는 입력으로 주어지지 않습니다.
maps는 0과 1로만 이루어져 있으며, 0은 벽이 있는 자리, 1은 벽이 없는 자리를 나타냅니다.
처음에 캐릭터는 게임 맵의 좌측 상단인 (1, 1) 위치에 있으며, 상대방 진영은 게임 맵의 우측 하단인 (n, m) 위치에 있습니다.

시도1)
간단한 최단거리는 BFS 시도
통과
*/

#include <vector>
#include <queue>

using namespace std;
using pos = pair<int, int>;

bool InRange(pos p, int R, int C)
{
    if(0 <= p.first && p.first < R && 0 <= p.second && p.second < C)
        return true;
    return false;
}

int BFS(vector<vector<int>>& maps)
{
    int R = maps.size();
    int C = maps[0].size();

    queue<pair<pos, int>> bfsQ;
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    visited[0][0] = true;
    pos start = {0,0};
    bfsQ.push({start, 1});  // 시작 위치 포함

    vector<pos> dirs = {{0,-1},{0,1},{-1,0},{1,0}}; // L R U D

    while(!bfsQ.empty())
    {
        auto cur = bfsQ.front(); bfsQ.pop();

        if(cur.first.first == R-1 && cur.first.second == C-1)   // 목적지 도달
            return cur.second;  // 거리 반환

        for(pos dir: dirs)
        {
            pos next = {cur.first.first + dir.first, cur.first.second + dir.second};
            if(InRange(next, R, C) && !visited[next.first][next.second])
            {
                visited[next.first][next.second] = true;
                if(maps[next.first][next.second] == 0)  // 벽인 경우
                    continue;
                bfsQ.push({next, cur.second+1});
            }
        }
    }
    // 목적지 도달 못하는 경우
    return -1;
}

int solution(vector<vector<int> > maps)
{
    int answer = 0;
    answer = BFS(maps);

    return answer;
}

int main()
{
    vector<vector<int>> maps = {{1,0,1,1,1},{1,0,1,0,1},{1,0,1,1,1},{1,1,1,0,1},{0,0,0,0,1}};
    solution(maps);

    return 0;
}