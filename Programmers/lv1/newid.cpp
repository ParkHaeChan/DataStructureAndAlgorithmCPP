/*
신규 아이디 추천
https://programmers.co.kr/learn/courses/30/lessons/72410

?:
다음과 같이 7단계의 순차적인 처리 과정을 통해 
신규 유저가 입력한 아이디가 카카오 아이디 규칙에 맞는 지 검사하고 규칙에 맞지 않은 경우 규칙에 맞는 새로운 아이디를 추천해 주려고 합니다.
신규 유저가 입력한 아이디가 new_id 라고 한다면,

1단계 new_id의 모든 대문자를 대응되는 소문자로 치환합니다.
2단계 new_id에서 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거합니다.
3단계 new_id에서 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환합니다.
4단계 new_id에서 마침표(.)가 처음이나 끝에 위치한다면 제거합니다.
5단계 new_id가 빈 문자열이라면, new_id에 "a"를 대입합니다.
6단계 new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거합니다.
     만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거합니다.
7단계 new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙입니다.

!!!:
아이디의 길이는 3자 이상 15자 이하여야 합니다.
아이디는 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.) 문자만 사용할 수 있습니다.
단, 마침표(.)는 처음과 끝에 사용할 수 없으며 또한 연속으로 사용할 수 없습니다.

new_id는 길이 1 이상 1,000 이하인 문자열입니다.
new_id는 알파벳 대문자, 알파벳 소문자, 숫자, 특수문자로 구성되어 있습니다.
new_id에 나타날 수 있는 특수문자는 -_.~!@#$%^&*()=+[{]}:?,<>/ 로 한정됩니다.

풀이)
주어진 7가지 조건을 그대로 수행하도록 구현하면 된다

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>    // transform, remove_if

using namespace std;

//  연속된 마침표 처리하기
string erase_connected_endpoint(string str)
{
    for(int i=0; i<str.size(); ++i)
    {
        if(str[i] == '.')
        {
            int cnt = i+1;
            int N = str.size();
            while(str[cnt] == '.')
                cnt++;
            if(cnt == i+1)
                continue;
            // 연속된 마침표를 삭제
            str = str.substr(0, i+1) + str.substr(cnt, N-cnt);
            // 문자열은 i 이후만 변경되므로 i = i-1 등의 처리는 필요 없다
        }
    }
    return str;
}

// 특정 문자 제거하기
string remove_notallowedwords(string str)
{
    str.erase(  //erase ( first: 삭제할 시작 위치, last: 삭제할 범위의 끝 = str.end() )
        // remove_if : 범위 내에서 람다 조건함수 작성하면 iterator 반환
        remove_if(str.begin(), str.end(), [](unsigned char x){
        // 람다식 내부는 원소 x가 삭제할 조건을 만족하면 true를 return하도록 작성
        if(isalnum(x) || (x == '-') || (x=='_') || (x=='.'))
            return false;
        else    // true 이면 삭제됨
            return true;
        }),
    str.end());
    return str;
}

string solution(string new_id) {
    string answer = "test";

    // 1단계 new_id의 모든 대문자를 대응되는 소문자로 치환
    transform(new_id.begin(), new_id.end(), new_id.begin(), [](auto e){
        return tolower(e);
    });
    // 2단계 new_id에서 알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거합니다.
    new_id = remove_notallowedwords(new_id);
    // 3단계 new_id에서 마침표(.)가 2번 이상 연속된 부분을 하나의 마침표(.)로 치환합니다.
    new_id = erase_connected_endpoint(new_id);
    // 4단계 new_id에서 마침표(.)가 처음이나 끝에 위치한다면 제거합니다.
    if(new_id[0] == '.')
        new_id = new_id.substr(1, new_id.size()-1);
    int N = new_id.size();
    if(new_id[N-1] == '.')
        new_id = new_id.substr(0, N-1);
    // 5단계 new_id가 빈 문자열이라면, new_id에 "a"를 대입합니다.
    if(new_id.empty())
        new_id = "a";
    // 6단계 new_id의 길이가 16자 이상이면, new_id의 첫 15개의 문자를 제외한 나머지 문자들을 모두 제거합니다.
    //      만약 제거 후 마침표(.)가 new_id의 끝에 위치한다면 끝에 위치한 마침표(.) 문자를 제거합니다.
    if(new_id.size() >= 16)
        new_id = new_id.substr(0, 15);
    N = new_id.size();
    if(new_id[N-1] == '.')
        new_id = new_id.substr(0, N-1);
    // 7단계 new_id의 길이가 2자 이하라면, new_id의 마지막 문자를 new_id의 길이가 3이 될 때까지 반복해서 끝에 붙입니다.
    N = new_id.size();
    string last = new_id.substr(N-1, 1);
    while(new_id.size() <= 2)
    {
        new_id += last;
    }
    return answer = new_id;
}

int main()
{
    string new_id = "...!@BaT#*..y.abcdefghijklm";

    cout << solution(new_id) << endl;

    return 0;
}