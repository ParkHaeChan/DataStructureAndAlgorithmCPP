/*
스킬트리
https://programmers.co.kr/learn/courses/30/lessons/49993

선행 스킬이란 어떤 스킬을 배우기 전에 먼저 배워야 하는 스킬을 뜻합니다.
예를 들어 선행 스킬 순서가 스파크 → 라이트닝 볼트 → 썬더일때, 썬더를 배우려면 먼저 라이트닝 볼트를 배워야 하고, 라이트닝 볼트를 배우려면 먼저 스파크를 배워야 합니다.
위 순서에 없는 다른 스킬(힐링 등)은 순서에 상관없이 배울 수 있습니다. 따라서 스파크 → 힐링 → 라이트닝 볼트 → 썬더와 같은 스킬트리는 가능하지만, 
썬더 → 스파크나 라이트닝 볼트 → 스파크 → 힐링 → 썬더와 같은 스킬트리는 불가능합니다.
선행 스킬 순서 skill과 유저들이 만든 스킬트리1를 담은 배열 skill_trees가 매개변수로 주어질 때, 
가능한 스킬트리 개수를 return 하는 solution 함수를 작성해주세요.

!!!:
스킬은 알파벳 대문자로 표기하며, 모든 문자열은 알파벳 대문자로만 이루어져 있습니다.
스킬 순서와 스킬트리는 문자열로 표기합니다.
예를 들어, C → B → D 라면 "CBD"로 표기합니다
선행 스킬 순서 skill의 길이는 1 이상 26 이하이며, 스킬은 중복해 주어지지 않습니다.
skill_trees는 길이 1 이상 20 이하인 배열입니다.
skill_trees의 원소는 스킬을 나타내는 문자열입니다.
skill_trees의 원소는 길이가 2 이상 26 이하인 문자열이며, 스킬이 중복해 주어지지 않습니다.

시도 1)
스킬 순서가 나오니 위상정렬로 풀어야 될 것 같은 느낌이 들지만
문제가 비교적 간단한 듯 하여 다른 방법을 시도해 본다.

일단 가능한 스킬은 대문자 알파벳이 전부이므로 A~Z 26가지이다.
먼저 입력 문자열 skill에 대해 이전에 배워야 하는 스킬이 있으면 parent 벡터로 만들어서 관리하도록한다.
CBD인 경우 D의 부모로 B, B의 부모로 C, C의 부모로는 자기 자신이 되도록 구성하면 된다. (이외 다른 알파벳은 자기 자신이 부모)
그리고 visited 벡터나 set으로 부모가 이전에 나온적 있는지를 확인한다.

*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;

    vector<char> parents(26);
    // 초기 상태: 자기 자신이 부모
    for(int i=0; i<parents.size(); ++i)
    {
        parents[i]='A'+i;
    }
    // skill에서 부모를 지정
    reverse(skill.begin(), skill.end());   // 거꾸로 접근
    for(int i=0; i<skill.size()-1; ++i)
        parents[skill[i]-'A'] = skill[i+1];

    for(auto str: skill_trees)
    {
        vector<bool> visited(26, false);
        bool able = true;
        for(char c: str)
        {   // 현재 스킬의 부모가 자기 자신이면
            if(parents[c-'A'] == c)
            {
                visited[c-'A'] = true;
                continue;   // 가능
            }
            else
            {   // 부모가 이전에 나온적 있는지
                if(visited[parents[c-'A']-'A'])
                {
                    visited[c-'A'] = true;
                    continue;   // 가능
                }
                else
                {
                    able = false;
                    break;
                }
            }
        }
        if(able)
            answer++;
    }

    return answer;
}

int main()
{
    string skill = "CBD";
    vector<string> skill_trees = {"BACDE", "CBADF", "AECB", "BDA"};

    solution(skill, skill_trees);

    return 0;
}