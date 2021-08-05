/*
프린터
https://programmers.co.kr/learn/courses/30/lessons/42587

1. 인쇄 대기목록의 가장 앞에 있는 문서(J)를 대기목록에서 꺼냅니다.
2. 나머지 인쇄 대기목록에서 J보다 중요도가 높은 문서가 한 개라도 존재하면 J를 대기목록의 가장 마지막에 넣습니다.
3. 그렇지 않으면 J를 인쇄합니다.

예를 들어, 4개의 문서(A, B, C, D)가 순서대로 인쇄 대기목록에 있고 중요도가 2 1 3 2 라면 C D A B 순으로 인쇄하게 됩니다.
?:
현재 대기목록에 있는 문서의 중요도가 순서대로 담긴 배열 priorities와 
내가 인쇄를 요청한 문서가 현재 대기목록의 어떤 위치에 있는지를 알려주는 location이 매개변수로 주어질 때, 
내가 인쇄를 요청한 문서가 몇 번째로 인쇄되는지 return 하도록 solution 함수를 작성해주세요.
!!!:
현재 대기목록에는 1개 이상 100개 이하의 문서가 있습니다.
인쇄 작업의 중요도는 1~9로 표현하며 숫자가 클수록 중요하다는 뜻입니다.
location은 0 이상 (현재 대기목록에 있는 작업 수 - 1) 이하의 값을 가지며 대기목록의 가장 앞에 있으면 0, 두 번째에 있으면 1로 표현합니다.

문제에서 요구하는 그대로 구현하면 작동한다. 큐에 넣으면 뒤에 더 큰 작업이 있는지 확인해 보려면
더 큰 작업이 나올 때 까지 큐에서 값을 빼면서 빼놓은 값을 다시 넣기 위해 또 다른 큐에 저장해둔다.
더 큰 작업이 나오면 처음 뺀 값을 다시 원래 큐에 넣고, 임시 큐에 있는 값을 전부 원래 큐에 넣는다.
이때 더 큰 작업은 front()로 확인만 하고 pop()으로 빼진 않은 상태로 두어서 다음번 반복때는 이 값부터 진행된다.
이 값이 가장 큰 우선순위였다면, 임시 큐에 나머지 값들이 모드 들어가고 원래 큐는 비게 된다.
이 상황이 오면 이 값이 1순위이므로 answer++을 하고 이 값의 location을 저장한 cur.second를 확인하여
찾는 위치면 반복문 탈출하여 종료한다. (또는 anwer를 바로 return 한다)
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;

    // priorities 와 현재 location을 묶어서 같이 다뤄야한다.
    using job = pair<int, int>;
    queue<job> jobQ;
    // 큐의 초기상태
    for(int i=0; i<priorities.size(); ++i)
    {
        jobQ.push({priorities[i], i});
    }
    // 하나 빼서 그보다 중요도 큰게 나오면 다시 뒤에 넣고 안나오면 그것을 출력
    while(!jobQ.empty())
    {
        job cur = jobQ.front(); jobQ.pop();
        queue<job> tempQ;
        while(!jobQ.empty())
        {
            job temp = jobQ.front();
            if(cur.first < temp.first)
            {
                jobQ.push(cur);
                while(!tempQ.empty())
                {
                    jobQ.push(tempQ.front());
                    tempQ.pop();
                }
                break;
            }
            else
            {
                jobQ.pop();
                tempQ.push(temp);
            }
        }
        if(jobQ.empty())
        {
            answer++;
            //cout << cur.second << endl;
            if(cur.second == location)
                break;
            while(!tempQ.empty())
            {
                jobQ.push(tempQ.front());
                tempQ.pop();
            }                
        }
    }

    return answer;
}

int main()
{
    vector<int> priorities = {1, 1, 9, 1, 1, 1};
    int location = 0;

    cout << solution(priorities, location) << endl;

    return 0;
}