#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    Node(unsigned i) : id(i), parent(i), rank(0) {}
    unsigned id;
    unsigned parent;
    unsigned rank;
};

 vector<Node> dset;

unsigned find_parent(unsigned id)
{
    Node node = dset[id];
    while(node.parent != node.id)
    {
        node = dset[node.parent];
    }

    return node.parent;
}

bool union_node(Node& a, Node& b)
{
    // 부모 같으면 cycle 발생
    if(find_parent(a.id) == find_parent(b.id))
        return false;

    if(a.rank > b.rank)
    {
        dset[find_parent(b.id)].parent = find_parent(a.id);
    }
    else
    {
        dset[find_parent(a.id)].parent = find_parent(b.id);
    }
    a.rank++;
    b.rank++;

    return true;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    
    // MST를 구성하는 문제이다
    // Prim이나 Kruskal을 쓰면 되는데 둘의 용도는
    // Prim: 많은 수의 edge로 구성된 밀집 그래프에 적합
    // kruskal: 주로 적은 수의 edge로 구성된 희소 그래프에서 사용
    
    // 입력에 따라 다르겠지만, edge에 대한 vector를 입력으로 주므로
    // kruskal을 사용해 보도록 한다.
    
    // 1. edge weight에 대해서 정렬한다. (각 벡터는 edge로 src, dst, weight 순으로 들어있다)
    // 비교함수 return 이 true이면 swap 발생 X. 즉 이대로 정렬됨 
    sort(costs.begin(), costs.end(), [](vector<int>& a, vector<int>& b){ return a[a.size()-1] < b[b.size()-1]; });

    // 2. Disjoint-Set forest 초기화
    for(unsigned i=0; i<n; ++i)
        dset.push_back(i);

    // 3. union을 수행한다.
    int cnt = 0;
    for(auto vect : costs)
    {
        if(union_node(dset[vect[0]], dset[vect[1]]))
        {
            answer += vect[2];
            cnt++;
        }
        if(cnt == n-1)
            break;
    }
    
    return answer;
}

int main()
{
    int N = 4;
    vector<vector<int>> input = {{0,1,1},{0,2,2},{1,2,5},{1,3,1},{2,3,8}};

    cout << solution(N, input) << endl;
    for(auto e: dset)
        cout << e.id << " : " <<e.parent << endl;

    return 0;
}