/*
단체사진 찍기
https://programmers.co.kr/learn/courses/30/lessons/1835

각 프렌즈가 원하는 조건을 입력으로 받았을 때 모든 조건을 만족할 수 있도록 서는 경우의 수를 계산하는 프로그램을 작성해보자.
입력은 조건의 개수를 나타내는 정수 n과 n개의 원소로 구성된 문자열 배열 data로 주어진다. 
data의 원소는 각 프렌즈가 원하는 조건이 N~F=0과 같은 형태의 문자열로 구성되어 있다. 제한조건은 아래와 같다.
1 <= n <= 100
data의 원소는 다섯 글자로 구성된 문자열이다. 각 원소의 조건은 다음과 같다.
첫 번째 글자와 세 번째 글자는 다음 8개 중 하나이다. {A, C, F, J, M, N, R, T} 
각각 어피치, 콘, 프로도, 제이지, 무지, 네오, 라이언, 튜브를 의미한다. 
첫 번째 글자는 조건을 제시한 프렌즈, 세 번째 글자는 상대방이다. 첫 번째 글자와 세 번째 글자는 항상 다르다.
두 번째 글자는 항상 ~이다.
네 번째 글자는 다음 3개 중 하나이다. {=, <, >} 각각 같음, 미만, 초과를 의미한다.
다섯 번째 글자는 0 이상 6 이하의 정수의 문자형이며, 조건에 제시되는 간격을 의미한다. 
이때 간격은 두 프렌즈 사이에 있는 다른 프렌즈의 수이다.

시도 1)
8명을 주어진 조건에 만족하도록 나열하는 경우의 수를 구하는 문제이다.
수가 적으므로 완전탐색 문제임을 알 수 있다.
조건을 코드로 구현하면 되는데 마냥 쉬운건 아닌 듯.
각각의 경우를 직접 처리해 본다고 가정하니 고려할게 너무 많은 것 같다.
그래서 모든 경우를 다 세고, 조건을 만족하는지 검사후 만족하는 것만 세도록 작성해본다.
next_permutation을 쓰면 간편하다.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    int answer = 0;

    string NAMES = "ACFJMNRT";  // 8개
    do
    {
        bool able = true;
        for(auto& e: data)
        {
            char f1 = e[0];
            char f2 = e[2];
            char op = e[3];
            int distance = e[4] - '0';

            // 떨어진 정도
            int i1 = NAMES.find(f1);
            int i2 = NAMES.find(f2);
            int dist = abs(i2-i1)-1;    // 인접한 경우(0)도 abs계산하면 1나오므로

            switch(op)
            {
                case '=':
                    if(dist == distance)
                        continue;
                    else
                        able = false;
                    break;
                case '<':
                    if(dist < distance)
                        continue;
                    else
                        able = false;
                    break;
                case '>':
                    if(dist > distance)
                        continue;
                    else
                        able = false;
                    break;
            }
            if(!able)
                break;
        }
        if(able)
            answer++;
    }while(next_permutation(NAMES.begin(), NAMES.end()));

    return answer;
}

int main()
{
    int n = 2;
    vector<string> data = {"N~F=0", "R~T>2"};
    solution(n, data);

    return 0;
}