// 구현 문제: 파싱, 시간 변환, 해싱(매핑)
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;
using dtime = pair<int, int>;   // h:m

struct car
{
    string id;
    dtime in;
    dtime out;
};

vector<string> parse_space(string& input)
{
    vector<string> ret;
    istringstream iss(input);
    string buff;
    while(getline(iss, buff, ' '))
    {
        ret.push_back(buff);
    }
    return ret;
}

vector<string> parse_colon(string& input)
{
    vector<string> ret;
    istringstream iss(input);
    string buff;
    while(getline(iss, buff, ':'))
    {
        ret.push_back(buff);
    }
    return ret;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    map<string, car> carMap;
    vector<pair<string, int>> durationVect;
    for(auto rcd: records)
    {
        vector<string> parsed_rcd = parse_space(rcd);
        vector<string> parse_time = parse_colon(parsed_rcd[0]);
        int h = stoi(parse_time[0]);
        int m = stoi(parse_time[1]);
        string id = parsed_rcd[1];
        car temp = {"xxxx", {-1,-1}, {-1, -1}};
        
        temp.id = id;
        if(parsed_rcd[2] == "IN")
        {
            temp.in = {h, m};
            carMap[id] = temp;
        }
        else
        {
            temp = carMap[id];
            temp.out = {h, m}; 
            int duration = (temp.out.first * 60 + temp.out.second) - (temp.in.first * 60 + temp.in.second);
            durationVect.push_back({id, duration});
            carMap[id] = {id, {-1,-1}, {-1, -1}};
        }
    }
    // 출차 기록 없으면 23:59로 설정
    dtime t = {-1, -1};
    for(auto& e: carMap)
    {
        if(e.second.in == t)
            continue;
        if(e.second.out == t)
        {
            car temp = e.second;
            e.second.out = {23, 59};
            temp.out = {23, 59};
            int duration = (temp.out.first * 60 + temp.out.second) - (temp.in.first * 60 + temp.in.second);
            durationVect.push_back({temp.id, duration});
        }
    }
    // 주차 시간 계산하여 적용
    map<string, int> feeMap;
    for(auto e: durationVect)
    {
        feeMap[e.first] += e.second;
    }

    vector<pair<string, int>> feeVect;
    for(auto e: feeMap)
    {
        int duration = e.second;
        if(fees[0]-duration >= 0)
        {   // 기본 요금
            feeVect.push_back({e.first, fees[1]});
        }
        else
        {
            int over = duration-fees[0];
            int over_fee = lround(ceil((double)over/fees[2]));
            over_fee *= fees[3];
            feeVect.push_back({e.first, fees[1]+over_fee});
        }
    }
    sort(feeVect.begin(), feeVect.end(), [](auto back, auto front){
        return back.first < front.first;
    });
    
    for(auto e: feeVect)
        answer.push_back(e.second);

    return answer;
}

int main()
{
    vector<int> fees = {180, 5000, 10, 600};
    vector<string> records = {"05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT", "07:59 5961 OUT", "07:59 0148 IN", "18:59 0000 IN", "19:09 0148 OUT", "22:59 5961 IN", "23:00 5961 OUT"};

    solution(fees, records);

    return 0;
}