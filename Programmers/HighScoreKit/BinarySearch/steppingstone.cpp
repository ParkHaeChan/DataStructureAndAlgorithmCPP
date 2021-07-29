/*
문제: https://programmers.co.kr/learn/courses/30/lessons/43236
// -제한 사항-
// 도착지점까지의 거리 distance는 1 이상 1,000,000,000 이하입니다.
// 바위는 1개 이상 50,000개 이하가 있습니다.
// n 은 1 이상 바위의 개수 이하입니다.

rocks 에서 n개의 위치를 제외하였을 때 거리값의 차의 최소가 제일 큰 경우를 출력하는 문제이다.

입력예시
distance가 25이고, rocks가 [2, 14, 11, 21, 17] 이고, n이 2이면서 2개의 위치를 [2, 14]로 지정하면,
rocks[11,21,17]이 남고, 여기서 실제 거리의 차이는
0~11 : 11, 11~17: 6, 17~21: 4, 21~distance(25): 4 라서 거리 최소는 4이다.
이렇게 n개를 제외한 뒤의 거리차의 최소 값이 최대가 되는 값을 구한다.

rocks는 정렬을 해도 상관이 없다는 것을 알 수 있다.
정렬된 rocks에서 제외할 n개의 값을 선택하는 경우 Combination(rocks, n) 가지가 발생한다.
이걸 다 해보는 것은 n과 rocks의 값이 최대 50000까지라는 것을 고려하면 불가능하다.

그러므로 이분탐색을 시도하는데, 우선 거리차의 최소값을 찾은 뒤,
실제로 이 거리가 거리차의 최소로 가능한지를 확인해 보고,
가능하면 2배로 다시 시도해 보고, 불가능하면 가능했던 값과의 중간값을 시도하는 식으로 찾는다.(Parametric Search)

주어진 rocks와 distance를 가지고 거리차 배열 diff를 만들 수 있다.
위 입력을 예시로 들면 [2,9,3,3,4,4]가 된다.
여기서 결정된 거리의 최소값 보다 작은 diff[i]가 발견 되더라도 n번 rocks의 원소를 빼면 diff가 증가하면서 여기에 걸리지 않을 수 있다.
이는 diff[i]가 min_diff보다 작거나 같으면 앞(i+1), 뒤(i-1) 원소 중 <작은 쪽>과 합치도록 하면된다.
(수정: 이번 i를 시도할 때 diff[i]가 min_diff 보다 작다는 것은, 이미 i이전에는 다 크거나 같은 경우라서 지나간 경우로 생각할 수 있다
그래서 앞(diff[i+1])에 더해주고 다음 시도할 때도 걸리는지를 확인하는 식으로 진행하면 된다)

이렇게 하다가 n회를 모두 소진하였음에도 min_diff 보다 작은 값이 발견된다면, min_diff 값으로 너무 큰 값을 시도한 것이므로 적절히 줄여야 한다.
최적의 횟수로 찾기 위해서는, 성공한 경우 2배로 증가시키고 실패할 경우 이전에 성공했던 값과 이번에 시도한 값의 평균값으로 시도하는 것을 반복하면 된다.
이때 평균을 계산하기 위해 가능한 이전 값(2배로 증가 시키기 전의 min_diff)이 갱신될 때 마다 last_diff에 저장해둔다.
수렴할 때 까지 반복하면, last_diff는 조건을 만족하는 상한값이 저장된다.

mid_diff가 수렴하는 상황은 last_diff의 차이가 1인 순간이다.
이때 mid_diff를 계산하면 (소수점은 버려지므로) last_diff와 같은 값이 나온다.
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {

    const int INF = 987654321;
    // rocks를 정렬
    sort(rocks.begin(), rocks.end());
    int N = rocks.size();
    
    // 거리차 벡터
    vector<int> diff(N+1);
    diff[0] = rocks[0];
    for(int i=1; i<N; ++i)
    {
        diff[i] = rocks[i] - rocks[i-1];
    }
    diff[N] = distance - rocks[N-1];

    // 거리차 최소값을 찾아 시도한다
    int min_diff = INF;
    for(auto e: diff)
        min_diff = min(min_diff, e);
    
    // 가능한 상한 저장
    int last_diff = min_diff;

    // 여러 min_diff 값을 시도해 보면서 변경
    while(true)
    {
        bool check = false; // 평균값을 적용하거나 두 배로 증가시키거나 둘 중 한쪽만 수행해야 한다.
        int cnt = n;    // n회를 세기 위한 counter
        // diff[index]가 min_diff보다 작은 값이 있을시 n회만큼 넘길 수 있다.
        for(int i=0; i<diff.size(); ++i)
        {
            if(diff[i] < min_diff)  // 주의: (<쓸지 <=쓸지 판단 잘해야 된다)
            {
                if(cnt > 0) // n회까지 넘기기 가능
                {
                   diff[i+1] += diff[i];   // 이전은 가능했을 것이므로 다음과 합친다(합쳐도 min_diff 보다 작을 수 있으므로 인덱스 넘기거나 하지 말 것)
                    cnt--;
                    continue;
                }
                else
                {// n회 검사하고도 min_diff보다 작은값이 존재하면 min_diff의 값을 줄여서 시도한다.
                    int mid_diff = (last_diff + min_diff)/2;
                    // 수렴하는지 검사
                    if(mid_diff == last_diff)
                        return last_diff;
                    min_diff = mid_diff;
                    check = true;
                    break;
                }
            }
        }
        // 넘기고 났는데 min_diff보다 큰값뿐이면 최대를 찾아야 하므로 2배 더 큰값을 시도해 본다.
        if(!check)
        {   //last는 가능한 경우의 상한이 저장된다
            last_diff = min_diff;
            min_diff *= 2;
        }

        // diff 배열 초기화
        diff[0] = rocks[0];
        for(int i=1; i<N; ++i)
        {
            diff[i] = rocks[i] - rocks[i-1];
        }
        diff[N] = distance - rocks[N-1];
    }
}

int main()
{
    int distance = 25;
    vector<int> rocks = {2, 14, 11, 21, 17};
    int n = 2;

    cout << solution(distance, rocks, n) << endl;

    return 0;
}