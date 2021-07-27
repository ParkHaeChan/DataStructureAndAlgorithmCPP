/*
Graph.hpp 와 KruskalMST.hpp 테스트 용도로 작성.

*/
#include "Graph.hpp"
#include <map>
#include "KruskalMST.hpp"

using namespace std;

int main()
{
    using T = unsigned;

    // 그래프 객체 생성
    Graph<T> G(9);

    map<unsigned, vector<pair<unsigned, T>>> edge_map;
    edge_map[1] = {{2,2},{5,3}};
    edge_map[2] = {{1,2},{5,5}, {4,1}};
    edge_map[3] = {{4,2},{7,3}};
    edge_map[4] = {{2,1},{3,2}, {5,2}, {6,4}, {8,5}};
    edge_map[5] = {{1,3},{2,5},{4,2},{8,3}};
    edge_map[6] = {{4,4},{7,4},{8,1}};
    edge_map[7] = {{3,3},{6,4}};
    edge_map[8] = {{4,5},{5,3},{6,1}};

    for(auto& i : edge_map)
        for(auto& j : i.second)
            G.add_edge(Edge<T>{i.first, j.first, j.second});

    cout << "[입력 그래프]" << endl;
    cout << G << endl;

    Graph<T> MST = minimum_spanning_tree(G);
    cout << "[최소 신장 트리]" << endl;
    cout << MST;

    return 0;
}