/*
거리두기 확인하기
https://programmers.co.kr/learn/courses/30/lessons/81302

아래와 같은 규칙으로 대기실에 거리를 두고 앉도록 안내하고 있습니다.

대기실은 5개이며, 각 대기실은 5x5 크기입니다.
거리두기를 위하여 응시자들 끼리는 맨해튼 거리가 2 이하로 앉지 말아 주세요. 
(두 테이블 T1, T2가 행렬 (r1, c1), (r2, c2)에 각각 위치하고 있다면, T1, T2 사이의 맨해튼 거리는 |r1 - r2| + |c1 - c2| 입니다.)
단 응시자가 앉아있는 자리 사이가 파티션으로 막혀 있을 경우에는 허용합니다.

?:
5개의 대기실을 본 죠르디는 각 대기실에서 응시자들이 거리두기를 잘 기키고 있는지 알고 싶어졌습니다. 
자리에 앉아있는 응시자들의 정보와 대기실 구조를 대기실별로 담은 2차원 문자열 배열 places가 매개변수로 주어집니다. 
각 대기실별로 거리두기를 지키고 있으면 1을, 한 명이라도 지키지 않고 있으면 0을 배열에 담아 return 하도록 solution 함수를 완성해 주세요.

!!!:
places의 행 길이(대기실 개수) = 5
places의 각 행은 하나의 대기실 구조를 나타냅니다.
places의 열 길이(대기실 세로 길이) = 5
places의 원소는 P,O,X로 이루어진 문자열입니다.
places 원소의 길이(대기실 가로 길이) = 5
P는 응시자가 앉아있는 자리를 의미합니다.
O는 빈 테이블을 의미합니다.
X는 파티션을 의미합니다.
입력으로 주어지는 5개 대기실의 크기는 모두 5x5 입니다.
return 값 형식
1차원 정수 배열에 5개의 원소를 담아서 return 합니다.
places에 담겨 있는 5개 대기실의 순서대로, 거리두기 준수 여부를 차례대로 배열에 담습니다.
각 대기실 별로 모든 응시자가 거리두기를 지키고 있으면 1을, 한 명이라도 지키지 않고 있으면 0을 담습니다.
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;
using pos = pair<int,int>;

bool InRange(pos cur, int R, int C)
{
    if(cur.first >= 0 && cur.first < R && cur.second >= 0 && cur.second < C)
        return true;
    return false;
}

int check_distance(const vector<string>& room)
{
    // P인 곳의 좌표를 모두 저장한 뒤 BFS로 2이내의 거리를 방문했을 때 다른 P를 만나면 0반환
    // 장애물은 못지나가도록 구현
    vector<pos> Pvect;
    for(int row=0; row<room.size(); ++row)
    {
        for(int col=0; col<room[row].size(); ++ col)
        {
            if(room[row][col] == 'P')
                Pvect.push_back({row,col});
        }
    }

    // 맨해튼 거리 계산(BFS)
    vector<pos> dirs = {{0, -1}, {0,1}, {-1, 0}, {1, 0}};   // LRUD
    for(int i=0; i<Pvect.size(); i++)
    {
        pos start = Pvect[i];

        queue<pair<pos, int>> bfsQ; // 위치, 맨해튼거리 함께 저장
        vector<vector<bool>> visited(room.size(), vector<bool>(room[0].size()));
        visited[start.first][start.second] = true;
        bfsQ.push({start,0});

        while(!bfsQ.empty())
        {
            auto cur = bfsQ.front(); bfsQ.pop();

            if(cur.second <= 2 && cur.first != start)
            {   // 2거리 내에 사람 있는지 검사
                if(room[cur.first.first][cur.first.second] == 'P')
                    return 0;
            }
            if(cur.second > 2)    // 거리 초과하면 더이상 탐색X
                continue;

            for(auto dir: dirs)
            {
                pos next = {cur.first.first + dir.first, cur.first.second + dir.second};
                if(InRange(next, room.size(), room[0].size()) && !visited[next.first][next.second])
                {
                    visited[next.first][next.second] = true;
                    if(room[next.first][next.second] == 'X')    // 칸막이면 못감(visited는 true로 둬서 반복 접근 막기)
                        continue;
                    bfsQ.push({next, cur.second+1});
                }
            }
        }
    }

    return 1;
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;

    for(int place=0; place < places.size(); ++place)
    {
        answer.push_back(check_distance(places[place]));
    }

    return answer;
}

int main()
{
    vector<vector<string>> places = {
        {"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"}, 
    {"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"},
     {"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"},
      {"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"},
       {"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}};

    solution(places);

    return 0;
}