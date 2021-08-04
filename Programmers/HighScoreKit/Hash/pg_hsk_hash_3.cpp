/*
위장
https://programmers.co.kr/learn/courses/30/lessons/42578

<문제가 요구하는 사항은 ?:로 쓴다>
?: 스파이가 가진 의상들이 담긴 2차원 배열 clothes가 주어질 때 서로 다른 옷의 조합의 수를 return 하도록 solution 함수를 작성해주세요.
!!!:
clothes의 각 행은 [의상의 이름, 의상의 종류]로 이루어져 있습니다.
스파이가 가진 의상의 수는 1개 이상 30개 이하입니다.
같은 이름을 가진 의상은 존재하지 않습니다.
clothes의 모든 원소는 문자열로 이루어져 있습니다.
모든 문자열의 길이는 1 이상 20 이하인 자연수이고 알파벳 소문자 또는 '_' 로만 이루어져 있습니다.
스파이는 하루에 최소 한 개의 의상은 입습니다.

<의상 종류, 의상명> 의 map형태로 옷의 종류와 가지수를 저장할 수 있다.
하지만 여기서는 의상의 종류가 몇가지 존재하는가만 알면 답을 구할 수 있으므로
<의상 종류, 갯수> 로 저장해도 된다.

각 의상 종류의 개수를 알면 이 조합으로 나올 수 있는 경우의 수를 계산하면 된다.
각 경우를 모두 구하려면 재귀를 이용해야 하지만,
가지수만 구하는 것이라면 한번의 계산으로 끝낼 수 있다.
옷이 종류별로 a,b,c,d,e 개가 있다면
가능한 모든 가지수는 (a+1)*(b+1)*(c+1)*(d+1)*(e+1)-1로 구할 수 있다. (끝에 -1은 아무것도 안입는 경우이다)
각각에 안입는 경우 한가지를 추가한 뒤 모든 경우를 구하기 위해 곱연산으로 이은 것이라 보면된다.
*/


#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 0;

    map<string, int> clotheskind;

    for(auto e: clothes)
    {
        string clothname = e[0];
        string kind = e[1];

        clotheskind[kind]++;
    }

    int sum = 1;
    for(auto e: clotheskind)
    {
        sum *= (e.second+1);
    }
    answer = sum-1;

    return answer;
}

int main()
{
    vector<vector<string>> clothes = {{"yellowhat", "headgear"}, {"bluesunglasses", "eyewear"}, {"green_turban", "headgear"}};

    cout << solution(clothes) << endl;

    return 0;
}