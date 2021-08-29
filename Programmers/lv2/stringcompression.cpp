/*
문자열 압축
https://programmers.co.kr/learn/courses/30/lessons/60057

예를 들어, "ababcdcdababcdcd"의 경우 문자를 1개 단위로 자르면 전혀 압축되지 않지만, 
2개 단위로 잘라서 압축한다면 "2ab2cd2ab2cd"로 표현할 수 있습니다. 
다른 방법으로 8개 단위로 잘라서 압축한다면 "2ababcdcd"로 표현할 수 있으며, 
이때가 가장 짧게 압축하여 표현할 수 있는 방법입니다.

?:
압축할 문자열 s가 매개변수로 주어질 때, 
위에 설명한 방법으로 1개 이상 단위로 문자열을 잘라 압축하여 표현한 문자열 중 
가장 짧은 것의 길이를 return 하도록 solution 함수를 완성해주세요.

!!!:
s의 길이는 1 이상 1,000 이하입니다.
s는 알파벳 소문자로만 이루어져 있습니다.
!!!!:
입력: "xababcdcdababcdcd"
문자열은 제일 앞부터 정해진 길이만큼 잘라야 합니다.
따라서 주어진 문자열을 x / ababcdcd / ababcdcd 로 자르는 것은 불가능 합니다.
이 경우 어떻게 문자열을 잘라도 압축되지 않으므로 가장 짧은 길이는 17이 됩니다.

시도1) 테스트 케이스 1개 통과 못함. input:"a" 인 경우 1출력해야되는데 INF값이 나옴;;
시도2) 통과
*/

#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int solution(string s) {
    int answer = 0;
    const int N = s.size();
    const int INF = INT_MAX;
    answer = INF;

    if(s.size() == 1)
        return 1;

    // 1 ~ N/2까지 압축을 시도한다
    // N/2이상으로 시도하는 것은 의미 없다: 남은 더 작은 쪽과 합쳐지는 경우가 없음
    for(int i=1; i<=N/2; ++i)
    {   // 앞에서 부터 자른다
        int stridx = 0;
        int samecnt = 1;    // 1은 생략됨
        string compressed = "";
        string last = s.substr(stridx, i);
        stridx += i;
        while(stridx < N)
        {
            if(stridx + i > N)
            {
                string sub = s.substr(stridx, N-stridx);
                // last와 같을 수 없을 것임
                compressed += sub;
                break;
            }
            else
            {
                string sub = s.substr(stridx, i);
                if(last == sub)
                    samecnt++;
                else
                {
                    if(samecnt != 1)
                        compressed += to_string(samecnt);
                    compressed += last;
                    samecnt = 1;
                    last = sub;
                }
            }
            stridx += i;
        }
        if(samecnt != 1)
            compressed += to_string(samecnt);
        compressed += last;
        answer = min(answer, (int)compressed.size());
    }

    return answer;
}

int main()
{
    string s = "a";

    solution(s);

    return 0;
}