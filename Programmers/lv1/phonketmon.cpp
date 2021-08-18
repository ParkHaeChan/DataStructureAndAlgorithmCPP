/*
폰켓몬
https://programmers.co.kr/learn/courses/30/lessons/1845

?:
당신은 최대한 다양한 종류의 폰켓몬을 가지길 원하기 때문에, 최대한 많은 종류의 폰켓몬을 포함해서 N/2마리를 선택하려 합니다. 
N마리 폰켓몬의 종류 번호가 담긴 배열 nums가 매개변수로 주어질 때, N/2마리의 폰켓몬을 선택하는 방법 중, 
가장 많은 종류의 폰켓몬을 선택하는 방법을 찾아, 그때의 폰켓몬 종류 번호의 개수를 return 하도록 solution 함수를 완성해주세요.

!!!:
nums는 폰켓몬의 종류 번호가 담긴 1차원 배열입니다.
nums의 길이(N)는 1 이상 10,000 이하의 자연수이며, 항상 짝수로 주어집니다.
폰켓몬의 종류 번호는 1 이상 200,000 이하의 자연수로 나타냅니다.
가장 많은 종류의 폰켓몬을 선택하는 방법이 여러 가지인 경우에도, 선택할 수 있는 폰켓몬 종류 개수의 최댓값 하나만 return 하면 됩니다.

종류 갯수를 저장한 다음
종류가 전체의 반보다 크면 반만 가져가야하므로 최대가 반이고,
종류가 반보다 작거나 같으면 모든 종류를 다 가져가는 경우가 최대이다.
*/

#include <vector>
#include <set>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    int Limit = nums.size()/2;
    set<int> kinds;

    for(auto e: nums)
        kinds.insert(e);

    answer = (kinds.size() > Limit) ? Limit : kinds.size();

    return answer;
}