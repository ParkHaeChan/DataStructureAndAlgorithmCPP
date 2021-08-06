/*
소수 찾기
https://programmers.co.kr/learn/courses/30/lessons/42839

?:
한자리 숫자가 적힌 종이 조각이 흩어져있습니다. 흩어진 종이 조각을 붙여 소수를 몇 개 만들 수 있는지 알아내려 합니다.
각 종이 조각에 적힌 숫자가 적힌 문자열 numbers가 주어졌을 때, 종이 조각으로 만들 수 있는 소수가 몇 개인지 return 하도록 solution 함수를 완성해주세요.

!!!:
numbers는 길이 1 이상 7 이하인 문자열입니다.
numbers는 0~9까지 숫자만으로 이루어져 있습니다.
"013"은 0, 1, 3 숫자가 적힌 종이 조각이 흩어져있다는 의미입니다.

시도1)
완전탐색으로 만들수 있는 모든 경우의 수를 확인하고,
소수판별을 하여 소수임이 확인되면 set에 저장한다.
answer로 set의 크기를 반환한다.
numbers가 7이하이므로 모든 경우의 수는 7!가지가 나온다.
std::next_permutation을 활용해 보았다. 편리한건 좋은데 이걸 사용하면
입력이 "17"인 경우, 1이나 7을 고려하지 않는 문제가 있다. 즉, 현재 문자를 기준으로 다음 순열을 찾기만한다.

시도2)
재귀를 사용한 완전 탐색을 구현한다
처음 입력을 정렬한 후 문자열 각 위치를 사용할지 안할지를 결정하며 재귀를 진행한다.
이때 매번 들어갈 때 마다 구성된 문자열로 소수판별을 시도하면, 만들 수 있는 모든 길이의 문자열에 대해 시도해본 것이 된다.

시도3) 123으로 시도해봤는데 소수 23이 안잡힌다.
교환할 때 문제가 발생한 것 같다. 살펴보니 교환은 제대로 했는데
그전에 다시 정렬을 해둬야 제대로 다음 상태로 진행할 수 있다는 것을 간과했다.

시도4) 몇몇 case가 아직 통과가 안된다.
교환하지 않는 경우로 넘길 때 같은 경우만 제외하고 작은 경우로는 시도해 봐야한다.
그렇지 않으면, 123이 입력인 경우 31같은 경우는 시도하지 않게 된다
그리고 반복문 내부에서 정렬할 때는 depth+1부터 정렬해야한다.
위에 그대로 begin()+depth부터 정렬해서 문제 생긴것이었다.
통과함...
*/

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

// 소수 판별
bool isPrime(int n)
{
    if(n < 2)
        return false;
    if(n == 2)
        return true;

    for(int i=2; i*i<=n; ++i)
    {
        if(n%i == 0)
            return false;
    }
    return true;
}

void recur(string& numbers, string& constructed, set<int>& primes, int depth)
{
    //탈출 조건 : construced.size()가 아닌 depth로 비교해야 제대로 작동한다.
    if(depth == numbers.size())
    {   // 소수판별하고 종료
        if(constructed.size() > 0)
        {
            int n = stoi(constructed);
            if(isPrime(n))
                primes.insert(n);
        }
        return;
    }

    // 이번 것 추가한 경우
    int original_length = constructed.size();   // 원상복구 위해 원본길이 저장
    constructed += numbers[depth];
    recur(numbers, constructed, primes, depth+1);
    // 이번것으로 시작하는 경우를 모두 수행하였으므로 돌아오면 다시 정렬해둔다.
    sort(numbers.begin()+depth, numbers.end());

    // 이번 것 추가하지 않은 경우
    //constructed -= numbers[i]; 이렇게 못쓰니까 좀 아쉽다...
    constructed = constructed.substr(0, original_length);   // 원상복구
    recur(numbers, constructed, primes, depth+1);
    // 이번것으로 시작하는 경우를 모두 수행하였으므로 돌아오면 다시 정렬해둔다.
    sort(numbers.begin()+depth, numbers.end());

    // 자리를 바꿔서 진행
    for(int i = depth+1; i<numbers.size(); ++i)
    {
        // 같거나 작은 경우는 중복을 발생시킨다 --> (X): 작은 경우도 시도해야 X(depth),2,1,...으로 된 case가 나온다. 아니면 X이후로는 오름차순만 고려된다.
        // 같은 경우만 거른다
        if(numbers[depth] == numbers[i])
            continue;
        
        // 보다 큰 수면 자리 바꿈
        if(numbers[depth] < numbers[i])
            swap(numbers[depth] , numbers[i]);

        // 바꾼 상태로 깊이 원상복귀하여 시도 --> (X) 깊이가 증가해야 무한루프 방지됨
        int original_length = constructed.size();
        constructed += numbers[depth];
        recur(numbers, constructed, primes, depth+1);
        // 이번것으로 시작하는 경우를 모두 수행하였으므로 돌아오면 다시 정렬해둔다.
        // 시도4) 반복문 안에서는 depth+1부터 정렬해야한다
        sort(numbers.begin()+depth+1, numbers.end());

        // 이번 것 추가하지 않은 경우
        constructed = constructed.substr(0, original_length);
        recur(numbers, constructed, primes, depth+1);
        // 이번것으로 시작하는 경우를 모두 수행하였으므로 돌아오면 다시 정렬해둔다.
        // 시도4) 반복문 안에서는 depth+1부터 정렬해야한다
        sort(numbers.begin()+depth+1, numbers.end());
    }
}

// 시도1)
// 주어진 numbers를 정렬후 cpp의 next_permutation을 활용하여 모든 경우를 만들어본다.
/*
next_permutation은 앞에 이미 큰 원소들이 배치되어 있으면 반복하지 않게 됩니다.
만약 데이터가 내림차순으로 정렬이되어 있다면 next_permutation 대신 prev_permutation을 사용하면 된다.
*/
int solution(string numbers) {
    int answer = 0;

    // numbers를 정렬한다
    sort(numbers.begin(), numbers.end());

    set<int> primes;
    string start = "";
    recur(numbers, start, primes, 0);
    /* 시도1)
    int n = stoi(start);
    if(isPrime(n))
        primes.insert(n);
    while(next_permutation(start.begin(), start.end()))
    {
        int n = stoi(start);
        if(isPrime(n))
            primes.insert(n);
    }
    */
    answer = primes.size();

    return answer;
}

int main()
{
    string numbers = "123";

    cout << solution(numbers) << endl;

    return 0;
}