/*
풀이는 박트리님 블로그의 풀이를 참고하여 직접 구현했다.
(코드는 변수명 알아보기 힘들어서 풀이 방식만 참고함ㅠㅠ)


우선 시뮬레이션에 사용할 2차원 벡터와 정렬 후 상태 확인하기 위한 pair 벡터 메모리 공간이 필요하다.
(+DP테이블)

정렬은 그릇 크기와 더미 번호를 묶어서 pair 벡터에 넣은 뒤 그릇 크기 기준 내림차순으로 수행한다

분할은 시뮬레이션 방식으로 세었다.
정렬된 접시에서 하나씩 참고하여 같은 크기의 접시들을 세는 동시에 더미에서 바로 그릇을 제거한다.
각 더미를 2차원 벡터로 구현했고, 입력이 오름차순으로 들어왔기 때문에 pop_back만 해도
그 더미의 제일 큰 접시가 제거된다.
이때 set에 제거한 그릇의 더미 번호를 저장해 둔 뒤, 해당 더미 번호를 가지고 남은 더미의 크기를 조사하여 0보다 크면 분할이 발생했다 볼 수 있고,
0이면 통째로 옮겨져 분할이 발생하지 않았다고 판단할 수 있다.

단, 이때는 이음새 부분도 분할되므로 결합할 때 고려해 줘야한다.
여기서 이음새는 예를 들면, 각 더미가 1:(3,4) 2:(3,4) 3:(3,4) 이면
그릇을 제거하는 시뮬레이션을 통해 분할 횟수를 세면 3회 분할로 센다.
하지만 최적의 경우는 분할을 2회만 하고 나머지 하나의 (3,4)는 중간에 이음새로 사용하는 경우이다. 
--> 3/3(3,4)4/4

여기서는 일단 분할을 해버리고, 결합할 때 같은 더미 번호인 서로 다른 크기의 접시가 만나는 경우를
이음새로 판단하여 분할도 안했어야 했고, 분할을 안했으면 결합도 같이 움직여서 1회로 끝났어야 했으므로
불필요한 연산이 2회 더 발생한 것으로 보고 연산수-2를 해주는 방식으로 구현했다.

결합은 가상의 더미에 뭉치도록 수행한 뒤 마지막에 1을 빼주도록 하였다.
결합 횟수는 같은 크기 그릇을 제거하는 시뮬레이션에서 발생한 더미 번호 종류 갯수 만큼 발생한다는 점을 이용했다.

DP테이블 계산은
지금까지 옮긴 접시의 맨위 더미 번호가 이번에 합쳐질 그릇들 중 제일 아래 접시의 더미 번호와 같으면,
이음새이므로 발생한 연산 수에서 2를 도로 빼준다.
이음새가 아닌 경우는 그냥 연산수(발생한 결합과 분할 횟수)를 더해주면 된다. 
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
	int T, test_case;
	
	freopen("input.txt", "r", stdin);
	
	//추가 상수
	const int INF = 987654321;
	//추가 변수
	int Answer;
	int N;	// 그릇의 뭉치 수 (1≤N≤50)
	int h;	// 각 뭉치에 쌓인 그릇의 개수  (1≤h≤50, 그릇크기 ≤10,000)
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		Answer = INF;
		// 입력 받기
		cin >> N;
        vector<vector<int>> DishStacks(N+1);	// 분할 횟수를 세기 위해 시뮬레이션 용으로 사용된다
        vector<pair<int,int>> sortedStack;		// 내림차순 정렬 시킨 상태를 알아보기 위해 사용된다
		for (int stack = 1; stack <= N; ++stack)
		{
			cin >> h;
			for (int dish = 1; dish <= h; ++dish)
			{
				int temp;
				cin >> temp;
				DishStacks[stack].push_back(temp);
                sortedStack.push_back({temp, stack});
            }
		}
		/////////////////////////////////////////////////////////////////////////////////////////////
		sort(sortedStack.begin(), sortedStack.end(), greater<pair<int,int>>()); // 그릇 크기 내림차순 정렬
		//for(auto e: sortedStack)
			//cout << e.first << ":" << e.second << endl;

		// 현재까지 모인 접시수 만큼 쌓으면서 최소 결합수를 DP로 계산
		// DP[현재 쌓인 그릇 수][현재 맨위에 있는 접시의 더미 번호] = 최소 연산 수
		vector<int> cols(N+1, INF);	// 최소를 구하므로 INF로 초기화
		vector<vector<int>> DP(sortedStack.size()+1, cols);
		//초기화: 그릇 하나도 안쌓은 상태는 0회
		for(int s=1; s<=N; ++s)
			DP[0][s] = 0;

		for(int i=0; i<sortedStack.size(); )	// index 증가: samecnt 만큼 한번에 처리
		{
			// 일단 한개 꺼내서 같은 크기 몇개 있는지를 알아야 된다.
			int dishsize = sortedStack[i].first;
			int stacknum = sortedStack[i].second;
			set<int> stacknumset;	// 나왔던 더미 번호들 저장용
			stacknumset.insert(stacknum);
			DishStacks[stacknum].pop_back();	// 사용된 접시 제거
			// 같은 크기 접시가 있는지 확인
			int samecnt = 1;	// 최소 현재(i)하나는 존재
			for(int next = i+1; next < sortedStack.size(); ++next)
			{
				if(sortedStack[next].first == dishsize)
				{
					samecnt++;
					stacknum = sortedStack[next].second;
					stacknumset.insert(stacknum);
					DishStacks[stacknum].pop_back();	// 사용된 접시 제거
					continue;
				}
				break;	//다른 크기 접시 나오면 바로 탈출
			}
			// 분할 횟수: 제거된 접시의 더미 번호를 조회하여 DishStacks가 남았으면 분할된 것으로 판단
			int divCnt = 0;
			for(int stacknum: stacknumset)
				if(DishStacks[stacknum].size() > 0)
					divCnt++;
			//cout << "divCnt: " << divCnt << endl;
			int mergeCnt = stacknumset.size();	// 결합 횟수는 더미 번호 종류 수 만큼 발생함
			// 초기 상태만 따로 처리
			if(i==0)
			{
				for(auto e:stacknumset)
					DP[i+samecnt][e] = DP[i][e] + mergeCnt + divCnt;
				
				i += samecnt;
				continue;
			}
			// 최상단에 위치 가능한 더미 번호
			for(int top : stacknumset)
			{
				// 원소가 하나뿐이라면 그냥 합쳐야 한다.
				if(stacknumset.size() == 1)
				{
					for(int stack=1; stack<=N; ++stack)
					{
						if(stack == top)	// 같은 더미에서 왔으므로 분할도 1회 추가로 발생했고 결합도 추가로 발생했을 것이므로 -2를 해줌
							DP[i+samecnt][top] = min(DP[i+samecnt][top], DP[i][stack] + mergeCnt + divCnt -2);
						else
							DP[i+samecnt][top] = min(DP[i+samecnt][top], DP[i][stack] + mergeCnt + divCnt);
					}
					break;
				}
				// 이외의 경우는 이음새가 될 번호를 찾아서 처리
				for(int stack=1; stack<=N; ++stack)
				{
					// 최상단에 쓸 더미 번호와 겹치면 넘긴다
					if(stack == top)
						continue;

					if(stacknumset.find(stack) != stacknumset.end())
					{// 이음새로 사용될 수 있는 경우
						DP[i+samecnt][top] = min(DP[i+samecnt][top], DP[i][stack] + mergeCnt + divCnt -2);
					}
					else
					{// 그외는 결합 횟수 증가
						DP[i+samecnt][top] = min(DP[i+samecnt][top], DP[i][stack] + mergeCnt + divCnt);
					}
				}
			}
			i += samecnt;
		}
		// 최종 층 중 최소의 경우 찾기
		for(int s=1; s<=N; ++s)
			Answer = min(Answer, DP[sortedStack.size()][s]);
		
		Answer--;	// 가상의 더미로 옮긴 것으로 간주했으므로 1을 빼줌

		/////////////////////////////////////////////////////////////////////////////////////////////

		 // Print the answer to standard output(screen).
		cout << "#testcase" << test_case + 1 << endl;
		cout << Answer << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}