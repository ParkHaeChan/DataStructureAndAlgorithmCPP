/*
Disjoint-Set 자료 구조를 이용하는 크루스칼 알고리즘으로 O(Ea(V)) 이다.
a()는 아커만 함수의 역함수 : 로그 함수보다 훨씬 느리게 증가한다.
참고로 Disjoint-Set 자료 구조 이용 안하는 방식은 O(ElogE)가 걸린다.
정점이 많으면 큰 차이가 발생한다.
*/

#pragma once
#include "Graph.hpp"
#include "SimpleDisjointSet.hpp"
#include <queue>    // priority_queue

template <typename T>
Graph<T> minimum_spanning_tree(const Graph<T>& G)
{
    // edge weight를 이용한 최소 힙 구성: Graph.hpp의 Edge struct에 <,> 연산자 edge weight로 정렬되도록 구현함
    std::priority_queue<Edge<T>, std::vector<Edge<T>>, std::greater<Edge<T>>> edge_min_heap;

    // 모든 edge를 최소 힙에 추가
    for(auto& e : G.edges())
        edge_min_heap.push(e);

    // 정점 개수에 해당하는 Disjoint-Set 자료 구조 생성 및 초기화
    auto N = G.vertices();
    SimpleDisjointSet dset(N);
    for(unsigned i=0; i<N; ++i)
        dset.make_set(i);

    // MST
    Graph<T> MST(N);
    while(!edge_min_heap.empty())
    {
        // 최소 힙에서 최소 가중치 edge를 추출
        auto e = edge_min_heap.top();
        edge_min_heap.pop();

        // 선택한 edge가 cycle을 생성하지 않으면 해당 edge를 MST에 추가
        if(dset.find(e.src) != dset.find(e.dst))
        {
            MST.add_edge(Edge<T>{e.src, e.dst, e.weight});
            dset.union_sets(e.src, e.dst);
        }
    }

    return MST;
}