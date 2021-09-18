/*
시도1) 이번에 들어온 사람 이후로 온 사람 set에 저장한 뒤
이번에 들어온 사람이 나가기 전에 나간 사람이 set에 포함되어 있는지 확인
--> 이번에 들어온 사람이 나간 후라도 만난 것을 확정할 수 있는 경우가 있다 (테스트 케이스 2번 참고)

즉, 만난 경우는 두 가지 경우를 고려해야 한다.
1) 이번에 들어온 사람이 들어온 후 들어왔는데 이번에 온 사람이 나가기 전에 나간 경우
2) 이번에 들어온 사람이 들어오기 전에 들어왔는데 이번에 온 사람이 나가고 나서 나간 경우
추가로 간접적으로 알 수 있는 경우도 고려해야 한다.
이번에 들어온 사람이 들어온 후 들어왔는데 이번에 온사람이 나가고 나간 사람 중에서도
이번에 온 사람이 들어온 후 들어온 뒤 이번에 온 사람이 나가기 전에 나간 사람보다 일찍 온 사람이면
이번에 들어온 사람과 만난 것을 알 수 있다.
이렇게 되면 구현이 복잡해진다 다른 방법을 생각해봤다

시도2) 들어온 순서대로 시간을 부여하고 나가는 시간을 재구성해본다
1 4 2 3 / 2 1 3 4 의 경우
1 2 3 4 시간에 들어왔다고 가정하면,
나간 시간은 최소
3 3 4 4 가 된다 max(self start time, 자기보다 먼저 나간 사람의 시각)
1은 4, 2 2명과 마주쳤고,
2는 1, 4와 마주쳤고,
3은 4와 마주쳤고,
4는 1,2,3과 마주친 것을 알 수 있다.

1 4 2 3 / 2 1 4 3 의 경우
1 2 3 4 / 3 3 3 4 가 된다
1은 들어온 시간과 나간 시간이 1~3이므로 이 사이에 존재하는 4,2와 만난다
2는 3~3이므로 3에 나간 경우를 보면 본인 제외하고 1, 4와 만난다
3은 4~4이므로 4에 나간 경우는 본인만 존재하므로 아무도 안만날 수도 있다
4는 2~3이므로 2이전에 있던 1과, 3이전에 나간 2를 만난다

in_time에서 out_time 사이에 채류한 사람
in_time 이전에 들어와서 out_time 전에 나간 경우
in_time 이전에 들어와서 out_time 이후에 나간 경우
주의) in_time 이전에 들어와서 in_time 전에 나간 사람은 못 만난다
in_time 이후에 들어와서 out_time 전에 나간 경우
in_time 이후에 들어와서 out_time 후에 나간 경우
주의) out_time 이후에 들어온 경우는 못 만난다.

정리하고 보니 시도1 에서 조건만 잘 방어했으면 풀 수 있는 문제였다...
굳이 시간을 적용할 필요는 없다.
이번에 들어온 사람 이전에 들어온 사람들을 set에 넣었다가,
이번에 들어온 사람이 들어오기 전에 나간 사람을 set에서 삭제하면 된다...
나머지도 같은 방식으로하면 됨
*/

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

vector<int> solution(vector<int> enter, vector<int> leave) {
    vector<int> answer(enter.size(), 0);

    map<int,int> enter_with_time;
    for(int in = 0; in<enter.size(); ++in)
    {
        enter_with_time[enter[in]] = in+1;   // {사람번호, 시간}
    }
    map<int,int> out_with_time;
    int last_time = -1;
    for(int out=0; out<leave.size(); ++out)
    {
        int leave_time = max(last_time, enter_with_time[leave[out]]);  // {이전 사람 나간 시간, 자기 들어온 시간 시간}
        out_with_time[leave[out]] = leave_time;
        last_time = leave_time;
    }
    // 각 사람에 대해 들어온 시간 이후에 들어오면서 동시에 나간시간 이전에 나간 사람의 수를 센다
    for(int p=1; p <= enter.size(); ++p)
    {
        int in_time = enter_with_time[p];
        int out_time = out_with_time[p];
        set<int> peopleset;
        // in_time에서 out_time 사이에 채류한 사람
        for(int op=1; op <= enter.size(); ++op)
        {
            if(p == op)
                continue;
            int other_in_time = enter_with_time[op];
            int other_out_time = out_with_time[op];
            if(other_in_time <= in_time && other_out_time >= in_time)
                peopleset.insert(op);
            else if(in_time <= other_in_time && other_in_time <= out_time)
                peopleset.insert(op);
        }
        answer[p-1] = peopleset.size();
    }

    return answer;
}