/*
기지국 설치
https://programmers.co.kr/learn/courses/30/lessons/12979

아파트의 개수 N, 현재 기지국이 설치된 아파트의 번호가 담긴 1차원 배열 stations, 전파의 도달 거리 W가 매개변수로 주어질 때, 
모든 아파트에 전파를 전달하기 위해 증설해야 할 기지국 개수의 최솟값을 리턴하는 solution 함수를 완성해주세요

제한사항
N: 200,000,000 이하의 자연수
stations의 크기: 10,000 이하의 자연수
stations는 오름차순으로 정렬되어 있고, 배열에 담긴 수는 N보다 같거나 작은 자연수입니다.
W: 10,000 이하의 자연수

시도 1)
입력 특징 및 문제의 요구사항을 살펴봤을 떄 그리디 문제인 것 같다.
앞에서 부터 최대한 많은 범위를 커버하도록 채워나간다.
n이 상당히 큰 값(2억)이기 때문에 배열로 시뮬레이션 하는 방식은 사용하기 어렵다
stations가 정렬되어 있으므로 순차적으로 처리하면 될 것 같은 예감이 든다.
즉, stations의 값을 꺼내와서 처음 아파트 부터 꺼내온 범위까지 닿도록 만들어 주면서 진행한다.
69.8점...효율성 테스트는 모두 통과했다. 답이 틀리게 나오는 경우가 있는 것 같다.

시도 2)
stations의 첫 값이 맨 앞을 커버하는 경우를 생각 못했다.
83.2점...아직 틀리는 케이스가 좀 있는 것 같다.
(4, 8, 17, 19, 21케이스 실패)

시도 3)
앞을 채울 때 새로 추가하는 기지국의 범위와 이미 있던 기지국의 범위 중 더 큰 값을
선택하도록 추가
점수 그대로

시도 4)
covered가 stations가 남았는데도 n에 도달한 경우 바로 반복문 탈출하도록 추가
점수 그대로

시도 5)
covered가 e-w-1인 경우 딱 맞게 채워진다... 이점을 간파하지 못해서 해맴...
통과
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    int covered = 0;
    int station_idx = 0;
    while(station_idx < stations.size())
    {
        auto e = stations[station_idx];
        if(e-w <= 1)    // 시도 2: 첫 기지국이 맨 앞 아파트를 커버하는 경우
        {
            covered = max(covered, e+w);
            station_idx++;
            continue;
        }
        if(covered >= n)    // 시도 4
            break;
        // 앞에 신호 안닿는 아파트 있는 경우
        while(covered < e-w-1)  // 시도 5: e-w에서 e-w-1로 수정
        {
            covered += 1+2*w;
            answer++;   // 기지국 추가
        }
        // 시도 3: 둘 중 더 큰 값으로 사용
        covered = max(covered, e+w);
        station_idx++;
    }
    // stations를 다 쓴 후에도 n에 도달 못한 경우
    while(covered < n)
    {
        covered += 1+2*w;
        answer++;   // 기지국 추가
    }
    return answer;
}

int main()
{
    int n = 11;
    vector<int> stations = {4,11};
    int w = 1;
    solution(n, stations, w);

    return 0;
}