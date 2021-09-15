/*
하노이의 탑
https://programmers.co.kr/learn/courses/30/lessons/12946

한 번에 하나의 원판만 옮길 수 있습니다.
큰 원판이 작은 원판 위에 있어서는 안됩니다.
하노이 탑의 세 개의 기둥을 왼쪽 부터 1번, 2번, 3번이라고 하겠습니다. 1번에는 n개의 원판이 있고 이 n개의 원판을 3번 원판으로 최소 횟수로 옮기려고 합니다.

1번 기둥에 있는 원판의 개수 n이 매개변수로 주어질 때, n개의 원판을 3번 원판으로 최소로 옮기는 방법을 return하는 solution를 완성해주세요.

제한사항
n은 15이하의 자연수 입니다.

시도1)
몇 번 봉에서 몇 번 봉으로 이동하는지를 일일이 벡터에 담는다.
재귀로 구현하는 하노이 탑에서 경로만 저장한다
*/

#include <string>
#include <vector>

using namespace std;

// 기본 재귀 방식 하노이: n개의 원판을 A에서 B를 거쳐 C로 옮긴다.
void hanoi(int A, int B, int C, int n, vector<vector<int>>& answer)
{
    if(n == 0)
    {   // 재귀 끝 (옮길 접시가 없다)
        return;
    }
    // n-1개를 A에서 C를 거쳐 B로 옮긴다
    hanoi(A, C, B, n-1, answer);
    // 맨 밑에 A를 C로 옮긴다
    answer.push_back({A, C});
    // n-1개를 B에서 A를 거쳐 C로 옮긴다
    hanoi(B, A, C, n-1, answer);
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;

    hanoi(1, 2, 3, n, answer);

    return answer;
}

int main()
{
    int n = 1;

    solution(n);

    return 0;
}