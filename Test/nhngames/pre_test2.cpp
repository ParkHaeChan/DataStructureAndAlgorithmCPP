#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using pos = pair<int, int>;

vector<vector<int>> rotate_90(vector<vector<int>> cctv)
{
    int N = cctv.size();
    vector<vector<int>> ret(N, vector<int>(N));
    for(int r=0; r<N; ++r)
    {
        vector<int>& row = cctv[r];
        int idx=0;
        for(int c=N-1; c>=0; c--)
        {
            ret[r][c] = row[idx++];
        }
    }
    return ret;
}

bool InRange(pos cur, int N)
{
    if(0<= cur.first && cur.first < N && 0<=cur.second && cur.second < N)
        return true;
    return false;
}

vector<pos> DIRS = {{-1, 0}, {0,-1},{1,0},{0,1}};  // ULDR

int BFS(vector<vector<int>>& Board, vector<vector<int>> CCTV)
{
    // 시작: 좌상단, 끝: 우하단
    int answer = 0;
    int N = Board.size();
    pos start = {0,0};
    queue<pair<pos, int>> bfsQ;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    visited[0][0] = true;
    bfsQ.push({start, 0});

    bool able = false;
    int cctvCnt = 0;
    while(!bfsQ.empty())
    {
        auto cur = bfsQ.front(); bfsQ.pop();
        auto curpos = cur.first;
        if(curpos.first == N-1 && curpos.second == N-1)
        {
            able = true;
            answer = cur.second;
            break;
        }
        // cctv 회전
        for(int i=0; i<(cur.second-cctvCnt)%4; ++i)
            CCTV = rotate_90(CCTV);
        if(CCTV[curpos.first][curpos.second] == 1)
        {   // cctv걸리면 정지 1회
            cur.second++;
            cctvCnt++;
        }
        for(int d=0; d<DIRS.size(); ++d)
        {
            pos next = {curpos.first+DIRS[d].first, curpos.second+DIRS[d].second};
            if(InRange(next, N))
            {
                if(visited[next.first][next.second])
                    continue;
                if(Board[next.first][next.second]==1)
                    continue; // 벽
                visited[next.first][next.second] = true;
                bfsQ.push({next, cur.second+1});    //  1칸 이동시간 추가
            }
        }
    }
    if(!able)
        return -1;  // 도달 불가능한 경우
    return answer;
}

int main()
{
    freopen("input2.txt", "r", stdin);
    int N;
    cin >> N;
    vector<vector<int>> Board(N, vector<int>(N));
    for(int r=0; r<N; ++r)
        for(int c=0; c<N; ++c)
            cin >> Board[r][c];
    
    vector<vector<int>> CCTV(N, vector<int>(N, 0));
    int boundary = N/2;
    for(int r=0; r<boundary; ++r)
        for(int c=0; c<boundary; ++c)
            CCTV[r][c] = 1;

    int answer = BFS(Board, CCTV);
    cout << answer << endl;

    return 0;
}