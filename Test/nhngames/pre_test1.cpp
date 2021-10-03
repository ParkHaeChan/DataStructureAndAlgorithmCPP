#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main()
{
    freopen("input1.txt","r", stdin);

    int N, K, M;
    cin >> N >> K >> M;
    int a, b;
    vector<queue<int>> floorwaitVect(K+1, queue<int>());
    multiset<int> elevator;
    for(int i=0; i<N; ++i)
    {
        cin >> a >> b;
        floorwaitVect[a].push(b);
    }
    int answer = 0;
    int current_floor = 1;
    int dir = 1;    // 1올라감, -1 내려감
    while(true)
    {
        // 현재 층에서 내릴 사람이 내림
        while(elevator.find(current_floor) != elevator.end())
        {
            elevator.erase(current_floor);
        }
        // 현재 층에서 정원 이내로 태울 수 있는 사람 태움
        while(elevator.size() < M)
        {
            if(floorwaitVect[current_floor].empty())
                break;
            int p = floorwaitVect[current_floor].front(); floorwaitVect[current_floor].pop();
            elevator.insert(p);
        }
        // 다음 층으로 이동
        if(current_floor == K && dir > 0 || current_floor == 1 && dir < 0)
        {   // 맨 위층 또는 1층되면 방향 반대로
            dir *= -1;
        }
        current_floor += dir;
        // 모든 층에 대기중인 사람이 없고, 엘베가 비면 반복문 탈출
        bool done = true;
        for(int i=1; i<=K; ++i)
        {
            if(floorwaitVect[i].empty())
                continue;
            else
            {
                done = false;
                break;
            }
        }
        if(done)
        {
            if(elevator.empty())
                break;
        }
        answer++;
    }
    cout << answer << endl;
    
    return 0;
}