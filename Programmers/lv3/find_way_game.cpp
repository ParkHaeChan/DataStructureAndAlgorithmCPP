/*
길 찾기 게임
https://programmers.co.kr/learn/courses/30/lessons/42892

트리를 구성하는 모든 노드의 x, y 좌표 값은 정수이다.
모든 노드는 서로 다른 x값을 가진다.
같은 레벨(level)에 있는 노드는 같은 y 좌표를 가진다.
자식 노드의 y 값은 항상 부모 노드보다 작다.
임의의 노드 V의 왼쪽 서브 트리(left subtree)에 있는 모든 노드의 x값은 V의 x값보다 작다.
임의의 노드 V의 오른쪽 서브 트리(right subtree)에 있는 모든 노드의 x값은 V의 x값보다 크다.

?:
이진트리를 구성하는 노드들의 좌표가 담긴 배열 nodeinfo가 매개변수로 주어질 때,
노드들로 구성된 이진트리를 전위 순회, 후위 순회한 결과를 2차원 배열에 순서대로 담아 return 하도록 solution 함수를 완성하자.

!!!:
nodeinfo는 이진트리를 구성하는 각 노드의 좌표가 1번 노드부터 순서대로 들어있는 2차원 배열이다.
nodeinfo의 길이는 1 이상 10,000 이하이다.
nodeinfo[i] 는 i + 1번 노드의 좌표이며, [x축 좌표, y축 좌표] 순으로 들어있다.
모든 노드의 좌표 값은 0 이상 100,000 이하인 정수이다.
트리의 깊이가 1,000 이하인 경우만 입력으로 주어진다.
모든 노드의 좌표는 문제에 주어진 규칙을 따르며, 잘못된 노드 위치가 주어지는 경우는 없다.

시도1)
트리를 구성하면 순회는 쉽게 해결할 수 있다.
주어진 입력을 통해 조건을 만족하는 트리를 구성하면된다.
루트에서 시작해서 자식을 찾아서 지정하는 방식으로 구현한다.
// left, right child 연결
    for(int lv=0; lv+1<LEVELS; ++lv)
    {   // 참조로 처리 (포인터 연결 유지)
        vector<tree_node>& parents= Tree[lv];
        vector<tree_node>& childs= Tree[lv+1];
        int p = 0;  // 부모 idx
        for(int c=0; c<childs.size(); ++c)
        {
            if(parents[p].parent == nullptr)    // parent가 root인 경우
            {
                if(childs[c].info.x < parents[p].info.x)
                {   // left
                    parents[p].leftChild = &childs[c];
                    childs[c].parent = &parents[p];
                    childs[c].isleftC = true;
                }
                else
                {   // right
                    parents[p].rightChild = &childs[c];
                    childs[c].parent = &parents[p];
                }
            }
            else
            {   // 부모가 어디쪽 자식이었는지에 따라 분기
                if(parents[p].isleftC)
                {   // 부모가 leftChild였던 경우
                    if(childs[c].info.x < parents[p].info.x)
                    {   // left child
                        parents[p].leftChild = &childs[c];
                        childs[c].parent = &parents[p];
                        childs[c].isleftC = true;
                    }
                    else if(childs[c].info.x > parents[p].info.x && childs[c].info.x < parents[p].parent->info.x)
                    {   // right child
                        parents[p].rightChild = &childs[c];
                        childs[c].parent = &parents[p];
                    }
                    else
                    {   // 이 부모에 연결될 자식이 아님(다음 부모에 연결가능한지 검사)
                        c--;
                        p++;    // p가 parents 넘어서 문제 생기면 입력이 잘못된 경우임
                    }
                }
                else    // 부모가 right child인 경우
                {
                    if(childs[c].info.x < parents[p].info.x && childs[c].info.x > parents[p].parent->info.x)
                    {   // left child
                        parents[p].leftChild = &childs[c];
                        childs[c].parent = &parents[p];
                        childs[c].isleftC = true;
                    }
                    else if(childs[c].info.x > parents[p].info.x && childs[c].info.x < parents[p].parent->info.x)
                    {   // right child
                        parents[p].rightChild = &childs[c];
                        childs[c].parent = &parents[p];
                    }
                    else
                    {   // 이 부모에 연결될 자식이 아님(다음 부모에 연결가능한지 검사)
                        c--;
                        p++;    // p가 parents 넘어서 문제 생기면 입력이 잘못된 경우임
                    }
                }
            }
        }
    }
반복문으로 구현하다보니 중간에 부모가 그 부모의 left인지 right인지를 알아야하는 것 같아서
그 처리를 추가하였는데, 그래도 더 윗단에서 어디였는지에 대한 정보가 계속 필요한 상황이 나타난다.
이 방식으로는 트리 구성이 매우 어렵다고 판단하여 루트에서 시작해서
이분 탐색방식으로 내려가면서 트리 구성하도록 변경하여 시도

시도2)
마지막 29번 케이스에서 메모리 초과가 발생했다.
tree_node 내부의 node를 포인터형으로 변경해주었다.
그래도 메모리 초과가 발생함.

시도3)
메모리 초과라 뜨는데 실제로는 입력이 1개인 경우가 들어와서 그런 경우였다.
통과

*/

