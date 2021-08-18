/*
로또의 최고 순위와 최저 순위
https://programmers.co.kr/learn/courses/30/lessons/77484

?:
민우가 구매한 로또 번호를 담은 배열 lottos, 당첨 번호를 담은 배열 win_nums가 매개변수로 주어집니다
이때, 당첨 가능한 최고 순위와 최저 순위를 차례대로 배열에 담아서 return 하도록 solution 함수를 완성해주세요.
!!!:
lottos는 길이 6인 정수 배열입니다.
lottos의 모든 원소는 0 이상 45 이하인 정수입니다.
0은 알아볼 수 없는 숫자를 의미합니다.
0을 제외한 다른 숫자들은 lottos에 2개 이상 담겨있지 않습니다.
lottos의 원소들은 정렬되어 있지 않을 수도 있습니다.
win_nums은 길이 6인 정수 배열입니다.
win_nums의 모든 원소는 1 이상 45 이하인 정수입니다.
win_nums에는 같은 숫자가 2개 이상 담겨있지 않습니다.
win_nums의 원소들은 정렬되어 있지 않을 수도 있습니다.

시도1)
lottos와 win_nums가 일치하는 수를 센다.
lottos에서 0의 수를 센다.
0이 모두 일치할 경우 등수와 일치하지 않을 경우 등수를 구한다.
*/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;

    // 0 개수 세기
    int zcnt = 0;
    for(auto e: lottos)
        if( e == 0)
            zcnt++;

    // 일치하는 숫자 수 세기
    int ccnt = 0;
    for(auto win: win_nums)
    {
        for(auto lot: lottos)
        {
            if(win == lot)
                ccnt++;
        }
    }

    // 등수 최대, 최소
    vector<int> ranking = {6,6,5,4,3,2,1};  // index : 일치하는 숫자 갯수
    answer = {ranking[zcnt+ccnt], ranking[ccnt]};

    return answer;
}