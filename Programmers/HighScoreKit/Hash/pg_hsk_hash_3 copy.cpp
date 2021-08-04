/*
위장
https://programmers.co.kr/learn/courses/30/lessons/42578

문제를 약간 바꿔서 옷을 입는 모든 경우의 수를 나타내라고 했다고 가정한다.
이때는 재귀를 이용해서 푼다.
각각의 옷을 입는 경우와 안입는 경우를 재귀적으로 적용하면 된다.
옷의 종류에 여러 옷이름이 들어갈 수 있어야 하므로 이를 위해 멀티맵을 사용한다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>  // multimap
#include <set>  // 종류만 중복되지 않게 저장했다가 벡터로 옮기는 역할

using namespace std;

void recur(multimap<string, string>& cmap, vector<string>& kind, int depth, string& ret)
{
    // 종료 조건: depth가 map의 버킷수(kind.size()) 만큼 진행하였을 경우
    if(depth == kind.size())
    {
        // 문제의 조건처럼 뭐 하나라도 입어야된다면, static bool로 그 경우만 출력 안시키도록 만들어준다.
        static bool first = true;   // (상식): static은 생성 시 1회만 초기화된다
        if(first)
        {
            first = false;
            return;
        }
        cout << ret << endl;
        return;
    }

    // depth에 해당하는 옷종류에서 옷이름 하나를 선택하여 입을지 말지 정한다.
    string k = kind[depth];
    
    auto piter = cmap.equal_range(k);
    string temp = k + ": not used ";
    recur(cmap, kind, depth+1, ret+=temp);    // 안입는 경우
    ret = ret.substr(0, ret.size()-temp.size());

    for(auto it = piter.first; it != piter.second; ++it)
    {
        //  ret을 참조로 쓰면 추가했던 만큼 다시 지우고 쓰고를 반복해야한다
        temp =  k + ": " + it->second + " ";
        recur(cmap, kind, depth+1, ret+=temp);    // 입는 경우
        ret = ret.substr(0, ret.size()-temp.size());
    }
}

int solution(vector<vector<string>> clothes) {
    int answer = 0;

    multimap<string, string> clotheskind;
    set<string> kindset;
    for(auto e: clothes)
    {
        string clothname = e[0];
        string kind = e[1];

        // multimap은 map과 달리 []를 사용할 수 없다
        clotheskind.insert({kind, clothname});  // insert로 넣을 떄 pair로 넣거나 {}로 감싼다
        kindset.insert(kind);
    }
    vector<string> kindvect;
    for(auto e: kindset)
        kindvect.push_back(e);

    string str = "";
    recur(clotheskind, kindvect, 0, str);

    return answer;
}

int main()
{
    vector<vector<string>> clothes = {{"yellowhat", "headgear"}, {"bluesunglasses", "eyewear"}, {"green_turban", "headgear"}};

    cout << solution(clothes) << endl;

    return 0;
}