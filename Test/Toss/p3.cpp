/*
가짜 영수증 찾기
누군가가 가짜 영수증을 제출하고 있습니다. 김토스는 재무팀을 돕기 위해 가짜 영수증을 찾아내는 시스템을 만들고 싶습니다.

가짜 영수증을 찾아내는 방법은 간단합니다. 가짜 영수증에는 금액이 옳지 않게 적혀있습니다. 옳은 금액은 다음의 조건을 모두 만족합니다.

옳은 금액은 0~9 사이의 숫자 또는 구분자(,)로만 구성되어야 한다.
예를 들면 1만원이나 10,000원, +300은 0~9 사이의 숫자 또는 구분자(,)가 아닌 문자가 포함되어 있으므로 옳지 않은 금액이다.

금액이 0원인 경우를 제외하고는 가장 왼쪽 숫자가 0일 수 없다. 예를 들면, 0은 옳은 금액이지만, 0100은 옳지 않다.

금액은 세자리 구분자(,)를 포함하고 있거나, 또는 전혀 포함하고 있지 않다. 예를 들면, 구분자를 전혀 포함하지 않은 금액 39900도 옳은 금액이다.
세자리 구분자는 가장 오른쪽 숫자로부터 시작해 왼쪽 방향으로 매 3개의 숫자마다 1개의 구분자(,)가 등장하는 형태이다. 예를 들면, 25,000,123은 옳은 금액이고, 24,999,99는 옳지 않은 금액이다.

가장 왼쪽 끝이나 오른쪽 끝에는 구분자를 두지 않는다. 예를 들면, 10,000,과 ,999,000은 모두 옳지 않다.

영수증에 적혀있는 금액을 보고 가짜 영수증인지 진짜 영수증인지 판단하는 시스템을 만들어주세요.
*/
#include <iostream>

#include <string>
#include <vector>

using namespace std;

bool solution(string amountText) {
    bool answer = true;

    bool commaExists = false;
    int N = amountText.size();

    // 0~9와 ,로만 구성되어 있는지 확인
    for(int i=0; i<N; ++i)
    {
        if(isdigit(amountText[i]))
            continue;
        else
        {
            if(amountText[i] == ',')
            {
                commaExists = true;
                continue;
            }
            else
                return false;
        }
    }

    // 가장 왼쪽이 숫자이고, 1~9인가
    if(isdigit(amountText[0]))
    {
        if(amountText[0] == '0')
        {   // 원래 0인 경우
            if(N == 1)
                return true;
            else
                return false;
        }
    }
    else
        return false;

    // ,가 제대로 찍혀 있는가
    if(commaExists)   // ,가 있는 경우
    {
        int pos = N-1;
        int last = N;
        for(int i=N-1; i>=0; --i)
        {
            if(amountText[i] == ',')
            {
                pos = i;
                if(last-pos != 4)
                    return false;
                last = pos;
            }
        }
        if(pos > 4)
            return false;
    }

    return answer;
}

int main()
{
    string m = ",999,000";

   cout << solution(m);

    return 0;
}