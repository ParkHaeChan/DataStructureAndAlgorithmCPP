/*
소수 만들기
https://programmers.co.kr/learn/courses/30/lessons/12977

?:
주어진 숫자 중 3개의 수를 더했을 때 소수가 되는 경우의 개수를 구하려고 합니다. 숫자들이 들어있는 배열 nums가 매개변수로 주어질 때, 
nums에 있는 숫자들 중 서로 다른 3개를 골라 더했을 때 소수가 되는 경우의 개수를 return 하도록 solution 함수를 완성해주세요.

!!!:
nums에 들어있는 숫자의 개수는 3개 이상 50개 이하입니다.
nums의 각 원소는 1 이상 1,000 이하의 자연수이며, 중복된 숫자가 들어있지 않습니다.

시도1)
재귀로 3개를 중복되지 않게 뽑아서 그 합이 소수인지 검사한다.
*/

#include <vector>
#include <iostream>
using namespace std;

int ANSWER = 0;

// 1~1000 의 값 3개의 힙이므로 int로 커버 가능
bool isPrime(int n)
{
    for(int i=2; i*i<=n; ++i)
    {
        if(n%i == 0)
            return false;
    }
    return true;
}

void recur(vector<int>& nums, int sum, int cur, int selected)
{
    //  3개의 합을 낼 수 없는 경우
    if(nums.size() - cur + selected < 3)
        return;
    if(selected >= 3)
    {
        if(isPrime(sum))
            ANSWER++;
        return;
    }
    // 포함X
    recur(nums, sum, cur+1, selected);
    // 포함O
    recur(nums, sum + nums[cur], cur+1, selected+1);
}

int solution(vector<int> nums) {

    recur(nums, 0, 0, 0);

    return ANSWER;
}

int main()
{
    vector<int> nums = {1,2,7,6,4};

    solution(nums);

    return 0;
}