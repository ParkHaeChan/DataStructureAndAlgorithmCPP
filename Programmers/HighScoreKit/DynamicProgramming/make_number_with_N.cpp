#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

/*
이 문제는 정말 많은 고민을 했다.
일단 DP로 풀 수 있다는 힌트를 가지고 시작했기에
어떻게든 최적 부분 구조와 반복되는 부분 문제가 나타나도록 상태를 정의하려 했으나
생각보다 각이 잘 나오지 않았다.
일단 brute force 방식으로 문제를 좀 더 깊이 이해해 보려고 시도했다.
처음 주어진 N으로 number가 1, 2, 3, 4, 5, ... 인 상태를 구성해 가면서 어떤 특징이
발생하는지 살펴보려 했는데, 특징적인 패턴은 N, NN, NNN 처럼 최소를 바로 구할 수 있는 경우와
(N+ ... + N)/N 처럼 어떤 숫자건 만들 수 있는 패턴 정도를 찾았으나
이외에는 딱히 쓸만한 통찰을 찾기가 어려웠다.

그래서 다음에는 막무가내로
DP[number][마지막에 적용한 연산] = 사용된 최소의 N 으로 가정해보았으나
이 경우 마지막에 적용한 연산이 전체에 대한 곱셈이나 나눗셈이면 묶어내면서 하나 줄일 수 있다는 것을
고려해야 하는데 그러면 마지막에 적용한 연산이 아니라 연산식 전체에 대한 정보가 있어야 한다.
그래서 이것도 아닌것 같아서 다른 방식이 뭔지 고민하다가 결국 검색을 통해서 해결 방식을 알아보았다.

이 문제의 힌트는 최솟값이 8보다 크면 -1을 return 한다는 것이다.
즉, N 하나로 구성할 수 있는 경우, N 두개와 사칙연산을 통해 구성할 수 있는 경우,
..., N 8개를 사칙연산을 통해 구성할 수 있는 수를 모두 구한 뒤 이 중에 없으면 -1을 반환하고,
찾는 number가 도중에 나오면 바로 끝내는 식으로 구하면 된다.
무턱대고 DP 테이블 구성하려고 나서면 오히려 더 알기 어려운 문제가 되는 것 같다.

이렇게 되면 어디서 중복되는 부분 문제가 생기는가가 동적계획법의 관건인데,
N 3개를 통해 구성할 수 있는 수들의 집합을 예로 들면,
N 1개를 통해 구성할 수 있는 수의 집합과 N 2개를 통해 구성할 수 있는 수의 집합과의
사칙연산과, 뒤집어서 N 2개와 N 1개 순으로 사칙연산을 했을 때의 집합을 합집합한 집합이
N 3개를 통해 구성할 수 있는 수들의 집합이 된다.
(덧셈, 곱셈의 경우는 연산 순서 바꿔도 같지만 그렇게 까지 최적화에 신경쓸 필요는 없을 듯)
(그리고 연산 도중 음수가 나오더라도 다시 양수로 돌아오는 경우도 생길 수 있으니 거르지 말고 놔둬야 한다)
이전 집합을 구하면 다음 N하나가 더 추가된 상태의 집합을 구할 수 있어서
일종의 동적계획법 문제가 되는 것이다.
DP 테이블에 집착하면 해결방법이 오히려 잘 안보이는 문제라 오히려 참신한 듯 하다.
*/

int set_init(int N, int cnt)
{
    string Nstr = "";
    for(int i=0; i<cnt; ++i)
        Nstr += to_string(N);
    return stoi(Nstr);
}

int solution(int N, int number) {
    int answer = -1;    // 못 찾으면 그대로 반환됨
    if(N == number)
        return 1;   // 이 경우는 바로 출력(추가된 테스트 케이스 인듯함)
    // 아래 반복문에서는 i=1 부터 시작해서 이 경우를 고려하지 못함.
    // 그렇다고 반복문에 우겨 넣으면 따로 처리해야해서 보기가 싫음;;;
    
    // N을 1~8개를 사칙연산하여 만들 수 있는 수 저장하는 집합
    vector<set<int>> set_vect(8);
    
    // 사칙연산외에 구성할 수 있는 수는 초기화로 넣어준다
    // 각 집합의 초기값: N을 그저 나열하는 경우: N, NN, NNN, ...
    for(int i=0; i<8; ++i)
        set_vect[i].insert(set_init(N, i+1));
    
    // N을 2~8회 사용하여 만들 수 있는 수  순으로 집합을 채워 나간다.
    // (N 1회 사용한 경우는 N 뿐임)
    for(int i=1; i<8; ++i)
    {
        // i보다 작은 모든 경우와 사칙연산하여 집합을 채워야 하므로
        // 예: N을 3회 사용한 연산 = (N2회 <사칙연산> N1회), (N1회 <사칙연산> N2회) 인 경우
        for(int j=0; j<i; ++j)
        {
            // 사칙연산 적용할 두 집합
            auto set1 = set_vect[j];    // 0, 1, 2, ..., i-1
            auto set2 = set_vect[i-(j+1)];  // i-1, i-2, ..., 2, 1, 0
            
            // 두 집합 원소간 사칙연산 적용하여 새 집합에 추가
            for(auto s1 : set1)
            {
                for(auto s2 : set2)
                {
                    //원소간 사칙연산하여 집합에 추가
                    set_vect[i].insert(s1 + s2);
                    set_vect[i].insert(s1 - s2);
                    set_vect[i].insert(s1 * s2);
                    
                    // 나눗셈은 예외 처리 필요
                    if(s2 != 0)
                        set_vect[i].insert(s1 / s2);  // 제한사항에 나머지는 무시한다함
                }
            }
        }
        //찾는 수가 이번 집합에서 발견되면 끝
        if(set_vect[i].find(number) != set_vect[i].end())
        {
            answer = i+1; // i는 index라 0부터 시작해서 실제론 +1 해야됨
            break;
        }
    }
    
    return answer;
}

int main()
{
    int N = 5;
    int number = 12;

    cout << solution(N, number) << endl;

    return 0;
}