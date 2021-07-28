/*
해설은 이전과 같고 코드를 정리함
통과 됨
*/
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;

    // 심사관 정렬
    sort(times.begin(), times.end());

    // 초기값 설정
    long long min_time = times[0];  // 1명 처리 최단 시간
    long long last_time = times[0]*2; // 임시 이전값 (하한일 경우만 갱신)
    
    // 특수 case 처리
    if(n == 1)
        return min_time;
    
    // 탐색 종료 조건: min_time이 수렴
    while(abs(min_time-last_time) > 0)
    {
        int sum = 0;
        for(int i=0; i<times.size(); ++i)
        {
            long long temp = min_time/(times[i]);
            if(temp > 0)
                sum += temp;
            else
                break;
        }
        if(sum >= n)    // 크거나 같으면 시간 줄이기를 시도해 본다.
        {
            if((min_time-last_time) == 1)
                break;  // last_time으로는 불가능했으므로 1밖에 차이 안나면 mid_time이 last_time과 같아지므로 여기서 종료해야 한다.
            long long mid_time = (min_time+last_time)/2;
            min_time = mid_time;
        }
        else
        {   // last_time을 여기서만 저장하는 이유: 위 if문 내에서 last_time을 갱신하면 이미 sum을 넘은 값을 하한으로 저장하는 문제가 발생한다.
            last_time = min_time;
            min_time *= 2;
        }
    }
    answer = min_time;

    return answer;
}

int main()
{
    int n = 6;
    vector<int> times = {7, 10};

    cout << solution(n, times) << endl;

    return 0;
}