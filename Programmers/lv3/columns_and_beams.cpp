/*
기둥과 보 설치
https://programmers.co.kr/learn/courses/30/lessons/60061

?:
기둥은 바닥 위에 있거나 보의 한쪽 끝 부분 위에 있거나, 또는 다른 기둥 위에 있어야 합니다.
보는 한쪽 끝 부분이 기둥 위에 있거나, 또는 양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 합니다.

벽면의 크기 n, 기둥과 보를 설치하거나 삭제하는 작업이 순서대로 담긴 2차원 배열 build_frame이 매개변수로 주어질 때, 
모든 명령어를 수행한 후 구조물의 상태를 return 하도록 solution 함수를 완성해주세요.

!!!:
n은 5 이상 100 이하인 자연수입니다.
build_frame의 세로(행) 길이는 1 이상 1,000 이하입니다.
build_frame의 가로(열) 길이는 4입니다.
build_frame의 원소는 [x, y, a, b]형태입니다.

x, y는 기둥, 보를 설치 또는 삭제할 교차점의 좌표이며, [가로 좌표, 세로 좌표] 형태입니다.
a는 설치 또는 삭제할 구조물의 종류를 나타내며, 0은 기둥, 1은 보를 나타냅니다.
b는 구조물을 설치할 지, 혹은 삭제할 지를 나타내며 0은 삭제, 1은 설치를 나타냅니다.
벽면을 벗어나게 기둥, 보를 설치하는 경우는 없습니다.
바닥에 보를 설치 하는 경우는 없습니다.
구조물은 교차점 좌표를 기준으로 보는 오른쪽, 기둥은 위쪽 방향으로 설치 또는 삭제합니다.
구조물이 겹치도록 설치하는 경우와, 없는 구조물을 삭제하는 경우는 입력으로 주어지지 않습니다.

return 하는 배열은 가로(열) 길이가 3인 2차원 배열로, 각 구조물의 좌표를 담고있어야 합니다.
return 하는 배열의 원소는 [x, y, a] 형식입니다.
x, y는 기둥, 보의 교차점 좌표이며, [가로 좌표, 세로 좌표] 형태입니다.
기둥, 보는 교차점 좌표를 기준으로 오른쪽, 또는 위쪽 방향으로 설치되어 있음을 나타냅니다.
a는 구조물의 종류를 나타내며, 0은 기둥, 1은 보를 나타냅니다.
return 하는 배열은 x좌표 기준으로 오름차순 정렬하며, x좌표가 같을 경우 y좌표 기준으로 오름차순 정렬해주세요.
x, y좌표가 모두 같은 경우 기둥이 보보다 앞에 오면 됩니다.

시도1)
까다로운 구현문제이다. 주어진 조건을 만족하는지 확인하면서 명령을 실행하면된다.
이때 현재까지 건축된 구조물의 상태를 계속 확인하며 진행해야 한다.
기둥과 보를 나타낼 방법을 정하여야한다.
문제에서 기둥의 경우는 위치+위쪽, 보의 경우는 위치(x,y)에서 오른쪽으로 뻗는 방식이라고 알려줬다.
즉, 위치 정보와 기둥/보를 구분할 수 있는 구분자로 구성할 수 있다.
위치는 pos = pair<int, int>로 관리하도록 한다.
점수: 9.6

시도2)
구조체 필요없으므로 삭제
board를 vector<vector<int>>로 하여서 한 위치에 기둥과 보를 모두 설치가능한 경우를 처리할 수 없었음
점수: 36.8

시도3)
정렬 필요없으므로 삭제
설치시 보드 범위 넘어가는 경우 처리 추가
점수 그대로...

시도4)
가능한지 체크를 하고 설치하는 것에서
일단 설치하고 가능한지 검사하도록 변경
점수: 32.8...

시도5)
문제에서 없는 구조물을 삭제하거나 구조물을 겹치게 설치하는 경우는 없다고 했으므로
보드 전체를 구성하지 않고, 가능한 명령인지만 파악하여 저장하도록 변경 (set사용)
통과...
*/

#include <string>
#include <vector>
#include <set>

using namespace std;
using pos = pair<int,int>;  // (x,y)순 저장

// 보드 전체 확인
bool check_board(set<vector<int>>& board, int n)
{
    for(auto& e: board)
    {
        int  x = e[0], y = e[1];
        // 기둥이 위치 가능한지 확인
        if(e[2] == 0)
        {   // 바닥 위에 있거나 보의 한쪽 끝 부분 위에 있거나, 또는 다른 기둥 위
            if(y == 0 || board.find({x-1, y, 1}) != board.end() || board.find({x, y, 1}) != board.end() || board.find({x,y-1,0}) != board.end())
                continue;
            else
                return false;
        }
        // 보가 위치 가능한지 확인
        if(e[2] == 1)
        {   //  한쪽 끝 부분이 기둥 위에 있거나, 또는 양쪽 끝 부분이 다른 보와 동시에 연결
            if(board.find({x,y-1,0}) != board.end() || board.find({x+1,y-1,0}) != board.end() || (board.find({x-1,y,1}) != board.end() && board.find({x+1,y,1}) != board.end()))
                continue;
            else
                return false;
        }
    }
    return true;
}

// 시도 5
void construct(set<vector<int>>& board, pos point, int kind, int cmd, int n)
{
    int x = point.first, y=point.second;
    if(cmd == 0)    // 삭제
    {   // 없는 구조물을 삭제하거나 구조물을 겹치게 설치하는 경우는 없다
        board.erase({x,y,kind});    // 우선 삭제하고
        if(!check_board(board, n))
            board.insert({x,y,kind});   // 불가능하면 다시 원복
    }
    else            // 설치
    {   
        board.insert({x,y,kind});   // 우선 설치하고
        if(!check_board(board, n))
            board.erase({x,y,kind});    // 불가능하면 다시 원복
    }
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;

    // 보드 초기화
    set<vector<int>> answerSet;

    // 명령을 순차적으로 적용
    for(auto& e: build_frame)
    {
        pos point = {e[0], e[1]};   // (x, y)
        int kind = e[2];    // 0: 기둥, 1: 보
        int cmd = e[3]; // 0: 삭제, 1: 설치
        construct(answerSet, point, kind, cmd, n);
    }
    for(auto& e: answerSet)
        answer.push_back(e);

    return answer;
}

int main()
{
    int n = 5;
    vector<vector<int>> build_frame = {{1,0,0,1},{1,1,1,1},{2,1,0,1},{2,2,1,1},{5,0,0,1},{5,1,0,1},{4,2,1,1},{3,2,1,1}};

    solution(n, build_frame);
    return 0;
}