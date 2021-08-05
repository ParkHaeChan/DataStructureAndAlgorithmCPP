/*
K번째 수
https://programmers.co.kr/learn/courses/30/lessons/42748

배열 array의 i번째 숫자부터 j번째 숫자까지 자르고 정렬했을 때, k번째에 있는 수를 구하려 합니다.

?:
배열 array, [i, j, k]를 원소로 가진 2차원 배열 commands가 매개변수로 주어질 때, 
commands의 모든 원소에 대해 앞서 설명한 연산을 적용했을 때 나온 결과를 배열에 담아 return 하도록 solution 함수를 작성해주세요.

!!!:
array의 길이는 1 이상 100 이하입니다.
array의 각 원소는 1 이상 100 이하입니다.
commands의 길이는 1 이상 50 이하입니다.
commands의 각 원소는 길이가 3입니다.

원소수가 적으므로 주어지는 index를 가지고 새로 벡터를 만들어서 정렬하면된다.
굳이 부분 정렬을 수행할 필요는 없다.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    int from, to, kth;
    for(int i=0; i<commands.size(); ++i)
    {
        from = commands[i][0];
        to = commands[i][1];
        kth = commands[i][2];
        
        vector<int> temp;
        for(int j=from-1; j<to; ++j)
            temp.push_back(array[j]);
        sort(temp.begin(), temp.end());
        answer.push_back(temp[kth-1]);
        temp.clear();
    }
    
    return answer;
}