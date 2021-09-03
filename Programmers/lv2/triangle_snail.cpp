/*
삼각 달팽이
https://programmers.co.kr/learn/courses/30/lessons/68645

?:
정수 n이 매개변수로 주어집니다.
n = 4 인 경우
         1
        2 9
       3 10 8
      4  5  6  7
다음 그림과 같이 밑변의 길이와 높이가 n인 삼각형에서 맨 위 꼭짓점부터 반시계 방향으로 달팽이 채우기를 진행한 후, 
첫 행부터 마지막 행까지 모두 순서대로 합친 새로운 배열을 return 하도록 solution 함수를 완성해주세요.

!!!:
n은 1 이상 1,000 이하입니다.

시도 1)
삼각형을 내려갈 때와 밑변을 처리할 때는 일반적인 방법으로 채워 나가면 된다.
삼각형을 다시 올라갈 때는 stack에 잠시 저장해 두었다가 최종적으로 수행이 끝나면,
각각의 층에 채워 넣는 방식으로 채울수 있다
각각은 n/2 만큼 수행된다
통과는 했는데 애매한 느낌...
start, fin가 cnt가 초과하는 상황에서는 추가가 안되게 잘 막은 듯
*/

#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(int n) {
    vector<int> answer;

    vector<vector<int>> triangle(n);
    vector<stack<int>> stackVect(n);
    int cnt = 1;
    int cntend = n*(n+1)/2;
    int start = 0; int fin = n;
    while(cnt <= cntend)
    {
        // 삼각형 내려가기
        for(int i=start; i<fin; ++i)
        {
            triangle[i].push_back(cnt++);
        }
        // 삼각형 밑변 채우기   (시작 1개는 내려가기에서 채워지므로 한칸 적게 적용)
        for(int i=start; i<fin-1; ++i)
        {
            triangle[fin-1].push_back(cnt++);
        }
        // 삼각형 올라가기
        for(int i=fin-2; i>=start+1; --i)
        {   // stack에 넣었다가 모든 반복문 종료후 반영
            stackVect[i].push(cnt++);
        }
        start += 2; fin -=1;
    }
    // stack 비우기
    for(int i=0; i<triangle.size(); ++i)
    {
        while(!stackVect[i].empty())
        {
            triangle[i].push_back(stackVect[i].top());
            stackVect[i].pop();
        }
    }
    // answer에 담기
    for(int i=0; i<triangle.size(); ++i)
    {
        for(int j=0; j<triangle[i].size(); ++j)
        {
            answer.push_back(triangle[i][j]);
        }
    }

    return answer;
}

int main()
{
    int n = 4;
    solution(n);

    return 0;
}