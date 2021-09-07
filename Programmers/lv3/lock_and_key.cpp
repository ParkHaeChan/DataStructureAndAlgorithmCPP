/*
자물쇠와 열쇠
https://programmers.co.kr/learn/courses/30/lessons/60059

잠겨있는 자물쇠는 격자 한 칸의 크기가 1 x 1인 N x N 크기의 정사각 격자 형태이고 특이한 모양의 열쇠는 M x M 크기인 정사각 격자 형태로 되어 있습니다.

자물쇠에는 홈이 파여 있고 열쇠 또한 홈과 돌기 부분이 있습니다. 
열쇠는 회전과 이동이 가능하며 열쇠의 돌기 부분을 자물쇠의 홈 부분에 딱 맞게 채우면 자물쇠가 열리게 되는 구조입니다. 
자물쇠 영역을 벗어난 부분에 있는 열쇠의 홈과 돌기는 자물쇠를 여는 데 영향을 주지 않지만, 
자물쇠 영역 내에서는 열쇠의 돌기 부분과 자물쇠의 홈 부분이 정확히 일치해야 하며 열쇠의 돌기와 자물쇠의 돌기가 만나서는 안됩니다. 
또한 자물쇠의 모든 홈을 채워 비어있는 곳이 없어야 자물쇠를 열 수 있습니다.

?:
열쇠를 나타내는 2차원 배열 key와 자물쇠를 나타내는 2차원 배열 lock이 매개변수로 주어질 때, 
열쇠로 자물쇠를 열수 있으면 true를, 열 수 없으면 false를 return 하도록 solution 함수를 완성해주세요.

!!!:
key는 M x M(3 ≤ M ≤ 20, M은 자연수)크기 2차원 배열입니다.
lock은 N x N(3 ≤ N ≤ 20, N은 자연수)크기 2차원 배열입니다.
M은 항상 N 이하입니다.
key와 lock의 원소는 0 또는 1로 이루어져 있습니다.
0은 홈 부분, 1은 돌기 부분을 나타냅니다.

시도1)
우선 키를 회전하고 이동하는 시뮬레이션 구현이 필요할 것이다.
회전은 90도 회전을 반복적으로 4회 적용해보는 것으로 모든 경우를 처리할 수 있고,
이동은 적어도 1칸은 걸쳐야 한다는 것을 고려하여 상하좌우 모두 M-1칸 이내로 움직여야한다.
점수: 35. 시간초과 실패가 많이 발생

시도2)
디버그로 배열 상태를 직접 찍어서 제대로 구현했는지 확인->이상 무,,,
DFS할 떄 visited 배열을 안써서 재귀가 쓸데없이 많이 돌았다...
점수: 41. 이번에는 시간초과는 발생하지 않았다.

시도3)
lock이랑 key의 크기가 다를 수 있다는 점을 간과했다.
DFS말고 키를 lock이랑 겹치는 크기 만큼 옮기면서 매칭하도록 변경
점수: 54점.. 좀 더 고칠 부분이 있나봄.

시도4)
lock과 키를 합치는 2차원 배열을 만들어 보기로 했다.
시작은 [0][0] 끝은 lock이 끝나는 지점[N-1][N-1]까지를
키 적용 시작 위치로 넣고 시도후 lock이 차는지 확인한다.

시도5)
... 회전을 마지막에 시도하니까 통과했다.
회전을 언제 시도하든 어차피 90도를 4번 돌리면 360가 되면서 상관없는줄 알았는데
암만 고민해도 뭐가 틀렸는지 모르겠어서 이거만 옮겨봤는데 통과했다.
수상해서 다시 회전을 위로 올렸는데 통과가 됐다.
키를 함수에서 회전 후 vector<vector<int>> 형으로 반환하는데,
그걸 key가 다시 받는 경우는 제대로 작동했으나, (key = rotate_90(key);)
반복문 밖에서 vector<vector<int>> temp_key; 를 선언한 뒤
반복문 내에서 temp_key = rotate_90(key); 이런 식으로 받으면 문제가 생겼다.

*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> rotate_90(vector<vector<int>>& key)
{
    // 90도 회전: 첫행 -> 끝열로 보낸다
    int N = key.size(); // 입력은 정사각행렬
    vector<vector<int>> temp(N, vector<int>(N, 0));
    for(int row=0; row<N; ++row)
    {   // 행을 열로 복사
        for(int col = 0; col<N; ++col)
        {
            temp[col][N-(row+1)] = key[row][col];
        }
    }
    return temp;
}

// 시도 4
bool match_key(int i, int j, vector<vector<int>>& key, vector<vector<int>> board)
{   // board는 복사해서 가져옴
    int M = key.size();

    // 키를 보드에 맞춘다
    for(int ki=0; ki<M; ++ki)
    {
        for(int kj=0; kj<M; ++kj)
        {   
            board[i+ki][j+kj] += key[ki][kj];
        }
    }
    // 키는 맞췃는데 lock에 1이 아닌 부분 있으면(0이거나 2가 된 경우)
    int B = board.size();
    for(int row=M-1; row <= B-M; ++row)
        for(int col=M-1; col <= B-M; ++col)
            if(board[row][col] != 1)
                return false;
    return true;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    int N = lock.size();    // 시도 3: lock위를 돌아다니며 맞춰 볼 것이다(최소 한칸은 걸쳐야 하므로 한쪽방향으로 2N-1회 움직인다)
    int M = key.size();
    vector<vector<int>> temp_key;
    for(int rotate=0; rotate<4; ++rotate)
    {
        // 회전: 임시 배열에 저장한 경우 반복문 끝날 때 갱신해야 회전을 연속적으로 적용할 수 있음(실수하기 쉬우므로 주의)
        temp_key = rotate_90(key);
        // 시도4
        int N = lock.size();
        int M = key.size();
        int B = (M-1)*2 + N;
        vector<vector<int>> board(B, vector<int>(B, 0));

        // lock을 보드 중심에 둔다
        for(int row=M-1; row <= B-M; ++row)
            for(int col=M-1; col <= B-M; ++col)
                board[row][col] = lock[row-(M-1)][col-(M-1)];

        // [i][j]위치를 시작으로 key를 맞춰본다
        for(int i=0; i<=B-M; ++i)
        {
            for(int j=0; j<=B-M; ++j)
            {
                if(match_key(i, j, temp_key, board))
                    return true;
            }
        }
        // 키 갱신(다음 회전 위해)
        key = temp_key;
    }
    return false;
}

int main()
{
    vector<vector<int>> key = {{0, 0, 0}, {1, 0, 0}, {0, 1, 1}};
    vector<vector<int>> lock = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};

    cout << solution(key, lock) << endl;
    return 0;
}