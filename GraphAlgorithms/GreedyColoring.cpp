/*
최소의 색상만을 이용해서 칠하는 문제는
최적의 그래프 컬러링 문제로 NP-Complete 문제이다. 이는 웰시-포웰 알고리즘으로 해결한다.

여기서는 그리디 방식으로 색칠을 시도하기 때문에 시작 위치에 따라 사용되는 색의 수가 달라질 수 있다.
*/
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include "Graph.hpp"

using namespace std;

// 그래프 컬러링에 사용할 색상
unordered_map<unsigned, string> color_map = {
    {0, "Not Set"},
    {1, "RED"},
    {2, "BLUE"},
    {3, "GREEN"},
    {4, "YELLOW"},
    {5, "BLACK"},
    {6, "WHITE"},
};

// 그리디 그래프 컬러링
template<typename T>
auto greedy_coloring(const Graph<T>& G)
{
    auto size = G.vertices();
    vector<unsigned> assigned_colors(size+1, 0);    // 0번은 사용되지 않는다 (1~size)

    // 1번 정점부터 차례대로 검사
    for(unsigned i=1; i<=size; ++i)
    {
        auto outgoing_edges = G.edges(i);   //i에서 나가는 모든 edge를 가져옴

        // i번째 정점과 인접해 있는 정점들의 현재 색상
        set<unsigned> neighbors;

        for(auto& e: outgoing_edges)
        {
            neighbors.insert(assigned_colors[e.dst]);
        }

        // 인접한 정점에 칠해지지 않은 색상 중에서 가장 작은 숫자의 색상을 선택(Greedy 속성)
        auto smallest = 1;
        for( ; smallest <= color_map.size(); ++smallest)
        {
            if(neighbors.find(smallest) == neighbors.end())
                break;
        }

        assigned_colors[i] = smallest;
    }

    return assigned_colors;
}

// 화면 출력 함수
template<typename T>
void print_colors(vector<T>& colors)
{
    for(auto i = 1; i < colors.size(); ++i)
    {
        cout << i << ": " << color_map[colors[i]] << endl;
    }
}

int main()
{
    using T = unsigned;

    Graph<T> G(8);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;
    edge_map[1] = {{2, 0},{5,0}};
    edge_map[2] = {{1, 0},{5,0},{4,0}};
    edge_map[3] = {{4, 0},{7,0}};
    edge_map[4] = {{2, 0},{3,0},{5,0},{6,0},{8,0}};
    edge_map[5] = {{1,0},{2, 0},{4,0},{8,0}};
    edge_map[6] = {{4, 0},{7,0},{8,0}};
    edge_map[7] = {{3, 0},{6,0}};
    edge_map[8] = {{4, 0},{5,0},{6,0}};

    for(auto& i : edge_map)
        for(auto& j : i.second)
            G.add_edge(Edge<T>{i.first, j.first, j.second});

    cout << "[입력 그래프]" << endl;
    cout << G << endl;

    auto colors = greedy_coloring<T>(G);
    cout << "[그래프 컬러링]" << endl;
    print_colors(colors);

    return 0;
}