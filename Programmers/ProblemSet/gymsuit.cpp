/*
문제: https://programmers.co.kr/learn/courses/30/lessons/42862#

cpp로 여러 테스트를 해보는 중 예상치 못했던 오류들을 찾아내고 있다.

예를들면, vector를 erase로 삭제하기 위해 삭제할 때 참조할 iterator들을 벡터에 모아두었다가
모아둔 iterator를 사용하여 삭제를 진행하면 에러가 발생한다.
이유는 이미 계산된 iterator는 벡터가 변형되면 쓸모가 없어지는 부정확한 위치를 가리키는 포인터가 되기 때문이다.
이터레이터를 사용할 때는 이런 점을 주의하여야 한다.
이터레이터는 필요할때 바로 계산하여 쓰고 버린다고 생각하면된다.

그리고 배열 내용을 삭제하면서 반복문으로 배열을 순회할 수는 없다.
순회 도중에 배열의 크기가 변하여 내용물의 index가 바뀌면서 중간에 뛰어넘어가는 요소가 발생하기 때문이다.

그리고 이런 greedy 문제는 sorting이 반드시 필요하다. (마지막 테스트case 통과 못하는 것은 sort문제)
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    
    // 정렬하고
    sort(reserve.begin(), reserve.end());
    sort(lost.begin(), lost.end());
    
    vector<int> shouldremoved;
    // 준비해 온 사람이 도난당한 경우 reserve에서 제외 + (아직 한벌 남았기 때문에 lost에서도 제외된다)
    for(int lo: lost)   // 이 구문으로 반복문 실행하면서 배열 크기가 바뀌면 제대로 작동하지 않으므로 주의한다.
    {
        auto iter = find(reserve.begin(), reserve.end(), lo);
        if(iter != reserve.end())
        {   // 반복문 내부에서 삭제하면 제대로 작동안해서 모아놨다가 한번에 삭제한다.
            shouldremoved.push_back(lo);
            //reserve.erase(iter);
            //reserve_iter_vect.push_back(iter);
            //auto it = find(lost.begin(), lost.end(), lo);
            //lost.erase(it);
            //lost_iter_vect.push_back(it);
        }
    }
    for(auto e: shouldremoved)  // 이런식으로 바로 계산해서 바로 쓰면 문제가 발생하지 않는다.
    {
        auto iter = find(lost.begin(), lost.end(), e);
        lost.erase(iter);
        iter = find(reserve.begin(), reserve.end(), e);
        reserve.erase(iter);
    }
    
    // 실제 빌려 입어야하는 사람 수
    int lostN = lost.size();
    // lost 인원에 대해
    for(int lo : lost)
    {
        for(int cur : reserve)
        {// 빌려줄 수 있는 경우
            if(cur+1 == lo || cur-1 == lo)
            {    
                lostN--;
                auto iter = find(reserve.begin(), reserve.end(), cur);
                reserve.erase(iter);
                break;
            }
        }
    }
    answer = n-lostN;
    
    return answer;
}

int main()
{
    int n = 3;
    vector<int> lost = {1,2,3};
    vector<int> reserve = {1,2,3};

    cout << solution(n, lost, reserve) << endl;

    return 0;
}