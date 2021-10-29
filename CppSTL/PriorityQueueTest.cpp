/*
std::priority_queue 의 사용법에 대해 정리한다.

기본 자료형을 사용하는 경우는 BasicDataType()을 참고,

사용자 정의 자료형을 사용하는 경우는 2가지 방식이 가능하나,

2번 방식이 더 간결하고, 이해하기 쉽다. 
*/

#include <iostream>
#include <queue>
#include <string>

using namespace std;

namespace usage1
{   // 방법1: 구조체 내부에 생성자와 < 와 > 연산자를 정의한다.
    // 복잡하고 햇갈리므로 추천하지 않는 방식이다.
    struct node
    {
        int first;
        double second;
        string third;
        
        // 생성자 정의
        node(int f, double s, string t) : first(f), second(s), third(t) {}
        
        // 비교 구조체 자리에 greater를 쓰느냐 less를 쓰느냐에 따라 < 와 > 연산자를 정의해야 함.
        // 둘 다 쓰면 둘 다 정의해준다... 참고로 std::sort에 비교함수 안써주면 정렬에도 영향을 주므로 주의한다.
        // const 지정자나 &는 필수는 아님
        bool operator>(const node& rhs) const
        {   
            return this->first > rhs.first; // 연산자 방향이랑 같게 써주고, pq의 비교 구조체 자리에 greater
        }
        bool operator<(const node& rhs) const
        {
            return this->first < rhs.first; // 연산자 방향이랑 같게 써주고, pq의 비교 구조체 자리에 less
        }
        // 이렇게 코드가 복잡해지므로
        // 따로 비교 구조체를 만드는 방법2를 사용하도록 하자
    };

    void UserDefinedDataType1()
    {   // 작동은 하지만 번거로우므로 (추천 X)
        priority_queue<node, vector<node>, greater<node>> minHeap;
        priority_queue<node, vector<node>, less<node>> maxHeap;
        for(int i=1; i<=5; ++i)
        {
            node temp{i, 0.0, ""};
            minHeap.push(temp);
            maxHeap.push(temp);
        }
        cout << "minHeap: ";
        while(!minHeap.empty())
        {
            cout << minHeap.top().first << " ";
            minHeap.pop();
        }
        cout << endl;
        cout << "maxHeap: ";
        while(!maxHeap.empty())
        {
            cout << maxHeap.top().first << " ";
            maxHeap.pop();
        }
        cout << endl;
    }
}

namespace usage2
{
    // 방법2: 비교 구조체를 따로 만들어서 greater, less 대신 사용한다.
    struct node2
    {   // node와 같으나 생성자와 대소비교 연산자를 정의하는 대신 비교구조체를 따로 만들어 준다
        int first;
        double second;
        string third;
    };

    struct cmp_asc
    {   // () 연산자로 node2에 대한 비교함수를 만든다
        bool operator()(node2 front, node2 back)    // 인자의 순서와 상대적 위치가 일치한다고 보면된다.
        {   // true면 교환발생
            return front.first > back.first;    // 앞이 크면 뒤와 교환 (오름차순이 된다)
        }
    };

    struct cmp_desc
    {   // () 연산자로 node2에 대한 비교함수를 만든다
        bool operator()(node2 front, node2 back)
        {   // true면 교환발생
            return front.first < back.first;    // 앞이 작으면 뒤와 교환 (내림차순이 된다)
        }
    };

    void UserDefinedDataType2()
    {   // 비교 구조체 사용하는 경우 (추천)
        // greater, less 자리에 비교 구조체 명시
        priority_queue<node2, vector<node2>, cmp_asc> minHeap;
        priority_queue<node2, vector<node2>, cmp_desc> maxHeap;
        for(int i=1; i<=5; ++i)
        {
            //node2
            minHeap.push({i, 0.0, ""});
            maxHeap.push({i, 0.0, ""});
        }
        cout << "minHeap: ";
        while(!minHeap.empty())
        {
            cout << minHeap.top().first << " ";
            minHeap.pop();
        }
        cout << endl;
        cout << "maxHeap: ";
        while(!maxHeap.empty())
        {
            cout << maxHeap.top().first << " ";
            maxHeap.pop();
        }
        cout << endl;
    }
}

void BasicDataType()
{   // 기본 자료형의 힙 설정: <자료형, 컨테이너, 비교구조체>
    // minHeap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    // maxHeap
    priority_queue<int, vector<int>, less<int>> maxHeap;
    for(int i=1; i<=5; ++i)
    {
        minHeap.push(i);
        maxHeap.push(i);
    }
    cout << "minHeap: ";
    while(!minHeap.empty())
    {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;
    cout << "maxHeap: ";
    while(!maxHeap.empty())
    {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;
}

int main()
{
    // BasicDataType();
    usage1::UserDefinedDataType1();
    usage2::UserDefinedDataType2();

    return 0;
}