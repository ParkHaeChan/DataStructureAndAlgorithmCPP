/*
완주하지 못한 선수
문제: https://programmers.co.kr/learn/courses/30/lessons/42576

마라톤에 참여한 선수들의 이름이 담긴 배열 participant와 완주한 선수들의 이름이 담긴 배열 completion이 주어질 때,
완주하지 못한 선수의 이름을 return 하도록 solution 함수를 작성해주세요.



제한 사항
마라톤 경기에 참여한 선수의 수는 1명 이상 100,000명 이하입니다.
completion의 길이는 participant의 길이보다 1 작습니다.
참가자의 이름은 1개 이상 20개 이하의 알파벳 소문자로 이루어져 있습니다.
참가자 중에는 동명이인이 있을 수 있습니다.

동명 이인이 있을 수 있으므로 map에 이름당 몇명이 존재하는지를 저장한다.
참가자 이름과 동명이인 명수를 저장하는 map을 만들어서 완주한 선수 이름에서 찾을 때 없는 이름을 반환한다.

*/

#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";

    map<string, int> part;

    // 모든 참가자에 대해 <이름,사람수>를 저장
    for(auto e: participant)
    {
        part[e]++;
    }
    // 완주자 만큼 사람수를 빼준다
    for(auto e: completion)
    {
        part[e]--;
    }
    // 남은 사람은 완주하지 못한 사람이다
    for(auto e: part)
    {
        if(e.second == 1)
            answer = e.first;
    }

    return answer;
}

int main()
{
    vector<string> participant = {"mislav", "stanko", "mislav", "ana"};
    vector<string> comletion = {"stanko", "ana", "mislav"};

    cout << solution(participant, comletion) << endl;

    return 0;
}