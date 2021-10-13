/*
다단계 칫솔 판매
https://programmers.co.kr/learn/courses/30/lessons/77486

자신을 조직에 참여시킨 추천인에게 배분하고 나머지는 자신이 가집니다. 
모든 판매원은 자신이 칫솔 판매에서 발생한 이익 뿐만 아니라, 
자신이 조직에 추천하여 가입시킨 판매원에게서 발생하는 이익의 10% 까지 자신에 이익
10% 를 계산할 때에는 원 단위에서 절사하며, 10%를 계산한 금액이 1 원 미만인 경우에는 이득을 분배하지 않고 자신이 모두 가집니다.
칫솔의 판매에서 발생하는 이익은 개당 100 원으로 정해져 있습니다.

?:
각 판매원의 이름을 담은 배열 enroll, 각 판매원을 다단계 조직에 참여시킨 다른 판매원의 이름을 담은 배열 referral, 
판매량 집계 데이터의 판매원 이름을 나열한 배열 seller, 판매량 집계 데이터의 판매 수량을 나열한 배열 amount가 매개변수로 주어질 때, 
각 판매원이 득한 이익금을 나열한 배열을 return 하도록 solution 함수를 완성해주세요. 
판매원에게 배분된 이익금의 총합을 계산하여(정수형으로), 입력으로 주어진 enroll에 이름이 포함된 순서에 따라 나열하면 됩니다.

!!!:
enroll의 길이는 1 이상 10,000 이하입니다.
enroll에 민호의 이름은 없습니다. 따라서 enroll의 길이는 민호를 제외한 조직 구성원의 총 수입니다.
referral의 길이는 enroll의 길이와 같습니다.
referral 내에서 i 번째에 있는 이름은 배열 enroll 내에서 i 번째에 있는 판매원을 조직에 참여시킨 사람의 이름입니다.
어느 누구의 추천도 없이 조직에 참여한 사람에 대해서는 referral 배열 내에 추천인의 이름이 기입되지 않고 “-“ 가 기입됩니다. 위 예제에서는 john 과 mary 가 이러한 예에 해당합니다.
enroll 에 등장하는 이름은 조직에 참여한 순서에 따릅니다.
즉, 어느 판매원의 이름이 enroll 의 i 번째에 등장한다면, 이 판매원을 조직에 참여시킨 사람의 이름, 즉 referral 의 i 번째 원소는 이미 배열 enroll 의 j 번째 (j < i) 에 등장했음이 보장됩니다.
seller의 길이는 1 이상 100,000 이하입니다.
seller 내의 i 번째에 있는 이름은 i 번째 판매 집계 데이터가 어느 판매원에 의한 것인지를 나타냅니다.
seller 에는 같은 이름이 중복해서 들어있을 수 있습니다.
amount의 길이는 seller의 길이와 같습니다.
amount 내의 i 번째에 있는 수는 i 번째 판매 집계 데이터의 판매량을 나타냅니다.
판매량의 범위, 즉 amount 의 원소들의 범위는 1 이상 100 이하인 자연수입니다.
칫솔 한 개를 판매하여 얻어지는 이익은 100 원으로 정해져 있습니다.
모든 조직 구성원들의 이름은 10 글자 이내의 영문 알파벳 소문자들로만 이루어져 있습니다.

시도1)
일단 트리를 구성할 수 있어야 한다.
2진트리가 아닌 일반적인 트리이므로 일반적인 그래프로 구현해도 된다.
트리에 string 이름이 붙으므로 map을 사용해서 숫자로 치환하는 것도 좋다.
그럼 1차원 구조체 배열로 트리를 구성할 수 있다.
후위 순회로 구현하면 각 노드의 이익을 계산할 수 있다. 즉 leaf로 이동할 수 있도록 child 정보를 각 노드에서 저장해야한다.
이후 seller에서 부터 이익금을 계산해서 순서대로 enroll에 있는 이들이 얼마의 수익을 가지는지 계산.

// 시도1 트리 구성
for(int i=0; i<referral.size(); ++i)
{   //  referral 내에서 i 번째에 있는 이름은 배열 enroll 내에서 i 번째에 있는 판매원을 조직에 참여시킨 사람의 이름
    int parent = nameMap[referral[i]];
    int child = nameMap[enroll[i]];
    TREE[parent].childs.push_back(child);
}
// 후위 순회 재귀탐색으로 각 노드의 profit 계산
int post_order(vector<node>& TREE, int id)
{
    if(TREE[id].childs.empty())
    {
        TREE[id].profit = lround((double)TREE[id].profit * 0.9);
        return lround((double)TREE[id].profit * 0.1);
    }
    
    for(int i=0; i<TREE[id].childs.size(); ++i)
    {
        TREE[id].profit += post_order(TREE, TREE[id].childs[i]);
    }
    TREE[id].profit = lround((double)TREE[id].profit * 0.9);
    return lround((double)TREE[id].profit * 0.1);
}
post_order(TREE, 0);

시도2)
답이 다르게 나와서 문제 다시 살펴보니
child가 올린 이익을 곧바로 center까지 올려주면서 계산해야 한다.
그러다 10%가 1원보다 작아지면 올리지 않고 그친다.
다 집계해서 더해서 올리는게 아니라 한번에 올려야 되므로
child에서 시작해서 parent로 올리기만 하면된다.
즉, 트리 각 노드는 parent만 알고있으면 된다.
테스트 케이스만 통과하고 0점 나온다...

시도3)
문제를 다시 읽어보면서 확인해봤다.
send가 10미만일 때 그냥 자기가 다 가지도록 변경했지만 여전히 0점...

시도4)
질문 참고해 보니 seller에 같은 이름 들어가는 경우가 있다고 한다. 하지만 이 경우는 내 풀이는 해당안되는 것 같고
(이미 입력을 그때 그때 계산하는 방식임)
10%를 계산할 떄 double로 형변환했다가 다시 int로 고치는데서 문제가 생길 수 있다고 한다. 
이 방법 대신 profit을 그냥 int형 10으로 나눈 상태를 올려 보낼 값으로 두고
profit-send로 본인 마진을 계산하도록 변경함.
통과

*/

