
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 못 푼 문제

string Answer;
int N, M, K;
vector<pair<bool,int>> edges;
vector<vector<pair<bool,int>>> Graph;   // bool: link, int: K-num

// cycle이 있는지 검사하기 위해 visited[src]를 true로 지정 후
// dest 부터 DFS로 순회하며 src로 돌아오는지 확인해 본다.
bool DFS(int here, int src, vector<bool>& visited)
{
    if(visited[here])
    {
        if(here == src)
            return true;    // 이 간선으로 인해 Cycle 존재
        else
            return false;   // 다른 간선으로 인해 존재
    }
    
    visited[here] = true;

    // 모든 정점 중 갈 수 있는 정점에 방문
    for(int i=1; i<=N; ++i)
    {
        if(Graph[here][i].first)
        {
            // return DFS(...)쓰면 안됨: return 값이 false면 다른 루트도 검사해 봐야함
            if(DFS(i, src, visited))
                return true;
        }
    }
    return false;
}

int main(int argc, char** argv)
{
	int T, test_case;

	freopen("input3.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
        cin >> N >> M >> K;
        edges = vector<pair<bool,int>>(N+1, {false, -2});
        Graph = vector<vector<pair<bool,int>>>(N+1, edges);
        for(int i=0; i<M; ++i)
        {
            int s, d;   // source, destination
            cin >> s >> d;
            Graph[s][d] = {true, -1}; // connect, fixed: -1
        }
        vector<pair<int, int>> Kvect;   // 실수로: Kvect(K)로 초기화했다가 반복문 횟수 이상하게 돌아서 수정...
        Answer = "";
        for(int i=0; i<K; ++i)
        {
            int s, d;
            cin >> s >> d;
            Kvect.push_back({s,d});
            // 이미 역방향이 연결되어 있으면
            if(Graph[d][s].first)
            {
                Answer += "1";  // CYCLE 생기므로 바꾼다
                continue;
            }
            // 이미 연결되어 있으면
            if(Graph[s][d].first)
            {
                Answer += "0";  // 어차피 못 바꾸므로 그대로 둔다.
                continue;
            }
            // 나머지는 이번에 새로 연결되는 경우
            Graph[s][d] = {true, i};
            Answer += "0";  // 일단은 그대로 둔다.
        }
        //cout << Answer << endl;
        // 이외 역순으로 처리하여 사전순 우선되도록 처리
        for(int i=K-1; i>=0; --i)
        {
            int s = Kvect[i].first;
            int d = Kvect[i].second;
            if(Answer[i] == '1' && Graph[d][s].second == -1)    //변경불가능한 간선 따라간거면 넘긴다.
                continue;

            if(Answer[i] == '1')    // 뒤집힌 경우
            { 
                vector<bool> visited(N+1, false);
                visited[d] = true; // d->s 갔다 치고 s에서 출발
                bool cycle = DFS(s, d, visited);    //d로 돌아오면 cycle존재
                // cycle이 있으면 원복시킨다.
                if(cycle)
                {
                    Graph[s][d].first = true;
                    Graph[d][s].first = false;
                    Answer[i] = '0';
                }
                else
                {   // 반대일 때 cycle이 없지만 원래대로 해도 cycle이 안생기면? -굳이 바꿔서 순서 높이면 안된다.
                    vector<bool> visited(N+1, false);
                    visited[s] = true; // s->d 갔다 치고 d에서 출발
                    bool cycle = DFS(d, s, visited);    //s로 돌아오면 cycle존재
                    if(!cycle)
                    {   // cycle 안생기면
                        Graph[s][d].first = true;
                        Graph[d][s].first = false;
                        Answer[i] = '0';
                    }
                }
            }
            else
            {
                // 앞에서 바뀐경우 (연결 끊어지면)
                if(!Graph[s][d].first)
                {   // 바뀐걸로 따라 간다.
                    Answer[i] = '1';
                    continue;
                }

                // cycle이 있으면
                vector<bool> visited(N+1, false);
                visited[s] = true; // s->d 갔다 치고 d에서 출발
                bool cycle = DFS(d, s, visited);    //s로 돌아오면 cycle존재
                if(cycle)
                {
                    Graph[s][d].first = false;
                    Graph[d][s].first = true;
                    Answer[i] = '1';
                }
            }
        }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}