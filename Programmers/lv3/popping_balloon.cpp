/*
풍선 터트리기
https://programmers.co.kr/learn/courses/30/lessons/68646

임의의 인접한 두 풍선을 고른 뒤, 두 풍선 중 하나를 터트립니다.
터진 풍선으로 인해 풍선들 사이에 빈 공간이 생겼다면, 빈 공간이 없도록 풍선들을 중앙으로 밀착시킵니다.
접한 두 풍선 중에서 번호가 더 작은 풍선을 터트리는 행위는 최대 1번만 할 수 있습니다

?:
일렬로 나열된 풍선들의 번호가 담긴 배열 a가 주어집니다. 
위에 서술된 규칙대로 풍선들을 1개만 남을 때까지 터트렸을 때 
최후까지 남기는 것이 가능한 풍선들의 개수를 return 하도록 solution 함수를 완성해주세요.

!!!:
a의 길이는 1 이상 1,000,000 이하입니다.
a[i]는 i+1 번째 풍선에 써진 숫자를 의미합니다.
a의 모든 수는 -1,000,000,000 이상 1,000,000,000 이하인 정수입니다.
a의 모든 수는 서로 다릅니다.

시도 1)
사실 O(N) 풀이 방법이 떠오르지 않아서 정답을 참고했다.
입력이 100만이다 보니 그리디 방식을 사용하여야 한다는 감은 있었는데 어떻게 풀어나가야 할지는 막막했다.

풀이 방식은 이렇다.

남기고 싶은 수(b)를 정하고, 그 수의 앞에 나왔던 수 중 가장 작은 수(a)와
그 수 이후로 나온 수들 중 가장 작은 수(c) 는 최후의 3개의 수(a, b, c)로 남을 수 있다.

이때, b가 남지 못하는 경우는 abc중 b가 가장 클 경우이고, 이외에는 최후까지 남기는 방법이 존재한다.

(시간초과 발생): 매 반복마다 두 구간의 최소값을 구하므로 N^2 시간이 걸려 시간초과가 발생함
동적계획법 방식으로 최소값을 빠르게 구하도록 조치가 필요할 듯

시도2)
각 위치이전의 최소값을 저장하는 배열을 사용하도록 변경


*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> a) {
    int answer = 2;     // 시작과 끝은 끝까지 남을 수 있다
    const int INF = INT32_MAX;
    int N = a.size();
    if(N < 3)
        return N;

    // 시도 2
    vector<int> MinArray(N);
    vector<int> InverseMinArray(N);
    MinArray[0] = a[0];
    InverseMinArray[N-1] = a[N-1];
    for(int i=1; i<MinArray.size(); ++i)
    {
        MinArray[i] = min(MinArray[i-1], a[i]);
        InverseMinArray[N-1-i] = min(InverseMinArray[N-i], a[N-1-i]);
    }

    for(int i=1; i<N-1; ++i)
    {   // i번째가 남을수 있는지 확인
        /* 시도 1
        int leftMin = INF;
        for(int l=0; l<i; ++l)
            leftMin = min(leftMin, a[l]);
        int rightMin = INF;
        for(int r=i+1; r<N; ++r)
            rightMin = min(rightMin, a[r]);
        */
       int leftMin = MinArray[i-1];
        int rightMin = InverseMinArray[i+1];

        int biggest = max(leftMin, rightMin);
        biggest = max(biggest, a[i]);
        if(biggest == a[i])
            continue;
        else
            answer++;
    }

    return answer;
}

int main()
{
    vector<int> a = {-16,27,65,-2,58,-92,-71,-68,-61,-33};
    solution(a);
    return 0;
}