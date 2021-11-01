/*
피로도
https://programmers.co.kr/learn/courses/30/lessons/87946

?:
유저의 현재 피로도 k와 각 던전별 "최소 필요 피로도", "소모 피로도"가 담긴 2차원 배열 dungeons 가 매개변수로 주어질 때, 
유저가 탐험할수 있는 최대 던전 수를 return 하도록 solution 함수를 완성해주세요.

!!!:
k는 1 이상 5,000 이하인 자연수입니다.
dungeons의 세로(행) 길이(즉, 던전의 개수)는 1 이상 8 이하입니다.
dungeons의 가로(열) 길이는 2 입니다.
dungeons의 각 행은 각 던전의 ["최소 필요 피로도", "소모 피로도"] 입니다.
"최소 필요 피로도"는 항상 "소모 피로도"보다 크거나 같습니다.
"최소 필요 피로도"와 "소모 피로도"는 1 이상 1,000 이하인 자연수입니다.
서로 다른 던전의 ["최소 필요 피로도", "소모 피로도"]가 서로 같을 수 있습니다.

시도1)
입력의 크기가 매우 작고(1~8) 모든 경우를 시도해봐야하는 구조이다.
완전탐색을 시도한다.
N개의 던전을 탐색하는 모든 순열을 시도한다. (next_permutation)
가능한 최대치를 찾는다.

*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int k, vector<vector<int>> dungeons) {
    int answer = 0;

    int N = dungeons.size();

    vector<int> procedures;
    for(int i=0; i<N; ++i)
    {
        procedures.push_back(i);
    }

    do
    {
        int K = k;
        int sum = 0;
        // procedures의 순서로 던전을 진행
        for(int p=0; p<N; ++p)
        {
            int cur = procedures[p];
            if(K >= dungeons[cur][0])
            {
                K -= dungeons[cur][1];
                sum++;
            }
            else
                break;
        }
        // 이때까지 탐험한 던전 수를 갱신
        answer = max(answer, sum);

    } while (next_permutation(procedures.begin(), procedures.end()));

    return answer;
}

int main()
{
    int k = 80;
    vector<vector<int>> dungeons = {{80,20},{50,40},{30,10}};
    solution(k, dungeons);

    return 0;
}