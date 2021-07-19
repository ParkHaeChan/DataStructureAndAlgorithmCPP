
#include <iostream>
#include <vector>
#include <string>

/*
덜 푼 문제이다.
brute force 시도하려다 못 함.
*/

using namespace std;

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

void change_edge_direction(int src, int dst)
{
    Graph[src][dst].first = true;
    Graph[dst][src].first = false;
}

bool brute_force(int current, vector<pair<int,int>>& Kvect)
{
    // 탈출 조건: current가 마지막일 때, cycle이 발생하지 않는 경우 발견
    if(current == Kvect.size())
    {
        // 모든 정점에서 시도하여 cycle이 발생하는지 검사
        
        for(int i=1; i<=N; ++i)
        {
            vector<bool> visited(N+1, false);
            if(DFS(i, i, visited))   // cycle 발생 시
                return false;
        }
        return true; // 가능한 Answer 찾음
    }    
    int s = Kvect[current].first;
    int d = Kvect[current].second;
    if(Graph[s][d].second == -1 && Graph[d][s].second == -1)    // 이미 확정된 변경 불가능한 간선
    {   // 그대로만 진행
        if(brute_force(current+1, Kvect))
            return true;    // 가능한 경우 찾음
    }
    else
    {
        // 이번 edge를 그대로 두고 cylce 검사를 진행
        if(brute_force(current+1, Kvect))
            return true;    // 가능한 경우 찾음

        // 이번 edge를 반대로 두고 cycle 검사를 진행
        change_edge_direction(d, s);
        if(Answer[current] == '0')
            Answer[current] = '1';
        else
            Answer[current] = '0';
        if(brute_force(current+1, Kvect))
            return true;    // 가능한 경우 찾음
        //  못찾은 경우 다시 원래대로
        change_edge_direction(s, d);
        if(Answer[current] == '0')
            Answer[current] = '1';
        else
            Answer[current] = '0';
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
            // 이미 역방향이 연결되어 있고 변경 불가능하면
            if(Graph[d][s].first && Graph[d][s].second == -1)
            {
                Answer += "1";  // CYCLE 생기므로 바꾼다
                Graph[s][d] = {false, -1}; // fix : 더 이상 못 바꾸므로 고정
                continue;
            }
            // 이미 연결되어 있고 못 바꾸면
            if(Graph[s][d].first && Graph[s][d].second == -1)
            {
                Answer += "0";  // 바꾸면 Cycle 생기므로 그대로 둔다.
                Graph[d][s] = {false, -1}; // fix
                continue;
            }
            // 나머지는 이번에 새로 결정되는 경우
            Graph[s][d] = {true, i};
            Answer += "0";  // 일단은 그대로 둔다.
        }
        
        // 작은 Answer 부터 차례로 구성하는 중 Answer가 나오면 끝낸다.
        // 확정된 경우를 제외하고 모든 경우를 조사한다.
        brute_force(0, Kvect);
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}