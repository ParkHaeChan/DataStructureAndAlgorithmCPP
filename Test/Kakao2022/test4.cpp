// 구현 + 완전탐색(중복 조합)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> ANSWER;
int Windiff = -1;
// 중복 조합
// 조합인데 이전 선택을 연속해서 할 수 있어야 하므로 시작위치 정보 인자 start가 추가됨
void comb_with_reputation(vector<int>& arr, int r, int depth, int start, vector<int>& selected, vector<int>& info)
{
    if(depth == arr.size()+(r-1))   // 탈출 조건 다른 것 주의(추가로 중복 가능한 만큼 depth가 소모된다)
    {
        if(selected.size() != r)    // selected는 r개인 경우만 고려
            return;

        vector<int> info_rion(11, 0);
        for(int e : selected)
        {
            info_rion[e]++;
        }
        int rion = 0;
        int apch = 0;
        for(int i=0; i<info.size(); ++i)
        {
            if(info_rion[i] > info[i])
                rion += 10-i;
            else
            {
                if(info_rion[i] == 0 && info[i] == 0)
                    continue;
                apch += 10-i;
            }
        }
        if(rion > apch)
        {
            if(Windiff <= rion-apch)
            {
                // 작은 점수 더 많이 맞춘족으로 변경
                if(!ANSWER.empty() && Windiff == (rion-apch))
                    for(int i=10; i>=0; --i)
                    {
                        if(info_rion[i] == ANSWER[i])
                            continue;
                        if(info_rion[i] < ANSWER[i])
                            return;
                        else
                            break;
                    }
                Windiff = rion-apch;
                ANSWER.clear();
                copy(info_rion.begin(), info_rion.end(), back_inserter(ANSWER));
            }
        }

        return;
    }

    // 중복 선택 가능하므로 start 그대로
    selected.push_back(arr[start]);
    comb_with_reputation(arr, r, depth+1, start, selected, info);
    selected.pop_back();
    // 이번꺼 선택 안하는 경우 (depth가 소모되면서 위에서 start+1로 재진입하게됨)
    comb_with_reputation(arr, r, depth+1, start+1, selected, info);
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer;

    vector<int> arr(11, 0);
    for(int i=0; i<arr.size(); ++i)
        arr[i] = i;
    vector<int> selected;
    comb_with_reputation(arr, n, 0, 0, selected, info);

    if(ANSWER.empty())
        answer.push_back(-1);
    else
        answer = ANSWER;

    return answer;
}

int main()
{
    int n = 9;
    vector<int> info = {0,0,1,2,0,1,1,1,1,1,1};
    solution(n, info);
    return 0;
}