#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

struct node
{
    int parent = -1;
    int profit = 0;
};

void ToCenter(vector<node>& TREE, int id, int profit)
{
    int send = profit/10;   // 시도 4
    int mine = profit-send;
    TREE[id].profit += mine;
    int parent = TREE[id].parent;
    while(parent != -1 && send > 0)
    {
        profit = send;
        // 시도 3
        if(profit < 10)
        {
            TREE[parent].profit += profit;
            break;
        }
        send = profit/10;   // 시도 4
        mine = profit-send;
        TREE[parent].profit += mine;
        parent = TREE[parent].parent;
    }
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;

    // 번호 붙이기
    map<string, int> nameMap;
    for(int i=0; i<enroll.size(); ++i)
        nameMap[enroll[i]] = i+1;
    
    // 0번: 민수, 1~N번: enroll에 등록된 이름순
    vector<node> TREE(enroll.size()+1);
    // 트리 구성
    for(int i=0; i<referral.size(); ++i)
    {   //  referral 내에서 i 번째에 있는 이름은 배열 enroll 내에서 i 번째에 있는 판매원을 조직에 참여시킨 사람의 이름
        int parent = nameMap[referral[i]];
        int child = nameMap[enroll[i]];
        TREE[child].parent = parent;
    }
    // seller들 값 반영
    for(int i=0; i<seller.size(); ++i)
    {
        int sellerid = nameMap[seller[i]];
        // 곧바로 center까지 올린다
        ToCenter(TREE, sellerid, amount[i]*100);
    }

    for(int i=1; i<=enroll.size(); ++i)
        answer.push_back(TREE[i].profit);

    return answer;
}

int main()
{
    vector<string> enroll = {"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"};
    vector<string> referral = {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"};
    vector<string> seller = {"young", "john", "tod", "emily", "mary"};
    vector<int> amount = {12, 4, 2, 5, 10};
    solution(enroll, referral, seller, amount);

    return 0;
}