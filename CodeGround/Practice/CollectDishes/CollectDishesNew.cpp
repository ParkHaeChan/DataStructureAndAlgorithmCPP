/*
문제: Codeground 연습문제: '그릇 모으기' 참고
한 3일 고민해 봐도 모르겠던 문제다.
분할횟수, 결합횟수 각각 다른 방식으로 세서 계산하는 방식으로 시도했었다.
이때 분할 횟수는 이음새 있는 경우를 제외하는데 공들였고, 결합횟수는 DP문제로 보고 계산했다.

근데 실제로 풀이는 이렇다.
조건을 약화시켜서 모든 접시의 크기가 다르면,
접시와 해당 접시가 어느 더미에서 왔는지를 같이 묶어서 접시 크기 순으로 정렬한 뒤,
젤 큰 접시부터 하나씩 가상의 더미로 옮긴다고 생각하면 된다.
이때, 각 접시의 분할 횟수는 다음과 같이 셀 수 있다.
이 더미가 이 접시를 빼면 사라지는 경우 : 분할 0회
이 더미에서 이 접시를 빼도 남는 경우 : 분할 +1회 발생
즉, 각 더미를 벡터 등으로 저장했어야 분할 수를 셀 수 있다.
그리고 원래의 조건인 같은 크기의 그릇이 존재하므로 이를 처리할 수 있어야 한다.
(같은 크기 접시가 같은 더미에 있으면 같은 크기 끼리는 뭉쳐있어야 최소 분할이 될 것이다)
그리고 결합도 주의할 점이 있다.
이번 접시와 지금까지 옮긴 접시가 같은 더미에서 왔으면 한번에 옮겼다 치고 결합횟수를 그대로 유지해야 할 것 같지만
위에 분할 과정에서 1회가 증가했을 것이기 때문에 여기선 1회를 차감해야 한다.
다를 경우에는 겹합 횟수가 1회 증가한 것이된다. 
최종적으로는 가상의 더미로 옮긴 것을 원래 있던 더미중 하나로 옮겼던 것이라 간주해야 하므로 -1 해주면 된다.
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;
	
	freopen("input.txt", "r", stdin);
	
	//추가 상수
	const int INF = 987654321;
	//추가 변수
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
			int upperbound = i+1;	// 현재 크기보다 큰 제일 작은 접시 index(접근 시 배열 바운더리 체크 필수!)
			for(int next = i+1; next < sortedStack.size(); ++next)
			{
				if(sortedStack[next].first == dishsize)
				{
					upperbound = next+1;
					samecnt++;
					stacknum = sortedStack[next].second;
					stacknumset.insert(stacknum);
					DishStacks[stacknum].pop_back();	// 사용된 접시 제거
					continue;
				}
				break;
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
					// 최상단에 쓸 더미 번호와 겹치면
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
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}