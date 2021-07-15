#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// 문제: https://programmers.co.kr/learn/courses/30/lessons/42885

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    // Greedy 문제로 다음과 같이 시도해 본다.
    // 정렬 후 최소 몸무게인 사람과 최대 몸무게인 사람이 같이 탈 수 있는지 확인
    // 몸무게가 초과하면 그 다음 최대 몸무게인 사람과 최소 몸무게인 사람이 가능한지 확인
    // 가능하면 그 두 명을 제외하고 보트 개수 +1 후 같은 작업 반복
    int N = people.size();
    int thin = 0;
    int fat=N-1;
    sort(people.begin(), people.end());
    
    // 젤 가벼운 사람과 젤 무거운 사람 무게 합 비교
    for( ; fat > thin; --fat)    // fat == thin 이면 같은 사람 가리키므로 따로 처리
    {
        if(people[thin] + people[fat] > limit)  //몸무게 초과하면
        {
            // 현재 제일 가벼운 사람과도 같이 못 타므로 무거운 사람 혼자 타야 한다.
            answer++;   // 보트 수 증가
            continue;   // 그 다음으로 무거운 사람과 비교
        }
        else
        {
            // 두 명이 탈 수 있는 경우
            answer++;   // 보트 수 증가
            thin++; // 다음 가벼운 사람과 비교
        }
    }
    if(thin == fat) // 같은 한 사람을 가리킴
    {
        answer++;   //혼자 탄다
    }
    // 이 외의 경우는 thin > fat으로 나오므로 처리가 필요 없다

    
    return answer;
}