// 구현 문제: 소수 찾기, 자료형 범위, 진법 변환
#include <string>
#include <vector>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

vector<string> parse_input(string& input)
{
    vector<string> ret;
    istringstream iss(input);
    string buff;
    while(getline(iss, buff, '0'))
    {
        ret.push_back(buff);
    }
    return ret;
}

bool is_prime(long long n)
{
    if(n < 2)
        return false;

    for(long long i=2; i*i<=n; ++i)
    {
        if(n%i == 0)
            return false;
    }
    return true;
}

int solution(int n, int k) {
    int answer = 0;

    // n을 k진수로 바꾼다
    int temp_n = n;
    string knum = "";
    stack<int> numStack;
    while(temp_n > 0)
    {
        numStack.push(temp_n%k);
        temp_n /= k;
    }
    while(!numStack.empty())
    {
        knum += to_string(numStack.top());
        numStack.pop();
    }
    vector<string> parsed = parse_input(knum);
    for(auto str : parsed)
    {
        if(str.empty())
            continue;
        if(is_prime(stoll(str)))
            answer++;
    }

    return answer;
}

int main()
{
    int n = 437674;
    int k = 3;
    solution(n, k);

    return 0;
}