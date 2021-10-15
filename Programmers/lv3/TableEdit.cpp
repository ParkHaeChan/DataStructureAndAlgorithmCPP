/*
표편집
https://programmers.co.kr/learn/courses/30/lessons/81303

표의 범위(0행 ~ 마지막 행)를 벗어날 수 없습니다. 이때, 다음과 같은 명령어를 이용하여 표를 편집합니다.

"U X": 현재 선택된 행에서 X칸 위에 있는 행을 선택합니다.
"D X": 현재 선택된 행에서 X칸 아래에 있는 행을 선택합니다.
"C" : 현재 선택된 행을 삭제한 후, 바로 아래 행을 선택합니다. 단, 삭제된 행이 가장 마지막 행인 경우 바로 윗 행을 선택합니다.
"Z" : 가장 최근에 삭제된 행을 원래대로 복구합니다. 단, 현재 선택된 행은 바뀌지 않습니다.

?:
처음 표의 행 개수를 나타내는 정수 n, 처음에 선택된 행의 위치를 나타내는 정수 k, 
수행한 명령어들이 담긴 문자열 배열 cmd가 매개변수로 주어질 때, 
모든 명령어를 수행한 후 표의 상태와 처음 주어진 표의 상태를 비교하여 삭제되지 않은 행은 O, 
삭제된 행은 X로 표시하여 문자열 형태로 return 하도록 solution 함수를 완성해주세요.

!!!:
5 ≤ n ≤ 1,000,000
0 ≤ k < n
1 ≤ cmd의 원소 개수 ≤ 200,000
cmd의 각 원소는 "U X", "D X", "C", "Z" 중 하나입니다.
X는 1 이상 300,000 이하인 자연수이며 0으로 시작하지 않습니다.
X가 나타내는 자연수에 ',' 는 주어지지 않습니다. 예를 들어 123,456의 경우 123456으로 주어집니다.
cmd에 등장하는 모든 X들의 값을 합친 결과가 1,000,000 이하인 경우만 입력으로 주어집니다.
표의 모든 행을 제거하여, 행이 하나도 남지 않는 경우는 입력으로 주어지지 않습니다.
본문에서 각 행이 제거되고 복구되는 과정을 보다 자연스럽게 보이기 위해 "이름" 열을 사용하였으나, "이름"열의 내용이 실제 문제를 푸는 과정에 필요하지는 않습니다. 
"이름"열에는 서로 다른 이름들이 중복없이 채워져 있다고 가정하고 문제를 해결해 주세요.
표의 범위를 벗어나는 이동은 입력으로 주어지지 않습니다.
원래대로 복구할 행이 없을 때(즉, 삭제된 행이 없을 때) "Z"가 명령어로 주어지는 경우는 없습니다.
정답은 표의 0행부터 n - 1행까지에 해당되는 O, X를 순서대로 이어붙인 문자열 형태로 return 해주세요.
정확성 테스트 케이스 제한 사항
5 ≤ n ≤ 1,000
1 ≤ cmd의 원소 개수 ≤ 1,000

시도1)
n,k가 100만에 cmd가 20만이다.
입력크기를 감안했을 때 O(N)을 먼저 시도해보고,
조금씩 최적회해나가는 방법을 사용해야 될 것 같다.
우선 cmd를 수행할 때 실제로 삭제하거나 하는 방식은 사용하지 않을 것이다.
그리고 X칸을 이동하는 것도 현재 삭제된 칸을 안치고 이동하는 방법을 적용해야한다.

삭제/복구가 발생할 때마다 최대 크기 100만의 bool 배열을 참고하는 방식은 시간초과가 발생할 수 있을 것 같다.
100만 크기의 배열을 선언하는 자체로도 시간이 꽤 걸린다.

이럴 떄 매 삭제 위치를 set에 저장하면 이분탐색을 통해서 해당 위치로 이동할 떄까지 삭제된 번호들 개수를 빠르게 찾을 수 있다. 

시도 2)
실제 삭제 이루어 진 후에도 start--, ++ 이 아니라 삭제된 위치를 고려해서 이동해야 한다.
table 배열 안쓰려했는데 구현이 빡세서 일단 쓰고 해봤다.
실패 및 시간초과 발생
별다른 뾰족한 수가 떠오르지 않는다...
<시도 2 코드>
vector<bool> table(n, true);
int start = k;
int end = n-1;
int size = n;
int last_removed = -1;
set<int> removedSet;        // 
stack<int> removedStack;    // 최근 삭제 구하기
string numstr;
int X, idx, larger;
set<int>::iterator it;
// 명령 파싱
for(auto& e: cmd)
{
    switch(e[0])
    {
    case 'U':
        numstr = e.substr(2);
        X = stoi(numstr);
        // 이동시 현 위치보다 작은 번호로 삭제된 개수를 구해서 그만큼 더 이동
        it = removedSet.upper_bound(start);
        idx = distance(removedSet.begin(), it);
        if(removedSet.empty())
            idx=0;
        else
            idx++;  // idx+1 == start 보다 작으면서 삭제된 갯수
        start -= (X+idx);
        break;
    case 'D':
        numstr = e.substr(2);
        X = stoi(numstr);
        // 이동시 현 위치보다 큰 번호로 삭제된 개수 구해서 그만큼 더 이동
        it = removedSet.upper_bound(start);
        idx = distance(removedSet.begin(), it);
        if(removedSet.empty())
            idx=0;
        else
            idx = n-idx;  // n-idx == start 보다 크면서 삭제된 번호들 갯수
        start += (X+idx);
        break;
    case 'C':   // 삭제
        removedSet.insert(start);
        removedStack.push(start);
        // 끝이 삭제된 경우 위로 커서 이동
        // n-1 - (start 보다 큰 원소 개수) == start 이면 start 가 끝
        it = removedSet.upper_bound(start);
        idx = distance(removedSet.begin(), it);
        larger = n - idx;
        if(n-1 - larger == start)
        {   // 삭제되지 않은 start보다 작으면서 가장 큰 값으로 이동
            for(int i=start-1; i>=0; --i)
                if(table[i])
                {
                    start = i;
                    break;
                }
        }
        else
        {   // 그외는 삭제된 위치 아래로 커서 이동
            for(int i=start+1; i<n; ++i)
                if(table[i])
                {
                    start = i;
                    break;
                }
        }
        end--;
        size--;
        break;
    case 'Z':   // 복구
        // 최근 삭제된 번호
        int recent = removedStack.top(); removedStack.pop();
        removedSet.erase(recent);
        end++;
        size++;
        break;
    }
}
for(int i=0; i<n; ++i)
{
    if(!removedSet.empty())
    {
        int del = *(removedSet.begin());
        if(i == del)
        {
            answer += "X";
            removedSet.erase(del);
        }
        else
            answer += "O";
    }
    else
        answer += "O";
}

참고로 case문 안에서 변수 선언하면 에러 발생한다. (단 맨 마지막 case에만 선언하는 것은 OK)
그래서 if-else문으로 바꿈

시도 3)
<해설 참고>
이 문제의 핵심은 삭제와 복원이다. 이를 빠르게 수행하는 자료구조는 바로 "연결리스트" 이다.
연결리스트를 2중연결리스트로 구현하면 노드가 삭제될 때 삭제된 노드의 양 끝은 자신의 원래 위치를 기억할 수 있다.
이게 가능한 이유는 문제에서 복원할 때 가장 최근에 삭제된 순으로 복원하기 때문에 가능하다. (뒤죽박죽이면 이 방식 사용 불가능)

또 다른 방법으로는 set을 이용하는 방법이 있다고 한다. (이는 연결리스트 방식보다는 느리지만 충분히 통과할 수준은 되는 듯)

set에 모든 노드를 저장한 상태에서 삽입/삭제는 log시간에 해결되고, 이동은 iterator인 next, prev를 통해 X번째로 이동하면 된다.
우선 set방식이 간단하므로 먼저 시도해본다.

*/

