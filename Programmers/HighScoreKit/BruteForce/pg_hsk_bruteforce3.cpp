/*
카펫
https://programmers.co.kr/learn/courses/30/lessons/42842

?:
중앙에는 노란색으로 칠해져 있고 테두리 1줄은 갈색으로 칠해져 있는 격자 모양 카펫
Leo가 본 카펫에서 갈색 격자의 수 brown, 노란색 격자의 수 yellow가 매개변수로 주어질 때 
카펫의 가로, 세로 크기를 순서대로 배열에 담아 return 하도록 solution 함수를 작성해주세요.
!!!:
갈색 격자의 수 brown은 8 이상 5,000 이하인 자연수입니다.
노란색 격자의 수 yellow는 1 이상 2,000,000 이하인 자연수입니다.
카펫의 가로 길이는 세로 길이와 같거나, 세로 길이보다 깁니다.

yellow 수로 가능한 직사각형 모양(가로가 세로보다 긴 경우로 만든다)을 만들어서
그렇게 만든 yellow 박스의 모양을 토대로 가능한 brown의 개수를 계산할 수 있다.
이렇게 계산한 brown 개수가 brown과 일치하면 그때 구성되는 직사각형의 크기를 반환한다.

yellow로 가능한 직사각형 모양을 만들기 위해
가능한 모든 약수를 시도해본다.(절반만 구하면 나머지는 자동으로 구해짐을 이용하자)
그렇게 yellow 박스의 모양을 구하면
brown은 테두리 1줄만 이므로 yellow 박스의 (가로+세로)*2 + 4(모서리)로 brown의 개수를 바로 구할 수 있다
*/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;

    // yellow의 약수
    for(int i=1; i*i<=yellow; ++i)
    {
        if(yellow%i != 0)
            continue;

        int smaller = i;
        int larger = yellow/i;

        // 유추된 brown 개수와 일치하는지 확인
        int counted = (smaller+larger)*2 + 4;
        if(counted == brown)
        {   // 일치하면 가로가 더 크도록하여 반환한다.
            answer = {larger+2, smaller+2};
            break;
        }
        else
            continue;
    }

    return answer;
}

int main()
{
    int brown = 24;
    int yellow = 24;

    solution(brown, yellow);

    return 0;
}