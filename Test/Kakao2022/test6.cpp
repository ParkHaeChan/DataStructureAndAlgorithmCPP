/*
type이 1일 경우는 적의 공격을 의미합니다. 건물의 내구도를 낮춥니다.
type이 2일 경우는 아군의 회복 스킬을 의미합니다. 건물의 내구도를 높입니다.

효율성 테스트 실패
---시험 후---
DP문제로 가정하여 board상태와 skill에 대해 전체를 저장해버리는 식으로 구현해봤다.
메모리 부족할 수도?
*/

#include <string>
#include <vector>
#include <map>

using namespace std;

map<pair<vector<vector<int>>, vector<int>>, vector<vector<int>>> DP;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;

    int R = board.size();
    int C = board[0].size();

    for(auto e: skill)
    {
        if(DP.find({board, e}) != DP.end())
        {
            board = DP[{board, e}];
            continue;
        }
        auto& calc_state = DP[{board, e}];
        int type = e[0];
        int r1 = e[1], c1 = e[2];
        int r2 = e[3], c2 = e[4];
        int degree = e[5];
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