/*
다리를 지나는 트럭
https://programmers.co.kr/learn/courses/30/lessons/42583

solution 함수의 매개변수로 다리에 올라갈 수 있는 트럭 수 bridge_length, 
다리가 견딜 수 있는 무게 weight, 트럭 별 무게 truck_weights가 주어집니다. 
이때 모든 트럭이 다리를 건너려면 최소 몇 초가 걸리는지 return 하도록 solution 함수를 완성하세요.

?: 모든 트럭이 다리를 건너려면 최소 몇 초가 걸리는지 알아내야 합니다

!!!:
bridge_length는 1 이상 10,000 이하입니다.
weight는 1 이상 10,000 이하입니다.
truck_weights의 길이는 1 이상 10,000 이하입니다.
모든 트럭의 무게는 1 이상 weight 이하입니다.

다리를 큐라고 생각하고 문제를 풀면된다.
이때 최대 하중은 큐에 들어 있는 트럭의 무게 만큼 계속 업데이트를 해주는 식으로 구현하면 된다.
문제에는 따로 명시 되어 있지 않아 트럭의 속도는 고려하지 않는줄 알았는데
문제 출처에는 단위시간당 단위길이만큼 움직인다고 나와있다. (1초에 1m간다고 생각하면 될 듯)
큐에 들어갈 수 있는 (트럭수 제한 + 무게제한)만 신경쓰면 된다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;

    queue<int> bridgeQ;
    queue<int> truckQ;

    for(int i=0; i<truck_weights.size(); ++i)
        truckQ.push(truck_weights[i]);

    // 다리 길이만큼 0 넣은 채로 초기화한다.
    for(int i=0; i<bridge_length; ++i)
        bridgeQ.push(0);

    int current_weight = 0;
    int time;
    for(time = 1; !truckQ.empty() || !bridgeQ.empty(); ++time)
    {
        // 다리 위에 트럭이 있으면 한칸씩 옮긴다
        if(!bridgeQ.empty())
        {
            current_weight -= bridgeQ.front();
            bridgeQ.pop();
        }

        // 이번 트럭이 다리에 올라갈 수 있는지 확인한다
        int truck;
        if(!truckQ.empty())
            truck = truckQ.front();
        else
            continue;   // 트럭이 안남았으면 다리 위에 있는 트럭만 옮겨지면 끝난다

        if(bridgeQ.size() < bridge_length && current_weight+truck <= weight)
        {
            truckQ.pop();
            current_weight += truck;
            bridgeQ.push(truck);
        }
        else
        {
            bridgeQ.push(0);    // 트럭이 못들어 가면 빈칸을 채운다
            continue;
        }
    }
    answer = time-1;

    return answer;
}

int main()
{
    int bridge_length = 100;
    int weight = 100;
    vector<int> truck_weights = {10,10,10,10,10,10,10,10,10,10};

    cout << solution(bridge_length, weight, truck_weights) << endl;

    return 0;
}