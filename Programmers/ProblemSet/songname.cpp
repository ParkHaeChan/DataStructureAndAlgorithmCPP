/*
문제: https://programmers.co.kr/learn/courses/30/lessons/17683

방금 그곡
cpp로 구현하기 상당히 까다로운 편인것 같다. 자주 연습삼아 풀어봐야겠다.

30번 case가 통과가 안돼서 좀 걸렸는데,

음악 길이보다 재생된 시간이 짧을 때는 처음부터 재생 시간만큼만 재생된다.

이 조건을 string[duration] = '\0'로 막을 수 있는 줄 알았는데,
문자열 끝을 나타내지 않고, 그냥 '\0'가 문자열 중간에 들어가고 문자열이 훼손 된 채로 있게된다.
char* 타입으로 문자열을 표현할 때는 맞을 수 있으나 string 형을 사용시에는 이처럼 문제가 발생할 수 있다.

string 타입일 때는 이런 실수를 하지 않도록 부분 문자열 얻기 메서드인 substr을 사용하도록 하자.

나머지 부분은 (stable)정렬이나 문자열 파싱(,) 같은 기본적인 구현 능력이 필요하다.

HH:MM 형식의 문자열로 시간이 주어질 때의 처리도 실수하지 않도록 주의가 필요하다.
여기서는 시간문자열을 substr으로 : 이전과 이후를 분리하여 stoi로 int형으로 고쳐 time형 구조체에 저장하는 방식을 사용했다.

C#, D#, F# 처럼 문자열 길이에 불필요한 영향을 주는 요소는 각각 소문자(c,d,f)로 인식하도록 치환하였다.
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>      // istringstream

using namespace std;

struct time
{
    int h;
    int m;
};

struct node
{
    int id;
    int duration;
    string title;
    string melody;
};

void transform(string& s)
{
    // #앞에를 소문자로 치환
    for(int i=0; i<s.size(); ++i)
        if(s[i] == '#')
        {
            s[i-1] = tolower(s[i-1]);
        }

    // #을 삭제
    s.erase(
        remove_if(s.begin(), s.end(), [](auto e){
            return e == '#';
        }), s.end());
}

vector<string> parse_string(string parseStr)
{
    vector<string> parsed;
    istringstream iss(parseStr);
    string buffer;
    while(getline(iss, buffer, ','))
    {
        parsed.push_back(buffer);
    }
    return parsed;  // 반환형이 참조형이면 삭제된 벡터에 대한 접근으로 에러가 발생한다
}

bool collect(string m, string melody)
{
    for(int i=0; i<melody.size(); ++i)
    {
        int j=0;
        for(; j<m.size(); ++j)
        {   // 배열접근시 항상 범위 주의
            if(j+i < melody.size())
            {
                if(m[j] == melody[j+i])
                    continue;
                else
                    break;
            }
            else
                break;
        }
        if(j == m.size())
            return true;
    }
    return false;
}

string solution(string m, vector<string> musicinfos) {
    string answer = "";
    // C# 같이 #이 붙은 단어는 소문자로 치환
    transform(m);
    //cout << m << endl;

    vector<node> musics;
    int id = 0;
    for(auto e : musicinfos)
    {
        vector<string> strvect = parse_string(e);
        struct::time start; // 시스템에서 사용중일 수 있으므로 앞에 struct:: 스코프지정자 써야할 수도 있다.
        struct::time end;
        start.h = stoi(strvect[0].substr(0, 2));
        start.m = stoi(strvect[0].substr(3, 2));
        end.h = stoi(strvect[1].substr(0, 2));
        end.m = stoi(strvect[1].substr(3, 2));
        int duration = (end.h-start.h)*60 + (end.m-start.m);
        string title = strvect[2];
        string melody = strvect[3];
        transform(melody);
        string temp = "";
        while(temp.size() <= duration)
            temp += melody;
        // 문자열 끝 표시 넣었는데 그냥 문자로 인식하고 읽는 거 같음...temp[duration] = '\0';
        temp = temp.substr(0, duration);
        musics.push_back({++id, duration, title, temp});
    }

    vector<node> answers;
    for(auto e : musics)
    {
        if(collect(m, e.melody))
        {
            answers.push_back(e);
        }
    }

    stable_sort(answers.begin(), answers.end(), [](auto a, auto b){
        if(a.duration == b.duration)
        {
            return a.id < b.id;
        }
        else
            return a.duration > b.duration;
    });
    if(answers.size() != 0)
        answer = answers[0].title;
    else
        answer = "(None)";

    return answer;
}

int main()
{
    string m = "CC#BCC#BCC#BCC#B";
    vector<string> musicinfos = {"22:59,23:17,FOO,CC#B", "04:00,04:08,BAR,CC#BCC#BCC#B"};

    cout << solution(m, musicinfos) << endl;

    return 0;
}