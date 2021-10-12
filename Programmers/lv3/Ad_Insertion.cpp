/*
광고 삽입
https://programmers.co.kr/learn/courses/30/lessons/72414

?:
"죠르디"의 동영상 재생시간 길이 play_time, 
공익광고의 재생시간 길이 adv_time, 
시청자들이 해당 동영상을 재생했던 구간 정보 logs가 매개변수로 주어질 때, 
시청자들의 누적 재생시간이 가장 많이 나오는 곳에 공익광고를 삽입하려고 합니다. 
이때, 공익광고가 들어갈 시작 시각을 구해서 return 하도록 solution 함수를 완성해주세요. 
만약, 시청자들의 누적 재생시간이 가장 많은 곳이 여러 곳이라면, 
그 중에서 가장 빠른 시작 시각을 return 하도록 합니다.

!!!:
play_time, adv_time은 길이 8로 고정된 문자열입니다.
play_time, adv_time은 HH:MM:SS 형식이며, 00:00:01 이상 99:59:59 이하입니다.
즉, 동영상 재생시간과 공익광고 재생시간은 00시간 00분 01초 이상 99시간 59분 59초 이하입니다.
공익광고 재생시간은 동영상 재생시간보다 짧거나 같게 주어집니다.
logs는 크기가 1 이상 300,000 이하인 문자열 배열입니다.

logs 배열의 각 원소는 시청자의 재생 구간을 나타냅니다.
logs 배열의 각 원소는 길이가 17로 고정된 문자열입니다.
logs 배열의 각 원소는 H1:M1:S1-H2:M2:S2 형식입니다.
H1:M1:S1은 동영상이 시작된 시각, H2:M2:S2는 동영상이 종료된 시각을 나타냅니다.
H1:M1:S1는 H2:M2:S2보다 1초 이상 이전 시각으로 주어집니다.
H1:M1:S1와 H2:M2:S2는 play_time 이내의 시각입니다.
시간을 나타내는 HH, H1, H2의 범위는 00~99, 분을 나타내는 MM, M1, M2의 범위는 00~59, 초를 나타내는 SS, S1, S2의 범위는 00~59까지 사용됩니다. 잘못된 시각은 입력으로 주어지지 않습니다. (예: 04:60:24, 11:12:78, 123:12:45 등)

return 값의 형식

공익광고를 삽입할 시각을 HH:MM:SS 형식의 8자리 문자열로 반환합니다.

시도1)
시간은 초단위로 풀어서 계산한다.
이 문제는 투포인터 문제일 가능성이 높다.
(슬라이드 윈도랑 햇갈리지 말자 슬라이드 윈도는 동적계획법에서 메모리 사용 최소화하는 기법이다)
log가 30만개나 들어오기 때문에 O(N)알고리즘을 구성해야하기 때문
log중 가장 빠른 위치에서 시작해서 광고 영상의 재생시간까지의 누적시간을 계산
이후 다음 빠른 log까지를 시작으로 삼고 다시 광고 영상의 재생시간까지의 누적시간을 계산...이후 반복
진행하면서 영상의 끝까지 누적시간이 갱신되는 경우만 적용한다.(같은 누적시간의 경우 젤 빠른 시간을 도출)
실패 및 시간초과 발생

sum을 재활용 할 수 있도록 구현하면 복잡도를 줄일 수 있을 것 같다.
자료형 범위 문제도 있을 것 같다.
30만개가 꽤 큰수로 합쳐지면서 sum이 int로 불충분할 수 있다.
점수: 41.9점

시도2)
자료형 고친걸로는 시간초과랑 실패 그대로이다...
투 포인터 부분을 다시 제대로 짜봐야 겠다
 이전 시도 1,2
int start = 0;
int end = start;
int idx = 0, sidx = 0;
long long lastsum = 0;
multiset<logtime> lgtmulset;
for(int sidx=0; sidx<logtimes.size(); ++sidx)
{   // start ~ end 구간이 adtime만큼 되도록 end 증가
    end = start+adtime;
    if(end > ptime)
        break;
    // end 전에 시작하는 위치들 찾기
    while(idx < logtimes.size() && end > logtimes[idx].first)
    {
        lgtmulset.insert(logtimes[idx]);
        idx++;
    };
    for(auto it = lgtmulset.begin(); it != lgtmulset.end(); )
    {   // 원소 중 end가 start보다 작은 경우 삭제: 이때 문제 안생기게 하려면 iterator 증가 후 삭제 하도록 구현
        if(start >= it->second)
        {
            lgtmulset.erase(it++);  // it가 복사로 작동하므로 문제 없다. erase 전에 it증가한다.
            // C11 방식: iter = lgtmulset.erase(iter); // 다음 이터레이터 반환해주는 듯
        }
        else
            it++;
    }
    // sum 계산
    long long sum = 0;
    for(auto it = lgtmulset.begin(); it != lgtmulset.end(); it++)
    {
        int eachend = min(end, it->second);
        int eachstart = max(start, it->first);
        sum += (eachend-eachstart);
    }
    if(sum > lastsum)
    {
        lastsum = sum;
        // answer에 시작 시간 변환하여 저장
        answer = int_to_time(start);
    }
    start = logtimes[sidx].first;
}

시도 3)
풀이 참고함
구간 전체를 배열로 만드는 것을 원래 맨 처음 고려하긴 했는데
그걸 전체 영상크기에 적용하려니 너무 크게나와서 불가능하다고 판단했었다.
하지만 100시간 == 360000 으로 별로 크지 않다... (시간을 잘 못 본듯...)
전체 영상의 구간 배열에 사람이 시청하는 만큼을 저장하면 된다.
그 뒤 투포인터를 사용하여 값을 계산한다.
따로 정렬할 필요도 없이 전체구간에서 1씩 더하고 빼고해주면서 구간합 갱신해주면 된다.

카카오 예전 문제에도 투포인터를 쓰는 문제가 있었는데(보석 쇼핑: https://programmers.co.kr/learn/courses/30/lessons/67258)
같이 묶어서 정리 잘 해둬야 겠다.
*/

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;
using logtime = pair<int, int>; // {start, end}

