/*
숫자 문자열과 영단어
https://programmers.co.kr/learn/courses/30/lessons/81301

?:
"one4seveneight"    :	1478
"23four5six7"   :	234567
"2three45sixseven"  :	234567
"123"   :	123

해법:
숫자면 그대로 두고 문자일 경우 어떤 숫자로 바뀔수 있는지 알아야한다.
앞에서 부터 가능한 문자열 가지수를 적용하여 치환가능한 문자열이 되면 치환한다.
map으로 치환할 문자를 미리 구해둔다.
set으로 치환할 문자열 길이를 미리 구해둔다.
substr으로 치환 및 재구축한다.
*/

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int solution(string s) {
    int answer = 0;
    string ans = "";

    map<string, int> engnumMap = {{"zero", 0},{"one",1},{"two",2},{"three", 3},{"four", 4},{"five", 5},{"six", 6},{"seven", 7},{"eight", 8}, {"nine", 9}};
    set<int> strlengthSet;
    for(auto m : engnumMap)
    {   // 문자열 숫자의 길이 저장
        strlengthSet.insert(m.first.size());
    }
    for(int i=0; i<s.size(); ++i)
    {
        if(isdigit(s[i]))
            ans.append(1, s[i]);
        else
        {   // eng --> num 치환
            for(int size : strlengthSet)
            {   // 모든 가능한 문자열 길이로 치환 시도
                string key = s.substr(i, size);
                int N = s.size();
                if(engnumMap.find(key) != engnumMap.end())
                {
                    ans += to_string(engnumMap[key]);
                    s = s.substr(i+size, N-(i+size));
                    i=-1;
                    break;
                }
            }
        }
    }

    return answer = stoi(ans);
}

int main()
{
    string s = "one4seveneight";
    solution(s);
    return 0;
}