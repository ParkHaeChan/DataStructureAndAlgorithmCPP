/*
캐시
https://programmers.co.kr/learn/courses/30/lessons/17680

?:
DB 캐시를 적용할 때 캐시 크기에 따른 실행시간 측정 프로그램을 작성하시오.

입력 형식
캐시 크기(cacheSize)와 도시이름 배열(cities)을 입력받는다.
cacheSize는 정수이며, 범위는 0 ≦ cacheSize ≦ 30 이다.
cities는 도시 이름으로 이뤄진 문자열 배열로, 최대 도시 수는 100,000개이다.
각 도시 이름은 공백, 숫자, 특수문자 등이 없는 영문자로 구성되며, 대소문자 구분을 하지 않는다. 도시 이름은 최대 20자로 이루어져 있다.

출력 형식
입력된 도시이름 배열을 순서대로 처리할 때, "총 실행시간"을 출력한다.

!!!:
캐시 교체 알고리즘은 LRU(Least Recently Used)를 사용한다.
cache hit일 경우 실행시간은 1이다.
cache miss일 경우 실행시간은 5이다.

시도1)
O(N)으로 LRU구현하여 사용했다. 
unordered_map이라 키입력 순으로 저장된다.
즉, 이 순서로 최저 사용 수만 만족하면 뒤에 값을 삭제하면 된다.
50점 (시간초과는 안뜨고 실패라 나옴)
LRU를 제일 적게 쓰인 순 중 젤 최근에 안쓰인 것을 삭제라고 착각해서 그런 듯

시도2)
LRU 제대로 파악하였을 때, deque 자료구조가 더 적절해 보여서 변경
set으로 캐시힛 여부를 log 시간에 파악하고,
실제 캐시 상태는 앞뒤로 추가, 삭제 가능한 deque로 시뮬레이션한다.
통과
*/

#include <string>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>

using namespace std;

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;

    if(cacheSize == 0)
        return cities.size() * 5;

    set<string> cache;
    deque<string> mem_state;
    const int INF = 987654321;
    
    for(auto e: cities)
    {   // 소문자로 변환
        transform(e.begin(), e.end(), e.begin(), [](auto c){
           return tolower(c); 
        });
        
        // 캐시 힛
        if(cache.find(e) != cache.end())
        {   // 제일 최근 사용된 캐시를 상단에 올리는 작업
            auto it = find(mem_state.begin(), mem_state.end(), e);
            mem_state.erase(it);
            mem_state.push_front(e);
            answer += 1;
            continue;
        }
        // 찾는데 없으면
        // 캐시가 꽉찬 경우 LRU(Least Recently Used) 순으로 삭제
        if(cache.size() == cacheSize)
        {   // 캐시 메모리 상에서 젤 뒤에 있는것 삭제
            string todel = mem_state.back(); mem_state.pop_back();
            cache.erase(todel); // set에서도 삭제
        }
        // 캐시에 추가
        answer += 5;
        cache.insert(e);
        mem_state.push_front(e);
    }

    return answer;
}

int main()
{
    int size = 3;
    vector<string> cities = {"Jeju", "Pangyo", "Seoul", "NewYork", "LA", "Jeju", "Pangyo", "Seoul", "NewYork", "LA"};

    solution(size, cities);

    return 0;
}