/*
이중우선순위큐
https://programmers.co.kr/learn/courses/30/lessons/42628

I  : 숫자 큐에 주어진 숫자를 삽입합니다.
D  1: 큐에서 최댓값을 삭제합니다.
D -1: 큐에서 최솟값을 삭제합니다.

?:
이중 우선순위 큐가 할 연산 operations가 매개변수로 주어질 때, 
모든 연산을 처리한 후 큐가 비어있으면 [0,0] 
비어있지 않으면 [최댓값, 최솟값]을 return 하도록 solution 함수를 구현해주세요.

!!!:
operations는 길이가 1 이상 1,000,000 이하인 문자열 배열입니다.
operations의 원소는 큐가 수행할 연산을 나타냅니다.
원소는 “명령어 데이터” 형식으로 주어집니다.- 최댓값/최솟값을 삭제하는 연산에서 최댓값/최솟값이 둘 이상인 경우, 하나만 삭제합니다.
빈 큐에 데이터를 삭제하라는 연산이 주어질 경우, 해당 연산은 무시합니다.

시도1) 문제에서 이중 우선순위 큐라고 했기 때문에 PQ를 두개 사용하는 것이 힌트이다.
하나는 최대값이 먼저 나오도록하고,
다른 하나는 최소값이 먼저나오도록한다.
이때 입력과 삭제를 어떻게할 것인지가 관건이다.
입력은 두 힙에 다 들어가야 할 것이다.
삭제연산은 최대를 삭제할 때는 최대힙에서만 삭제하고, 최소를 삭제할 때는 최소힙에서만 삭제한다.
이때 큐가 비는 경우를 고려하기 위해선,
전체 입력이 얼마나 들어왔었는지를 기억하고 있어야 한다.
그리고 삭제가 시행 될 때 마다 전체입력 카운트를 줄이는 식으로 구현한다.

시도2) 첫번째 case에서 실패했다.
"I 4", "I 3", "I 2", "I 1", "D 1", "D 1", "D -1", "D -1", "I 5", "I 6" 이 경우 [6,5]가 나와야하는데 [6,3]이 나왔다.
삭제할 때 조치가 더 필요한것을 깜빡했다.
heapsize 가 0이 되면 실제로 현재 두 힙을 다 비워줘야 이런 문제를 방지할 수 있다.

시도3) HeapSize가 0이 되는 순간에 두 힙을 비워주도록 다시 변경함.
통과...
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;

    // min,max heap
    priority_queue<int, vector<int>, greater<int>> minPQ;
    priority_queue<int, vector<int>, less<int>> maxPQ;
    int HeapSize = 0;    // 힙의 용량

    for(string s : operations)
    {
        // 우선 명령어를 파싱한다
        // 맨 앞 글자가 이번에 수행할 명령
        char cmd = s[0];
        // 나머지는 숫자로 바꾼다
        int n = stoi(s.substr(1, s.size()-1));

        // I 인 경우와 D인 경우로 나뉜다
        if(cmd == 'I')
        {
            HeapSize++;
            minPQ.push(n);
            maxPQ.push(n);
        }
        else if(cmd == 'D')
        {
            if(HeapSize > 0)
            {
                if(n == -1)
                    minPQ.pop();
                else
                    maxPQ.pop();

                HeapSize--;
                if(HeapSize == 0)
                {
                    // 시도3: heapsize가 0이되는 순간에 두 힙을 비운다
                    while(!minPQ.empty())
                        minPQ.pop();
                    while(!maxPQ.empty())
                        maxPQ.pop();
                }
            }
            else
            {
                /* 시도2: 남은 heap을 모두 삭제한다.
                while(!minPQ.empty())
                    minPQ.pop();
                while(!maxPQ.empty())
                    maxPQ.pop();   */
                continue;   // 무시되는 연산
            }
        }
    }
    if(HeapSize == 0)
    {
        answer = {0, 0};
    }
    else
    {
        answer = {maxPQ.top(), minPQ.top()};
    }

    return answer;
}

int main()
{
    //vector<string> operations = {"I 7","I 5","I -5","D -1"};
    vector<string> operations = {"I 4", "I 3", "I 2", "I 1", "D 1", "D 1", "D -1", "D -1", "I 5", "I 6"};   // [6,5]

    solution(operations);

    return 0;
}