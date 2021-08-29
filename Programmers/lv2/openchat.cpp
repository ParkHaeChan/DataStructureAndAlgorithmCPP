/*
오픈채팅방
https://programmers.co.kr/learn/courses/30/lessons/42888

채팅방에 들어오고 나가거나, 닉네임을 변경한 기록이 담긴 문자열 배열 record가 매개변수로 주어질 때, 
모든 기록이 처리된 후, 최종적으로 방을 개설한 사람이 보게 되는 메시지를 문자열 배열 형태로 return 하도록 solution 함수를 완성하라.

!!!:
record는 다음과 같은 문자열이 담긴 배열이며, 길이는 1 이상 100,000 이하이다.
다음은 record에 담긴 문자열에 대한 설명이다.
모든 유저는 [유저 아이디]로 구분한다.
[유저 아이디] 사용자가 [닉네임]으로 채팅방에 입장 - "Enter [유저 아이디] [닉네임]" (ex. "Enter uid1234 Muzi")
[유저 아이디] 사용자가 채팅방에서 퇴장 - "Leave [유저 아이디]" (ex. "Leave uid1234")
[유저 아이디] 사용자가 닉네임을 [닉네임]으로 변경 - "Change [유저 아이디] [닉네임]" (ex. "Change uid1234 Muzi")

첫 단어는 Enter, Leave, Change 중 하나이다.
각 단어는 공백으로 구분되어 있으며, 알파벳 대문자, 소문자, 숫자로만 이루어져있다.
유저 아이디와 닉네임은 알파벳 대문자, 소문자를 구별한다.
유저 아이디와 닉네임의 길이는 1 이상 10 이하이다.
채팅방에서 나간 유저가 닉네임을 변경하는 등 잘못 된 입력은 주어지지 않는다.

걸린시간: 26분
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

vector<string> parse_str(string input)
{
    vector<string> ret;
    stringstream iss;
    string buff;
    iss << input;
    while(getline(iss, buff, ' '))  // 공백 문자 기준 파싱
    {
        ret.push_back(buff);
    }
    return ret;
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string, string> uid_nicknameMap;
    map<string, int> cmdMap;
    cmdMap = {{"Enter",1}, {"Leave", 2}, {"Change", 3}};    // cmd 구분용
    vector<pair<string, int>> saved;    // answer 출력 저장용: {uid와 Enter/Leave만 저장}

    // 1) 입력 종류 별로 처리
    // 입력 문자열 파싱
    for(auto str : record)
    {
        auto parsed = parse_str(str);
        string cmd = parsed[0];
        string uid = parsed[1];
        string nickname;    // Leave인 경우는 nickname이 없음
        if(cmd != "Leave")
            nickname = parsed[2];

        // enter leave는 각각 들어왔습니다, 나갔습니다 그대로 저장되었다가 출력되고
        // change의 경우는 출력할 닉네임이 바뀌는 것만 저장하였다가 최종적으로 출력전에 변환한다.
        // 이를 위해 최종 출력 전에는 uid로 출력하여 구분해 놓는다.
        switch (cmdMap[cmd])
        {
        case 1: // Enter
            // 이번에 처음들어온 경우는 닉네임 생성(이외는 change에서 변경)
            uid_nicknameMap[uid] = nickname;
            saved.push_back({uid, 1});
            break;
        case 2: // Leave
            saved.push_back({uid, 2});
            break;
        case 3: // Change
            uid_nicknameMap[uid] = nickname;
            break;
        }
    }
    // 최종 처리: uid --> nickname 변환
    for(auto e: saved)
    {
        switch (e.second)
        {
        case 1: // enter
            answer.push_back(uid_nicknameMap[e.first] + "님이 들어왔습니다.");
            break;
        case 2: // leave
            answer.push_back(uid_nicknameMap[e.first] + "님이 나갔습니다.");
            break;
        }
    }
    return answer;
}

int main()
{
    vector<string> record = {"Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan"};

    vector<string> answer = solution(record);

    return 0;
}