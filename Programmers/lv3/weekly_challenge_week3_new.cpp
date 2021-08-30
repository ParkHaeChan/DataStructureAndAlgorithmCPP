/*

돌리는 주체를 퍼즐 조각이 아닌 게임 보드로 바꾸면 연산수가 훨씬 줄어 들 수 있다.
즉, 퍼즐은 그대로 가져와서 맞춰보고 맞는거 있으면 게임 보드에서 해당 자리를 지우고,
게임 보드를 90도 돌리고 다시 남은 퍼즐을 맞춰보고 하는 식으로 풀어야 한다.
이때는 퍼즐을 각각 찾아서 시작 위치를 기준으로 어떻게 분포하고 있는지를 저장하는 방식으로 각 퍼즐을 저장한다
vector<pair<int,int>> 로 하나의 퍼즐 조각을 저장할 수 있다. (왼쪽 최상단을 [0][0]위치로 보고 상대적 위치를 저장한다)

시도1) 꽤 많은 TestCase를 통과하지 못하는 것 같다
4,6,7,8,9,10, 12,13에서 실패 했다.
시도2)
fit_puzzle에서 뭔가 처리가 애매한 부분이 있는 것 같아서 고쳐봤다.
고쳤는데 오히려 더 점수가 떨어졌다. 이부분이 확실히 문제인 것 같다.
시도3)
game_board가 1인 부분에서 블록을 확인할 때 보드에서 안지우면, 블록의 모양이 옆으로 펴져있는 경우
같은 블록을 여러번 세는 문제가 있을 수 있다. 즉 임시 game_board를 만들어 두었다가
확실히 삭제되는 케이스만 적용한 다음 회전해서 재시도하는 식이어야 한다.
시도4) 4번 케이스는 정답 찾은 후 break로 반복문 탈출 안시켜서 생기는 문제였다.
puzzles에서 puzzle 삭제할 때 std::find로 처리하는 부분이 문제있을 수 있어보여서 바꿨다.
시도5) 통과
bfs돌릴 떄 큐에 추가할 때 블록 위치 정보를 미리 넣었는데 그렇게하면
중복 방문을 차단하기는 했지만 모종의 문제가 발생할 수 있는 것 같다.


*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using pos = pair<int,int>;

int TABLESIZE;

const vector<pos> directions = {{-1,0},{1,0},{0,-1},{0,1}};   // UDLR (상하좌우)

bool InRange(pos cur, int N)
{
    if(cur.first >= 0 && cur.first < N && cur.second >= 0 && cur.second < N)
        return true;
    return false;
}

vector<vector<int>> rotate_90(vector<vector<int>> input)
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

vector<pos> find_puzzle_bfs(pos start, vector<vector<int>>& table)
{
    // start에서 bfs를 시도하여 퍼즐 크기및 모양을 파악한다
    vector<pos> puzzle_figure;
    queue<pos> bfsQ;
    vector<bool> temp(TABLESIZE, false);
    vector<vector<bool>> visited(TABLESIZE, temp);
    bfsQ.push(start);

    while(!bfsQ.empty())
    {
        auto cur = bfsQ.front(); bfsQ.pop();
        if(visited[cur.first][cur.second])
            continue;
        visited[cur.first][cur.second] = true;
        puzzle_figure.push_back(cur);   // 시도5) visited 확정 될 때 블록에 추가
        for(auto dir : directions)  // 4방향 시도
        {
            pos next = {cur.first + dir.first, cur.second + dir.second};
            if(!InRange(next, TABLESIZE) || visited[next.first][next.second])
                continue;
            if(table[next.first][next.second] == 1)
            {
                bfsQ.push(next);
                // 시도5) 여기서 추가하지 않고 직접 방문 할 때만 추가하도록 변경
                //puzzle_figure.push_back(cur);
            }
        }
    }
    // start를 [0,0]위치로 한 상대적 위치로 치환
    for(int i=0; i<puzzle_figure.size(); ++i)
    {
        // 찾은 퍼즐은 table에서 지워야 다음 퍼즐 찾을 때 방해되지 않는다.
        table[puzzle_figure[i].first][puzzle_figure[i].second] = 0;

        puzzle_figure[i].first -= start.first;
        puzzle_figure[i].second -= start.second;
    }

    return puzzle_figure;
}

void flip_board(vector<vector<int>>& game_board)
{
    for(int row=0; row<TABLESIZE; ++row)
        for(int col=0; col<TABLESIZE; ++col)
            if(game_board[row][col] == 1)
                game_board[row][col] = 0;
            else if(game_board[row][col] == 0)
                game_board[row][col] = 1;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = 0;
    TABLESIZE = game_board.size();

    // 1) 퍼즐 조각을 찾아서 상대적 위치를 저장한다.
    vector<vector<pos>> puzzles;
    for(int row=0; row<TABLESIZE; ++row)
    {
        for(int col=0; col<TABLESIZE; ++col)
        {
            if(table[row][col] == 1)
            {
                puzzles.push_back(find_puzzle_bfs({row, col}, table));
            }
        }
    }

    // 2) game board를 빈칸이 1이 되도록 뒤집는다
    // (이후 퍼즐이 들어간 차리는 0으로 채울 것임)
    flip_board(game_board);

    // 매 반복시 모든 퍼즐을 맞춰보고 게임판을 90도씩 회전시킨다
    for(int rotate=0; rotate<4; ++rotate)
    {
        // 시도3) 게임보드 원본 상태 저장
        vector<vector<int>> original_gb;
        copy(game_board.begin(), game_board.end(), std::back_inserter(original_gb));
        // 현재 보드 상태에서 빈칸을 찾는다
        for(int row=0; row<TABLESIZE; ++row)
        {
            for(int col=0; col<TABLESIZE; ++col)
            {
                if(game_board[row][col] == 1)   // 빈칸 찾음
                {
                    // 시도3) 이 위치에 어떤 블록이 들어갈 수 있는지 확인해본다 (이 블록이 보드에서 제거되야 중복으로 안센다)
                    vector<pos> block = find_puzzle_bfs({row, col}, game_board);    // 치환까지 된 상태이다
                    
                    // 이 블록과 완전 일치하는 퍼즐 확인
                    for(int i=0; i<puzzles.size(); ++i)
                    {
                        int k=0;
                        if(puzzles[i].size() == block.size())   // 크기 같고
                        {
                            for(k=0; k<block.size(); ++k)
                            {
                                if(block[k] != puzzles[i][k])   // 전부 일치
                                    break;
                            }
                            if(k == block.size())
                            {   // 일치하면 보드에서 지우고 정답 개수 추가
                                find_puzzle_bfs({row, col}, original_gb);  // 원본 보드에서 확정 삭제
                                // 시도 4) auto it = find(puzzles.begin(), puzzles.end(), puzzle);
                                puzzles.erase(puzzles.begin()+i);  // puzzles에서도 삭제
                                answer += block.size();
                                break;  // case 4 해결
                            }
                        }
                    }
                }
            }
        }
        game_board = rotate_90(original_gb);
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