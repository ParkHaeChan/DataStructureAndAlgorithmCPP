/*
셔틀버스
https://programmers.co.kr/learn/courses/30/lessons/17678

셔틀은 09:00부터 총 n회 t분 간격으로 역에 도착하며, 하나의 셔틀에는 최대 m명의 승객이 탈 수 있다.
셔틀은 도착했을 때 도착한 순간에 대기열에 선 크루까지 포함해서 대기 순서대로 태우고 바로 출발한다. 
예를 들어 09:00에 도착한 셔틀은 자리가 있다면 09:00에 줄을 선 크루도 탈 수 있다.

일찍 나와서 셔틀을 기다리는 것이 귀찮았던 콘은, 일주일간의 집요한 관찰 끝에 어떤 크루가 몇 시에 셔틀 대기열에 도착하는지 알아냈다. 
콘이 셔틀을 타고 사무실로 갈 수 있는 도착 시각 중 제일 늦은 시각을 구하여라.

단, 콘은 게으르기 때문에 같은 시각에 도착한 크루 중 대기열에서 제일 뒤에 선다. 
또한, 모든 크루는 잠을 자야 하므로 23:59에 집에 돌아간다. 
따라서 어떤 크루도 다음날 셔틀을 타는 일은 없다.

input
셔틀 운행 횟수 n, 셔틀 운행 간격 t, 한 셔틀에 탈 수 있는 최대 크루 수 m, 크루가 대기열에 도착하는 시각을 모은 배열 timetable이 입력으로 주어진다.
0 ＜ n ≦ 10
0 ＜ t ≦ 60
0 ＜ m ≦ 45
timetable은 최소 길이 1이고 최대 길이 2000인 배열로, 하루 동안 크루가 대기열에 도착하는 시각이 HH:MM 형식으로 이루어져 있다.
크루의 도착 시각 HH:MM은 00:01에서 23:59 사이이다.

output:
콘이 무사히 셔틀을 타고 사무실로 갈 수 있는 제일 늦은 도착 시각을 출력한다. 도착 시각은 HH:MM 형식이며, 00:00에서 23:59 사이의 값이 될 수 있다.

시도1)
셔틀은 09:00 부터 t분 간격으로 n회 출발하므로
t = 60이고 n = 10d이면, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6(18:00)에 출발한다.
n 과 t로 버스 출발시간을 미리 찾아서 저장해 둔다.
다음으로는 timetable을 정렬하여 m명 이내로 버스를 타는 가장 늦은 시간대를 찾아야한다.
이는 그리디 방식으로 가장 늦게 오는 버스에 콘이 제일 늦게 가서 탈 수 있는지를 확인해보면 된다.

시도2)
3번 테스트 케이스를 미처 고려하지 못했다.
이전에 온사람이 두 버스를 다 타고 가는 경우가 발생할 수 있다.
늦은 버스부터 확인하지 않고 차례로 버스를 다 채우는 방식을 쓰도록 변경

통과...하지만 코드가 너무 길다
*/

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct btime
{
    int hour;
    int min;
};

vector<btime> bus_time(int n, int t)
{
    vector<btime> ret;
    int hour = 9, min = 0;
    ret.push_back({hour, min});
    
    for(int cnt = 0; cnt < n-1; ++cnt)
    {   // 분을 더해준다
        min += t;
        // 60분 넘을 때 처리
        if(min >= 60)
        {
            min -= 60;
            hour += 1;
        }
        ret.push_back({hour, min});
    }
    return ret;
}

vector<btime> crew_time(vector<string>& timetable)
{
    vector<btime> ret;
    for(auto& s: timetable)
    {
        btime temp;
        istringstream iss(s);
        string buff;
        vector<string> tv;
        while(getline(iss, buff, ':'))
        {
            tv.push_back(buff);
        }
        int hour = stoi(tv[0]);
        int min = stoi(tv[1]);
        ret.push_back({hour, min});
    }
    return ret;
}

bool InRange(btime departure, btime cur)
{
    if(cur.hour == departure.hour)
    {
        return cur.min <= departure.min;
    }
    else
        return cur.hour < departure.hour;
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";

    // 버스 도착 시간 (이미 정렬된 상태)
    vector<btime> bus_departure_times = bus_time(n, t);

    // timetable 파싱하여 구조체에 저장
    vector<btime> crew_wait_times = crew_time(timetable);

    // 크루들 타는 시간순으로 정렬
    sort(crew_wait_times.begin(), crew_wait_times.end(), [](auto back, auto front){
        if(back.hour == front.hour)
        {
            return back.min < front.min;
        }
        else
            return back.hour < front.hour;
    });

    // 시도2) 버스 오는 순으로 사람들 태워 가도록 시뮬레이션
    int crew = 0;
    for(int i = 0; i < bus_departure_times.size(); ++i)
    {
        auto bus_time = bus_departure_times[i]; // 타이핑 줄이는 트릭(변경시는 주의 필요, 참조로 받던가 해야함)
        int cnt = 0;
        int CREWSIZE = crew_wait_times.size();
        int last = crew;
        for(; crew<CREWSIZE; ++crew)
        {
            if(cnt == m)
                break;
            if(InRange(bus_time, crew_wait_times[crew]))
            {
                cnt++;
                last = crew;    // 마지막 탄사람 갱신
            }
            else
                break;
        }
        //  최대한 늦은 버스를 탈 것이므로 그 이전 버스는 통과
        if(i < bus_departure_times.size()-1)
            continue;
        if(cnt < m)
        {   // 버스 시간에 타면 된다
            if(bus_time.hour < 10)
                answer += "0" + to_string(bus_time.hour);
            else
                answer += to_string(bus_time.hour);
            answer += ":";
            if(bus_time.min < 10)
                answer += "0" + to_string(bus_time.min);
            else
                answer += to_string(bus_time.min);
            break;
        }
        else
        {   // 마지막에 버스 타는 사람보다 일찍 와야 탈 수 있다
            int hour = crew_wait_times[last].hour;
            int min = crew_wait_times[last].min;
            min--;
            if(min < 0)
            {
                min = 59;
                hour--;
            }
            if(hour < 10)
                answer += "0" + to_string(hour);
            else
                answer += to_string(hour);
            answer += ":";
            if(min < 10)
                answer += "0" + to_string(min);
            else
                answer += to_string(min);

            break;
        }
    }
    return answer;
}

int main()
{
    int n=2, t=1, m=2;
    vector<string> timetable = {"09:00", "09:00", "09:00", "09:00"};
    // int n=1, t=1, m=5;
    // vector<string> timetable = {"08:00", "08:01", "08:02", "08:03"};
    //int n=10, t=60, m=45;
    //vector<string> timetable = {"23:59","23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59"};
    solution(n, t, m, timetable);
    return 0;
}