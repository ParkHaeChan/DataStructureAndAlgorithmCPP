#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
조건을 만족하면서 최대한 많은 곳을 방문(스티커를 떼면)하면
점수를 최대로 얻을 수 있다.
즉, 그래프 탐색 문제이다.
모든 정점에서 시작하여 조건을 만족하며 DFS방식으로 최대 깊이에 도달했을 때
누적된 점수를 계산하여 answer와 비교후 최대 값만 저장

오답: 이 경우 다음 처리가 추가되어야 한다.
재 방문을 하기 위해 visited를 false로 풀 때, 이번 방문 이전에도 visited가 true였으면
그대로 true로 둬야 중복을 피할 수 있다...
그리고 이 문제는 놀랍게도 DP로 풀이가 가능하다.
즉, 쌩 DFS 방식으로는 시간초과가 뜬다.

DP로 풀 때는 다음이 관건이다. 원형으로 보지 않고 1자 배열로 풀어서 보면,
i번쨰까지 고려했을 때 최대 값으로 DP[i]를 나타 낼 수 있고,
인접 위치는 못쓰는 조건 때문에 부분 문제는 다음과 같이 2가지로 분류된다.
DP[i-1]에서 온 경우: 이 경우 DP[i]는 i번째 스티커를 뜯지 않는다.
DP[i-2]에서 온 경우: 이 경우 DP[i]는 i번째 스티커를 뜯는다.

그리고 원형으로 이어져 있다는 점은 다음과 같은 방식으로 처리할 수 있다.
0번 스티커를 뜯으며 시작할 경우: DP[0] = sticker[0], DP[N-1](마지막)은 뜯을 수 있다 하더라도 고려하지 않는다
0번 스티커를 안뜯고 시작할 경우: DP[0] = 0, DP[N-1]까지도 뜯을 수 있다면 고려한다.
*/

int answer = 0;

void DFS(vector<int>& sticker, vector<bool>& visited, int start, int sum)
{
    int ssize = sticker.size();
    
    //탈출 조건
    int fin=0;
    for(fin=0; fin<ssize; ++fin)
        if(!visited[fin])
            break;
    if(fin == ssize)
    {
        answer = max(answer, sum);
        return;
    }

    int ret = 0;
    for(int i=start; i<ssize; ++i)
    {
        if(!visited[i])
        {
            visited[(i+ssize-1)%ssize] = true;
            visited[i] = true;
            visited[(i+1)%ssize] = true;
            DFS(sticker, visited, i, sum+sticker[i]);
            visited[(i+ssize-1)%ssize] = false;
            visited[i] = false;
            visited[(i+1)%ssize] = false;
        }
    }
}

int solution(vector<int> sticker)
{
    /*  오답: DP로 접근할 수 있는 문제인데 어떻게 접근해야 할지를 몰랐음.
    vector<bool> visited(sticker.size());
    DFS(sticker, visited, 0, 0);
    */
    int  ret = 0;
    int N = sticker.size();
    vector<int> DP(N, 0);

    //초기 조건: 0번 스티커부터 뜯을 경우
    DP[0] = sticker[0];
    DP[1] = sticker[0]; //0을 선택 했으므로 1까지 고려했을 때 최대는 0만 선택한 경우

    // 0번 뜯으면 마지막(N-1)은 못뜯으므로 고려X.(순환고리)
    for(int i=2; i<N-1; ++i)    
    {
        //DP[i] = max( DP[i-1] + 0 , DP[i-2] + sticker[i] )
        DP[i] = max( DP[i-1], DP[i-2] + sticker[i]);
    }
    ret = max(DP[N-1], DP[N-2]);    // max( DP[N-1], DP[N-2] + (sticker[N-1] = 0 마지막 못 듣으므로) )

    //DP테이블 초기화
    DP = vector<int>(N, 0); // reserve(N)은 초기화에 못 씀

    //초기 조건: 0번 스티커 안뜯는 경우
    DP[0] = 0;
    DP[1] = sticker[1];
    //DP[2] = sticker[1]; // 1부터 뜯었으므로 2번은 선택 불가능해진다(즉, DP[0] + sticker[2])인 경우 불가능.(X)
    // 오류: [1]을 선택 안하고 sticker[2]를 선택하는 경우도 가능하다.
    // 즉, DP[2] = max(DP[1], sticker[2])이다. 이는 DP[0] = 0 이므로 반복문 내에서 처리 가능하다.

    //첨에 선택X 이므로 마지막(N-1)까지 가능.(순환고리)
    for(int i=2; i<N; ++i)    
    {
        //DP[i] = max( DP[i-1] + 0 , DP[i-2] + sticker[i] )
        DP[i] = max( DP[i-1], DP[i-2] + sticker[i]);
    }
    ret = max(ret, DP[N-1]);

    return ret;
}

int main()
{
    vector<int> sticker = {14, 6, 5, 11, 3, 9, 2, 10};

    cout << solution(sticker) << endl;

    return 0;
}