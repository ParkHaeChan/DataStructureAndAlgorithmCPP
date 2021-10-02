/*
합승 택시 요금
https://programmers.co.kr/learn/courses/30/lessons/72413

?:
A, B 두 사람이 s에서 출발해서 각각의 도착 지점까지 택시를 타고 간다고 가정할 때, 
최저 예상 택시요금을 계산해서 return 하도록 solution 함수를 완성해 주세요.

!!!:
지점갯수 n은 3 이상 200 이하인 자연수입니다.
지점 s, a, b는 1 이상 n 이하인 자연수이며, 각기 서로 다른 값입니다.
즉, 출발지점, A의 도착지점, B의 도착지점은 서로 겹치지 않습니다.
fares는 2차원 정수 배열입니다.
fares 배열의 크기는 2 이상 n x (n-1) / 2 이하입니다.
예를들어, n = 6이라면 fares 배열의 크기는 2 이상 15 이하입니다. (6 x 5 / 2 = 15)
fares 배열의 각 행은 [c, d, f] 형태입니다.
c지점과 d지점 사이의 예상 택시요금이 f원이라는 뜻입니다.
지점 c, d는 1 이상 n 이하인 자연수이며, 각기 서로 다른 값입니다.
요금 f는 1 이상 100,000 이하인 자연수입니다.
fares 배열에 두 지점 간 예상 택시요금은 1개만 주어집니다. 즉, [c, d, f]가 있다면 [d, c, f]는 주어지지 않습니다.
출발지점 s에서 도착지점 a와 b로 가는 경로가 존재하는 경우만 입력으로 주어집니다.

시도1)
모든 쌍 최단거리를 찾은 후 (floyd)
s + 공유 + a
s + 공유 + b
가 최소가 되는 경우를 찾는다.
무한대를 너무 크게 정의하면
연산하다가 오버플로우가 발생하여 음수가 되서 최소값에 반영되는 문제가 발생

시도2)
무한대값 10만 1로 조정(1~10만 범위로 주어졌으므로)
효율성 테스트는 통과했는데 실패가 뜨는 케이스가 몇개 있다.
85점

시도3)
혹시 자료형 범위 문제인가 싶어서 long long으로 시도했는데 아니었다.
방법이 틀린것 같지는 않아서 힌트 참고했는데,
무한대 값을 적절히 크게 잡아주면된다고한다.
그래서 다시 long long으로 고치고 무한대를 10만 1에서 987654321로 바꿔주니 통과했다
아무래도 한 구간의 최대크기가 10만인데 다른 곳을 거쳐가는 경우까지 고려하면 무한대를 10만 1로 잡으면 문제가 발생할 수 밖에 없다.
그렇다고 무한대를 음수로 설정하면 합계산시 양수가 되는 경우 존재하지 않는 경로를 존재하는 것처럼 처리하는 문제가 생길 수 있다.
주의가 필요한 문제인 것 같다.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    // FLOYD
    // init
    const int INF = 987654321; // 987654321넣었더니 오버플로우 발생하며 음수되서 답이 틀리게 나오는 경우가 생김
    vector<vector<long long>> ShortestTable(n+1, vector<long long>(n+1, INF));  // 초기거리 무한대
    for(int i=0; i<=n; ++i)
        ShortestTable[i][i] = 0;    // 대각성분 초기화
    for(auto& e: fares)
    {
        ShortestTable[e[0]][e[1]] = e[2];
        ShortestTable[e[1]][e[0]] = e[2];
    }
    // relaxing
    for(int k=1; k<=n; ++k)
    {
        for(int i=1; i<=n; ++i)
        {
            for(int j=1; j<=n; ++j)
            {
                ShortestTable[i][j] = min(ShortestTable[i][j], ShortestTable[i][k]+ShortestTable[k][j]);
            }
        }
    }
    // s에서 공통으로 가는 위치를 하나 정한 뒤 각자 목적지가는 최소값
    long long answer = ShortestTable[s][a] + ShortestTable[s][b]; // 각자 따로 가는 경우
    for(int mid=1; mid<=n; ++mid)
    {   // 합승하다가 따로가는 경우
        answer = min(answer, ShortestTable[s][mid]+ShortestTable[mid][a]+ShortestTable[mid][b]);
    }

    return answer;
}

int main()
{
    // vector<int> nsab = {6,4,6,2};
    // vector<vector<int>> fares = {{4, 1, 10}, {3, 5, 24}, {5, 6, 2}, {3, 1, 41}, {5, 1, 24}, {4, 6, 50}, {2, 4, 66}, {2, 3, 22}, {1, 6, 25}};
    vector<int> nsab = {7,3,4,1};
    vector<vector<int>> fares = {{5, 7, 9}, {4, 6, 4}, {3, 6, 1}, {3, 2, 3}, {2, 1, 6}};
    solution(nsab[0],nsab[1],nsab[2],nsab[3],fares);

    return 0;
}