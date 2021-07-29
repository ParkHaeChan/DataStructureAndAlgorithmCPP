/*
문제: https://programmers.co.kr/learn/courses/30/lessons/43236

rocks 에서 n개의 위치를 제외하였을 때 거리값의 차의 최소가 제일 큰 경우를 출력하는 문제이다.

입력예시
distance가 25이고, rocks가 [2, 14, 11, 21, 17] 이고, n이 2이면서 2개의 위치를 [2, 14]로 지정하면,
rocks[11,21,17]이 남고, 여기서 실제 거리의 차이는
0~11 : 11, 11~17: 6, 17~21: 4, 21~distance(25): 4 라서 거리 최소는 4이다.
이렇게 n개를 제외한 뒤의 거리차의 최소 값이 최대가 되는 값을 구한다.

rocks는 정렬을 해도 상관이 없다는 것을 알 수 있다.
정렬된 rocks에서 제외할 n개의 값을 선택하는 경우는 rocks Combination n 가지의 경우다.
이걸 다 해보는 것은 n이 최대 50000까지 있는 것을 생각해보면 시간내에 불가능하다.

여기서 이분탐색을 시도하기 위해서는 거리의 최소값을 결정한 뒤,
실제로 이 거리가 거리차의 최소로 가능한지를 확인해 보는 식으로 구현한다.

여기서 rocks와 distance를 가지고 거리차 배열 diff를 만들 수 있다.
위 입력을 예시로 들면 [2,9,3,3,4,4]가 된다.
여기서 결정된 거리의 최소값 보다 작은 diff[i]가 발견 되더라도 n번 rocks의 원소를 빼면 diff가 증가하면서 여기에 걸리지 않을 수 있다.
이는 diff[i]가 min_diff보다 작거나 같으면 앞, 뒤 원소 중 작은 쪽과 합치도록 하면된다.

이렇게 하고도 현재 결정한 거리의 최소값(min_diff) 보다 작은 값이 발견된다면, 이 값은 너무 큰 값을 시도한 것이므로 줄여야 한다.
반대로 n회가 소진되던, 남았던 현재 결정한 거리의 최소값 보다 큰값만 발견되면, 이 값은 더 커질수 있으므로 값을 키워서 시도해봐야 한다.
min_diff의 이전 값을 저장하는 last_diff는 min_diff의 이전 값을 무조건 저장하는 것이 아니라 위 조건을 만족하지 않았던 최대의 min_diff를 저장하도록 한다.
즉, last_diff는 조건이 실패하는 상한값을 저장한다.

수렴하는 상황은 last_diff(불가능 상한)와 min_diff(가능 하한)의 차이가 1인 순간이다.
(주의: min_diff와 last_diff가 같을 때는 아직 못찾은 것이다. 즉, if(mindiff-lastdiff<=1)로 작성하지 않도록 주의한다.)
*/

// -제한 사항-
// 도착지점까지의 거리 distance는 1 이상 1,000,000,000 이하입니다.
// 바위는 1개 이상 50,000개 이하가 있습니다.
// n 은 1 이상 바위의 개수 이하입니다.

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool InRange(int start, int end, int val)
{
    if(start <= val && val <= end)
        return true;
    else
        return false;
}

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

    int min_diff = INF;
    for(auto e: diff)
        min_diff = min(min_diff, e);
    
    int last_diff = min_diff;

    // min_diff 값을 시도해 보면서 변경
    while(true)
    {
        bool check = false; // n회 적용하고도 작은 값 있는지 검사
        int cnt = n;    // 임시 counter
        // n회 만큼 diff[index]가 min_diff보다 작은 값이 있어도 넘길 수 있다.
        for(int i=0; i<diff.size(); ++i)
        {
            if(diff[i] < min_diff)  // 주의: 같은 경우도 넘겨도 된다!
            {
                if(cnt > 0) // n회까지 검사한다
                {
                    // i의 앞이나 뒤 중 작은 값과 함께 합쳐지도록 처리 ==> 이렇게 생각한게 문제였다...(뒤는 이미 고려된 상황:<안되면 다음으로 넘어갈 수가 없음> 이므로 앞에 더한다)
                    // boundary check 필요
                    /*
                    pair<int, int> left_val = {INF, i-1};
                    if(InRange(0, N, i-1))
                        left_val.first = diff[i-1];
                    pair<int, int> right_val = {INF, i+1};
                    if(InRange(0, N, i+1))
                        right_val.first = diff[i+1];
                    
                    
                    // 앞쪽 값이 더 작아서 합쳐지면 그 다음값을 확인하도록 넘어가는 처리 필요
                    // 뒤쪽에 합치는 경우는 어차피 넘어갔으므로 무시하면 됨
                    if(right_val.first < left_val.first)
                    */
                    {
                        diff[i+1] += diff[i];   // 다음에서 뒤로 참조할때 문제 생길 수 있으므로 갱신한다
                        //i++; 넘기면 안됨
                    }
                    cnt--;
                    continue;
                }
                else
                {// n회 검사하고도 작거나 min_diff보다 작은값이 존재하면 min_diff는 값을 줄여서 시도한다.
                    int mid_diff = (last_diff + min_diff)/2;
                    // 수렴하는 상황
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
        {   //last는 가능한 경우의 하한을 저장
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