/*
줄 서는 방법
https://programmers.co.kr/learn/courses/30/lessons/12936

n명의 사람이 일렬로 줄을 서고 있습니다. n명의 사람들에게는 각각 1번부터 n번까지 번호가 매겨져 있습니다. 
n명이 사람을 줄을 서는 방법은 여러가지 방법이 있습니다. 예를 들어서 3명의 사람이 있다면 다음과 같이 6개의 방법이 있습니다.

시도1) next_permutation 사용
효율성 테스트에서 시간초과 발생

시도2) 
앞글자로 시작하는 경우의 수를 먼저 센다.
k보다 작으면 k에서 빼주고, 그 다음 글자로 시작하는 경우부터 확인한다.
재귀로 구현

시도3)
k를 빼는 과정에서 k가 factorial과 같은 경우
마지막 번째라면 상관 없지만 중간에 그렇게 될 경우 문제가 생긴다.
예를 들면 n=3, k=6인 경우 3으로 시작하는 것 까지는 맞게 도는데
이후로 이미 k가 0이므로 2로 시작하는 경우를 따지지 않는다.
이 부분 해결 후 통과
*/

#include <string>
#include <vector>

using namespace std;

vector<bool> visited;
// 기본 permutation을 구현 후 이번 재귀로 나오는 모든 가지수가 k보다 작은지 확인
void fast_permutation(vector<int>& arr, int depth, long long k, vector<int>& selected)
{   
    if(depth == arr.size())
    {
        return;
    }

    int n = arr.size();
    int s = selected.size()+1;  // 이때까지 뽑은 수 + 이번에 뽑을 것(1)
    for(int start=0; start < arr.size(); ++start)
    {
        if(visited[start])
            continue;
        
        // 이번 선택으로 나오는 모든 가지수: (n-s)!
        long long factorial = 1;
        for(int f=2; f<=n-s; ++f)
            factorial *= f;
        if(k > factorial)   // 시도 3: k == factorial의 경우는 다음 재귀에서 찾도록 놔둠
        {   // k에서 fact만큼 줄이고 다음 start로 재시도
            k -= factorial;
            // 시도 3에서 삭제: if(k > 0)   // 시도 2: 0인 경우는 이번 start를 선택해야 함
            continue;
        }

        visited[start] = true;
        selected.push_back(arr[start]);
        fast_permutation(arr, depth+1, k, selected);
        /*  한번에 찾으므로 다른 것 시도할 필요 없이 그대로 종료하면 selected가 찾는 답이다
        visited[start] = false;
        selected.pop_back();
        */
    }
}

vector<int> solution(int n, long long k) {
    vector<int> answer;

    for(int i=1; i<=n; ++i)
        answer.push_back(i);

    vector<int> selected;
    visited = vector<bool>(n, false);
    fast_permutation(answer, 0, k, selected);

    return answer = selected;
}

int main()
{
    int n =3;
    long long k = 6;

    solution(n, k);

    return 0;
}