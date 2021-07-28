/*
문제: https://programmers.co.kr/learn/courses/30/lessons/43238

=제한 사항=
입국심사를 기다리는 사람은 1명 이상 1,000,000,000명 이하입니다.
각 심사관이 한 명을 심사하는데 걸리는 시간은 1분 이상 1,000,000,000분 이하입니다.
심사관은 1명 이상 100,000명 이하입니다.

해설:
심사를 기다리는 사람(n)이 매우 많다. (최대 10억)
그리고 심사관이 심사하는데 걸리는 시간의 분포도 매우 크다 (1~10억)
이렇게 큰 수를 처리하라는 뜻은 Log 시간에 처리가 가능한 알고리즘을 작성하라는 힌트를 주는 것이라 볼 수 있다.

심사관은 10만명 이하이므로 정렬하는데는 문제가 없다.
문제는 n명을 일일이 시뮬레이션으로 처리하면 시간이 너무 오래 걸릴 것이다.

이럴때는 관점을 바꿔서 시간이 주어지면 최대 몇명이 심사를 받을 수 있는지로 바꿔서 생각해본다.

예를 들어 일반적인 시뮬레이션 방식으로 보면,
1명이 심사를 본다면 제일 빠른 심사관이 걸리는 시간만큼일 것이다.
2명이 심사를 본다면 두번째로 빠른 심사관이 걸리는 시간 또는 제일 빠른 심사관이 2명을 보는 시간 중 하나일 것이다.
3명이 심사를 본다면 ... 고려해야 될 상황이 복잡해진다.

반대로,
시간이 주어지면 몇명이 심사를 받을 수 있는지를 계산해보면 (예시 입력으로 두 심사관이 7분, 10분씩 걸린다 가정하면)
하한은 7분이고 제일 빠른 심사관이 처리하여 1명이 가능하다.
2배로 올려 14분일 때는 제일 빠른 심사관이 2번, 그리고 14분 이내에 끝낼수 있는 심사관들이 추가로 1명씩 가능하다.

시간내에 처리가능한 사람이 n명을 넘을 때 까지 시간을 2배씩 증가시키고,
n명을 넘으면 이전의 두 값의 중간값을 시도한다.

이런식으로 계산해 나가면 X분에 처리할 수 있는 사람은
X분 이내에 처리할 수 있는 심사관들을 모두 구하여
각 심사관이 X분 내에 처리 가능한 심사는 X분 / 심사관 처리 속도이고 (나머지는 버림)
이를 누적하여 n보다 같거나 크면서 시간을 최소로 하는 x분을 이분탐색을 통해 찾으면 된다.
x가 수렴하게 되면 그때가 n명을 처리할 수 있는 시간이다.

테스트 절반밖에 통과 못해서 새로 짜고 있음(Immiigration_new.cpp 참고)
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;

    // 심사관 정렬
    sort(times.begin(), times.end());

    // 하한 시간 설정
    long long min_time = times[0];  // 1명 처리 최단 시간
    long long last_time = times[0]*2; // 임시 초기값
    
    if(n == 1)
        return min_time;
    
    // 탐색 종료 조건: min_time이 수렴
    while(abs(min_time-last_time) > 0)
    {
        long long sum = 0;

        // min_time 내에 심사 가능한 심사관 확보
        // auto ub_iter = upper_bound(times.begin(), times.end(), min_time);
        //for(auto iter = times.begin(); iter != ub_iter; ++iter)
        // 그냥 바로하다가 0되면 탈출하는게 낫다
        for(int i=0; i<times.size(); ++i)
        {
            long long temp = min_time/static_cast<long long>(times[i]);
            if(temp > 0)
                sum += temp;
            else
                break;
        }
        /* n 이랑 일치한다고 최소 시간이지는 않음
        if(sum == n)
        {
            break;
        }*/
        if(sum >= n)    // 크거나 같으면 시간 줄이기를 시도해 본다.
        {
            long long mid_time = (min_time+last_time)/2;
            //last_time = min_time; // 이걸 저장 해버리면 이전에 너무 커서 줄였던 값을 또 고려하게 됨
            if(last_time > min_time)
                last_time = min_time;

            // 차이가 1밖에 안나는데 일치하는 경우(더 줄이면 불일치한 상태로 반복문 종료됨)
            if(abs(min_time-mid_time)<=1)
                if(n == sum)
                    break;

            min_time = mid_time;
        }
        else
        {
            last_time = min_time;
            min_time *= 2;
        }
    }
    answer = min_time;

    return answer;
}

int main()
{
    int n = 6;
    vector<int> times = {7, 10};

    cout << solution(n, times) << endl;

    return 0;
}