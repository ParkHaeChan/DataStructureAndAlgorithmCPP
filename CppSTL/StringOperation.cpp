
#include <string>
#include <iostream>
#include <algorithm>    // remove_if 
#include <vector>

#include <sstream>      // istringstream

using namespace std;

template<typename T>
void print_vector(vector<T>& vect)
{
    for(auto& e: vect)
        cout << e << " ";
    cout << endl;
}

int main()
{
    string str = "string with some \t spaces \n and line...";
    cout << str << endl;

    // 공백 문자 제거하기
    str.erase(  //erase ( first: 삭제할 시작 위치, last: 삭제할 범위의 끝 = str.end() )
        // remove_if : 범위 내에서 람다 조건함수 작성하면 iterator 반환
        remove_if(str.begin(), str.end(), [](unsigned char x){
        // 람다식 내부는 원소 x가 삭제할 조건을 만족하면 true를 return하도록 작성
        return isspace(x);
        }),
    str.end());
    cout << str << endl;

    // 문자열 Parsing 하기
    // 한글유니코드는 따로 해보자... string parseStr = "이 문자열은, 콤마를 기준으로, 파싱해 주세요!";
    string parseStr = "this,string,will?parsed!with,the#comma";
    vector<string> parsed;
    // 1) stringstream과 getline을 이용 (파싱 구분문자가 1개인 경우)
    istringstream iss(parseStr);
    string buffer;
    while(getline(iss, buffer, ','))
    {
        parsed.push_back(buffer);
    }
    print_vector<string>(parsed);

    parsed.clear();
    // 2) string.find를 사용하여 콤마의 위치를 찾아 파싱
    int start = 0;
    int pos = parseStr.find(',', start);   // 맨 처음 콤마가 나오는 위치 index 얻기
    buffer = parseStr.substr(start, pos-start);
    parsed.push_back(buffer);
    while(pos != string::npos)      // npos: (상식) 어떤 연산이 실패했을시 반환되는 맴버함수의 리턴값
    {
        start = pos+1;
        pos = parseStr.find(',', start);
        buffer = parseStr.substr(start, pos-start);
        parsed.push_back(buffer);
    }
    print_vector<string>(parsed);

    parsed.clear();
    // 2-2) 구분 문자가 여러개인 경우 (,!?#)
    const int INF = 987654321;
    start = 0; pos = INF;
    string divisors = ",!?#";
    for(char c : divisors)
    {
        size_t temp = parseStr.find(c, start);   // 맨 처음 구분자가 나오는 위치 index 얻기
        if(temp != string::npos)
        {
            pos = min(pos, (int)temp);
        }          
    }
    buffer = parseStr.substr(start, pos-start);
    parsed.push_back(buffer);
    while(pos != INF)      // npos: (상식) 어떤 연산이 실패했을시 반환되는 맴버함수의 리턴값
    {
        start = pos+1;
        pos = INF;
        for(char c : divisors)
        {
            size_t temp = parseStr.find(c, start);   // 맨 처음 구분자가 나오는 위치 index 얻기
            if(temp != string::npos)
            {
                pos = min(pos, (int)temp);
            }
        }
        buffer = parseStr.substr(start, pos-start);
        parsed.push_back(buffer);
    }
    print_vector<string>(parsed);

    parsed.clear();
    // 3) std::find 사용
    auto start_iter = parseStr.begin();
    auto pos_iter = find(start_iter, parseStr.end(), ',');    // iterator 얻기 (주의: start_iter에서 시작하도록 하자 습관처럼 begin() 쓰다간 무한 루프 걸림)
    string newbuff;
    copy(start_iter, pos_iter, back_inserter(newbuff));     // std::back_inserter : 공간 할당하면서 삽입한다
    parsed.push_back(newbuff);
    newbuff.clear();    // 이어서 back_inserter 사용할 것이므로 다시 비워둔다
    while(pos_iter != parseStr.end())
    {
        start_iter = pos_iter + 1;
        pos_iter = find(start_iter, parseStr.end(), ',');
        copy(start_iter, pos_iter, back_inserter(newbuff));
        parsed.push_back(newbuff);
        newbuff.clear();
    }
    print_vector<string>(parsed);

    parsed.clear();
    // 3-2) std::find , 구분자 여럿일 때
    auto start_it = parseStr.begin();
    auto pos_it = parseStr.end();
    auto dist = distance(start_it, pos_it);
    (string)divisors = ",!?#";
    for(char c : divisors)
    {
        auto temp_it = find(start_it, parseStr.end(), c);
        if(distance(start_it, temp_it) < dist)
        {
            dist = distance(start_it, temp_it);
            pos_it = temp_it;
        }
    }
    copy(start_it, pos_it, back_inserter(newbuff));
    parsed.push_back(newbuff);
    newbuff.clear();
    while(pos_it != parseStr.end())
    {
        start_it = pos_it+1;
        pos_it = parseStr.end();
        dist = distance(start_it, pos_it);
        for(char c : divisors)
        {
            auto temp_it = find(start_it, parseStr.end(), c);
            if(distance(start_it, temp_it) < dist)
            {
                dist = distance(start_it, temp_it);
                pos_it = temp_it;
            }
        }
        copy(start_it, pos_it, back_inserter(newbuff));
        parsed.push_back(newbuff);
        newbuff.clear();
    }
    print_vector<string>(parsed);

    return 0;
}