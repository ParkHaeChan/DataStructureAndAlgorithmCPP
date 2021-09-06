/*
기능 개발
https://programmers.co.kr/learn/courses/30/lessons/42586

프로그래머스 팀에서는 기능 개선 작업을 수행 중입니다. 각 기능은 진도가 100%일 때 서비스에 반영할 수 있습니다.
또, 각 기능의 개발속도는 모두 다르기 때문에 뒤에 있는 기능이 앞에 있는 기능보다 먼저 개발될 수 있고, 이때 뒤에 있는 기능은 앞에 있는 기능이 배포될 때 함께 배포됩니다.

먼저 배포되어야 하는 순서대로 작업의 진도가 적힌 정수 배열 progresses와 각 작업의 개발 속도가 적힌 정수 배열 speeds가 주어질 때 
각 배포마다 몇 개의 기능이 배포되는지를 return 하도록 solution 함수를 완성하세요.

제한 사항
작업의 개수(progresses, speeds배열의 길이)는 100개 이하입니다.
작업 진도는 100 미만의 자연수입니다.
작업 속도는 100 이하의 자연수입니다.
배포는 하루에 한 번만 할 수 있으며, 하루의 끝에 이루어진다고 가정합니다. 예를 들어 진도율이 95%인 작업의 개발 속도가 하루에 4%라면 배포는 2일 뒤에 이루어집니다.

시도 1)
여기서는 맞게 나오는데, 제출해서 돌렸을 때는 답이 다르게 나왔다.
컴파일러 문제인가 싶었는데
배열 인덱스 범위 넘어갈때 컴파일러 마다 처리가 달라서 그런 것이였다...
start 범위 처리 해주니 통과함
<<항상 배열을 index로 접근 할 떄는 범위를 주의하자>>
*/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int start = 0, cnt = 0;
    int N = progresses.size();
    while(start < N)
    {
        cnt = 0;
        while(progresses[start] >= 100 && start < N)
        {
            start++;
            cnt++;
        }
        if(cnt > 0)
            answer.push_back(cnt);
        // progress 진행
        for(int i=start; i<N; ++i)
        {
            progresses[i] += speeds[i];
        }
    }

    return answer;
}

int main()
{
    vector<int> progresses = {93, 30, 55};
    vector<int> speeds = {1, 30, 5};
    // vector<int> progresses = {95, 90, 99, 99, 80, 99};
    // vector<int> speeds = {1, 1, 1, 1, 1, 1};

    solution(progresses, speeds);
    return 0;
}