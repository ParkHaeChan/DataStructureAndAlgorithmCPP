/*
2016년
https://programmers.co.kr/learn/courses/30/lessons/12901

?:
2016년 1월 1일은 금요일입니다. 2016년 a월 b일은 무슨 요일일까요?
두 수 a ,b를 입력받아 2016년 a월 b일이 무슨 요일인지 리턴하는 함수, solution을 완성하세요. 
요일의 이름은 일요일부터 토요일까지 각각 SUN,MON,TUE,WED,THU,FRI,SAT입니다. 
예를 들어 a=5, b=24라면 5월 24일은 화요일이므로 문자열 "TUE"를 반환하세요.

!!!:
2016년은 윤년입니다.
2016년 a월 b일은 실제로 있는 날입니다.
(13월 26일이나 2월 45일같은 날짜는 주어지지 않습니다)

윤년일 경우: 양력에서는 4년마다 한 번씩 2월을 29일로 한다.
1월	31일
2월	28일
29일 (윤년)
3월	31일
4월	30일
5월	31일
6월	30일
7월	31일
8월	31일
9월	30일
10월 31일
11월 30일
12월 31일

시도1) 해당 날짜까지의 일수를 구해서 7로 나눈 나머지로 무슨 요일인지 파악하도록 구성함
2개의 case에서 실패
시도2) 목요일에 MAP index에 7이라 썼다... 0이어야 제대로 작동할 것이다.
*/

#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(int a, int b) {
    string answer = "";

    // 20160101은 금요일
    map<int, string> datedayMap;
    // 하드 코딩 : 오타 주의
    datedayMap[1] = "FRI";
    datedayMap[2] = "SAT";
    datedayMap[3] = "SUN";
    datedayMap[4] = "MON";
    datedayMap[5] = "TUE";
    datedayMap[6] = "WED";
    datedayMap[0] = "THU";  // 7로 나눈 나머지를 찾아야하는데 7을 쓰면ㅋㅋㅋ

    // 월마다 몇일 있는지 저장
    vector<int> monthday = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // a월 b일을 전체 일수로 치환
    int dates = 0;
    for(int i=1; i<a; ++i)
    {
        dates += monthday[i];
    }
    dates += b;

    answer = datedayMap[dates%7];

    return answer;
}