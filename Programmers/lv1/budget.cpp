/*
예산
https://programmers.co.kr/learn/courses/30/lessons/12982

?:
부서별로 신청한 금액이 들어있는 배열 d와 예산 budget이 매개변수로 주어질 때, 최대 몇 개의 부서에 물품을 지원할 수 있는지 return 하도록 solution 함수를 완성해주세요.
!!!:
d는 부서별로 신청한 금액이 들어있는 배열이며, 길이(전체 부서의 개수)는 1 이상 100 이하입니다.
d의 각 원소는 부서별로 신청한 금액을 나타내며, 부서별 신청 금액은 1 이상 100,000 이하의 자연수입니다.
budget은 예산을 나타내며, 1 이상 10,000,000 이하의 자연수입니다.

간단한 greedy 문제이다. 정렬 후 최저 예산부터 budget에서 빼면서 세면된다.
*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> d, int budget) {
    int answer = 0;

    sort(d.begin(), d.end());

    for(auto e: d)
    {
        if(budget - e >= 0)
        {
            budget -= e;
            answer++;
        }
        else
            break;
    }

    return answer;
}