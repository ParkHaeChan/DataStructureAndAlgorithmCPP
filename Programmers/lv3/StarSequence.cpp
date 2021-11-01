/*
스타 수열
https://programmers.co.kr/learn/courses/30/lessons/70130

어떤 수열 x의 부분 수열(Subsequence)이란, x의 몇몇 원소들을 제거하거나 그러지 않고 남은 원소들이 원래 순서를 유지하여 얻을 수 있는 
새로운 수열을 말합니다.
예를 들어, [1,3]은 [1,2,3,4,5]의 부분수열입니다. 원래 수열에서 2, 4, 5를 제거해서 얻을 수 있기 때문입니다.

다음과 같은 조건을 모두 만족하는 수열 x를 스타 수열이라고 정의합니다.
x의 길이가 2 이상의 짝수입니다. (빈 수열은 허용되지 않습니다.)
x의 길이를 2n이라 할 때, 다음과 같은 n개의 집합 {x[0], x[1]}, {x[2], x[3]}, ..., {x[2n-2], x[2n-1]} 의 교집합의 원소의 개수가 1 이상입니다.
x[0] != x[1], x[2] != x[3], ..., x[2n-2] != x[2n-1] 입니다.
예를 들어, [1,2,1,3,4,1,1,3]은 스타 수열입니다. {1,2}, {1,3}, {4,1}, {1,3} 의 교집합은 {1} 이고, 각 집합 내의 숫자들이 서로 다르기 때문입니다.

?:
1차원 정수 배열 a가 매개변수로 주어집니다. a의 모든 부분 수열 중에서 가장 길이가 긴 스타 수열의 길이를 return 하도록 solution 함수를 완성해주세요. 
이때, a의 모든 부분 수열 중에서 스타 수열이 없다면, 0을 return 해주세요.

!!!:
a의 길이는 1 이상 500,000 이하입니다.
a의 모든 수는 0 이상 (a의 길이) 미만입니다.

시도1)
a의 길이가 상당히 크고(50만), 여러 가지 조건을 만족하는 최대 길이의 부분집합 a를 찾아야하므로 완전탐색 방법으로는 시간 내에 풀 수 없다.
적절한 방법으로 '투 포인터' 방식을 시도해본다.

처음 2칸(0,1)을 확인하여 스타 수열의 조건을 만족하면 다음 2칸을 더 추가한다.
스타 수열의 조건을 만족하지 않는 경우는 (1,2)로 앞 뒤를 각각 1칸씩 이동한 상태에서 검사한다.
이를 수열의 끝까지 반복

이때 최대 길이가 늘어난 경우, 해당 길이를 유지하며 start와 end를 이동하면 된다. (그 보다 작은 경우는 더 확인할 필요가 없다)

부분수열이 중간을 선택 안하는 경우도 있는 것을 고려하지 못했다...
bool verify(int start, int end)
{
    // 길이 짝수 조건은 무조건 만족함
    // 2개씩 짝지었을 때 서로 다른 조건
    map<int, int> cntMap;
    for(int i=start; i<=end; i+=2)
    {
        if(A[i] == A[i+1])
            return false;
        else
        {
            cntMap[A[i]]++;
            cntMap[A[i+1]]++;
        }
    }
    // 교집합의 원소 갯수가 1이상인 조건
    int N = (end-start+1)/2;
    for(auto& e: cntMap)
    {   // 하나라도 N번(start~end까지의 절반) 사용된 원소가 존재하면 가능
        if(e.second == N)
            return true;
    }
    return false;
}

int solution(std::vector<int> a) {
    int answer = -1;
    A = a;
    int start = 0, end = 1;
    if(a.size() < 2)
        return 0;

    // start에서 end까지가 스타 수열을 만족하는지 확인
    while(start<a.size()-1 && end<a.size())
    {
        if(verify(start, end))
        {
            answer = max(answer, end-start+1);
            end += 2;
        }
        else
        {
            start++;
            end++;
        }
    }

    return answer;
}

시도2)
start와 end를 각각 움직여서 스타 수열 조건을 만족하게 한 후 추가하는 방식으로 진행하도록 변경
이전까지 작성한 스타 수열의 조건을 만족하도록 원소(한 쌍)를 추가한다.
이때 문제는 어떤 원소를 교집합 원소로 정할 것인지이다.
미리 정하고 이어나갈지, 구성하면서 그떄그때 결정할 것인지를 생각해봤는데 둘 다 애매한 방식같다...
일단, 첫 반복으로 어떤 수가 몇번씩 나온는지 계산한 다음
젤 많이 나온 숫잡부터 만들 수 있는 최대 길이가 얼마나 가능한지 시도한다.
이때가지 만든 길이가 이번에 사용할 숫자가 나타난 횟수보다 크거나 같으면 중단(더 길게 못 만들 것이므로)
통과
*/

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int solution(std::vector<int> a) {
    int answer = -1;

    map<int, int> cntMap;
    for(auto e: a)
        cntMap[e]++;    // 각 수가 몇번씩 등장하는지 센다
    
    // map to vect
    vector<pair<int, int>> pairVect;
    for(auto& e: cntMap)
        pairVect.push_back(e);
    sort(pairVect.begin(), pairVect.end(), [](auto back, auto front){
        return back.second > front.second;  // 많이 나타난 수가 먼저오도록 정렬
    });
    
    // 이 수로 만들 수 있는 최대 길이 시도
    for(auto& e: pairVect)
    {   
        if(answer >= e.second)  // 더 긴 부분수열을 못 만드므로 볼 이유가 없다
            break;
        int common = e.first;   // 공통수
        int sum = 0;
        vector<int> posVect;
        vector<bool> visited(a.size(), false);

        for(int i=0; i<a.size(); ++i)
            if(a[i] == common)
            {   // 공통수가 나오는 위치를 저장하고 동시에 방문표시
                posVect.push_back(i);
                visited[i] = true;
            }
        
        for(int pos: posVect)
        {   // 공통수의 앞이나 뒤를 포함해 한 쌍을 만든다
            // 방문 표시를 통해 둘이 딱 붙어있는 경우나 이미 사용된 수를 또 사용하는 경우를 제외함
            if(pos-1>=0 && !visited[pos-1])
            {
                visited[pos-1] = true;
                sum++;
            }
            else if(pos+1<a.size() && !visited[pos+1])
            {
                visited[pos+1] = true;
                sum++;
            }
        }
        answer = max(answer, sum);
    }

    return answer*2;
}

int main()
{
    vector<int> a = {0,3,3,0,7,2,0,2,2,0};
    // vector<int> a = {1,1,1,1};
    solution(a);

    return 0;
}