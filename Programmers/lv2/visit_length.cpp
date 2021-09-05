/*
방문 길이
https://programmers.co.kr/learn/courses/30/lessons/49994

게임 캐릭터를 4가지 명령어를 통해 움직이려 합니다. 명령어는 다음과 같습니다.

U: 위쪽으로 한 칸 가기
D: 아래쪽으로 한 칸 가기
R: 오른쪽으로 한 칸 가기
L: 왼쪽으로 한 칸 가기

캐릭터는 좌표평면의 (0, 0) 위치에서 시작합니다. 좌표평면의 경계는 왼쪽 위(-5, 5), 왼쪽 아래(-5, -5), 오른쪽 위(5, 5), 오른쪽 아래(5, -5)로 이루어져 있습니다.

이때, 우리는 게임 캐릭터가 지나간 길 중 캐릭터가 처음 걸어본 길의 길이를 구하려고 합니다. 
예를 들어 위의 예시에서 게임 캐릭터가 움직인 길이는 9이지만, 캐릭터가 처음 걸어본 길의 길이는 7이 됩니다. 
(8, 9번 명령어에서 움직인 길은 2, 3번 명령어에서 이미 거쳐 간 길입니다)
단, 좌표평면의 경계를 넘어가는 명령어는 무시합니다.

시도1)
점이 아닌 길을 저장해야 한다.
그리고 이미 갔던길을 또 가는 경우는 길이에 포함하지 않아야 한다.
이를 위해 pair와 set을 적절히 활용한다.
*/

#include <string>
#include <set>

using namespace std;

using pos = pair<int, int>;
using edge = pair<pos, pos>;

bool InRange(pos cur)
{   // 좌표평면의 경계는 왼쪽 위(-5, 5), 왼쪽 아래(-5, -5), 오른쪽 위(5, 5), 오른쪽 아래(5, -5)로 이루어져 있습니다
    if(-5 <= cur.first && cur.first <= 5 && -5 <= cur.second && cur.second <= 5)
        return true;
    return false;
}

int solution(string dirs) {
    int answer = 0;
    // 시작 위치
    pos cur = {0,0};  // x,y 순
    pos next;
    set<edge> visited;
    // 이동
    for(char cmd: dirs)
    {
        pos temp;
        switch (cmd)
        {
        case 'U':
            temp = {cur.first, cur.second+1};
            break;
        case 'D':
            temp = {cur.first, cur.second-1};
            break;
        case 'R':
            temp = {cur.first+1, cur.second};
            break;
        case 'L':
            temp = {cur.first-1, cur.second};
            break;
        }
        if(!InRange(temp))
            continue;   // 좌표평면의 경계를 넘어가는 명령어는 무시
        else
            next = temp;
        
        edge curedge = {cur, next};
        edge rcuredge = {next, cur};
        if(visited.find(curedge) == visited.end() && visited.find(rcuredge) == visited.end())
        {   // 방문한 적 없는 경우
            visited.insert(curedge);
            visited.insert(rcuredge);
            answer++;
        }
        cur = next; // 이동
    }

    return answer;
}

int main()
{
    string dirs = "LULLLLLLU";

    solution(dirs);

    return 0;
}