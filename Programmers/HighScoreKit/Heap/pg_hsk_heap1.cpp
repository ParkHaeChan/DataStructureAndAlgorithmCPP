/*
더 맵게
https://programmers.co.kr/learn/courses/30/lessons/42626

섞은 음식의 스코빌 지수 = 가장 맵지 않은 음식의 스코빌 지수 + (두 번째로 맵지 않은 음식의 스코빌 지수 * 2)

?:
Leo는 모든 음식의 스코빌 지수가 K 이상이 될 때까지 반복하여 섞습니다.
Leo가 가진 음식의 스코빌 지수를 담은 배열 scoville과 원하는 스코빌 지수 K가 주어질 때,
모든 음식의 스코빌 지수를 K 이상으로 만들기 위해 섞어야 하는 최소 횟수를 return 하도록 solution 함수를 작성해주세요.

!!!:
scoville의 길이는 2 이상 1,000,000 이하입니다.
K는 0 이상 1,000,000,000 이하입니다.
scoville의 원소는 각각 0 이상 1,000,000 이하입니다.
모든 음식의 스코빌 지수를 K 이상으로 만들 수 없는 경우에는 -1을 return 합니다.

최소 heap에 모든 음식의 스코빌 지수를 넣은 후
2개 값을 heap에서 빼서 위의 섞기를 수행한 후 다시 heap에 넣기를 반복해서
다음 값이 k 이상이면 섞기 횟수를 반환하며 종료한다.

시도1) 만들 수 없는 경우에 대한 처리를 깜빡했다.
시도2) 통과...
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;

    priority_queue<int, vector<int>, greater<int>> scovilleHeap;   // 기본형은 minheap인데 연습삼아 전체를 써봄

    // 초기화
    for(auto e: scoville)
        scovilleHeap.push(e);

    while(!scovilleHeap.empty())
    {
        int cur1 = scovilleHeap.top(); scovilleHeap.pop();
        if(cur1 >= K)
            break;

        int cur2;
        if(!scovilleHeap.empty())
        {
            cur2 = scovilleHeap.top();
            scovilleHeap.pop();
        }
        else
        {   // cur1뿐인데 k를 넘지 못하므로 불가능한 경우이다
            answer = -1;
            break;
        }

        int newscv = cur1+cur2*2;
        scovilleHeap.push(newscv);
        answer++;
    }

    return answer;
}

int main()
{
    int k = 7;
    vector<int> scoville = {1, 2, 3, 9, 10, 12};

    cout << solution(scoville, k) << endl;

    return 0;
}