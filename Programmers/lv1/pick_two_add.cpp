/*
두 개 뽑아서 더하기
https://programmers.co.kr/learn/courses/30/lessons/68644

?:
정수 배열 numbers가 주어집니다. 
numbers에서 서로 다른 인덱스에 있는 두 개의 수를 뽑아 더해서 만들 수 있는 모든 수를 
배열에 오름차순으로 담아 return 하도록 solution 함수를 완성해주세요.
!!!:
numbers의 길이는 2 이상 100 이하입니다.
numbers의 모든 수는 0 이상 100 이하입니다.

2중 for문으로 처리할 수 있다.
정렬된 상태로 뽑아서 더하면 또 정렬할 필요가 없다
중복을 허용하지 않으므로 set에 넣었다 빼는 식으로 하면 편하다.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> solution(vector<int> numbers) {
    vector<int> answer;

    sort(numbers.begin(), numbers.end());
    set<int> twosum;
    for(int i=0; i<numbers.size(); ++i)
    {
        for(int j=i+1; j<numbers.size(); ++j)
        {
            twosum.insert(numbers[i]+numbers[j]);
        }
    }
    for(int e: twosum)
    {
        answer.push_back(e);
    }

    return answer;
}