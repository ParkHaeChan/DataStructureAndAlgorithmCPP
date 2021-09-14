/*
야근 지수
https://programmers.co.kr/learn/courses/30/lessons/12927

야근 피로도는 야근을 시작한 시점에서 남은 일의 작업량을 제곱하여 더한 값입니다. 
Demi는 N시간 동안 야근 피로도를 최소화하도록 일할 겁니다.Demi가 1시간 동안 작업량 1만큼을 처리할 수 있다고 할 때, 
퇴근까지 남은 N 시간과 각 일에 대한 작업량 works에 대해 야근 피로도를 최소화한 값을 리턴하는 함수 solution을 완성해주세요.

!!!:
works는 길이 1 이상, 20,000 이하인 배열입니다.
works의 원소는 50000 이하인 자연수입니다.
n은 1,000,000 이하인 자연수입니다.

시도1)
n이 100만인 점을 생각하면 시뮬레이션 방식으로는 시간초과가 날 것임을 알 수 있다.
시뮬레이션으로 푼다면 각 원소를 맥스힙에 넣었다가 뽑아서 -1하고 n줄이고, 다시 힙에 넣고를 반복하면 된다.
다음은 그리디 방식으로 풀 수 있는지 확인해 본다.
일단 works의 모든 값을 더한다 그리고 n을 뺀다.
그리고 works의 size()로 나눈 값을 제곱한다. (이때 나머지도 균등하게 분배한다)
20점...
이 방법으로는 다 합친후 나둘때 작은 값의 작업에 값을 더해주게 되므로 정답을 구하는데 적합하지 않다.
ex) n=100, {999, 1, 998, 990}

시도2)
힙에서 넣고 빼고를 반복하도록 구현
13번 케이스 제외하고 성공 (시간 초과)
n이 크고 works가 적절히 분배된 경우는 이런식의 시뮬레이션 방식은 시간초과가 날 수 있을 것 같다.

시도3)
힙이 비었는지 검사하지 않고 top, pop을 실행할 경우 힙 사이즈가 이상한 값으로 튀는 문제가 있다. (저절로 999개가 되어 있음...)
즉, n = 99, {1,1,1} 같은 경우에 처리가 튈 수 있으므로 주의한다. 최대값에서 1씩 빼는 방식은 그대로 유지(효율성 테스트 통과했음)
통과
*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

struct node
{
    int val;
    bool operator<(const node& lhs) const
    {   // lhs : back, rhs: front
        return lhs.val > this->val;
    }
};

long long solution(int n, vector<int> works) {
    long long answer = 0;

    priority_queue<node> PQ;
    for(auto e: works)
        PQ.push({e});
    
    while(n-- > 0 && !PQ.empty())   // 시도3: empty() 검사 추가
    {
        auto cur = PQ.top(); PQ.pop();
        cur.val--;
        if(cur.val <= 0)    // 시도3: 0 인 경우도 저장하지 않음
            continue;
        PQ.push(cur);
    }
    
    while(!PQ.empty())
    {
        auto cur = PQ.top(); PQ.pop();
        answer += cur.val * cur.val;
    }

    return answer;
}

int main()
{
    int n = 99;
    vector<int> works = {1, 1, 1};    // 580

    solution(n, works);

    return 0;
}