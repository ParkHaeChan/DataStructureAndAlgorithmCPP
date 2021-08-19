/*
실패율
https://programmers.co.kr/learn/courses/30/lessons/42889

실패율은 다음과 같이 정의한다.
스테이지에 도달했으나 아직 클리어하지 못한 플레이어의 수 / 스테이지에 도달한 플레이어 수
?:
전체 스테이지의 개수 N, 게임을 이용하는 사용자가 현재 멈춰있는 스테이지의 번호가 담긴 배열 stages가 매개변수로 주어질 때,
실패율이 높은 스테이지부터 내림차순으로 스테이지의 번호가 담겨있는 배열을 return 하도록 solution 함수를 완성하라.

!!!:
스테이지의 개수 N은 1 이상 500 이하의 자연수이다.
stages의 길이는 1 이상 200,000 이하이다.
stages에는 1 이상 N + 1 이하의 자연수가 담겨있다.
각 자연수는 사용자가 현재 도전 중인 스테이지의 번호를 나타낸다.
단, N + 1 은 마지막 스테이지(N 번째 스테이지) 까지 클리어 한 사용자를 나타낸다.
만약 실패율이 같은 스테이지가 있다면 작은 번호의 스테이지가 먼저 오도록 하면 된다.
스테이지에 도달한 유저가 없는 경우 해당 스테이지의 실패율은 0 으로 정의한다.
*/

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int gcd(int a, int b)
{   // 유클리드 알고리즘
    if(a < b)   // a에 큰값 오도록
        swap(a, b);

    while(b != 0)
    {
        int n = a%b;
        a = b;
        b = n;
    }
    return  a; 
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;

    // 오름차순 정렬
    sort(stages.begin(), stages.end());

    // 전체 플레이어 수
    int PLAYERS = stages.size();

    // 정렬 된 stages에서 작은 수 부터 각각의 실패율을 계산하여 map으로 저장
    // {현재 스테이지 : 멈춘 사람 수}
    map<int,int> failureMap;
    for(int i=0; i<PLAYERS; ++i)
    {
        failureMap[stages[i]]++;
    }
    // stage에 도달한 player 수 = 전체 플레이어 - 도달 못한 플레이어 수
    // 여기서는 도달 못한 플레이어 수를 전체 플레이어에서 빼주기 쉽게 미리 누적해둔다
    map<int, int> cumulatedMap;
    pair<int,int> last = {0, 0};
    for(auto it = failureMap.begin(); it != failureMap.end(); ++it)
    {
        int stage = it->first;
        int people = it->second;
        cumulatedMap[stage] += people + cumulatedMap[last.first];
        last = {stage, people};
    }
    // 각 stage의 실패율을 계산하여 pair<stage, 실패율>로 관리
    // 두가지 방식을 사용할 수 있다
    // 1) 두 수의 최대 공약수로 나눈 뒤 각각 분자와 분모를 비교하여 정렬
    // 2) 실수로 변환하여 나눗셈 수행한 뒤 대소 비교(정밀도 주의 필요)
    // 1) 은 후속처리(분모 같게 만들기)가 필요하다
    // 2) 를 사용하되 1)의 처리를 한 다음 2)를 사용하면, 실수 비교로 ==를 사용해도 문제가 생길 확률이 약간 준다
    // 여기서는 입력이 작아서(20만) 별 문제가 생기지 않았지만 수억 단위로 넘어가면 문제가 생길 수도 있으므로 주의가 필요하다
    vector<pair<int, double>> failureRateVect;
    for(int stage = 1; stage <= N; ++stage) // 모든 stage에 대해 실패율 순으로 정렬해야 함
    {
        // 실패율
        int numerator = failureMap[stage];
        int denominator = PLAYERS - cumulatedMap[stage] + failureMap[stage];
        int GCD = gcd(numerator, denominator);
        failureRateVect.push_back({stage, (double)(numerator/GCD)/(denominator/GCD)});
    }
    // 실패율 오름차순으로 정렬
    sort(failureRateVect.begin(), failureRateVect.end(), [](auto a, auto b){
        if(a.second == b.second)
        {
            return a.first < b.first;   // stage 낮은 순
        }
        else
            return a.second > b.second; // 실패율 높은 순
    });
    for(auto e: failureRateVect)
        answer.push_back(e.first);

    return answer;
}

int main()
{
    int N = 5;
    vector<int> stages = {2, 1, 2, 6, 2, 4, 3, 3};

    solution(N, stages);

    return 0;
}