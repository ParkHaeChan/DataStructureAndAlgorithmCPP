/*
교점에 별 만들기
https://programmers.co.kr/learn/courses/30/lessons/87377


Ax + By + C = 0으로 표현할 수 있는 n개의 직선이 주어질 때, 이 직선의 교점 중 정수 좌표에 별을 그리려 합니다.
별이 그려진 부분은 *, 빈 공간(격자선이 교차하는 지점)은 .으로 표현
모든 별을 포함하는 최소한의 크기만 나타내면 됩니다.

?:
직선 A, B, C에 대한 정보가 담긴 배열 line이 매개변수로 주어집니다. 
이때 모든 별을 포함하는 최소 사각형을 return 하도록 solution 함수를 완성해주세요.

!!!:
line의 세로(행) 길이는 2 이상 1,000 이하인 자연수입니다.
line의 가로(열) 길이는 3입니다.
line의 각 원소는 [A, B, C] 형태입니다.
A, B, C는 -100,000 이상 100,000 이하인 정수입니다.
무수히 많은 교점이 생기는 직선 쌍은 주어지지 않습니다.
A = 0이면서 B = 0인 경우는 주어지지 않습니다.
정답은 1,000 * 1,000 크기 이내에서 표현됩니다.
별이 한 개 이상 그려지는 입력만 주어집니다.

참고 사항
Ax + By + E = 0
Cx + Dy + F = 0
두 직선의 교점이 유일하게 존재할 경우, 그 교점은 다음과 같습니다.

X = (BF - ED) / (AD - BC)
Y = (EC - AF) / (AD - BC)
또, AD - BC = 0인 경우 두 직선은 평행 또는 일치합니다.

시도1)
각 직선끼리 모두 교점을 찾아야 하므로
각 직선을 2쌍으로 묶는 모든 경우를 조사하는 조합을 사용한다.
최대 1000개가 입력으로 주어지므로 최대 1000 C 2가지가 발생하고 이는 재귀로 가능한 수준이다
(또는 간단히 2중 for문으로 구현 가능하다)
다음은 별을 출력하기 위해 찾은 좌표를 저장해 두었다가
좌측 최상단 별의 위치를 기준으로 정규화하여 최소크기의 격자에 출력시킨다
몇몇 케이스 통과 못함.
자료형 크기 문제가 생길 수 있다고 한다.
ABC가 10만~-10만이라 AD-BC계산할 때 int형 넘을 수 있다.

시도2)
자료형 넘는 case외에도 틀리는 경우가 있다.
시간 초과도 있다. --. 이거는 posVect 의 point를 pair<long long, long long>으로 바꿔주고 관련된 다른 자료형도 바꿔주니 해결됨
3번 케이스에 관련된 경우와 관련된 것 같다
79.3점

시도3)
maxX, Y값을 찾을 때 초기값을 0으로 둔게 문제였다... (좌표에 음수도 있으므로 LLONG_MIN으로 고쳐주니 통과됨)

*/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
using point = pair<int, int>;

vector<point> pvect;

void recur(vector<vector<int>>& line, int depth, vector<int>& selected)
{
    if(depth == line.size())
    {
        if(selected.size() == 2)
        {
            pvect.push_back({selected[0], selected[1]});
        }
        return;
    }
    if(selected.size() > 2)
        return; // 더 볼 필요 없음...

    selected.push_back(depth);
    recur(line, depth+1, selected);
    selected.pop_back();
    recur(line, depth+1, selected);
}

vector<string> solution(vector<vector<int>> line) {
    vector<string> answer;
    vector<int> selected;
    recur(line, 0, selected);

    vector<pair<long long, long long>> posVect;
    for(int i=0; i<pvect.size(); ++i)
    {
        int l1 = pvect[i].first;
        int l2 = pvect[i].second;
        auto line1 = line[l1];
        auto line2 = line[l2];
        long long A = line1[0], B = line1[1], E = line1[2];
        long long C = line2[0], D = line2[1], F = line2[2];

        long long denominator = A*D - B*C;
        if(denominator == 0)
            continue;   // 서로 평행하거나 겹침

        // 정수 판정
        long long x_numerator = B*F - E*D;
        long long y_numerator = E*C - A*F;
        if(x_numerator%denominator == 0 && y_numerator%denominator == 0)
        {   // 정확히 나눠 떨어지면 정수
            posVect.push_back({x_numerator/denominator, y_numerator/denominator});
        }
    }
    // 가장 왼쪽 좌표값과 가장 낮은 좌표값 찾아서 빼주면서 정규화
    const long long INF = LLONG_MAX;
    long long minX = INF, minY = INF;
    long long maxX = LONG_MIN, maxY = LLONG_MIN;
    for(auto& e: posVect)
    {
        minX = min(minX, e.first);
        minY = min(minY, e.second);
        maxX = max(maxX, e.first);
        maxY = max(maxY, e.second);
    }
    transform(posVect.begin(), posVect.end(), posVect.begin(), [=](point p){
        p.first -= minX;
        p.second -= minY;
        return p;
    });
    int C = maxX-minX;
    int R = maxY-minY;
    string temp(C+1, '.');
    for(int r=0; r<=R; ++r)
        answer.push_back(temp);

    for(auto& e: posVect)
    {
        int x = e.first;
        int y = e.second;
        answer[y][x] = '*';
    }
    reverse(answer.begin(), answer.end());

    return answer;
}

int main()
{
    vector<vector<int>> line = {{2, -1, 4}, {-2, -1, 4}, {0, -1, 1}, {5, -8, -12}, {5, 8, 12}};
    solution(line);

    return 0;
}