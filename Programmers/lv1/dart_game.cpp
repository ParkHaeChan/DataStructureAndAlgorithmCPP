/*
다트 게임
https://programmers.co.kr/learn/courses/30/lessons/17682

다트 게임은 총 3번의 기회로 구성된다.
각 기회마다 얻을 수 있는 점수는 0점에서 10점까지이다.
점수와 함께 Single(S), Double(D), Triple(T) 영역이 존재하고 각 영역 당첨 시 점수에서 1제곱, 2제곱, 3제곱 (점수1 , 점수2 , 점수3 )으로 계산된다.
옵션으로 스타상(*) , 아차상(#)이 존재하며 

<<<스타상(*) 당첨 시 해당 점수와 바로 전에 얻은 점수를 각 2배로 만든다. 아차상(#) 당첨 시 해당 점수는 마이너스된다.>>>

스타상(*)은 첫 번째 기회에서도 나올 수 있다. 이 경우 첫 번째 스타상(*)의 점수만 2배가 된다. (예제 4번 참고)
스타상(*)의 효과는 다른 스타상(*)의 효과와 중첩될 수 있다. 이 경우 중첩된 스타상(*) 점수는 4배가 된다. (예제 4번 참고)
스타상(*)의 효과는 아차상(#)의 효과와 중첩될 수 있다. 이 경우 중첩된 아차상(#)의 점수는 -2배가 된다. (예제 5번 참고)
Single(S), Double(D), Triple(T)은 점수마다 하나씩 존재한다.
스타상(*), 아차상(#)은 점수마다 둘 중 하나만 존재할 수 있으며, 존재하지 않을 수도 있다.

0~10의 정수와 문자 S, D, T, *, #로 구성된 문자열이 입력될 시 총점수를 반환하는 함수를 작성하라.

입력:
"점수|보너스|[옵션]"으로 이루어진 문자열 3세트.
예) 1S2D*3T
점수는 0에서 10 사이의 정수이다.
보너스는 S, D, T 중 하나이다.
옵선은 *이나 # 중 하나이며, 없을 수도 있다.

출력 형식
3번의 기회에서 얻은 점수 합계에 해당하는 정수값을 출력한다.

시도1) 인덱스 범위에 주의할 것
시도2) 0~10까지 점수가 있기 때문에 10인 case를 처리할 수 있어야 한다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct dart
{
    int score;
    char bonus;
    char option;
};

int solution(string dartResult) {
    int answer = 0;
    
    // 3회로 던지므로 각 회별로 파싱한다
    vector<dart> darts;
    for(int readoffset = 0; readoffset < dartResult.size(); )
    {
        // parse input: 기본으로 2개 값을 읽되 다음이 *,#이면 다음까지 읽는다
        // 10인 경우도 처리가능해야 한다 : 10인 경우만 따로 처리하면 쉽지만 숫자를 따로 파싱하도록 구현해본다.
        string numcheck = dartResult.substr(readoffset, 2);
        int score = stoi(numcheck); // 숫자 아닌 부분은 버림
        if(score / 10 > 0)
            readoffset += 2;
        else
            readoffset++;
        char bonus = dartResult[readoffset++];
        char option = 'X';
        if(readoffset < dartResult.size() && dartResult[readoffset] == '*' || dartResult[readoffset] == '#')    // 시도 1)
            option = dartResult[readoffset++];
        darts.push_back({score, bonus, option});
    }

    // 점수를 계산한다 (옵션은 뒤의 점수에 영향을 줄 수 있으므로 계산된 값을 다시 저장해 둔다)
    for(int i=0; i<darts.size(); ++i)
    {
        int calculated;
        auto& e = darts[i]; // 참조로 받던가 아니면 아래서 darts[i].score에 직접 접근하든가
        switch (e.bonus)
        {
        case 'S':
            calculated = e.score;
            break;
        case 'D':
            calculated = lround(pow(e.score, 2));
            break;
        case 'T':
            calculated = lround(pow(e.score, 3));
            break;
        }
        switch (e.option)
        {
        case '*':   // 해당 점수와 바로 전에 얻은 점수를 각 2배로
            calculated *= 2;
            if((i-1)>=0)        // 방어적으로 짜야된다 (범위 주의) 시도1)
                darts[i-1].score *= 2;
            break;
        case '#':   // 해당 점수는 마이너스된다
            calculated *= -1;
            break;
        }
        e.score = calculated;
    }
    for(auto e: darts)
        answer += e.score;

    return answer;
}

int main()
{
    string dartResult = "1D2S#10S";

    cout << solution(dartResult) << endl;

    return 0;
}