int transform_timestr(string t)
{
    string buff;
    istringstream iss(t);
    vector<int> times;
    while(getline(iss, buff, ':'))
    {
        times.push_back(stoi(buff));
    }
    //  초단위로 변경
    return times[0]*3600 + times[1]*60 + times[2];
}

logtime transform_logtimestr(string t)
{
    string s = t.substr(0, 8);
    string e = t.substr(9, 8);
    int start = transform_timestr(s);
    int end = transform_timestr(e);

    return logtime{start, end};
}

string int_to_time(int start)
{
    int hour = start/3600;
    int min = (start%3600)/60;
    int sec = start%60;

    // 공백 문자열로 초기화 후 1자리 수면 0을 추가하고 수를 더하는 식으로 구현해도 좋다
    string h = to_string(hour);
    string m = to_string(min);
    string s = to_string(sec);
    if(hour < 10)
        h.insert(h.begin(), '0');
    if(min < 10)
        m.insert(m.begin(), '0');
    if(sec < 10)
        s.insert(s.begin(), '0');

    return h+":"+m+":"+s;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";

    // 시간 변환 : string to int
    int ptime = transform_timestr(play_time);
    int adtime = transform_timestr(adv_time);
    // 시도 3: 전체 영상 구간 배열
    vector<int> viewers(360000, 0);   // 최대 100시간
    // vector<logtime> logtimes; 필요 없음...변환후 해당 구간에 시청자 수 추가 
    for(auto& e: logs)
    {
        auto temp = transform_logtimestr(e);
        for(int i=temp.first; i<temp.second; ++i)
            viewers[i]++;
    }
    /* sorting 필요 없음
    sort(logtimes.begin(), logtimes.end(), [](auto back, auto front){
        return back.first < front.first;
    });
    */
    // 시도 3 투포인터 적용
    int start = 0;
    int end = 0;
    long long sum = 0;
    long long last_max = 0;
    for(int i=0; i<adtime; ++i)
    {
        sum += viewers[i];
    }
    last_max = sum;
    int front = 0;
    answer = int_to_time(front);
    for(int i=adtime; i<ptime; ++i)
    {
        sum += viewers[i];
        sum -= viewers[front++];
        if(last_max < sum)
        {
            last_max = sum;
            answer = int_to_time(front);
        }
    }
    
    return answer;
}

int main()
{
    // string play_time = "50:00:00";
    // string adv_time = "50:00:00";
    // vector<string> logs = {"15:36:51-38:21:49", "10:14:18-15:36:51", "38:21:49-42:51:45"};
    string play_time = "02:03:55";
    string adv_time = "00:14:15";
    vector<string> logs = {"01:20:15-01:45:14", "00:40:31-01:00:00", "00:25:50-00:48:29", "01:30:59-01:53:29", "01:37:44-02:02:30"};
    solution(play_time, adv_time, logs);

    return 0;
}