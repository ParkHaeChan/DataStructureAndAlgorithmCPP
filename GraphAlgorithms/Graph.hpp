/*
edge를 이용하여 Graph를 나타낸다.
내부적으로는 edge의 벡터를 저장하는 방식으로 구성된다.
그래프가 edge 객체 대한 정보로 구성되어 있기 때문에 kruskal 알고리즘을 적용하기 쉽다.
(실제 코딩 문제에서는 인접리스트나 행렬형이 더 자주 나올 것임)
*/
#pragma once
#include <iostream>
#include <vector>

template<typename T>
struct Edge
{
    unsigned src;
    unsigned dst;
    T weight;

    // Edge 객체 비교는 가중치를 이용
    inline bool operator< (const Edge<T>& e) const
    {
        return this->weight < e.weight;
    }

    // Edge 객체 비교는 가중치를 이용
    inline bool operator> (const Edge<T>& e) const
    {
        return this->weight > e.weight;
    }
};

template <typename T>
class Graph
{
    public:
    // N개의 정점으로 구성된 그래프
    Graph(unsigned N) : V(N) {}

    // 그래프의 정점 개수 반환
    auto vertices() const {return V;}

    // 전체 에지 리스트 반환
    auto& edges() const {return edge_list;}

    // 정점 v에서 나가는 모든 edge를 반환
    auto edges(unsigned v) const    //auto&로 쓰면 참조로 반환되어 함수 종료되면 edges_from_v 메모리 날아가서 제대로 작동X
    {
        std::vector<Edge<T>> edges_from_v;
        for(auto& e : edge_list)
            if(e.src == v)
                edges_from_v.emplace_back(e);      

        return edges_from_v;     
    }

    bool InRange(int start, int end, Edge<T>& cur)
    {
        if(cur.src >= start && cur.src <= end && cur.dst >= start && cur.dst <= end)
            return true;
        return false;
    }

    void add_edge(Edge<T>&& e)
    {
        // 에지 양 끝 정점 ID가 유효한지 검사
        if(InRange(1,V, e))
            edge_list.emplace_back(e);
        else
            std::cerr << "유효 범위를 벗어난 정점!" << std::endl;
    }

    // 표준 출력 스트림 지원
    template<typename U>
    friend std::ostream& operator<< (std::ostream& os, const Graph<U>& G);

    private:
    unsigned V; // 정점 개수
    std::vector<Edge<T>> edge_list;
};

template<typename U>
std::ostream& operator<< (std::ostream& os, const Graph<U>& G)
{
    for(unsigned i = 1; i <= G.vertices(); ++i)
    {
        os << i << ":\t";
        auto edges = G.edges(i);
        for(auto& e : edges)
            os << "{" << e.dst << ": " << e.weight << "}, ";

        os << std::endl;
    }

    return os;
}