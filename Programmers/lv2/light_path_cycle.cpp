/*
빛의 경로 사이클
https://programmers.co.kr/learn/courses/30/lessons/86052

각 칸마다 S, L, 또는 R가 써져 있는 격자가 있습니다. 당신은 이 격자에서 빛을 쏘고자 합니다. 이 격자의 각 칸에는 다음과 같은 특이한 성질이 있습니다.

빛이 "S"가 써진 칸에 도달한 경우, 직진합니다.
빛이 "L"이 써진 칸에 도달한 경우, 좌회전을 합니다.
빛이 "R"이 써진 칸에 도달한 경우, 우회전을 합니다.
빛이 격자의 끝을 넘어갈 경우, 반대쪽 끝으로 다시 돌아옵니다. 예를 들어, 빛이 1행에서 행이 줄어드는 방향으로 이동할 경우, 같은 열의 반대쪽 끝 행으로 다시 돌아옵니다.
당신은 이 격자 내에서 빛이 이동할 수 있는 경로 사이클이 몇 개 있고, 각 사이클의 길이가 얼마인지 알고 싶습니다. 경로 사이클이란, 빛이 이동하는 순환 경로를 의미합니다.

?:
격자의 정보를 나타내는 1차원 문자열 배열 grid가 매개변수로 주어집니다. 
주어진 격자를 통해 만들어지는 빛의 경로 사이클의 모든 길이들을 배열에 담아 오름차순으로 정렬하여 return 하도록 solution 함수를 완성해주세요.

!!!:
1 ≤ grid의 길이 ≤ 500
1 ≤ grid의 각 문자열의 길이 ≤ 500
grid의 모든 문자열의 길이는 서로 같습니다.
grid의 모든 문자열은 'L', 'R', 'S'로 이루어져 있습니다

시도1)
시작 위치는 1행 1열로 두고, 시작 방향은 4가지 방향을 모두 시도하여 서로 다른 사이클이 몇개가 있는지 센다.
이전 방향을 알아야 다음 방향을 바꿀때 적절히 변경할 수 있다. (순환식으로 작성: ULDR)
사이클 구분및 크기를 구하기 위해 간선 방문 여부를 저장해야한다. 
사이클 만들어지면 set에 저장 후 다른 사이클을 계산하면 set에 있는 사이클과 같은지 비교하여 같은 사이클인지 판단.
시간초과 + 실패
예시 입력에 대해선 모두 작동했으나 너무 무겁게 도는 느낌이다.

시도2)
문제를 자세히 살펴보니 한번구한 사이클에 사용된 간선은
중복해서 사용될 경우 같은 사이클을 생성하게 된다. (실제 거울과 같은 이치라 보면 됨)
즉, 모든 위치에서 빛을 4방향으로 시도하되, 사용된 간선이 사용될 경우는 사이클로 보고 즉시 시도 중단하면 된다.
시간초과는 사라졌지만 여전히 실패한다.

시도3)
암만봐도 어디가 틀린지 모르겠어서 문제 다시 읽어봤는데
정답을 오름차순 정렬로 하라고 했는데 내림차순으로 정렬해 버렸다...
통과

*/

#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using pos = pair<int, int>;
using edge = pair<pos, int>;    // 시작 위치와 이동방향을 함께 저장

vector<pos> directions = {{-1, 0}, {0, -1}, {1,0}, {0,1}};  // ULDR
set<edge> used_edges; // 시도 2

void range_check(int& r, int& c, int R, int C)
{   // 순환되도록 조정
    if(r < 0)
        r = R-1;
    else if(r == R)
        r = 0;
    if(c < 0)
        c = C-1;
    else if(c == C)
        c = 0;
}

//set<edge> find_cycle(edge start, vector<string>& grid)    // 시도 1
int find_cycle(edge start, vector<string>& grid)    // 시도 2
{
    // 시도1
    // set<edge> ret;  
    // start에서 시작하여 조건대로 진행한다
    // ret.insert(start);

    // 시도 2
    // if(used_edges.find(start) != used_edges.end())
    //     return 0;   // 이미 찾은 크기의 사이클

    //시도 3
    used_edges.insert(start);

    int R = grid.size();
    int C = grid[0].size();
    int ret = 1;
    while(true)  // 사이클되면 탈출
    {
        int dir = start.second;
        int r = start.first.first + directions[dir].first;
        int c = start.first.second + directions[dir].second;
        range_check(r,c, R, C);

        switch (grid[r][c])
        {
        case 'S':   // 직진
            break;
        case 'L':   //  좌회전
            dir = (dir+1)%4;
            break;
        case 'R':   // 우회전
            dir = (dir-1) < 0 ? 3:(dir-1); 
            break;
        }
        edge next = {{r,c}, dir};
        if(used_edges.find(next) != used_edges.end())
            break;
        else
        {
            used_edges.insert(next);
            start = next;
        }
        ret++;
    }
    return ret;
}

vector<int> solution(vector<string> grid) {
    vector<int> answer;
    //set<set<edge>> cycles;    // 시도 1

    int R = grid.size();
    int C = grid[0].size();
    // 모든 정점에서 4방향으로 시작하여 사이클 생기는 경우 확인
    for(int i=0; i<R; ++i)
    {
        if(used_edges.size() == R*C*4)
            break;  // 모든 간선 사용한 경우
        for(int j=0; j<C; ++j)
        {
            for(int k=0; k<directions.size(); ++k)
            {
                edge start = {{i,j}, k};
                if(used_edges.find(start) != used_edges.end())
                    continue;
                int cycle_size = find_cycle(start, grid);
                answer.push_back(cycle_size);
            }
        }
    }
    //sort(answer.begin(), answer.end(), [](auto back, auto front){return back > front;});
    sort(answer.begin(), answer.end()); // 시도 3: 실수 주의...

    return answer;
}

int main()
{
    vector<string> grid = {"SL","LR", "SL","LR"};
    solution(grid);
    return 0;
}