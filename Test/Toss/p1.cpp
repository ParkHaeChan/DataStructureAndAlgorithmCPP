/*
부가가치세계산기

?:
과세의 대상이 되는 과세금액에서 10%만큼 산정
소수점(이하) 첫째자리에서 올림 처리
공급가액에서 비과세 금액을 빼주시면 됩니다 (비과세 금액은 말 그대로 부가가치세가 부과되지 않는 금액)
봉사료가 존재하는 업종의 경우에는 주문금액에서 봉사료를 제한 금액이 공급대가가 됩니다.
공급대가에서 비과세금액을 뺀 남은 금액이 1원이면 0원으로 처리해 주세요.
주문금액(orderAmount) / 비과세금액(taxFreeAmount) / 봉사료(serviceFee)에 따른 부가가치세 금액(answer)을 반환합니다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

long long solution(long long orderAmount, long long taxFreeAmount, long long serviceFee) {
    // orderAmount : 주문금액
    // taxFreeAmount : 비과세금액
    // serviceFee : 봉사료        
    long long answer = 0;

    // 공급대가
    long long supplyprice = orderAmount-serviceFee;

    // 비과세 금액을 뺀다
    supplyprice -= taxFreeAmount;

    if(supplyprice == 1)
        return 0;
    
    // 주문 금액의 10%가 세금
    answer = lround(ceil(supplyprice / 10.0));

    return answer;
}

int main()
{
    long long orderAmount = 2;
    long long taxFree = 0;
    long long service = 0;
    cout << solution(orderAmount, taxFree, service) << endl;

    return 0;
}