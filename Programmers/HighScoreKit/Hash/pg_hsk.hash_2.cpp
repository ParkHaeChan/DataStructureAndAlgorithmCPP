/*
전화번호 목록
https://programmers.co.kr/learn/courses/30/lessons/42577

어떤 번호가 다른 번호의 접두어인 경우가 있으면 false를 그렇지 않으면 true를 return 하도록 solution 함수를 작성해주세요.

!!!: --> <앞으로 제한사항 표시로 쓸 것임>
phone_book의 길이는 1 이상 1,000,000 이하입니다.
각 전화번호의 길이는 1 이상 20 이하입니다.
같은 전화번호가 중복해서 들어있지 않습니다.

시도1) 효율성 테스트를 통과하지 못했다.
아마 100만개를 정렬하는 부분에서 효율이 떨어지는 것 같다.
해법1)
앞에서 정렬을 하지 않더라도 map에 넣을 때 자동으로 정렬된다는 점을 이용해야 될 것 같다.
이때는 문자열 길이순으로 정렬되지는 않지만, 적어도 앞글자가 같은 것 끼리는 정렬되어 있을 것이다.
예외 처리를 약간 해주면 될 것 같다.

시도2) 이번에도 시간초과가 발생했다.
이래도 문제가 생긴다면 문자열 비교에 걸리는 시간이 길어서 그런 것일 수 있다.
해법2) 문자열 비교가 아닌 map에 존재 여부를 물어보는 식으로 바꿔서 시도해 본다.

시도3으로 통과했다.
set을 써서 문자열 길이들을 미리 준비해 둔 다음, 부분 문자열 찾을 때 사용하였다.
중복된 번호는 없기 때문에 찾으려는 문자열 길이가 현재 문자열 길이와 같은 경우는 발생하지 않는다고 판단하였다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;

    // 시도1) 전화번호가 짧은 번호부터 확인하는게 좋으므로 문자열 길이순으로 정렬
    /*
    sort(phone_book.begin(), phone_book.end(), [](auto a, auto b){
        return a.size() < b.size();
    });
    */

    // 시도3) 문자열 길이만 저장하는 집합을 만들어서 부분문자열을 만들때 참고한다
    set<int> strsizes;
    // 전번 존재 여부를 빠르게 파악하기 위해 map을 사용
    map<string, bool> pb;
    for(auto e: phone_book)
    {
        pb[e] = true;
        strsizes.insert(e.size());
    }

    // 시도1) 접두사 존재하는지 확인
    /*
    for(int i=0; i<phone_book.size(); ++i)
    {
        for(int j=i+1; j<phone_book.size(); ++j)
        {
            // 접두사만 확인하면 되므로 앞에서 부터 확인하려는 문자열 길이만큼만 확인하면 된다
            // 길이순으로 정렬했기 때문에 phone_book[j]는 test보다 같거나 크다.
            string test = phone_book[i];
            string head = phone_book[j].substr(0, test.size());
            if(test == head)
                return false;
        }
    }
    */
    /*
    // 시도2) map에 저장돼있는 순서대로 존재여부를 확인한다.
    for(auto e: pb)
    {
        string test = e.first;
        for(auto el: pb)
        {
            // 같은 번호가 중복되서 존재하지 않는다고 조건에 명시했다.
            if(el.first == test)
                continue;
            // 접두사 확인
            string head = el.first.substr(0, test.size());
            if(test == head)
                return false;
        }
    }
    */
   // 시도3) 문자열을 비교하지 않고 map에 존재 여부를 찾는다.
    for(auto el: pb)
    {
        for(auto ss: strsizes)
        {   // 크기가 작거나 같으면 접두사가 생길 수 없음(set도 정렬이 기본이다)
            if(el.first.size() <= ss)
                break;

            // 접두사 확인
            string head = el.first.substr(0, ss);
            if(pb[head])
                return false;
        }
    }

    return answer;
}

int main()
{
    vector<string> phone_book = {"119", "97674223", "1195524421"};

    cout << solution(phone_book) << endl;

    return 0;
}