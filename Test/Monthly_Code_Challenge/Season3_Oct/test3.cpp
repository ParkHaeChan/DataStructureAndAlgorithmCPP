/*

격자의 행의 개수 n, 열의 개수 m, 정수 x와 y, 
그리고 쿼리들의 목록을 나타내는 2차원 정수 배열 queries가 매개변수로 주어집니다. 
n × m개의 가능한 시작점에 대해서 해당 시작점에 공을 두고 queries 내의 쿼리들을 순서대로 시뮬레이션했을 때, 
x행 y열에 도착하는 시작점의 개수를 return 하도록 solution 함수를 완성해주세요.

1 ≤ n ≤ 10^9
1 ≤ m ≤ 10^9
0 ≤ x < n
0 ≤ y < m
1 ≤ queries의 행의 개수 ≤ 200,000
queries의 각 행은 [command,dx] 두 정수로 이루어져 있습니다.
0 ≤ command ≤ 3
1 ≤ dx ≤ 109
이는 query(command, dx)를 의미합니다.

시도1)
격자의 크기가 매우 크다.
즉, 시뮬레이션 방식으로는 풀 수 없다.
반대로 생각해보면, x,y에서 출발해서 주어진 쿼리의 반대로 움직였을 때,
쿼리 몇개를 무시해도(범위 넘어가서 무시되는 경우 고려) [n,m]의 범위에 들어가는 모든 경우의 수라는 것을 알 수 있다.
하지만 이는 모든 쿼리 수가 20만개임을 고려하면 완전 탐색으로는 불가능한 수준이다.
어쩔 수 없이 문제 이해를 위해 제시된 방식을 시도해본다

시도2)
동적 계획법을 적용해 본다.
현재 위치[pos]에서 i번째 쿼리를 진행중일때 최종 위치로 x,y에 도달 가능한지를 저장하는 방식으로 사용
그래도 시간초과 뜬다 map으로 DP table 삼으면 성능이 오히려 더 떨어진다.

시도3)
x,y에서 거꾸로 가는 방식 시도

시간 끝나서 못 품....
*/
//#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using pos = pair<int, int>;

pos Move(pos next, int n, int m)
{
    int r = next.first;
    int c = next.second;
    if(r<0)
        r = 0;
    if(r >= n)
        r = n-1;
    if(c < 0)
        c = 0;
    if(c >= m)
        c = m-1;
    return pos{r,c};
}

vector<pos> DIRS = {{0,-1},{0,1},{-1,0},{1,0}}; // 0:열감소, 1: 열증가, 2:행감소 3: 행증가

long long solution(int n, int m, int x, int y, vector<vector<int>> queries) {
    long long answer = 0;

    map<pair<pos, int>, bool> DPMap;
    pos start = {x, y};
    for(int i=queries.size()-1; i>=0; --i)
    {   // 순차적으로 적용
        int cmd = queries[i][0];
        int dx = queries[i][1];
        int pr = start.first - DIRS[cmd].first*dx;
        int pc = start.second - DIRS[cmd].second*dx;
        pos prev{pr, pc};
        prev = Move(prev, n, m);
        // i번째 일때 이 위치에 있으면 도달 가능
        DPMap[{prev, i}] = true;
    }

    // 모든 시작 가능 위치
    for(int r=0; r<n; ++r)
    {
        for(int c=0; c<m; ++c)
        {
            pos start = {r, c};
            for(int i=0; i<queries.size(); ++i)
            {   // 순차적으로 적용
                if(DPMap[{start, i}])
                {   // 이미 계산된적 있는 경우
                    answer++;
                    break;
                }
                int cmd = queries[i][0];
                int dx = queries[i][1];
                int nr = start.first + DIRS[cmd].first*dx;
                int nc = start.second + DIRS[cmd].second*dx;
                pos next{nr, nc};
                next = Move(next, n, m);
                start = next;
            }
        }
    }

    return answer;
}

int main()
{
    int n = 2;
    int m = 2;
    int x = 0;
    int y = 0;
    vector<vector<int>> queries = {{2,1},{0,1},{1,1},{0,1},{2,1}};
    solution(n,m, x,y, queries);

    return 0;
}