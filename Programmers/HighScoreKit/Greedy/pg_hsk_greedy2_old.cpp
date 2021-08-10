// 문제가 개편되었습니다. 이로 인해 함수 구성이나 테스트케이스가 변경되어, 과거의 코드는 동작하지 않을 수 있습니다.
// 새로운 함수 구성을 적용하려면 [코드 초기화] 버튼을 누르세요. 단, [코드 초기화] 버튼을 누르면 작성 중인 코드는 사라집니다.
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string name) {
    int answer = 0;

    int first = name[0] - 'A';
    first = first > 26-first ? 26-first : first;
    string allA;
    int N = name.size();
    int last = first;
    bool flag = false;
    //오른쪽 시작
    int rsum = first;
    int rback = 0;
    for(int i=1; i<N; ++i)
    {
        int cur = name[i] - 'A';
        //A가 연속으로 많이 나와서 돌아가는게 더 나을 경우
        if(cur == 0 && i < N-1 && last != 0)
        {
            int idx = i+1;
            int cnt = 1;
            while(name[idx] == 'A')
            {
                idx++;
                cnt++;
            }
            if(cnt > i)  //돌아가는게 나을 경우
            {
                rback = rsum + i-1; //여기에 lsum 더할 것.
                flag = true;
                break;
            }
        }
        if(name.substr(i, N-i) == allA.assign(N-i,'A')) //남은게 모두 A일 경우
            break;
        rsum++; // 오른쪽이동
        cur = cur > 26-cur ? 26-cur : cur;
        rsum += cur;
        last = cur;
    }
    //왼쪽으로 돌아서 진행하는 경우
    int lsum = first;
    int lback = 0;
    last = first;
    for(int i=N-1; i>= 1; --i)
    {
        int cur = name[i] - 'A';
        //A가 연속으로 많이 나와서 돌아가는게 더 나을 경우
        if(cur == 0 && i > 0 && last != 0)
        {
            int idx = i-1;
            int cnt = 1;
            while(name[idx] == 'A')
            {
                idx--;
                cnt++;
            }
            if(cnt > N-i)  //돌아가는게 나을 경우
            {
                lback = lsum + (N-1)-i; //여기에 rsum 더할 것.
                flag = true;
                break;
            }
        }
        if(name.substr(1, i) == allA.assign(i,'A')) //남은게 모두 A일 경우
            break;
        lsum++; // 왼쪽이동
        cur = cur > 26-cur ? 26-cur : cur;
        lsum += cur;
        last = cur;
    }
    if(flag)
    {
        cout << rback << " " << lback << endl;
        rback += lsum-first;
        lback += rsum-first;
        cout << rback << " " << lback << endl;
        int min = rback > lback ? lback : rback;
        return min;
    }
    answer = rsum > lsum ? lsum : rsum;

    
    return answer;
}