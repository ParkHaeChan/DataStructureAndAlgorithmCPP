/*
내적
https://programmers.co.kr/learn/courses/30/lessons/70128

?:
길이가 같은 두 1차원 정수 배열 a, b가 매개변수로 주어집니다. a와 b의 내적을 return 하도록 solution 함수를 완성해주세요.
이때, a와 b의 내적은 a[0]*b[0] + a[1]*b[1] + ... + a[n-1]*b[n-1] 입니다. (n은 a, b의 길이)

!!!:
a, b의 길이는 1 이상 1,000 이하입니다.
a, b의 모든 수는 -1,000 이상 1,000 이하입니다.

내적 연산은 두 벡터 길이가 같아야한다. 입력은 이를 만족한다 가정하면
각 index끼리 곱하고 sum에 더해주면 끝난다. 길이가 1000이고 각각 -1000~1000까지 가능하므로
최대 1000*1000*1000 = 10억으로(최소는 반대로 -10억) int형으로 커버 가능하다.
*/
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> a, vector<int> b) {
    int answer = 0;

    for(int i=0; i<a.size(); ++i)
    {
        answer += a[i]*b[i];
    }

    return answer;
}