/*
메뉴 리뉴얼
https://programmers.co.kr/learn/courses/30/lessons/72411

레스토랑을 운영하던 스카피는 코로나19로 인한 불경기를 극복하고자 메뉴를 새로 구성하려고 고민하고 있습니다.
기존에는 단품으로만 제공하던 메뉴를 조합해서 코스요리 형태로 재구성해서 새로운 메뉴를 제공하기로 결정했습니다. 
어떤 단품메뉴들을 조합해서 코스요리 메뉴로 구성하면 좋을 지 고민하던 "스카피"는 
이전에 각 손님들이 주문할 때 가장 많이 함께 주문한 단품메뉴들을 코스요리 메뉴로 구성하기로 했습니다.
단, 코스요리 메뉴는 최소 2가지 이상의 단품메뉴로 구성하려고 합니다. 
또한, 최소 2명 이상의 손님으로부터 주문된 단품메뉴 조합에 대해서만 코스요리 메뉴 후보에 포함하기로 했습니다.

예를 들어, 손님 6명이 주문한 단품메뉴들의 조합이 다음과 같다면,
(각 손님은 단품메뉴를 2개 이상 주문해야 하며, 각 단품메뉴는 A ~ Z의 알파벳 대문자로 표기합니다.)

손님 번호	주문한 단품메뉴 조합
1번 손님	A, B, C, F, G
2번 손님	A, C
3번 손님	C, D, E
4번 손님	A, C, D, E
5번 손님	B, C, F, G
6번 손님	A, C, D, E, H

가장 많이 함께 주문된 단품메뉴 조합에 따라 "스카피"가 만들게 될 코스요리 메뉴 구성 후보는 다음과 같습니다.

코스 종류	    메뉴 구성	설명
요리 2개 코스	A, C	    1번, 2번, 4번, 6번 손님으로부터 총 4번 주문됐습니다.
요리 3개 코스	C, D, E	    3번, 4번, 6번 손님으로부터 총 3번 주문됐습니다.
요리 4개 코스	B, C, F, G	1번, 5번 손님으로부터 총 2번 주문됐습니다.
요리 4개 코스	A, C, D, E	4번, 6번 손님으로부터 총 2번 주문됐습니다.

?:
각 손님들이 주문한 단품메뉴들이 문자열 형식으로 담긴 배열 orders, 
"스카피"가 추가하고 싶어하는 코스요리를 구성하는 단품메뉴들의 갯수가 담긴 배열 course가 매개변수로 주어질 때, 
"스카피"가 새로 추가하게 될 코스요리의 메뉴 구성을 문자열 형태로 배열에 담아 return 하도록 solution 함수를 완성해 주세요.

!!!:
orders 배열의 크기는 2 이상 20 이하입니다.
orders 배열의 각 원소는 크기가 2 이상 10 이하인 문자열입니다.
각 문자열은 알파벳 대문자로만 이루어져 있습니다.
각 문자열에는 같은 알파벳이 중복해서 들어있지 않습니다.
course 배열의 크기는 1 이상 10 이하입니다.
course 배열의 각 원소는 2 이상 10 이하인 자연수가 오름차순으로 정렬되어 있습니다.
course 배열에는 같은 값이 중복해서 들어있지 않습니다.
정답은 각 코스요리 메뉴의 구성을 문자열 형식으로 배열에 담아 사전 순으로 오름차순 정렬해서 return 해주세요.
배열의 각 원소에 저장된 문자열 또한 알파벳 오름차순으로 정렬되어야 합니다.
만약 가장 많이 함께 주문된 메뉴 구성이 여러 개라면, 모두 배열에 담아 return 하면 됩니다.
orders와 course 매개변수는 return 하는 배열의 길이가 1 이상이 되도록 주어집니다.

시도1)
코스의 각 원소가 2~10 이므로 최소 2가지 음식 조합으로 나온다.
재귀로 가능한 모든 경우를 찾아서 map에 각 메뉴가 몇번 등장하는지 센다.
시도2)
1명만 시킨 경우가 최대인 경우는 제외한다. 이때 배열이 비므로 empty면 continue하도록 변경
시도3)
"WX"인 경우와 "XW"인 경우를 WX로 같이봐야한다. 입력 메뉴도 정렬해서 넣는다.
----testcase 12,13,15 실패------
시도4)
배열 인덱스 넘거나 빈 배열에 접근하는 문제 해결후 통과
*/

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> menu_personMap; // 메뉴 조합 주문 횟수 저장
string ORDER;

void recur(string& str, int depth)    // 2가지 이상의 모든 메뉴 조합을 만든다
{
    if(depth == ORDER.size())
    {
        if(str.size() < 2)
            return;

        menu_personMap[str]++;
        return;
    }

    // 각자리 글자 선택 안하는 경우, 하는 경우
    recur(str, depth+1);
    str += ORDER[depth];
    recur(str, depth+1);
    str = str.substr(0, str.size()-1);
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    for(string str : orders)
    {
        ORDER = str;
        sort(ORDER.begin(), ORDER.end());
        string s;
        recur(s, 0);
    }

    // course개 중 가장 많이 주문된 메뉴 찾는다
    for(int c : course)
    {
        vector<pair<int, string>> menus;
        for(auto e: menu_personMap)
        {
            string key = e.first;
            int val = e.second;
            if(key.size() == c && val > 1)
                menus.push_back({-val, key});   // 주문수 내림차순 정렬
        }
        
        if(menus.empty())
            continue;
        sort(menus.begin(), menus.end());
        int last = menus[0].first;
        answer.push_back(menus[0].second);
        /* 이런식의 접근은 배열 범위 예외처리를 위한 코드가 많아진다. (버그 확률 증가 원인)
        int idx = 1;
        while(last == menus[idx].first)
        {
            answer.push_back(menus[idx].second);
            idx++;
            if(idx >= menus.size())
                break;
        }
        */
        // 반복자를 활용한다
        auto it = menus.begin()+1;
        for( ; it != menus.end(); it++)
        {   // 포인터 처럼 작동하므로 (*)를 붙여준다
            if(last == (*it).first)
                answer.push_back((*it).second);
        }
    }

    // 사전순 정렬
    sort(answer.begin(), answer.end());

    return answer;
}

int main()
{
    //vector<string> orders = {"ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH"};
    vector<string> orders = {"ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD"};
    //vector<string> orders = {"XYZ", "XWY", "WXA"};
    //vector<int> course = {2,3,4};
    vector<int> course = {2,3,5};

    solution(orders, course);

    return 0;
}