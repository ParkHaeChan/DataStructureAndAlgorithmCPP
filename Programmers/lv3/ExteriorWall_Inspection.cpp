/*
외벽 정검
https://programmers.co.kr/learn/courses/30/lessons/60062

?:
외벽의 길이 n, 취약 지점의 위치가 담긴 배열 weak, 각 친구가 1시간 동안 이동할 수 있는 거리가 담긴 배열 dist가 매개변수로 주어질 때, 
취약 지점을 점검하기 위해 보내야 하는 친구 수의 최소값을 return 하도록 solution 함수를 완성해주세요.

!!!:
n은 1 이상 200 이하인 자연수입니다.
weak의 길이는 1 이상 15 이하입니다.
서로 다른 두 취약점의 위치가 같은 경우는 주어지지 않습니다.
취약 지점의 위치는 오름차순으로 정렬되어 주어집니다.
weak의 원소는 0 이상 n - 1 이하인 정수입니다.
dist의 길이는 1 이상 8 이하입니다.
dist의 원소는 1 이상 100 이하인 자연수입니다.
친구들을 모두 투입해도 취약 지점을 전부 점검할 수 없는 경우에는 -1을 return 해주세요.

시도1)
원형으로 표현했지만 이어서 2회 나열하는 방식으로 풀어서 볼 수 있다.
예제 입력에서 n = 12, 취약지점 WEAK이 [1, 5, 6, 10]이면,
1,5,6,10에 이어서 한번더 써주면 반대방향으로 이동하는 경우도 한번에 고려할 수 있다.
즉, 1,5,6,10,n+1,n+5,n+6,n+10 으로 두고 WEAK의 원소 개수인 4개를
최소 친구수로 덮어지는지를 확인하면 된다.
그럼 최소 구간을 구할 수 있고, 이 최소 구간이 몇명의 친구로 덮어지는지 확인한다.
const int INF = 987654321;
int distance = INF;
// 취약 지점을 모두 포함하는 최단 구간
for(int i=0; i+WeakPoints-1<weak.size(); ++i)
{
    distance = min(distance, weak[i+WeakPoints-1]-weak[i]);
}
// 몇 명의 친구로 채울 수 있는지
sort(dist.begin(), dist.end(), [](auto back, auto front){
    return back > front;
});
while(distance > 0)
{
    if(answer >= dist.size())
    {
        answer = -1;
        break;
    }
    distance -= dist[answer++];
}

시도2)
위에서 덮을 때 이어서 덮지 않아도 된다. 하지만 띄우다 보면 2회 연달아 써줬기 때문에
같은 구간을 두번 덮는 문제가 생길 수 있다...
다시 원점으로 돌아가서,
문제의 입력이 상당히 작은 것을 고려하면 완전탐색으로 모든 경우를 시도해보는 방식으로 구현해도 문제되지 않을 것 같다.
즉, dist를 나열한 모든 경우의 수를 weak 개를 포함할 수 있는 모든 시작 위치에서 
dist거리만큼 커버하는 모든 경우를 확인한 뒤 최소 인원이 투입된 경우를 구하면 된다.

통과.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = 0;
    const int INF = 987654321;
    answer = INF;
    int WeakPoints = weak.size();
    // 원형 벽을 풀어서 본다 (이어지도록)
    for(int i=0; i<WeakPoints; ++i)
    {
        weak.push_back(weak[i]+n);
    }
    // 시도2
    // WeakPoints개를 포함할 수 있는 모든 시작 위치에 시도
    sort(dist.begin(), dist.end());
    for(int start=0; start<WeakPoints; ++start)
    {   // 모든 dist 순열에 대해(8!) 시도
        do
        {
            int count = 1; // 투입된 친구 수
            int length = weak[start]+dist[count-1]; // 친구가 커버하는 거리
            // WeakPoints 만큼 커버 가능한지 확인
            for(int i=start; i<start+WeakPoints; ++i)
            {
                if(length < weak[i])
                {   // 커버 불가능하면 인원 추가 투입
                    count++;
                    if(count > dist.size()) // 모든 인원 투입되도 불가능한 경우
                        break;
                    length = weak[i]+dist[count-1]; // 다음 친구는 weak[i]를 커버하며 시작
                }
            }
            answer = min(answer, count);
        }while(next_permutation(dist.begin(), dist.end()));
    }
    if(answer > dist.size())
        answer = -1;

    return answer;
}

int main()
{
    int n = 12;
    vector<int> weak = {1, 5, 6, 10};
    vector<int> dist = {1, 2, 3, 4};
    solution(n, weak, dist);

    return 0;
}