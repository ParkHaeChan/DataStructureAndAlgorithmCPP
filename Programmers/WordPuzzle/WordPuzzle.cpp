#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
DP[t문자열 길이] = 사용한 최소 단어 조각 수
DP[문자열 길이] = DP[문자열 길이-(1,2,3,4,5)] + 각 경우 나머지 글자길이 커버 가능하면 + 1 (단어조각 최대 길이가 5임)
*/

void printDP(const vector<int>& DP)
{
    for(int i=0; i<DP.size(); ++i)
    {
        cout << DP[i];
        if(i != DP.size()-1)
            cout << " ";
        else
            cout << endl;
    }
}

int solution(vector<string> strs, string t)
{
    int answer = 0;
    const int INF = 987654321;
    int N = t.size();
    vector<int> DP(N+1, INF);
    
    // 초기 값: 각 단어 조각 시도하여 가능한 경우
    DP[0] = 0;
    for(int w=0; w<strs.size(); ++w)
    {
        if(t.substr(0, strs[w].size()) == strs[w])
        {    
            DP[strs[w].size()] = 1;
        }
    }

    // 한 글자씩 늘려가며 DP테이블 채운다.
    for(int i=1; i<=N; ++i)
    {
        for(int k=1; k<=5; ++k) // 각 단어는 최대 5글자로 구성
        {
            int start = 0;  // 검사 시작 위치
            if(i > k)
            {
                start = i-k;
            }
            //단어 조각 중에 가능한 경우가 있는지 확인
            for(int w=0; w<strs.size(); ++w)
            {
                if(t.substr(start, k) == strs[w])
                {    
                    if(start == 0)
                        DP[i] = 1;
                    else
                        DP[i] = min(DP[i], DP[i-k] + 1);
                }
            }
        }
    }
    printDP(DP);



    return answer;
}

int main()
{
    string t = "banana";
    vector<string> strs = {"ba","an","nan","ban","n"};

    cout << solution(strs, t);

    return 0;
}