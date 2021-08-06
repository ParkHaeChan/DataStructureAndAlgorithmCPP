/*
큰 수 만들기
https://programmers.co.kr/learn/courses/30/lessons/42883


시도5)
j의 시작은 0부터 하는게 맞다.(남은게 내림차순이 아닌 이상)
여기가 문제가 아니라, 문자열을 substr으로 매번 다시 만드는게 문자열 크기가 커지면 시간초과가 나는 원인이 되는 것 같다.
그래서 이번에는 매번 삭제한 후 새로 문자열을 만들지 않고 삭제한 위치를 따로 표시한 다음 건너 뛰고 비교하도록 바꿔보았다.
많은 변경이 발생할 것 같아서 새 파일에 작성했다.
하지만 상당히 이해하기 어려운 코드가 되는 것 같다. 게다가 이번에도 시간초과가 발생했다.

시도6) 아직도 10번에서 시간초과 된다...
도저히 모르겠어서 이전에 통과했던 것 시도해봤는데 이번엔 통과 안됐다.
힌트 살펴본 결과 앞자리가 9가 나오면 이 숫자가 삭제될 일은 없다.
즉, 9가 나온 경우는 바로 다음 숫자를 보도록 처리하면된다고한다...

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
<이 경우는 위의 9가 나온 경우를 최적화 해줘도 시간초과가 발생한다>
문자열이 많이 길어지면 삭제된 구간 표시하고 넘기는데 드는 시간이 오히려
문자열을 생성하는 것보다 더 오래걸리는 모순이 발생한다.
그냥 부분문자열 생성하는 방식으로는 아슬아슬하게 통과한다.
그 방법이 이해도 빠르고 코딩도 쉽고 여러모로 편하다.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    int N = number.size();
    vector<bool> deleted(N, false);
    bool isDecreasing = false;

    int cnt = 0, lastBackDeleted = N-1;
    while(cnt < k)
    {
        int i;
        for(i=0; i<N; ++i)
        {
            // 삭제되지 않은 위치를 찾는다
            if(deleted[i])
                continue;

            // 앞자리가 9인 경우는 삭제될 일이 99...99 인 상황 뿐이다
            if(number[i] == '9')
                continue;

            int temp = i;
            int j;
            for(j=i+1; j<N; ++j)
            {
                if(isDecreasing)
                {   // 바로 뒤에서 부터 삭제하도록 조치
                    j = N;
                    break;
                }

                // 삭제되지 않은 위치를 찾는다
                if(deleted[j])
                    continue;

                // 앞자리가 9인 경우는 삭제될 일이 99...99 인 상황 뿐이다
                if(number[temp] == '9')
                    break;

                // 인접한 두 값을 비교하여 앞에쪽이 작으면 삭제된다.
                if(number[temp] < number[j])
                {
                    deleted[temp] = true;
                    cnt++;
                    i = -1; // break로 0부터 시작하게 하려면 i를 -1로 두면된다. (Tip으로 쓸만한 듯)
                    break;
                }
                else
                {   // 뒤에쪽이 이번엔 앞에쪽이 되고 앞에쪽은 삭제되지 않은 값중에서 찾을 것
                    temp = j;
                    continue;
                }
            }
            if(cnt == k)
                break;
        }
        // 삭제되지 않고 반복문을 탈출했다면 내림차순 정렬된 상태이므로 맨뒤를 삭제한다
        if(i == N)
        {
            for(int r=lastBackDeleted; r>=0; --r)
                if(!deleted[r])
                {
                    cnt++;
                    deleted[r] = true;
                    lastBackDeleted = r;
                    break;
                }
        }
        if(cnt == k)
            break;
    }
    for(int i=0; i<N; ++i)
    {
        if(!deleted[i])
            answer += number[i];
    }

    return answer;
}

int main()
{
    string number = "4177252841";
    int k = 4;

    cout << solution(number, k) << endl;

    return 0;
}