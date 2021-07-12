#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

/*
i번째 위치부터 n-1번째 위치(t문자열끝)까지의 문자열을 만드는 데 필요한 최소 단어조각의 개수를 dp[i].

dp[i] = min(dp[i+1], dp[i+2], dp[i+3], ... , dp[i+5])+1 
단, 값을 가져올 때는 해당 거리만큼을 단어 조각으로 채울 수 있어야 합니다.

끝에서(N-1) 부터 계산해 나간다. (dp[N] = 0으로 가정)
*/


int solution(vector<string> strs, string t)
{
    int answer = 0;
    const int INF = 987654321;
    int N = t.size();
    vector<int> dp(N+1, INF);
    set<string> set_strs(strs.begin(), strs.end());
    // dp[i]: i~N-1(t의 끝)까지 사용한 최소 단어수
    dp[N] = 0; // (t: 끝의 뒤)
    
    // dp[i]를 i위치 부터 끝까지의 최소 값으로 정의 했으므로 뒤에서 부터 계산해 나간다.
    for(int i=N-1; i>=0; --i)
    {
        // dp[i] = min(dp[i], dp[i+(k = 1,2,3,4,5: 단어 조각 최대 길이까지)]+1)
        for(int k=1; k<=5; ++k)
        {
            //검사할 단어가 t의 마지막 index를 넘으면 안됨
            if(i+k > N)
                break;
                
            /*k길이의 단어 조각중 가능한 경우 (여기서 아마 효율성 테스트 통과 못하는 듯 함)
            for(auto word : strs)
            {
                if(t.substr(i, k) == word)
                {
                    dp[i] = min(dp[i], dp[i+k]+1);
                    break;
                }
            }
            */
            if(set_strs.find(t.substr(i,k)) != set_strs.end())
            {
                dp[i] = min(dp[i], dp[i+k]+1);
            }
        }
    }
    answer = dp[0];
    if(answer == INF)
        return -1;
    else
        return answer;
}