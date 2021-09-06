/*
복서 정렬하기
https://programmers.co.kr/learn/courses/30/lessons/85002

복서 선수들의 몸무게 weights와, 복서 선수들의 전적을 나타내는 head2head가 매개변수로 주어집니다. 
복서 선수들의 번호를 다음과 같은 순서로 정렬한 후 return 하도록 solution 함수를 완성해주세요.

1. 전체 승률이 높은 복서의 번호가 앞쪽으로 갑니다. 아직 다른 복서랑 붙어본 적이 없는 복서의 승률은 0%로 취급합니다.
2. 승률이 동일한 복서의 번호들 중에서는 자신보다 몸무게가 무거운 복서를 이긴 횟수가 많은 복서의 번호가 앞쪽으로 갑니다.
3. 자신보다 무거운 복서를 이긴 횟수까지 동일한 복서의 번호들 중에서는 자기 몸무게가 무거운 복서의 번호가 앞쪽으로 갑니다.
4. 자기 몸무게까지 동일한 복서의 번호들 중에서는 작은 번호가 앞쪽으로 갑니다.

!!!:
weights의 길이는 2 이상 1,000 이하입니다.
weights의 모든 값은 45 이상 150 이하의 정수입니다.
weights[i] 는 i+1번 복서의 몸무게(kg)를 의미합니다.
head2head의 길이는 weights의 길이와 같습니다.
head2head의 모든 문자열은 길이가 weights의 길이와 동일하며, 'N', 'W', 'L'로 이루어진 문자열입니다.
head2head[i] 는 i+1번 복서의 전적을 의미하며, head2head[i][j]는 i+1번 복서와 j+1번 복서의 매치 결과를 의미합니다.
'N' (None)은 두 복서가 아직 붙어본 적이 없음을 의미합니다.
'W' (Win)는 i+1번 복서가 j+1번 복서를 이겼음을 의미합니다.
'L' (Lose)는 i+1번 복사가 j+1번 복서에게 졌음을 의미합니다.
임의의 i에 대해서 head2head[i][i] 는 항상 'N'입니다. 자기 자신과 싸울 수는 없기 때문입니다.
임의의 i, j에 대해서 head2head[i][j] = 'W' 이면, head2head[j][i] = 'L'입니다.
임의의 i, j에 대해서 head2head[i][j] = 'L' 이면, head2head[j][i] = 'W'입니다.

시도1)
승률 계산을 잘 못해서 테스트 케이스 틀린게 많이 나옴
승률 = 승/경기횟수 --> 안 싸운 경우는 경기횟수에 치지 않는다.

*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct boxer
{
    int id;
    int weight;
    double win_rate;
    int win_overweights;
};

pair<double, int> get_wins(vector<string>& head2head, vector<int>& weights, int id)
{
    pair<double, int> ret;
    int wins = 0;
    int win_overweights = 0;
    int matches = head2head[id].size();
    for(int i=0; i<head2head[id].size(); ++i)
    {
        if(head2head[id][i] == 'W')
        {
            wins++;
            // 자기 보다 무거운 사람 이긴 경우
            if(weights[id] < weights[i])
                win_overweights++;
        }
        if(head2head[id][i] == 'N')
            matches--;
    }
    if(matches == 0)
        ret = {(double)0, win_overweights};
    else
        ret = {(double)wins/matches, win_overweights};
    return ret;
}

vector<int> solution(vector<int> weights, vector<string> head2head) {
    vector<int> answer;

    int N = weights.size();
    vector<boxer> boxers(N);
    for(int i=0; i<N; ++i)
    {
        boxers[i].id = i;
        boxers[i].weight = weights[i];
        auto win_info = get_wins(head2head, weights, i);
        boxers[i].win_rate = win_info.first;
        boxers[i].win_overweights = win_info.second;
    }

    sort(boxers.begin(),boxers.end(), [](auto back, auto front){
        // 1. 전체 승률이 높은 복서의 번호가 앞쪽으로 갑니다
        if(back.win_rate == front.win_rate) 
        {   // 2. 승률이 동일한 복서의 번호들 중에서는 자신보다 몸무게가 무거운 복서를 이긴 횟수가 많은 복서의 번호가 앞쪽으로 갑니다
            if(back.win_overweights == front.win_overweights)
            {   // 3. 자신보다 무거운 복서를 이긴 횟수까지 동일한 복서의 번호들 중에서는 자기 몸무게가 무거운 복서의 번호가 앞쪽으로 갑니다.
                if(back.weight == front.weight)
                {   // 4. 자기 몸무게까지 동일한 복서의 번호들 중에서는 작은 번호가 앞쪽으로 갑니다.
                    return back.id < front.id;
                }
                else
                    return back.weight > front.weight;
            }
            else
                return back.win_overweights > front.win_overweights;
        }
        else
            return back.win_rate > front.win_rate;
    });
    
    for(auto e: boxers)
        answer.push_back(e.id+1);

    return answer;
}

int main()
{
    vector<int> weights = {60, 70, 60};
    vector<string> head2head = {"NNN", "NNN", "NNN"};

    solution(weights, head2head);

    return 0;
}