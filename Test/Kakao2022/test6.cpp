/*
type이 1일 경우는 적의 공격을 의미합니다. 건물의 내구도를 낮춥니다.
type이 2일 경우는 아군의 회복 스킬을 의미합니다. 건물의 내구도를 높입니다.

효율성 테스트 실패
---시험 후---
시도2
DP문제로 가정하여 board상태와 skill에 대해 전체를 저장해버리는 식으로 구현해봤다.
메모리 부족할 수도? --> 이 방법도 사실 이전 방식과 별반 차이가 없는 것 같다.
상태를 확인하는데 꽤 많은 시간이 소모될 것이 자명해보인다.

시도3
skill의 구간을 DP로 저장하는 방식을 사용하면,
적어도 같은 구간에 대해 적용되는 skill을 여러번 계산하는 수고는 줄일 수 있다.
이 부분도 효율적으로 압축하는 방법이 있으면 더 나은 방법을 찾을 수 있을 것 같다.
*/

#include <string>
#include <vector>
#include <map>

using namespace std;

// 시도2
// map<pair<vector<vector<int>>, vector<int>>, vector<vector<int>>> DP;
// 시도3
map<vector<int>, int> DP;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;

    int R = board.size();
    int C = board[0].size();

    for(auto e: skill)
    {
        /* 시도2
        if(DP.find({board, e}) != DP.end())
        {
            board = DP[{board, e}];
            continue;
        }
        auto& calc_state = DP[{board, e}];
        */
        int type = e[0];
        int r1 = e[1], c1 = e[2];
        int r2 = e[3], c2 = e[4];
        int degree = e[5];
        /* 시도2
        if(type == 1)
        {
            for(int i=r1; i<=r2; ++i)
            {
                for(int j=c1; j<=c2; ++j)
                {
                    board[i][j] -= degree;
                }
            }
        }
        if(type == 2)
        {
            for(int i=r1; i<=r2; ++i)
            {
                for(int j=c1; j<=c2; ++j)
                {
                    board[i][j] += degree;
                }
            }
        }
        calc_state = board;
        */
        // 시도3
        if(type == 1)
            DP[{r1,c1,r2,c2}] -= degree;
        if(type == 2)
            DP[{r1,c1,r2,c2}] += degree;
    }
    for(auto& e: DP)
    {
        auto& v = e.first;
        int deg = e.second;
        for(int i=v[0]; i<=v[2]; ++i)
        {
            for(int j=v[1]; j<=v[3]; ++j)
            {
                board[i][j] += deg;
            }
        }
    }
    for(int i=0; i<R; ++i)
    {
        for(int j=0; j<C; ++j)
        {
            if(board[i][j] > 0)
                answer++;
        }
    }

    return answer;
}

int main()
{
    vector<vector<int>> board = {{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5}};
    vector<vector<int>> skill = {{1,0,0,3,4,4},{1,2,0,2,3,2},{2,1,0,3,1,2},{1,0,1,3,3,1}};

    solution(board, skill);

    return 0;
}