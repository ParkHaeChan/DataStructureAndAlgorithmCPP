/*
보석 쇼핑
https://programmers.co.kr/learn/courses/30/lessons/67258

진열된 모든 종류의 보석을 적어도 1개 이상 포함하는 가장 짧은 구간을 찾아서 구매

예를 들어 아래 진열대는 4종류의 보석(RUBY, DIA, EMERALD, SAPPHIRE) 8개가 진열된 예시입니다.

진열대 번호	1	2	    3	    4	5	6	    7	        8
보석 이름	DIA	RUBY	RUBY	DIA	DIA	EMERALD	SAPPHIRE	DIA
진열대의 3번부터 7번까지 5개의 보석을 구매하면 모든 종류의 보석을 적어도 하나 이상씩 포함하게 됩니다.

진열대의 3, 4, 6, 7번의 보석만 구매하는 것은 중간에 특정 구간(5번)이 빠지게 되므로 어피치의 쇼핑 습관에 맞지 않습니다.

진열대 번호 순서대로 보석들의 이름이 저장된 배열 gems가 매개변수로 주어집니다. 
이때 모든 보석을 하나 이상 포함하는 가장 짧은 구간을 찾아서 return 하도록 solution 함수를 완성해주세요.
가장 짧은 구간의 시작 진열대 번호와 끝 진열대 번호를 차례대로 배열에 담아서 return 하도록 하며, 
만약 가장 짧은 구간이 여러 개라면 시작 진열대 번호가 가장 작은 구간을 return 합니다.

!!!:
gems 배열의 크기는 1 이상 100,000 이하입니다.
gems 배열의 각 원소는 진열대에 나열된 보석을 나타냅니다.
gems 배열에는 1번 진열대부터 진열대 번호 순서대로 보석이름이 차례대로 저장되어 있습니다.
gems 배열의 각 원소는 길이가 1 이상 10 이하인 알파벳 대문자로만 구성된 문자열입니다.

시도1)
문제의 특성상 이것도 일종의 그리디 문제일 것이라는 예감이든다.
가장 짧은 구간이면서 가장 빠른 번호인 점이 힌트이다.
일단은 전체 vector를 돌면서 보석의 종류가 몇가지 있는지 set이나 map을 통해 알아보고,

다음으로는 이 vector를 앞에서 부터 차례로 모든 보석 가지수가 포함된 최소 구간을 확인한다.
모든 경우를 고려하면 최대 10만이므로 각 위치에서 시작하는 모든 경우를 고려하면 시간 초과가 난다.

고민을 해본 결과, 분할 정복법 2분 탐색을 시도해 볼 수 있을 것 같다.
반으로 나눈 절반중 앞에 모든 경우가 존재하는 경우, 뒤에 존재하는 경우, 둘 모두에 존재하지 않는 경우로 나눠서
분할 정복을 실행한다.
점수: 15... 효율성 테스트 실패, 테스트 케이스 절반 탈락
효율성 테스트 통과가 안되니 그 부분부터 공략해본다.

시도2)
파라매트릭 서치 방식으로 재귀를 수행하도록 변경.
가능한 경우만 재귀 진입하는 것 까진 같은데, 불가능한 경우는 반의 반을 늘리고,
가능한 경우는 반으로 줄이는 식으로 진행
여전히 효율성 테스트 통과가 안되고 많은 테스트 케이스에서 실패한다

시도3)
해설 참고하였다 투포인터 방식을 이용한다는 것을 확인...
start, end = 0에서 모든 경우가 포함될 때까지 end를 증가시킨 후,
모든 경우가 포함되면 모든 경우가 포함되는게 유지될 때 까지 start를 줄인다.
그러면서 가능한 최저길이가 나오면 저장한다. end가 gems의 끝까지 갈때까지 시도한다.
*/

#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct range
{
    int start;
    int end;
    int length;
};

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    set<string> gem_types;

    for(string& str: gems)
        gem_types.insert(str);

    int SIZE = gems.size();
    if(gem_types.size() == 1)
        return {1,1};

    int start = 0;
    int end = 0;
    int min_length = 100001;    // 입력이 10만까지 가능
    map<string, int> gemMap;
    while(end < SIZE)
    {
        // 모든 경우를 커버할 때까지 end를 늘려 나간다
        gemMap[gems[end++]]++;
        if(gemMap.size() != gem_types.size())
            continue;

        // 모든 경우를 유지하고 있을 떄 까지 start를 늘려 나간다
        while(gemMap[gems[start]] > 1)  // 1인 경우는 빼면 종류 수가 깨진다
            gemMap[gems[start++]]--;
        
        // 종류 수가 깨지는 start를 찾았으므로 저장한다
        gemMap.erase(gems[start++]);  // map에서 삭제(end를 늘려가며 다시 찾는다)
        if(min_length > end-start)  // 같은 경우는 start가 작은 것을 쓰므로 갱신X
        {
            min_length = end-start;
            answer = {start, end};
        }
    }
    return answer;
}

int main()
{
    vector<string> gems = {"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"};
    //vector<string> gems = {"AA", "AB", "AC", "AA", "AC"};
    //vector<string> gems = {"XYZ", "XYZ", "XYZ"};
    //vector<string> gems = {"ZZZ", "YYY", "NNNN", "YYY", "BBB"};
    solution(gems);

    return 0;
}