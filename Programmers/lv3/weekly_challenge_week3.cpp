/*
테이블 위에 놓인 퍼즐 조각을 게임 보드의 빈 공간에 적절히 올려놓으려 합니다. 
게임 보드와 테이블은 모두 각 칸이 1x1 크기인 정사각 격자 모양입니다. 
이때, 다음 규칙에 따라 테이블 위에 놓인 퍼즐 조각을 게임 보드의 빈칸에 채우면 됩니다.

조각은 한 번에 하나씩 채워 넣습니다.
조각을 회전시킬 수 있습니다.
조각을 뒤집을 수는 없습니다.
게임 보드에 새로 채워 넣은 퍼즐 조각과 인접한 칸이 비어있으면 안 됩니다.

현재 게임 보드의 상태 game_board, 테이블 위에 놓인 퍼즐 조각의 상태 table이 매개변수로 주어집니다. 
규칙에 맞게 최대한 많은 퍼즐 조각을 채워 넣을 경우, 총 몇 칸을 채울 수 있는지 return 하도록 solution 함수를 완성해주세요.

!!!:
3 ≤ game_board의 행 길이 ≤ 50
game_board의 각 열 길이 = game_board의 행 길이
즉, 게임 보드는 정사각 격자 모양입니다.
game_board의 모든 원소는 0 또는 1입니다.
0은 빈칸, 1은 이미 채워진 칸을 나타냅니다.
퍼즐 조각이 놓일 빈칸은 1 x 1 크기 정사각형이 최소 1개에서 최대 6개까지 연결된 형태로만 주어집니다.
table의 행 길이 = game_board의 행 길이
table의 각 열 길이 = table의 행 길이
즉, 테이블은 game_board와 같은 크기의 정사각 격자 모양입니다.
table의 모든 원소는 0 또는 1입니다.
0은 빈칸, 1은 조각이 놓인 칸을 나타냅니다.
퍼즐 조각은 1 x 1 크기 정사각형이 최소 1개에서 최대 6개까지 연결된 형태로만 주어집니다.
game_board에는 반드시 하나 이상의 빈칸이 있습니다.
table에는 반드시 하나 이상의 블록이 놓여 있습니다.

시도1)
블록을 구분할 수 있어야한다. 이때 회전된 경우를 같은 경우로 볼 수 있도록해야한다.
1,2개 까지는 구성할 수 있는 도형이 하나 뿐이다.(회전이 의미가 없다)
3개로 구성할 수 있는 경우 부터는 만들 수 있는 가지수가 여러가지가 생긴다.
최종적으로 6개짜리를 만들 수 있기 때문에, 이 정도까지는 모든 경우를 고려할 수 있도록 작성할 수 있다.
3개로 구성할 수 있는 경우는 2가지
4개로 구성할 수 있는 경우는 7가지
5개로 구성할 수 있는 경우는 ...

이런 식으로 풀기에는 하드코딩할게 너무 많아진다.
문제에서 회전이 가능하다고 했으므로, 회전은 중심을 기준으로 돌 것이므로 중심을 기준으로 N-1개를 붙인 경우를 생각하고,
돌리는 방법을 생각해보는 식으로 구현해야 될 것 같다.
N이 홀수인 경우는 N * N 격자에서 중심부터 세면 될 것이고, 짝수인 경우는 N+1 격자에서 중심부터 세나가면된다.
회전된 경우는 N*N 행렬 전체를 90도 회전하는 방법을 구현하여 4번 적용하면 모든 경우를 찾을 수 있다.
이제 회전 된 경우와 겹치지 않도록 중심을 기준으로 위나 오른쪽으로만 뻗어나가도록 제한을 걸어야한다고 생각했는데,
이런 식으로는 실제로 중복인데 중복이 아닌것 처럼 작동하는 경우가 있다.
예를 들면, 3개로 구성할 수 있는 경우로 아래와 같은 경우가 발생한다.

001 011
011 010
000 000

이 두 경우는 사실 회전시키면 같은 경우인데 중심을 기준으로 돌리면 서로 다른 케이스만 나온다.
이는 중심의 인접한 위치에 붙일 자리가 있는데 다른 곳에 붙이게 되는 경우에 발생한다. (첫줄의 001에서 1이 있는 자리가 그 자리이다)

이 점을 고려하면 BFS를 사용하여 중심에서 뻗어나가는 방식으로 세면 되는 것을 확인할 수 있다.
(매번 N칸이 채워지는 순간 4방향 돌린 경우를 확인하여 다음 회전된 case로 중복이 발생하지 않도록하는 방식으로 진행한다)
이 상태는 map을 사용하여 저장한다. ( map<vector<vector<int>>, int> (보드 상태, 일련 번호) 저장)

이제 문제는 보드에서 각 도형의 중심을 어떻게 찾는가 이다.
1,2개 짜리는 찾는 족족 가능하므로 상관없지만, 3개 부터는 중심을 찾아야한다.
생각나는 방법은 모든 위치에서 시작해서 BFS로 최소 거리로 모든 곳을 방문할 수 있는 위치를 찾는 것이 있다.
이는 도형 크기가 작아서 가능한 방식이다.

전체적으로는 다음과 같이 작동한다.

1) 가능한 모든 도형을 미리 계산하여 map에 저장한다.
1-1) 중심 기준으로 BFS로 뻗어나가면서 회전한 경우를 하나의 map에 일련번호와 매칭해서 저장한다.

2) 테이블에서 도형을 찾는다.
2차원 배열을 반복문을 통해 순차적으로 접근하면서 1인 위치에서 BFS를 시도한다.
2-1) 인접한 도형 개수가 2이하이면, 테이블 내에 이런 도형이 몇개인지만 파악하면 된다.
2-2) 3개 부터는 어떤 모양인지도 알아야 하므로, 중심 위치를 찾는다.
2-3) 중심 위치에서 N칸씩 잡고 map에서 일련번호를 찾아 이 일련번호의 도형이 몇개인지 센다. (map사용<일련 번호, 개수>)

3) 게임 보드에서 빈칸이 있는 칸에서 테이블에서와 마찬가지로 모양을 찾아서 시도하여 일치하면 카운트를 줄인다.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
문제 접근을 잘 못한듯 하여 다른 방식을 참고하여 재시도 해보려 한다.

돌리는 주체를 퍼즐 조각이 아닌 게임 보드로 바꾸면 연산수가 훨씬 줄어 들 수 있다.
즉, 퍼즐은 그대로 가져와서 맞춰보고 맞는거 있으면 게임 보드에서 해당 자리를 지우고,
게임 보드를 90도 돌리고 다시 남은 퍼즐을 맞춰보고 하는 식으로 풀어야 한다.
이때는 퍼즐을 각각 찾아서 시작 위치를 기준으로 어떻게 분포하고 있는지를 저장하는 방식으로 각 퍼즐을 저장한다
vector<pair<int,int>> 로 하나의 퍼즐 조각을 저장할 수 있다. (왼쪽 최상단을 [0][0]위치로 보고 상대적 위치를 저장한다)

*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;
using pos = pair<int,int>;

const vector<pos> directions = {{-1,0},{1,0},{0,-1},{0,1}};   // UDLR (상하좌우)

bool InRange(pos cur, int N)
{
    if(cur.first >= 0 && cur.first < N && cur.second >= 0 && cur.second < N)
        return true;
    return false;
}

void print_board(vector<vector<int>> input)
{
    const int R = input.size();
    const int C = input[0].size();
    for(int i=0; i<R; ++i)
    {
        for(int j=0; j<C; ++j)
        {
            cout << input[i][j] << " ";
        }
        cout << endl;
    }
    cout << "rotate 90..."<< endl;
}

vector<vector<int>> rotate_90(vector<vector<bool>> input)
{   // 입력이 정사각행렬인 경우만 들어온다 가정
    const int R = input.size();
    const int C = input[0].size();
    vector<int> temp(C, 0);
    vector<vector<int>> ret(R, temp);   // 회전된 결과를 담을 2차원 배열

    // 90도 회전: 이번에 옮길 행이 회전된 행렬에서는 열이 된다는 것을 파악
    for(int r=0; r<R; ++r)
    {   // 행 선택하기
        auto& row = input[r];
        // 이번 행은 회전된 행렬에서는 오른쪽 끝부터 열을 채우는데 사용된다
        for(int c=0; c<C; ++c)
        {   // 열 채우기 [위애서 아래로 채우고][위치고정] = [선택된 행의 값 차례로 적용]
            ret[c][C-r-1] = row[c];    // 끝번 열 부터 반대로 채워 나감
        }
    }

    return ret;
}

map<vector<vector<int>>, int> BFS_makeFigures(int N)
{   
    if((N%2) == 0)
        N++;
    vector<int> temp(N, 0);
    vector<vector<int>> board(N, temp);
    map<vector<vector<int>>, int> retMap;

    int center = N/2;

    vector<bool> vistemp(N, false);
    vector<vector<bool>> visited(N, vistemp);
    // 도형의 중심
    pos start = {center, center};
    // 중심에서 BFS로 상하좌우순으로 뻗어나가도록 작성
    queue<pair<pos, int>> bfsQ;

    bfsQ.push({start, 1});  // 1개 차있는 상황임을 나타냄
    while(!bfsQ.empty())
    {
        auto cur = bfsQ.front(); bfsQ.pop();
        int row = cur.first.first;
        int col = cur.first.second;
        if(visited[row][col])
            continue;
        visited[row][col] = true;

        if(cur.second == N) // 만드려는 크기까지 만들었으면
        {   // 90도씩 돌려가면서 만들어본다.
            static int ID = 0;  // 일련 번호
            for(int rotate=1; rotate<=4; ++rotate)
            {
                vector<vector<int>> figure = rotate_90(visited);
                retMap[figure] = ID;
            }
            ID++;
        }
        else
            for(auto dir: directions)
            {
                int next_r = row+dir.first;
                int next_c = col+dir.second;
                if(!InRange({next_r, next_c}, N))
                    continue;

                if(!visited[next_r][next_c])
                    bfsQ.push({{next_r, next_c}, cur.second+1});
            }
    }
}

int CountSize(pos start) // DFS
{
    int ret = 1;


    return ret;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = -1;
    const int TABLESIZE = game_board.size();

    vector<map<vector<vector<int>>, int>> figureMapVect;
    // 가능한 모든 도형 크기로 나올 수 있는 모양 모두 계산하여 저장
    // 2이하는 그냥 개수만 세면된다. (돌릴 필요 없음)
    for(int figuresize=3; figuresize<=6; ++figuresize)
        figureMapVect.push_back(BFS_makeFigures(figuresize));

    // table에서 해당 도형이 몇개 있는지 파악한다
    // 도형이 시작되는 위치를 찾는다
    for(int row = 0; row<TABLESIZE; ++row)
    {
        for(int col = 0; col<TABLESIZE; ++col)
        {
            if(table[row][col] == 1)
            {   // 몇개로 구성되어 있는지 센다
                // ...이 방식으로는 불가능하다고 판단하여 중단 새로 작성 예정
            }
        }
    }

    return answer;
}

int main()
{
    vector<vector<int>> game_board = {{1,1,0,0,1,0},{0,0,1,0,1,0},{0,1,1,0,0,1},{1,1,0,1,1,1},{1,0,0,0,1,0},{0,1,1,1,0,0}};
    vector<vector<int>> table = {{1,0,0,1,1,0},{1,0,1,0,1,0},{0,1,1,0,1,1},{0,0,1,0,0,0},{1,1,0,1,1,0},{0,1,0,0,0,0}};

    cout << solution(game_board, table) << endl;

    return 0;
}