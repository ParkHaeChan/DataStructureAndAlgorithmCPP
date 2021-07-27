#pragma once
#include <vector>
#include <algorithm>    // find_if

class SimpleDisjointSet
{
    private:
    struct Node
    {
        unsigned id;
        unsigned rank;
        unsigned parent;

        Node(unsigned _id) : id(_id), rank(0), parent(_id) {}

        bool operator != (const Node& n) const
        {
            return this->id != n.id;
        }
    };

    // Disjoint-Set Forest
    std::vector<Node> nodes;

    public:
    SimpleDisjointSet(unsigned N)
    {
        nodes.reserve(N);
    }

    void make_set(const unsigned& x)
    {
        nodes.emplace_back(x);
    }

    // 못 찾으면 -1을 반환한다
    unsigned find(unsigned x)
    {
        auto node_it = std::find_if(nodes.begin(), nodes.end(), [x](auto n){return n.id == x;});
        if(node_it == nodes.end())
            return -1;

        unsigned node_id = node_it->id;

        while(node_id != nodes[node_id].parent)
        {
            node_id = nodes[node_id].parent;
        }

        return node_id;
    }

    void union_sets(unsigned x, unsigned y)
    {
        auto root_x = find(x);
        auto root_y = find(y);

        // 만약 X와 Y가 같은 트리에 있다면 그대로 종료
        if(root_x == root_y)
            return;
        
        // 작은 랭크의 트리를 큰 랭크의 트리 쪽으로 병합(작은 랭크의 트리의 부모를 큰 랭크의 트리의 부모로 변경)
        if(nodes[root_x].rank > nodes[root_y].rank)
        {
            nodes[root_y].parent = nodes[root_x].parent;
            nodes[root_x].rank++;   // rank는 해당 트리의 높이인데 여기서는 실제로 높이가 높아지는지는 알 수 없음
        }
        else
        {
            nodes[root_x].parent = nodes[root_y].parent;
            nodes[root_y].rank++;
        }
        /*
        위 코드를 아래 코드로 쓰면 더 짧게 작성할 수는 있으나 한번에 와닿진 않을 수 있어 위 방식으로 썼다.
        if(nodes[root_x].rank > nodes[root_y].rank)
            std::swap(root_x, root_Y);

        nodes[root_x].parent = nodes[root_y].parent;
        nodes[root_y].rank++;
        */
    }
};