#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
문제: https://programmers.co.kr/learn/courses/30/lessons/42897
거의 똑같은 문제를 풀어봤다.
(스티커 뜯기 문제랑 똑같다: https://github.com/ParkHaeChan/DataStructureAndAlgorithmCPP/blob/main/Programmers/Dynamic%20Programming/StickerGathering/stickergather.cpp)
원형으로 배치되어 있는 조건은 시작점이 어디든 상관이 없다.
이런 경우는 그냥 원하는 곳에서 시작하면되는데,
편하게 생각하려면 그냥 0번 인덱스를 시작으로 생각하고 진행하면 된다.
조건에 의해 인접한 집은 털 수가 없다.
즉, 0번을 털기로 했으면 1번과 끝번을 털 수 없다.

이 조건을 만족하기 위해 다음과 같이 시작을 분기하여 진행해야한다.
1) 0번 집부터 털고 시작한 경우: 이 경우 끝번 집은 털 수 있어도 털지 않는다.
2) 0번 집을 안털고 시작한 경우: 이 경우 끝번 집을 털 수 있으면 턴다.

그럼 DP 테이블은 다음 처럼 구성된다.
DP[현재까지 진행한 집의 번호] = 최대 money
부분문제는 다음처럼 구성된다.
DP[i] = max(DP[i-1] , DP[i-2] + money[i]) : max(i번 집 안털 경우, i번 집 털 경우)
DP[0] : 1)의 경우 = money[0], 2)의 경우 = 0
DP[1] : 1)의 경우 = money[0], 2)의 경우 = money[1] -> 이때 DP[2]는 money[1] 또는 0 + money[2]
*/

int solution(vector<int> money) {
    int answer = 0;
    
    int N = money.size();
    vector<int> DP(N, 0);
    
    // 1) 0번 집 털고 시작하는 경우: 마지막 집은 털 수 있어도 안턴다.
    DP[0] = money[0];
    // 주의! 0을 선택했으니까 1은 선택안해서 0이겠지하고 이런 실수를 할 때가 있음: DP[1] = 0;(최적부분구조 조건실패)
    DP[1] = money[0];
    for(int i=2; i<N-1; ++i)
    {
        DP[i] = max(DP[i-1], DP[i-2]+money[i]);
    }
    answer = max(answer, DP[N-2]);
    
    // 2) 0번 집 안털고 시작하는 경우: 마지막 집까지 진행
    DP = vector<int>(N, 0); // DP 테이블 초기화
    DP[0] = 0;
    DP[1] = money[1];
    // 이때는 또 DP[2] = money[1];로 지정하는 실수할 수 있음->DP[2]는 money[1] 또는 0(DP[0]) + money[2]이다.
    for(int i=2; i<N; ++i)
    {
        DP[i] = max(DP[i-1], DP[i-2]+money[i]);
    }
    answer = max(answer, DP[N-1]);
    
    return answer;
}