#include <string>
#include <vector>
#include <set>
#include <stack>

using namespace std;

string solution(int n, int k, vector<string> cmd) {
    string answer(n, 'X');  // 모두 X로 초기화

    set<int> table;
    for(int i=0; i<n; ++i)
        table.insert(i);

    stack<int> removedStack;
    set<int>::iterator start = table.find(k);
    for(auto& e: cmd)
    {
        if(e[0] == 'U' || e[0] == 'D')
        {
            string numstr = e.substr(2);
            int X = stoi(numstr);
            if(e[0] == 'U')
                start = prev(start, X);
            else
                start = next(start, X);
        }
        else if(e[0] == 'C')   // 삭제
        {
            int todel = *start;
            removedStack.push(todel);
            if(todel == *table.rbegin())
            {   // rbegin(): 역순 이터레이터의 시작 == set의 맨 끝
                // 맨 마지막을 삭제한 경우는 이전 값 가리키도록
                start = prev(start);
            }
            else
                start = next(start);
            table.erase(todel);
        }
        else // if(e[0] == 'Z')   // 복구
        {
            int removed = removedStack.top(); removedStack.pop();
            table.insert(removed);
        }
    }
    for(auto& e: table)
    {
        answer[e] = 'O';
    }

    return answer;
}

int main()
{
    int n = 8;
    int k = 2;
    // vector<string> cmd = {"D 2","C","U 3","C","D 4","C","U 2","Z","Z"};
    vector<string> cmd = {"D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z", "U 1", "C"};
    solution(n, k, cmd);

    return 0;
}