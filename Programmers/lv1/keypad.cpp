/*
[카카오 인턴] 키패드 누르기
https://programmers.co.kr/learn/courses/30/lessons/67256

?:
맨 처음 왼손 엄지손가락은 * 키패드에 오른손 엄지손가락은 # 키패드 위치에서 시작하며, 엄지손가락을 사용하는 규칙은 다음과 같습니다.
엄지손가락은 상하좌우 4가지 방향으로만 이동할 수 있으며 키패드 이동 한 칸은 거리로 1에 해당합니다.
왼쪽 열의 3개의 숫자 1, 4, 7을 입력할 때는 왼손 엄지손가락을 사용합니다.
오른쪽 열의 3개의 숫자 3, 6, 9를 입력할 때는 오른손 엄지손가락을 사용합니다.
가운데 열의 4개의 숫자 2, 5, 8, 0을 입력할 때는 두 엄지손가락의 현재 키패드의 위치에서 더 가까운 엄지손가락을 사용합니다.
만약 두 엄지손가락의 거리가 같다면, 오른손잡이는 오른손 엄지손가락, 왼손잡이는 왼손 엄지손가락을 사용합니다.

순서대로 누를 번호가 담긴 배열 numbers, 왼손잡이인지 오른손잡이인 지를 나타내는 문자열 hand가 매개변수로 주어질 때, 
각 번호를 누른 엄지손가락이 왼손인 지 오른손인 지를 나타내는 연속된 문자열 형태로 return 하도록 solution 함수를 완성해주세요

문제에서 언급한대로 구현할 수 있는가 보는 문제이다.
거리를 BFS방식으로 구했는데, 더 쉬운 방법은 target position의 위치를 찾아서 현재 위치와의 차이를 구하면 된다.
*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

bool inRange(pair<int,int> pos)
{   // pos: row, col (4,3)
    if(0 <= pos.first && pos.first < 4 && 0 <= pos.second && pos.second < 3)
        return true;
    return false;
}

int thumb_distance2(int cur, int target)    // 거리 한번에 계산
{
    // 키패드 그래프: -1: *, -2:#
    vector<vector<int>> keypad = {{1,2,3},{4,5,6},{7,8,9},{-1,0,-2}};
    using position = pair<int,int>;
    // 시작 위치 인덱스 찾기
    position start= {0,0};  // row, col
    while(keypad[start.first][start.second] != cur)
    {
        start.second++;
        if(start.second % 3 == 0)
        {    
            start.second = 0;
            start.first++;
        }
    }
    // 목적지 인덱스 찾기
    position targetpos= {0,0};  // row, col
    while(keypad[targetpos.first][targetpos.second] != target)
    {
        targetpos.second++;
        if(targetpos.second % 3 == 0)
        {    
            targetpos.second = 0;
            targetpos.first++;
        }
    }
    return abs(targetpos.first-start.first) + abs(targetpos.second-start.second);
}

int thumb_distance(int cur, int target) // BFS
{
    // 키패드 그래프: -1: *, -2:#
    vector<vector<int>> keypad = {{1,2,3},{4,5,6},{7,8,9},{-1,0,-2}};
    // 4방향
    using position = pair<int,int>;
    vector<position> direction = {{0,1},{0,-1},{1,0},{-1, 0}}; //R,L,D,U
    // 시작 위치 인덱스 찾기
    position start= {0,0};  // row, col
    while(keypad[start.first][start.second] != cur)
    {
        start.second++;
        if(start.second % 3 == 0)
        {    
            start.second = 0;
            start.first++;
        }
    }
    // 시작 위치에서 4방향 시도하여 이동거리 구한다.
    queue<pair<position, int>> pos_distQ;
    pos_distQ.push({start, 0});
    while(!pos_distQ.empty())
    {
        auto cur = pos_distQ.front(); pos_distQ.pop();
        if(keypad[cur.first.first][cur.first.second] == target)
            return cur.second;

        for(auto dir: direction)
        {
            position newpos = {cur.first.first+dir.first, cur.first.second+dir.second};
            if(inRange(newpos))  // 이동 가능한 위치만 큐에 삽입
            {
                pos_distQ.push({newpos, cur.second+1});
            }
        }
    }
}

string solution(vector<int> numbers, string hand) {
    string answer = "";

    // 각 손가락의 위치를 저장 (*,#은 초기위치이고 이후로는 숫자만 입력됨)
    int leftThumb=-1, rightThumb=-2;
    
    for(int i=0; i<numbers.size(); ++i)
    {
        // 147은 왼쪽, 369는 오른쪽으로 누른다
        if(numbers[i] == 1 || numbers[i] == 4 || numbers[i] == 7)
        {
            answer += "L";
            leftThumb = numbers[i];
            continue;
        }
        if(numbers[i] == 3 || numbers[i] == 6 || numbers[i] == 9)
        {
            answer += "R";
            rightThumb = numbers[i];
            continue;
        }
        // 2580은 두 엄지손가락의 현재 키패드의 위치에서 더 가까운 엄지손가락을 사용
        // 거리는 BFS로 젠다
        int ldist = thumb_distance2(leftThumb, numbers[i]);
        int rdist = thumb_distance2(rightThumb, numbers[i]);
        if(rdist == ldist)
        {// 만약 두 엄지손가락의 거리가 같다면, 오른손잡이는 오른손 엄지손가락, 왼손잡이는 왼손 엄지손가락을 사용
            if(hand[0] == 'l')  // 왼손잡이
            {
                answer += "L";
                leftThumb = numbers[i];
            }
            else
            {
                answer += "R";
                rightThumb = numbers[i];
            }
        }
        else
        {   // 거리 더 잛은 쪽을 사용
            if(ldist > rdist)
            {
                answer += "R";
                rightThumb = numbers[i];
            }
            else
            {
                answer += "L";
                leftThumb = numbers[i];
            }
        }
    }
    return answer;
}

int main()
{
    vector<int> numbers = {1, 3, 4, 5, 8, 2, 1, 4, 5, 9, 5};
    string hand = "right";

    solution(numbers, hand);

    return 0;
}