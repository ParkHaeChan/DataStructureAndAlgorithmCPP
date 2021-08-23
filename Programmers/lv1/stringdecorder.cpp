/*
문자열 내림차순으로 배치하기
https://programmers.co.kr/learn/courses/30/lessons/12917

문자열 s에 나타나는 문자를 큰것부터 작은 순으로 정렬해 새로운 문자열을 리턴하는 함수, solution을 완성해주세요.
s는 영문 대소문자로만 구성되어 있으며, 대문자는 소문자보다 작은 것으로 간주합니다.

입출력 예
"Zbcdefg" --> "gfedcbZ"

비교함수 람다로 만들어서 해결했는데, 대문자와 소문자인 경우 크기비교할 때
대문자인 쪽을 뒤로 보내기 위해서
현재 상태가 a, b순으로 배열에 위치하고,
조건식이 true일때 swap이 발생한다고 생각했는데
약간 반대인 것 같다. a, b순으로 위치하고 있지 않거나,
false일 떄 swap이 발생하거나 인것 같다.

그래서 테스트 해봤다
입력을 ABCabc로 주고 콘솔에 출력해보았다
=====================================
다 대문자
a: B b: A
둘 다 대문자
a: C b: B
b만 대문자
a: a b: C
둘 다 소문자
a: b b: a
둘 다 소문자
a: c b: b
=====================================
비교함수 [](auto a, auto b){ ... }로 작성했을 떄
a가 배열의 뒤에 위치한 원소이고
b가 배열의 앞에 위치한 원소임을 알수 있다.
그리고 함수가 true를 반환하면 a,b 자리가 바뀌고,
false이면 그대로 있는 것을 확인할 수 있다.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string solution(string s) {
    string answer = "";
    
    sort(s.begin(), s.end(), [](auto a, auto b){
        if(isupper(a) && isupper(b))
        {
            cout << "둘 다 대문자" << endl;
            cout << "a: " << a << " b: " << b << endl;
            if(a>b)
                cout << "교환: O" << endl;
            else
                cout << "교환: X" << endl;
            return a > b;
        }
        else if(isupper(a))
        {
            cout << "a만 대문자" << endl;
            cout << "a: " << a << " b: " << b << endl;
            cout << "교환: X" << endl;
            return false;
        }
        else if(isupper(b))
        {
            cout << "b만 대문자" << endl;
            cout << "a: " << a << " b: " << b << endl;
            cout << "교환: O" << endl;
            return true;
        }
        else    // 둘 다 소문자
        {
            cout << "둘 다 소문자" << endl;
            cout << "a: " << a << " b: " << b << endl;
            if(a>b)
                cout << "교환: O" << endl;
            else
                cout << "교환: X" << endl;
            return a > b;
        }
    });
    
    return answer = s;
}

int main()
{
    string s = "ABCabc";

    cout << solution(s) << endl;

    return 0;
}