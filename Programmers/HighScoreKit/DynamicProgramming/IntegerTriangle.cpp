#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
문제: https://programmers.co.kr/learn/courses/30/lessons/43105

비교적 쉽게 알아냈다. (구현까지 해서 약 5분?)
DFS를 적용하여 맨 위에서 아래까지 더하면서 내려가면 모든 경우를 구할 수 있다.
이 통찰을 역으로 생각해서 아래서 부터 큰쪽을 더해서 올라가는 식으로 바꿔서 생각한다.

주어진 입력을 트리로 보면
시작을 맨 아래 노드의 부모에서 시작해서 현재 위치의 두 자식 중 큰쪽을 더한다.
갱신된 부모 값들이 이번에는 자식이 되어 위의 처리를 반복하며 루트까지 올라가면 된다.

DFS로는 모든 경우를 찾아봐야 하지만, 이렇게 접근 하면 두 자식 노드중 작은 값이
탈락하여 고려할 경우의 수가 매번 반으로 줄어 급격하게 감소한다.
*/

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    
    // leaf노드 바로 위 부모 행 부터 시작
    int start_layer = triangle.size()-2;
    
    for(int parent_layer = start_layer; parent_layer >= 0; --parent_layer)
    {
        //바로 아래 자식 노드 벡터
        auto child_layer = triangle[parent_layer+1];
        for(int i=0; i<child_layer.size()-1; ++i)
        {
            int leftchild = child_layer[i];
            int rightchild = child_layer[i+1];
            int largerchild = max(leftchild, rightchild);
            triangle[parent_layer][i] += largerchild;
        }
    }
    answer = triangle[0][0];
    
    return answer;
}