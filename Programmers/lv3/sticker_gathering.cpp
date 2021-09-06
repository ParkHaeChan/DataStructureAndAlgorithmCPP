/*
스티커 모으기(2)
https://programmers.co.kr/learn/courses/30/lessons/12971

원형으로 연결된 스티커에서 몇 장의 스티커를 뜯어내어 뜯어낸 스티커에 적힌 숫자의 합이 최대가 되도록 하고 싶습니다.
 단 스티커 한 장을 뜯어내면 양쪽으로 인접해있는 스티커는 찢어져서 사용할 수 없게 됩니다.

예를 들어 위 그림에서 14가 적힌 스티커를 뜯으면 인접해있는 10, 6이 적힌 스티커는 사용할 수 없습니다. 
스티커에 적힌 숫자가 배열 형태로 주어질 때, 
스티커를 뜯어내어 얻을 수 있는 숫자의 합의 최댓값을 return 하는 solution 함수를 완성해 주세요. 
원형의 스티커 모양을 위해 배열의 첫 번째 원소와 마지막 원소가 서로 연결되어 있다고 간주합니다.

!!!:
sticker는 원형으로 연결된 스티커의 각 칸에 적힌 숫자가 순서대로 들어있는 배열로, 길이(N)는 1 이상 100,000 이하입니다.
sticker의 각 원소는 스티커의 각 칸에 적힌 숫자이며, 각 칸에 적힌 숫자는 1 이상 100 이하의 자연수입니다.
원형의 스티커 모양을 위해 sticker 배열의 첫 번째 원소와 마지막 원소가 서로 연결되어있다고 간주합니다.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> sticker)
{
    int answer =0;

    int N = sticker.size();
    vector<int> DP(N, 0);

    if(N == 1)
        return sticker[0];

    // DP[i] : i번째 스티커를 뜯었을 떄 얻을 수 있는 최대 점수
    // 점화식: DP[i] = max(DP[i-2]+sticker[i], DP[i-1]);

    // 0번을 뜯으면 마지막 N-1은 못 뜯는다 (순환)
    DP[0] = sticker[0];
    DP[1] = max(sticker[0], sticker[1]);
    for(int i=2; i<N-1; ++i)
    {
        DP[i] = max(DP[i-2]+sticker[i], DP[i-1]);
    }
    int start_0 = DP[N-2];

    DP = vector<int>(N, 0); // 초기화
    // 0번을 안뜯으면 마지막 N-1을 뜯을 수 있다
    DP[0] = 0;
    DP[1] = sticker[1];
    for(int i=2; i<N; ++i)
    {
        DP[i] = max(DP[i-2]+sticker[i], DP[i-1]);
    }
    int start_1 = DP[N-1];

    answer = max(start_0, start_1);

    return answer;
}

int main()
{
    vector<int> sticker = {14, 6, 5, 11, 3, 9, 2, 10};

    solution(sticker);

    return 0;
}