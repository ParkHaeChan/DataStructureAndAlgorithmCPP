/*
기능개발
https://programmers.co.kr/learn/courses/30/lessons/42586

각 기능의 개발속도는 모두 다르기 때문에 뒤에 있는 기능이 앞에 있는 기능보다 먼저 개발될 수 있고,
이때 뒤에 있는 기능은 앞에 있는 기능이 배포될 때 함께 배포됩니다.

?: 먼저 배포되어야 하는 순서대로 작업의 진도가 적힌 정수 배열 progresses와 
각 작업의 개발 속도가 적힌 정수 배열 speeds가 주어질 때 
각 배포마다 몇 개의 기능이 배포되는지를 return 하도록 solution 함수를 완성하세요.
!!!:
작업의 개수(progresses, speeds배열의 길이)는 100개 이하입니다.
작업 진도는 100 미만의 자연수입니다.
작업 속도는 100 이하의 자연수입니다.
배포는 하루에 한 번만 할 수 있으며, 하루의 끝에 이루어진다고 가정합니다. 예를 들어 진도율이 95%인 작업의 개발 속도가 하루에 4%라면 배포는 2일 뒤에 이루어집니다.

시도1)
젤 앞의 작업이 끝날때 뒤의 작업율 100을 넘긴 작업을 모두 모아서 처리한다. (X) --> 잘 못 이해함...
남은 작업에 대해서 남은 작업중 맨앞의 작업이 끝날때 뒤의 작업율 100을 넘긴 작업을 모아서 처리한다
(반복...)

시도2)
입력2를 읽어보고 문제점이 뭔지 알았다.
100, 99, 100, 100, 100 이면, 맨 앞에 100 하나만 처리되야 한다.
즉, 아직 덜된 작업을 만나면 거기서 중단하고(시작지점으로 설정)하고 다시 시도한다.
완료된 작업 검사할 때 start위치부터 시작하도록 하면 완료된 상태를 저장하기 위한 bool벡터를 사용할 필요가 없어진다.
*/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int start = 0, doneCnt = 0;
    while(true)
    {
        for(int i=0; i<progresses.size(); ++i)
        {
            progresses[i] += speeds[i];
        }

        if(progresses[start] < 100)
            continue;
        else
        {
            int cnt = 0;
            // 여기서도 start부터 봐야 함
            for(int i=start; i<progresses.size(); ++i)
            {
                if(progresses[i] >= 100)
                {
                    cnt++;
                }
                else
                {   // 덜된 작업있으면 거기서 부터 다시 시작해야됨
                    start = i;
                    break;
                }
            }
            answer.push_back(cnt);
            doneCnt += cnt;
        }
        if(doneCnt == progresses.size())
            break;
    }
    return answer;
}

int main()
{
    vector<int> progresses = {95, 90, 99, 99, 80, 99};
    vector<int> speeds = {1, 1, 1, 1, 1, 1};

    solution(progresses, speeds);

    return 0;
}