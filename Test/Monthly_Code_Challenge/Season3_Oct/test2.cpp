/*
문제에서 제시한 방법 대로 하면 시간 초과 발생할 것이다.
n이 최대 10의 7승이다.
즉, 시뮬레이션이 아닌 바로 계산할 수 있도록 구현해야된다.

left, right는 1차원 배열로 펼쳤을 떄 구간이므로,
이 구간을 바로 계산할 수 있으면 된다.
이는 각각을 n으로 나눈 몫과 나머지로 2차원 배열에서의 위치로 역추적 가능하다.
예를 들면 3*3 에서 5번째는 3*1 + 2로 2행(1행부터 시작했을 떄) 의 2번째 열에 있는 수로 구할 수 있다.

초기 배열상태는 r,c중 큰 값이 저장됨을 알 수 있다.
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;

    /* 없어도 됨...
    vector<vector<int>> Board(n+1, vector<int>(n+1, 0));
    for(int r=1; r<=n; ++r)
    {
        for(int c=1; c<=n; ++c)
        {
            Board[r][c] = max(r,c);
        }
    }*/

    for(long long i=left; i<=right; ++i)
    {
        int row = i/n;
        int col = i%n;
        answer.push_back(max(row+1, col+1));
    }

    return answer;
}

int main()
{
    int n = 3;
    long long left = 2;
    long long right = 5;
    solution(n, left, right);

    return 0;
}