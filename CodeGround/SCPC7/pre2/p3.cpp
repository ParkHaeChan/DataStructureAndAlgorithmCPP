/*
표적지의 점수 배치를 입력 받아 가장 많은 총 점수를 받는 방법을 찾는 프로그램을 작성하라.
표적지는 크기가 N×N인 격자이다.
입력 파일에는 여러 테스트 케이스가 포함될 수 있다.
파일의 첫째 줄에 테스트 케이스의 개수를 나타내는 자연수 T 가 주어지고,
이후 차례로  T 개의 테스트 케이스가 주어진다. (1 ≤ T ≤ 50) 
각 테스트 케이스의 첫 줄에는 표적지의 크기 N과 퍼지는 정도 K가 주어진다. (1≤K≤N≤600). 
둘째 줄부터 N개의 각 줄에는 N개의 수가 주어진다. 이 수들은 각 칸에 배정된 점수들이다. 점수의 절대값은 최대 109이다.
*/

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

long long Answer;
int N, K;

vector<vector<long long>> Map;
using position = pair<int, int>;    // (row, col)

bool InRange(position cur)
{
    if(0 <= cur.first && cur.first < N && 0 <= cur.second && cur.second < N)
        return true;
    return false;
}

// 산탄총 점수 계산
long long BFS(position start)
{
    long long score = 0;
    // start 위치를 기준으로 K만큼 거리를 BFS로 방문
    vector<position> DIR = {{0, -1}, {0, 1}, {1,0},{-1,0}};    // LRDU(matrix: row,col)
    map<position, int> visited; // 0:방문X 1: Q내부, 2: 확정
    
    queue<pair<position, int>> Q;
    Q.push({start, K});

    while(!Q.empty())
    {
        pair<position, int> cur = Q.front(); Q.pop();
        if(visited[cur.first]>1)
            continue;

        visited[cur.first] = 2;
        if(InRange(cur.first))
            score += Map[cur.first.first][cur.first.second]*cur.second;

        for(int i=0; i<DIR.size(); ++i)
        {   // 모든 다음 방문이 0점 처리되는 경우
            if(cur.second-1 == 0)
                break;

            position next;
            next.first = cur.first.first+DIR[i].first;
            next.second = cur.first.second+DIR[i].second;
            
            if(visited[next]>0)
                continue;
            else
            {
                visited[next] = 1;  // 큐에 들어 있는 상태
                Q.push({next, cur.second-1});
            }
        }
    }
    
    return score;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
	int T, test_case;

	freopen("input3.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
        cin >> N >> K;

		Answer = 0;
        // MAP 입력 받기
        vector<long long> col(N, 0);
        Map = vector<vector<long long>>(N, col);
        for(int row=0; row<N; ++row)
        {
            for(int col=0; col<N; ++col)
            {
                cin >> Map[row][col];
            }
        }

        long long temp = 0;
        for(int i=-K; i<N+K; ++i)
        {
            for(int j=-K; j<N+K; ++j)
            {
                temp = max(temp, BFS({i,j}));
            }
        }
        Answer = temp;
        
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}