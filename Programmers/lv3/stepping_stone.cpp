/*
징검다리 건너기
https://programmers.co.kr/learn/courses/30/lessons/64062

징검다리는 일렬로 놓여 있고 각 징검다리의 디딤돌에는 모두 숫자가 적혀 있으며 디딤돌의 숫자는 한 번 밟을 때마다 1씩 줄어듭니다.
디딤돌의 숫자가 0이 되면 더 이상 밟을 수 없으며 이때는 그 다음 디딤돌로 한번에 여러 칸을 건너 뛸 수 있습니다.
단, 다음으로 밟을 수 있는 디딤돌이 여러 개인 경우 무조건 가장 가까운 디딤돌로만 건너뛸 수 있습니다.

?: 디딤돌에 적힌 숫자가 순서대로 담긴 배열 stones와 한 번에 건너뛸 수 있는 디딤돌의 최대 칸수 k가 매개변수로 주어질 때, 
최대 몇 명까지 징검다리를 건널 수 있는지 return 하도록 solution 함수를 완성해주세요.

!!!:
징검다리를 건너야 하는 니니즈 친구들의 수는 무제한 이라고 간주합니다.
stones 배열의 크기는 1 이상 200,000 이하입니다.
stones 배열 각 원소들의 값은 1 이상 200,000,000 이하인 자연수입니다.
k는 1 이상 stones의 길이 이하인 자연수입니다.

시도1)
stones에서 가장 작은 수를 찾고(0이 아닌)
그 수만큼 건너면 그 돌은 0이되고 나머지는 그 돌의 수 만큼 줄인다.
이를 돌 사이가 k가 넘는 구간이 생길때 까지 다시 반복하는 식으로 구해본다.
int solution(vector<int> stones, int k) {
    int answer = 0;
    const int INF = 987654321;
    int min_val;
    
    while(true)
    {
        min_val = INF;
        int interval = 0;
        bool out = false;
        for(int i=0; i<stones.size(); ++i)
        {
            if(stones[i] <= 0)
            {
                interval++;
            }
            else
                interval = 0;
            if(interval == k)
            {
                out = true;
                break;
            }
            if(stones[i] > 0)
                min_val = min(min_val, stones[i]);
        }
        if(out)
            break;
        answer += min_val;
        for(int i=0; i<stones.size(); ++i)
        {
            stones[i] -= min_val;
        }
    }

    return answer;
}
(효율성 테스트 실패)

시도2)
그리디 인가 싶어서 고민좀 해봤는데 잘 안떠올라서
이분탐색이 가능할 것 같아서 시도해본다
시작부터 0이하인 구간이 k만큼 있는 경우가 아니면
최소한 stones에 있는 젤 작은 값 만큼은 가능하다고 치고(0아닌 값)
거기서 2배를 시도해보고 안되면 반으로 줄이고를 반복한다.
첫 두 케이스 제외하고 효율성 테스트까지 모두 통과했다.
k == 1인 경우 처리 추가후 통과
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iterator> // back_inserter

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = 0;
    const int INF = INT32_MAX;

    int minval = INF;
    int interval = 0;
    for(int i=0; i<stones.size(); ++i)
    {   /*
        if(stones[i] <= 0)
        {
            interval++;
        }
        else
            interval = 0;

        if(interval == k)
            return 0;   // 시작부터 불가능함
        stones는 자연수로 시작부터 불가능한 경우는 없다
        */
        minval = min(minval, stones[i]);    // stones는 자연수
    }

    if(k == 1)
        return minval;

    // 이분 탐색
    int last = minval;  // 가능한 경우만 저장
    int tried = last*2;
    while(true)
    {
        vector<int> temp;
        copy(stones.begin(), stones.end(), back_inserter(temp));
        int interval = 0;
        bool done = false;
        for(int i=0; i<temp.size(); ++i)
        {
            temp[i] -= tried;
            if(temp[i] <= 0)
                interval++;
            else
                interval = 0;

            if(interval == k)
            {
                done = true;
                break;
            }
        }
        if(done)
        {   // 불가능했으므로 중간값을 시도한다
            int mid = (last+tried)/2;
            if(mid == last)
            {
                answer = mid;
                break;
            }
            tried = mid;
        }
        else    // 2배로 시도해본다
        {
            last = tried;
            tried *= 2;
        }
    }

    return answer+1;
}

int main()
{
    vector<int> stones = {2, 4, 5, 3, 2, 1, 4, 2, 5, 1};
    int k = 3;
    solution(stones, k);

    return 0;
}