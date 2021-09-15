/*
최고의 집합
https://programmers.co.kr/learn/courses/30/lessons/12938

자연수 n 개로 이루어진 중복 집합(multi set, 편의상 이후에는 "집합"으로 통칭) 중에 다음 두 조건을 만족하는 집합을 최고의 집합이라고 합니다.

각 원소의 ㅎ
위 조건을 만족하면서 각 원소의 곱 이 최대가 되는 집합
예를 들어서 자연수 2개로 이루어진 집합 중 합이 9가 되는 집합은 다음과 같이 4개가 있습니다.
{ 1, 8 }, { 2, 7 }, { 3, 6 }, { 4, 5 }
그중 각 원소의 곱이 최대인 { 4, 5 }가 최고의 집합입니다.

집합의 원소의 개수 n과 모든 원소들의 합 s가 매개변수로 주어질 때, 최고의 집합을 return 하는 solution 함수를 완성해주세요.

!!!:
최고의 집합은 오름차순으로 정렬된 1차원 배열(list, vector) 로 return 해주세요.
만약 최고의 집합이 존재하지 않는 경우에 크기가 1인 1차원 배열(list, vector) 에 -1 을 채워서 return 해주세요.
자연수의 개수 n은 1 이상 10,000 이하의 자연수입니다.
모든 원소들의 합 s는 1 이상, 100,000,000 이하의 자연수입니다.

시도1)
n이 1만 이하이고 모든 원소들의 합은 1억이하 이므로 모든 경우를 구성하는 방식으로는 불가능
그렇면 동적계획법 또는 탐욕법 문제일 것이다.
합이 S이면서 집합의 곱이 최대가 되어야 하므로 집합 구성에 1*(S-1) 같은 경우는 탈락할 가능성이 크다.
그리고 중복이 가능하므로 각 n이 서로 최대한 분산이 적은 값으로 구성되면 각각의 곱이 최대가 된다.
10점 나옴...
좀 생각해보니까 나머지를 그냥 더해주지 않고 최대한 분해해서 더해줘야
다른 값들과의 편차가 적어진다.

시도2)
통과
*/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;

    int quotient = s/n;
    int remainder = s%n;
    
    if(quotient == 0)
        answer.push_back(-1);
    else
    {
        for(int i=0; i<n; ++i)
            answer.push_back(quotient);

        // 뒤에서 부터 하나씩 적용
        int back_idx = answer.size()-1;
        while(remainder-->0)
        {
            answer[back_idx--]++;
        }
    }

    return answer;
}

int main()
{
    int n = 2, s = 9;
    solution(n, s);
}