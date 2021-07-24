/*
풀이 시간: 약 2시간 (무슨 카테고리의 문제인지 고민 + 어떻게 풀지 고민하는데 1시간 이상 소모)

문제의 목표는 분할과 결합의 총 횟수를 구하는 것이다.
적절히 분할을 모두 끝내서 결합할 단계만 남은 상태를 구하면,
결합 횟수 = 분할된 뭉치들 갯수 -1 로  쉽게 구할 수 있다.

관건은 어떻게 분할 횟수를 구하는가 이다.
모든 케이스를 다 고려하면 각 위치 별로 분할(O,X)의 2가지 경우가 발생하므로
한 뭉치당 50그릇이 가능하므로 2의 49승 가지수를 고려해야 한다. 이는 너무 많아서 시간초과가 발생할 것이다. (이 방식 제외)
그럼 일일이 다 분할하는게 아니란 말이고,
약간 살펴보면, 같은 크기의 그릇이 연달아 나오는 경우는 분할을 하면 안된다는 것을 알 수 있다. (2번째 입력 예시의 힌트!)
그러면, 같은 크기 연속일 때는 분할 안하고, 이외의 경우는 다 분할한다고 하면,
이때는 분할 안해도 되는 경우에 분할을 하는 경우가 발생한다.
예를 들면 (2,3), (2,3), (2,4)의 경우 하나의 (2,3)은 이음새로 사용할 수 있으므로 분할 안해야 하는데 분할하게 된다.
이런 경우를 따로 처리할 수 있으면 쉽게 분할 횟수를 구할 수 있다.
일단 이렇게 (2,3), (2,4)와 같이 서로 다른 숫자가 나오는 경우는 차이가 제일 적게나는 1가지 경우만 이음새로 남기면 된다.
그 경우를 분할 횟수에서 도로 차감하면 된다.
이 경우를 배열로 다음과 같이 저장한다(상태 저장 기법) diff[그릇 크기로 index] = index그릇과 차이 가장 적게 큰 그릇크기를 저장

-예시 상황-
(2,3), (2,3), (2,4)의 경우 3분할이 발생하고, 222334가 최종인데 이때 (2,3)이음새를 diff[2] = 3을 통해 확인하여 분할 횟수를 1회 차감 한다.
만일 (1,3), (2,4), (2,4)가 입력이면, 122344가 최종인데 (1,2), (2,3)이음새를 처리 가능한지를 diff[1], diff[2]를 통해 확인하면
diff[1] = 3, diff[2] = 4 이므로 처리불가하여 분할 횟수 차감이 일어나지 않는다.

-에러 체크-
위 방식으로 시도한 경우 다음과 같은 CASE에서 문제가 발생했다.
(1 2 5 9), (4 5 6 8) 이렇게 되면 4,5,6은 각각 모두 분할 후 또 모두 이음새로 처리되며 다 매꿔지는데
실제로는 한번은 4,5가 됬던 5,6이 됬던 5가 끼기 위해 분할이 됐어야 한다.

-실제 풀이-
각 그릇이 들어올 때 어드 뭉치에서 왔는지 라벨을 붙인 후, 정렬한다.(정렬은 그릇 크기순으로)
pair를 써서 first에 그릇 크기, second에 원래 있던 뭉치 번호를 지정하면 된다.
정렬하면 방금 입력에 대해서는 다음과 같이 정렬돼 있다.
그릇크기: 1, 뭉치 번호: 1
그릇크기: 2, 뭉치 번호: 1
그릇크기: 4, 뭉치 번호: 2
그릇크기: 5, 뭉치 번호: 1
그릇크기: 5, 뭉치 번호: 2
그릇크기: 6, 뭉치 번호: 2
그릇크기: 8, 뭉치 번호: 2
그릇크기: 9, 뭉치 번호: 1

뭉치 번호 1은 2번 분할되었고, 뭉치 번호 2는 1회 분할된 것을 확인할 수 있다.
세는 방식은 같은 뭉치 번호가 나오다 안나오다 다시 나오면 분할 1회라 계산하면 된다.
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int Answer;

int Counter(const vector<pair<int,int>>& vect, int stacknum)
{
	// 분할 횟수: 뭉치 번호가 끊어졌다가 다시 나오는 횟수를 센다
	bool start = false;	// 현재 검사하는 뭉치 번호인 그릇이 나오기 시작
	bool isDiv = false;
	int ret = vect.size();
	
	
	set<int> befores;
	set<int> afters;
	int val = vect[0].first;
	int i=0;
	while(i<vect.size())
	{
		for(; i<vect.size(); ++i)
		{
			if(val == vect[i].first)
			{
				befores.insert(vect[i].second);
			}
			else
				break;
		}
		val = vect[i].first;
		for(; i<vect.size(); ++i)
		{
			if(val == vect[i].first)
			{
				afters.insert(vect[i].second);
			}
			else
				break;
		}
		for(auto e: befores)
			if(afters.find(e) != afters.end())
				ret--;	// 필요 이상으로 분할했으므로 분할 횟수 하나 차감
		befores.clear();
		afters.clear();
	}
	return ret;
}

int main(int argc, char** argv)
{
	int T, test_case;
	
	freopen("input.txt", "r", stdin);
	
	//추가 상수
	const int INF = 987654321;
	//추가 변수
	int N;	// 그릇의 뭉치 수 (1≤N≤50)
	int h;	// 각 뭉치에 쌓인 그릇의 개수  (1≤h≤50, 그릇크기 ≤10,000)
	int divideCnt;	// 분할 횟수
	int mergetCnt;	// 결합

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		Answer = INF;
		divideCnt = 0;
		vector<pair<int, int>> DishStacks;
		// 입력 받기
		cin >> N;
		for (int dstack = 1; dstack <= N; ++dstack)
		{
			cin >> h;
			for (int dish = 1; dish <= h; ++dish)
			{
				int temp;
				cin >> temp;
				DishStacks.push_back({temp, dstack});
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////
		sort(DishStacks.begin(), DishStacks.end(), [](auto a, auto b){
			if(a.first == b.first)
				return a.second < b.second;	// 뭉치 번호 오름차순
			else
				return a.first > b.first;	// 그릇 크기 내림차순
		});

		// 분할 횟수 구하기: (X) 이 방법으로는 구할 수 없다. 45 45 45인 경우 2분할만해야되는데 3분할 나온다.
		// divideCnt = Counter(DishStacks, N);

		// 결합 횟수는 DP를 이용하여 구한다
		// 모든 접시를 하나의 가상의 뭉치에 결합한다고 생각하고 결합횟수는 마지막에 1빼주면 된다.(원래 있던 뭉치중에 하나에 옮겼던 것으로 간주)
		// 옮겨진 그릇의 원래 뭉치와 이번에 옮기는 접시의 뭉치가 같으면(분할 안하는게 이득이므로) 분할1회를 빼주는 식으로 구현
		// DP[현재 쌓인 접시 수][젤 위의 접시가 원래 있던 뭉치 번호] = 최소 결합 횟수
		// case1) 이번에 올릴 접시가 같은 뭉치에서 온 경우
		// DP[이전 쌓인 접시 수 + 이번에 올릴 접시 수(같은 크기)][top stacknum] = DP[이전에 쌓인 접시 수][top stacknum]
		// case2) 이번에 올릴 접시가 다른 뭉치에서 온 경우
		// DP[이전 쌓인 접시 수 + 이번에 올릴 접시 수(같은 크기)][top stacknum] = DP[이전에 쌓인 접시 수][!top stacknum]+1
		int Dishes = DishStacks.size();
		vector<int> col(N+1, INF);	// 최소를 찾으므로 무한대로 초기화
		vector<vector<int>> DP(Dishes+1, col);	// 1 ~ 그릇수까지 사용
		for(int i=0; i<Dishes; )	// index는 samesum만큼 증가
		{
			set<int> tstacknumset;	// this: 이번 접시 크기의 뭉치 번호들 저장
			set<int> lstacknumset;	// left: 남은 접시 크기의 뭉치 번호들 저장
			tstacknumset.insert(DishStacks[i].second);
			int samesum = 1;
			int upperbound = i+1;
			// 같은 크기 접시 갯수 및 뭉치 번호 파악
			for(int next = i+1; next < Dishes; ++next)
			{
				if(DishStacks[i].first == DishStacks[next].first)
				{
					samesum++;
					tstacknumset.insert(DishStacks[next].second);
					upperbound = next+1;
					continue;
				}
				lstacknumset.insert(DishStacks[next].second);
			}
			// 분할 횟수 구하기: 다음 크기 접시들에 이번 크기 접시 뭉치 번호가 존재하면 분할된 것
			for(auto e: tstacknumset)
				if(lstacknumset.find(e) != lstacknumset.end())
					divideCnt++;
			// 이음새인 경우를 빼준다: 인접한 두 크기 접시 중 그릇 뭉치가 하나라도 일치하면 1 감소
			if(upperbound < Dishes)
			{
				lstacknumset.clear();	// 재활용 위해 비운다
				lstacknumset.insert(DishStacks[upperbound].second);
				for(int next = upperbound+1; next < Dishes; ++next)
				{
					if(DishStacks[upperbound].first == DishStacks[next].first)
					{
						lstacknumset.insert(DishStacks[next].second);
						continue;
					}
					break;
				}
				for(auto e: tstacknumset)
					if(lstacknumset.find(e) != lstacknumset.end())
					{	
						divideCnt--;
						break;
					}
			}
			//cout << divideCnt << endl;
			// DP 테이블 갱신: 같은 크기 그릇 중 최상단에 갈 그릇의 뭉치 번호
			int merge = tstacknumset.size();
			for(auto e : tstacknumset)
			{
				if(i == 0)	// 초기 상태
				{
					DP[samesum][e] = merge;	// 초기 결합에 사용된 수: 뭉치 번호 종류 수
					continue;
				}
				// 모든 경우중 현재 가능한 그릇 번호에 대해
				for(int stack=1; stack<=N; ++stack)
				{
					if(e == stack)	// 같은 뭉치면
					{
						if(tstacknumset.size() == 1)	// 하나면 어차피 분할 안했어야 하므로 결합횟수 1회 차감
							DP[i+samesum][e] = min(DP[i+samesum][e], DP[i][stack]+merge-1);
						else
						{
							for(auto el : tstacknumset)	// 이때는 e가 이음새로 사용되야 하므로 결합횟수 1회 차감
								if(el != e)	// 현재 e가 아닌 뭉치 번호가 맨 위로 가는 경우로 만들어 줌
									DP[i+samesum][el] = min(DP[i+samesum][el], DP[i][stack]+merge-1);
						}
					}
					else
					{	// 이음새 고려 안해도 되므로 그냥 합친다.
						DP[i+samesum][e] = min(DP[i+samesum][e], DP[i][stack]+merge);
					}
				}		
			}
			i += samesum;	// 같은 크기 접시 수 만큼 index넘긴다.
		}

		// 끝까지 쌓았을 때 최소인 경우 찾기
		for(int s=1; s<=N; ++s)
		    Answer = min(Answer, DP[Dishes][s]);

		Answer += divideCnt-1;	//분할 횟수 만큼 더하고 가상의 뭉치에 결합한 것 -1 해줌
		 /////////////////////////////////////////////////////////////////////////////////////////////

		 // Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}