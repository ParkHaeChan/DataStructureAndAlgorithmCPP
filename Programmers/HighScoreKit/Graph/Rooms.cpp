/*
문제: https://programmers.co.kr/learn/courses/30/lessons/49190

상하좌우와 그 사이의 대각선으로 8방향이 주어지며 좌표평면을 arrows 배열에 주어진대로 이동하면서
면이 발생하면(삼각형이상) 그 면의 개수를 세는 문제이다.

가장 먼저 떠올리기 쉬운 것은 그래프로 봤을 때 사이클이 발생하면 도형이 생성된다는 것이다.
하지만, 예외가 있는데 선분처럼 같은 edge를 반복해서 사이클이 생기는 경우는 방이 생성되었다고 볼 수 없다.

그렇기 때문에 vertex와 edge에 대해서 중복검사를 각각 시행하여야 방이 생성되었는지를 판별할 수 있다.
사용했던 정점에 다시 돌아왔는데, 사용했던 선분을 다시 사용하지 않았다면 방이 생성되었다고 센다.
정점은 2차원 좌표계이기 때문에 pair<int, int>로 저장될 것이고,
간선은 두 정점으로 표현되기 때문에 pair<pair<int, int>, pair<int, int>>로 표현될 수 있다.
방문 여부는 map<K, V>로 저장하여 확인할 수 있다.

또 주의할 것은 아래의 3번째 입력처럼{2,7,2,5,0}으로 이동한 경우는 방이 3개가 생기는데 2개 발생한 것으로 세는 문제가 있다.
이는 중간에 소수점 좌표가 생기며 발생하는 방을 고려하지 못하기 때문이다.
이 문제는 처음 입력을 2배로 적용함으로써 해결할 수 있다. (주어진 8방향으로 움직이면서 생성될 수 있는 소수점 단위가 0.5 뿐이기 때문에 가능한 방법이다)

그래프 문제임에도 입력을 통해 graph를 따로 생성하지 않는 이유는
입력이 10만개까지 가능하여 접근가능한 모든 좌표를 정점으로하여 2차원 배열을 사용한다면 음수까지 고려하여 최대(20만*20만)의 크기가 필요하다.
메모리가 턱없이 부족할 것이다. 그래서 실제로 사용되는 정점의 위치와 방문 여부만 저장하는 방식으로 구현해야 한다.

이 문제에서는 그래프가 사이클이 생기는 여부만 가지고 방의 개수를 셀 수 있으므로, TSP라던가 강한 연결요소라던가 최대 유량같은
그래프 알고리즘에 대한 지식은 사용되지 않는다. 그래프 문제라기 보다는 IDEA 문제에 가까운 것 같다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<int> arrows) {
    int answer = 0;

    using point = pair<int, int>;
    using edge = pair<point, point>;

    // 8방향 벡터
    vector<point> directions = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

    // 정점 방문 여부 저장 map
    map<point, bool> vertexVisited;
    // 간선 방문 여부 저장 map
    map<edge, bool> edgeVisited;
    // 현재 위치: (0, 0)
    auto current = point(0, 0);
    vertexVisited[current] = true;

    // arrows 를 적용하면서 cycle이 생기는지 확인
    for(auto e: arrows)
    {
        auto dir = directions[e];
        int dx = dir.first;
        int dy = dir.second;
        
        // 2배로 적용할 것이므로 2회씩 적용한다.
        for(int i=0; i<2; ++i)
        {
            point lastPos = current;
            current.first += dx;
            current.second += dy;
            
            if(vertexVisited[current])
            {   // 방문했던 정점: cycle 발생
                if(edgeVisited[{lastPos, current}] || edgeVisited[{current, lastPos}])
                {   
                    // 같은 간선에 의해 발생한 cycle
                }
                else
                {
                    answer++; // 방 개수 추가
                    // 간선 방문 표시 (양방향)
                    edgeVisited[{lastPos, current}] = true;
                    edgeVisited[{current, lastPos}] = true;
                }
            }

            // 정점 방문 표시
            vertexVisited[current] = true;
            // 간선 방문 표시 (양방향)
            edgeVisited[{lastPos, current}] = true;
            edgeVisited[{current, lastPos}] = true;
            
        }
    }

    return answer;
}

int main()
{
    //vector<int> arrows = {6, 6, 6, 4, 4, 4, 2, 2, 2, 0, 0, 0, 1, 6, 5, 5, 3, 6, 0}; // answer : 3
    //vector<int> arrows = {1, 1, 4, 4, 6, 6, 1, 7, 3};   // answer : 1
    vector<int> arrows = {2, 7, 2, 5, 0};   // answer :3

    cout << solution(arrows) << endl;

    return 0;
}