#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct node
{
    int x;
    int y;
    int id;
};

struct tree_node
{
    tree_node* leftChild;
    tree_node* rightChild;
    node* info;
};

void Add_Node(tree_node& root, tree_node& tnode)
{
    if(tnode.info->x < root.info->x)
    {
        if(root.leftChild == nullptr)
            root.leftChild = &tnode;
        else
            Add_Node(*(root.leftChild), tnode);
    }
    else if(tnode.info->x > root.info->x)
    {
        if(root.rightChild == nullptr)
            root.rightChild = &tnode;
        else
            Add_Node(*(root.rightChild), tnode);
    }
}

void preorder(tree_node& root, vector<int>& order)
{
    order.push_back(root.info->id);
    if(root.leftChild != nullptr)
        preorder(*(root.leftChild), order);
    if(root.rightChild != nullptr)
        preorder(*(root.rightChild), order);
}

void postorder(tree_node& root, vector<int>& order)
{
    if(root.leftChild != nullptr)
        postorder(*(root.leftChild), order);
    if(root.rightChild != nullptr)
        postorder(*(root.rightChild), order);
    order.push_back(root.info->id);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;

    if(nodeinfo.size() == 1)
    {
        return {{1},{1}};
    }

    vector<node> nodeVect;
    set<int> levelSet;
    for(int i=0; i<nodeinfo.size(); ++i)
    {
        nodeVect.push_back({nodeinfo[i][0], nodeinfo[i][1], i+1});
        levelSet.insert(nodeinfo[i][1]);
    }
    const int LEVELS = levelSet.size();
    vector<vector<tree_node>> Tree(LEVELS); // 트리 노드 저장용 벡터
    // y가 큰 값이 먼저오도록 정렬(같은 경우 x가 작은 경우가 먼저오도록)
    sort(nodeVect.begin(), nodeVect.end(), [](auto back, auto front){
        if(back.y == front.y)
            return back.x < front.x;
        else
            return back.y > front.y;
    });
    int idx=0;
    Tree[idx].push_back({nullptr, nullptr, &nodeVect[0]});
    int tree_idx = 1;
    for(idx=1; idx+1<nodeVect.size(); ++idx)
    {
        Tree[tree_idx].push_back({nullptr, nullptr, &nodeVect[idx]});
        if(nodeVect[idx].y != nodeVect[idx+1].y)
            tree_idx++;
    }
    Tree[tree_idx].push_back({nullptr, nullptr, &nodeVect[idx]});    // 남은 1개 처리

    // 시도2: 루트에서 부터 이분탐색 방식으로 추가한다
    for(int lv=1; lv<LEVELS; ++lv)
    {   // 참조로 처리 (포인터 연결 유지)
        vector<tree_node>& childs= Tree[lv];
        for(auto& e: childs)
        {
            auto& root = Tree[0][0];
            Add_Node(root, e);
        }
    }

    vector<int> pre;
    preorder(Tree[0][0], pre);
    vector<int> post;
    postorder(Tree[0][0], post);

    return answer = {pre, post};
}

int main()
{
    //vector<vector<int>> nodeinfo = {{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}};
    vector<vector<int>> nodeinfo = {{5,3}};
    solution(nodeinfo);

    return 0;
}