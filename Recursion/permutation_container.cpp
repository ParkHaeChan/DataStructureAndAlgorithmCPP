/*
모 코딩대회 문제(현Dae모bi스)

0 ~ 9 사이의 숫자가 쓰여있는 정육면체 주사위 n개가 주어졌을 때, 당신은 이 주사위로 만들 수 없는 가장 작은 자연수를 찾으려 합니다. 
주사위로 숫자를 만드는 방법은 다음과 같습니다.
주사위를 모두 굴립니다.
그중 1 ~ n개를 임의로 선택합니다.
선택한 주사위를 임의의 순서로 왼쪽부터 오른쪽까지 나열합니다. 
단, 0이 나온 주사위를 맨 왼쪽에 놓을 수 없습니다. 0이 나온 주사위 하나만 선택하는 것도 불가능합니다.
임의로 나열한 주사위를 왼쪽부터 읽어 숫자를 만듭니다. 예를 들어, 2개의 주사위가 선택되었고 왼쪽 주사위는 1, 오른쪽 주사위는 2가 나왔다면 숫자 12를 만듭니다.
주사위는 원하는 숫자가 나올 때까지 계속 굴릴 수 있습니다.

예를 들어, 주사위 두 개가 주어지고, 각 주사위에 쓰여있는 숫자가 [1, 6, 2, 5, 3, 4], [9, 9, 1, 0, 7, 8]라고 할 때 만들 수 있는 숫자는 다음과 같습니다.
1, 2, 3, ..., 20, 21, 27, 28, ...

따라서 만들 수 없는 가장 작은 자연수는 22입니다.
주사위의 정보를 담은 2차원 정수 배열 dice가 매개변수로 주어질 때, 만들 수 없는 가장 작은 자연수를 return 하도록 solution 함수를 완성해주세요.

제한사항
1 ≤ dice의 길이 = 주사위의 개수 ≤ 4
dice의 원소는 각 주사위에 쓰인 수를 담고 있는 길이 6인 정수 배열입니다.
주사위는 항상 0 이상 9 이하인 수가 6개 쓰여있으며, 중복된 수가 쓰여있을 수도 있습니다.

입출력예
[[1, 6, 2, 5, 3, 4], [9, 9, 1, 0, 7, 8]]    ==>	22
[[0, 1, 5, 3, 9, 2], [2, 1, 0, 4, 8, 7], [6, 3, 4, 7, 6, 5]]    ==>	66

해설:
만들 수 있는 숫자는 주사위의 모든 순열에 대해 나올 수 있는 숫자를 이어붙여서 만들 수 있다.
만들 수 없는 최소의 숫자를 찾고 싶으므로,
1자리 수를 만드는 경우, 2자리 수를 만드는 경우, ... 를 따로 수행한 뒤
각 수행 마다 1~9, 10~99, 100~999, ... 중 불가능한 최소를 찾는 방식으로 수행한다.
*/

#include <string>
#include <vector>
#include <set>  // 한 주사위 안의 숫자들끼리의 중복을 없엔다(덤으로 정렬까지 됨: 디버깅할 떄 보기편함)
#include <iostream>

using namespace std;

set<int> maked;

bool debug = false;

// actual은 디버깅 용도
void recur(vector<set<int>>& dices, int depth, int target, string makedstr, vector<bool> selected, vector<int>& actual)
{
    if(depth == target)
    {   // 그냥 0이거나, 맨 왼쪽이 0인 경우는 불가능
        if(makedstr.size() != target || makedstr[0] == '0')
            return;
        maked.insert(stoi(makedstr));
        if(debug)
        {
            for(int e : actual)
            {
                cout << e << " : ";
            }
            cout << makedstr;
            cout << endl;
        }
        return;
    }

    // 순열이기 때문에 이전에 값이 뒤에 또 나올 수 있어야 한다
    // 단 중복은 불가능하므로 selected로 체크한다
    for(int i=0; i<dices.size(); ++i)
    {   // 이미 선택된 container는 제외
        if(selected[i])
            continue;
        selected[i] = true;
        actual.push_back(i);
        for(auto e: dices[i])
            recur(dices, depth+1, target, makedstr+to_string(e), selected, actual);
        selected[i] = false;
        actual.pop_back();
    }
}

int solution(vector<vector<int>> dice) {
    int N = dice.size();
    vector<set<int>> setvect;

    // set으로 중복을 줄인다
    for(int i=0; i<N; ++i)
    {
        set<int> temp;
        for(auto e: dice[i])
        {
            temp.insert(e);
        }
        setvect.push_back(temp);
    }

    string temp = "";
    vector<bool> selected(N, false);
    vector<int> actual; // 디버깅용
    for(int i=1; true; ++i)
    {
        recur(setvect, 0, i, temp, selected, actual);
        string start = "1";
        string end = "10";
        int cnt = i-1;
        while(cnt > 0)
        {
            start += "0";
            end += "0";
            cnt--;
        }
        for(int num = stoi(start); num < stoi(end); num++)
        {
            if(maked.find(num) == maked.end())
                return num;
        }
        // 다음 추가된 자리수 숫자로 재계산
        maked.clear();  // 클리어 안해도 상관없긴하다. (어차피 자리수 다른 수 찾을거라 걸릴 일이 없음)
    }
}

int main()
{
    vector<vector<int>> dice = {{1, 6, 2, 5, 3, 4}, {9, 9, 1, 0, 7, 8}};
    //vector<vector<int>> dice = {{0, 1, 5, 3, 9, 2}, {2, 1, 0, 4, 8, 7}, {6, 3, 4, 7, 6, 5}};

    cout << solution(dice) << endl;

    return 0;
}