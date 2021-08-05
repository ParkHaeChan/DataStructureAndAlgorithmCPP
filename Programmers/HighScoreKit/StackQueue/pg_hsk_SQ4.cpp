/*
주식가격
https://programmers.co.kr/learn/courses/30/lessons/42584

?: 
초 단위로 기록된 주식가격이 담긴 배열 prices가 매개변수로 주어질 때, 가격이 떨어지지 않은 기간은 몇 초인지를 return 하도록 solution 함수를 완성하세요.

!!!: 
prices의 각 가격은 1 이상 10,000 이하인 자연수입니다.
prices의 길이는 2 이상 100,000 이하입니다.

문제를 이해를 제대로 해야된다.
가격이 떨어지지 않은 기간이 몇초인지는 해당 시점부터 앞으로 가면서 확인했을 때, 해당 시점보다 낮아지는 순간이 오면,
그 때까지 흐른 시간을 벡터에 저장하면 된다. 그리고 다음 가격에 대해서도 같은 방식으로 반복하면된다.
마지막 상태는 무조건 0이 된다.
*/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    int stayed = 0;
    
    for(int i=0; i<prices.size()-1; ++i)
    {
        //1. 자기 앞이랑 비교해서 줄었으면 이때까지 시점 저장후 다음으로 넘긴다.
        for(int j=i+1; j<prices.size(); ++j)
        {
            stayed++;
            if(prices[i] > prices[j])
                break;
        }
        answer.push_back(stayed);
        stayed = 0;
    }
    answer.push_back(0); //끝은 무조건 0임.
    
    return answer;
}