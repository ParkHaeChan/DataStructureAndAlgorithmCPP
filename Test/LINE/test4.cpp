#include <string>
#include <vector>

using namespace std;

vector<bool> IsPrime(1000001, true);

int prime_divisor(int n)
{   // n 
    for(int i=2; i<=n; ++i)
    {
        if(IsPrime[i])
        {
            if(n%i == 0)
                return i;
        }
    }
}

vector<int> recur(vector<int> arr)
{
    int p = prime_divisor(arr.size());
    int len = arr.size()/p;
    if(len == 1)
        return arr;
    vector<vector<int>> dived(len);

    int cnt=0;
    for(int i=0; i<arr.size(); ++i)
    {
        dived[cnt++].push_back(arr[i]);
        cnt %= len;
    }

    for(int i=0; i<len; ++i)
    {
        dived[i] = recur(dived[i]);
    }

    vector<int> ret;
    for(int d=0; d<dived.size(); ++d)
        for(int i=0; i<dived[i].size(); ++i)
        {
            ret.push_back(dived[d][i]);
        }

    return ret;
}

vector<int> solution(int n) {
    vector<int> answer;
    IsPrime[0] = false;
    IsPrime[1] = false;
    for(int i=2; i*i <= 1000000; ++i)
    {
        IsPrime[i] = true;
        int temp = 2;
        while(temp*i <= 1000000)
        {
            IsPrime[i*temp] = false;
            temp++;
        }
    }

    vector<int> arr;
    for(int i=1; i<=n; ++i)
        arr.push_back(i);
    
    answer = recur(arr);

    return answer;
}

int main()
{
    int n = 12;

    solution(n);

    return 0;
}