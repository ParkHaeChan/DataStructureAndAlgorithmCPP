/*
추석 트래픽
https://programmers.co.kr/learn/courses/30/lessons/17676

초당 최대 처리량은 요청의 응답 완료 여부에 관계없이 임의 시간부터 1초(=1,000밀리초)간 처리하는 요청의 최대 개수를 의미한다.

input:
solution 함수에 전달되는 lines 배열은 N(1 ≦ N ≦ 2,000)개의 로그 문자열로 되어 있으며, 
각 로그 문자열마다 요청에 대한 응답완료시간 S와 처리시간 T가 공백으로 구분되어 있다.
응답완료시간 S는 작년 추석인 2016년 9월 15일만 포함하여 고정 길이 2016-09-15 hh:mm:ss.sss 형식으로 되어 있다.
처리시간 T는 0.1s, 0.312s, 2s 와 같이 최대 소수점 셋째 자리까지 기록하며 뒤에는 초 단위를 의미하는 s로 끝난다.

예를 들어, 로그 문자열 2016-09-15 03:10:33.020 0.011s은 
"2016년 9월 15일 오전 3시 10분 33.010초"부터 "2016년 9월 15일 오전 3시 10분 33.020초"까지 "0.011초" 동안 처리된 요청을 의미한다. (처리시간은 시작시간과 끝시간을 포함)
서버에는 타임아웃이 3초로 적용되어 있기 때문에 처리시간은 0.001 ≦ T ≦ 3.000이다.
lines 배열은 응답완료시간 S를 기준으로 오름차순 정렬되어 있다.

output:
solution 함수에서는 로그 데이터 lines 배열에 대해 초당 최대 처리량을 리턴한다.

시도)
비슷한 문제를 풀어봤어서 한번에 그리디 문제 인것을 확인함.
문제는 시간을 어떻게 처리할꺼였는데, 전체적으로 1000을 곱해서 소수점을 없에는 쪽으로 구현함
9월 14일로 날짜 바뀌는 경우가 있을까봐 걱정했는데 그런 경우는 없는 듯함.
버그나 케이스 실패 없이 한번에 통과해서 기분좋다ㅎㅎ
*/

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct node
{
    //string date;
    double start;
    double end;
};

vector<string> parse_str(string str)
{
    vector<string> ret;
    string buff;
    istringstream iss(str);

    while(getline(iss, buff, ' '))
    {
        ret.push_back(buff);
    }
    return ret;
}

vector<double> parse_time(string str)
{
    vector<double> ret;
    string buff;
    istringstream iss(str);

    while(getline(iss, buff, ':'))
    {
        ret.push_back(stod(buff));
    }
    return ret;
}

int during_1_sec(vector<node>& nodeVect, double end)
{
    double range = end+1000;    // 밀리초 단위 (end를 포함하므로 range는 포함 X해야 1초 구간이다)
    int ret = 0;
    for(auto& e: nodeVect)
    {
        // 시작이나 끝이 구간 내인 경우
        if(end <= e.end && e.end < range || end <= e.start && e.start < range)
        {
            ret++;
        }
        else if(e.start < end && e.end >= range)   // 시작이 end보다 작고 끝이 range 이상인 경우도 가능
        {
            ret++;
        }
    }
    return ret;
}

int solution(vector<string> lines) {
    int answer = 0;

    int N = lines.size();
    vector<node> nodeVect;
    // 파싱하여 날짜 시간 순으로 정렬 될 수 있도록 처리
    // 최대 3초이고 lines 크기가 2000까지 가므로 6000초 -> 100분 날짜가 바뀌는 경우도 고려해야 될 듯...(그런 경우 없음)
    node temp;
    for(string& str : lines)
    {
        vector<string> parsed = parse_str(str);
        //temp.date = parsed[0];
        double duration = stod(parsed[2]);
        vector<double> times = parse_time(parsed[1]);
        temp.end = 3600000*times[0] + 60000*times[1] + 1000*times[2];  // hour + min + sec (밀리초단위)
        double get_end =
        temp.start = temp.end - (1000*duration-1);
        nodeVect.push_back(temp);
    }
    // 정렬 (끝난 시간 순)
    sort(nodeVect.begin(), nodeVect.end(), [](auto back, auto front){
        if(back.end == front.end)
        {
            return back.start < front.start;    // 먼저 시작한게 앞에 오도록
        }
        else
            return back.end < front.end;    // 빨리 끝나는게 먼저 오도록
        // 날짜 변경은 고려X(9월 14일이 시작인 경우는 없다)
    });
    // 각 요청 끝날 때를 기점으로 1초(1000ms) 동안 몇개의 작업이 있었는지 확인
    for(auto& e: nodeVect)
    {
        answer = max(answer, during_1_sec(nodeVect, e.end));
    }
    
    return answer;
}

int main()
{
    vector<string> lines = {"2016-09-15 20:59:57.421 0.351s",
"2016-09-15 20:59:58.233 1.181s",
"2016-09-15 20:59:58.299 0.8s",
"2016-09-15 20:59:58.688 1.041s",
"2016-09-15 20:59:59.591 1.412s",
"2016-09-15 21:00:00.464 1.466s",
"2016-09-15 21:00:00.741 1.581s",
"2016-09-15 21:00:00.748 2.31s",
"2016-09-15 21:00:00.966 0.381s",
"2016-09-15 21:00:02.066 2.62s"};

    solution(lines);
    return 0;
}