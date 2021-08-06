/*
H-Index
https://programmers.co.kr/learn/courses/30/lessons/42747

?:
어떤 과학자가 발표한 논문 n편 중, h번 이상 인용된 논문이 h편 이상이고 나머지 논문이 h번 이하 인용되었다면 h의 최댓값이 이 과학자의 H-Index입니다.
어떤 과학자가 발표한 논문의 인용 횟수를 담은 배열 citations가 매개변수로 주어질 때, 이 과학자의 H-Index를 return 하도록 solution 함수를 작성해주세요.

!!!:
과학자가 발표한 논문의 수는 1편 이상 1,000편 이하입니다.
논문별 인용 횟수는 0회 이상 10,000회 이하입니다.

시도1)
논문 n편 중 h번 이상 인용된 논문이 h편 이상이면 그 h가 h-index이다.
즉, citations 배열을 정렬한 후 해당 인덱스 보다 인용수가 적으면 거기까지가 h-index의 최대가 된다.

시도2)
조건을 좀 더 살펴봤어야 한다. 남은 n-h개의 논문은 h보다 적게 인용되어야 h-index가 될 수 있다.
위 조건만 가지면 {3, 0, 6, 1, 5} -> 정렬 후 {0,1,3,5,6} 모든 경우 i <= citations[i]로 그냥 끝까지 간다.
이 경우는 3보다 같거나 큰 수가 3개이고 나머지는 3보다 작으므로 h-index가 3이다.
앞에서 부터 확인해가면서 더 큰값이 가능하지 않으면 반복문을 탈출하도록 구현하였다

시도3)
뒤에서 부터 h-index를 센다.
citations[n-i] <= i가 (i=1~n) 되는 순간의 citations[n-i] 가 최대 h-index이다.

시도4)
n편 중, h번 이상 인용된 논문이 h편 이상이고 나머지 논문이 h번 이하 인용
이 부분을 그대로 코드로 치환하였다

시도5) 뭔지 모르겠어서 힌트 봤는데 문제가 오해할만 했던거 같다.
위키를 참고해서 읽어보면 뭐를 답으로 써야하는지 나온다.
-wiki-
Formally, if f is the function that corresponds to the number of citations for each publication,
we compute the h-index as follows: 
First we order the values of f from the largest to the lowest value. 
Then, we look for the last position in which f is greater than or equal to the position (we call h this position).

For example, if we have a researcher with 5 publications A, B, C, D, and E with 10, 8, 5, 4, and 3 citations, respectively, 
the h-index is equal to 4 because the 4th publication has 4 citations and the 5th has only 3. 
In contrast, if the same publications have 25, 8, 5, 3, and 3 citations, then the index is 3 (i.e. the 3rd position) 
because the fourth paper has only 3 citations.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    
    // 내림차순 정렬
    sort(citations.begin(), citations.end(), [](auto a, auto b){
        return a>b;
    });
    
    // citation[i]이 논문수(i+1) 이상일때 h = 논문수(i+1) 저장
    for(int i=0; i<citations.size(); ++i)
    if(citations[i] >= i+1)
        answer = i+1;
    
    return answer;
}

int main()
{
    //vector<int> citations = {3, 0, 6, 1, 5};    // 3
    //vector<int> citations = {10, 8, 5, 3, 4};   // 4
    //vector<int> citations = {25, 8, 5, 3, 3};   // 3
    vector<int> citations = {88, 89};   // 2

    cout << solution(citations) << endl;

    return 0;
}