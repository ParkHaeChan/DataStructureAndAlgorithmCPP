/*
불량 사용자
https://programmers.co.kr/learn/courses/30/lessons/64064

사용자 아이디 중 일부 문자를 '*' 문자로 가려서 전달했습니다. 가리고자 하는 문자 하나에 '*' 문자 하나를 사용하였고 아이디 당 최소 하나 이상의 '*' 문자를 사용
?:
이벤트 응모자 아이디 목록이 담긴 배열 user_id와 불량 사용자 아이디 목록이 담긴 배열 banned_id가 매개변수로 주어질 때, 
당첨에서 제외되어야 할 제재 아이디 목록은 몇가지 경우의 수가 가능한 지 return 하도록 solution 함수를 완성해주세요.

!!!:
user_id 배열의 크기는 1 이상 8 이하입니다.
user_id 배열 각 원소들의 값은 길이가 1 이상 8 이하인 문자열입니다.
응모한 사용자 아이디들은 서로 중복되지 않습니다.
응모한 사용자 아이디는 알파벳 소문자와 숫자로만으로 구성되어 있습니다.
banned_id 배열의 크기는 1 이상 user_id 배열의 크기 이하입니다.
banned_id 배열 각 원소들의 값은 길이가 1 이상 8 이하인 문자열입니다.
불량 사용자 아이디는 알파벳 소문자와 숫자, 가리기 위한 문자 '*' 로만 이루어져 있습니다.
불량 사용자 아이디는 '*' 문자를 하나 이상 포함하고 있습니다.
불량 사용자 아이디 하나는 응모자 아이디 중 하나에 해당하고 같은 응모자 아이디가 중복해서 제재 아이디 목록에 들어가는 경우는 없습니다.
제재 아이디 목록들을 구했을 때 아이디들이 나열된 순서와 관계없이 아이디 목록의 내용이 동일하다면 같은 것으로 처리하여 하나로 세면 됩니다.

시도1)
제재 아이디가 중복되지 않고, 순서와 상관없다는 점(조합)을 주의한다
제재 아이디가 여러 경우에 사용될 수 있지만,
이때, 여러 경우의 제재 아이디에 해당하는 아이디가 중복으로 들어가지 않게 구성하여야 하고,
제재 아이디가 모두 사용되어야 한다.
제재 아이디로 검사하는 부분은 반복문으로 간단하게 구현한다. (8자리 문자열임)
순서와 상관 없는 부분은, 구성한 조합을 정렬하여 set에 넣어주면된다.
테스트 5에서 시간초과 발생

시도2)
재귀에서 인자를 vector<string>으로 두어서 모든 경우를 시도하도록 했는데
여기를 set으로 두면, 이후에 같은 입력은 중복으로 안들어가지만,
재귀 돌고 나와서 erase로 지우는 문제가 있어서 vector를 썼었다.
이 경우를 따로 처리하도록 변경하여 set을 사용하도록 구현
아직 시간초과 발생

시도3)

*/

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

set<set<string>> answerSet;
multimap<string, string> idMap;
vector<string> banVect;

void recur(int depth, set<string>& strSet)
{
    if(depth == banVect.size())
    {
        if(strSet.size() == banVect.size())
        {
            answerSet.insert(strSet);
        }
        return;
    }
    auto it_pair = idMap.equal_range(banVect[depth]);
    vector<string> candidateVect;
    for(auto it=it_pair.first; it != it_pair.second; ++it)
    {
        candidateVect.push_back(it->second);
    }
    for(int i=0; i<candidateVect.size(); ++i)
    {
        // 시도2: set에 중복있으면 넘기도록 구현
        if(strSet.find(candidateVect[i]) != strSet.end())
            continue;
        strSet.insert(candidateVect[i]);
        recur(depth+1, strSet);
        strSet.erase(candidateVect[i]);
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    banVect = banned_id;
    for(string& banned: banned_id)
    {
        for(string& user: user_id)
        {
            if(banned.size() == user.size())
            {   // 변환 가능한지 확인
                bool able = true;
                for(int i=0; i<banned.size(); ++i)
                {
                    if((banned[i] == '*') || (banned[i] == user[i]))
                        continue;
                    else
                        able = false;
                }
                if(able)
                {
                    idMap.insert({banned, user});
                }
            }
            else
                continue;
        }
    }
    set<string> temp;   // 시도2
    recur(0, temp);
    answer = answerSet.size();

    return answer;
}

int main()
{
    vector<string> user_id = {"frodo", "fradi", "crodo", "abc123", "frodoc"};
    vector<string> banned_id = {"fr*d*", "*rodo", "******", "******"};

    solution(user_id, banned_id);

    return 0;
}