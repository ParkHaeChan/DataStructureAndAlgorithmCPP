
#include <iostream>
#include <vector>
#include <algorithm>    // upper_bound, lower_bound

using namespace std;

int main()
{
    // upper,lower_bound들은 기본적으로 정렬이 되있는 상태에서만 사용될 수 있다 --> std::binary_search의 기반이다.
    vector<int> inputs = {1,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
    // 아래 inputs로 실행하면 제대로 안나오는 것을 확인 할 수 있다(내부적으로 이분 검색으로 빠르게 찾으려 하기 때문일 것이다)
    //vector<int> inputs = {1,1,1,2,1,1,2,2,1,2,2,3,3,3,3,4,4,1,4,4};

    auto iter = upper_bound(inputs.begin(), inputs.end(), 2);    
    for( ; iter != inputs.end(); iter++)
        cout << *iter << " ";
    cout << endl;
    // print: 3 3 3 3 4 4 4 4 (찾는 값 포함 X, 찾는 값의 맨 끝+1 만큼)

    iter = lower_bound(inputs.begin(), inputs.end(), 2);
    for( ; iter != inputs.end(); ++iter)
        cout << *iter << " ";
    cout << endl;
    // print: 2 2 2 2 3 3 3 3 4 4 4 4 (찾는 값의 맨 앞 부터)

    // 같은 값이 연속해서 나오는 구간 찾기
    int val = 1;
    auto begin_iter = lower_bound(inputs.begin(), inputs.end(), val);
    auto end_iter = upper_bound(inputs.begin(), inputs.end(), val);
    for( ; begin_iter != end_iter; ++begin_iter)
        cout << *begin_iter << " ";
    cout << endl;
    // print: 1 1 1 1 1

    // 순차 검색으로 찾기 O(N) : 반환형 iterator로 val의 실제 위치를 찾아준다(제일 앞의 값을 찾는다)
    auto find_iter = find(inputs.begin(), inputs.end(), val);
    if(find_iter != inputs.end())
    {
        cout << val << " exists!" << endl;
        // 여기서 부터 출력시킨다
        for( ; find_iter != inputs.end(); ++find_iter)
            cout << *find_iter << " ";
        cout << endl;
    }

    // 역순 정렬
    sort(inputs.begin(), inputs.end(), [](auto a, auto b){
        return a > b;
    });
    for(auto e : inputs)
        cout << e << " ";
    cout << endl;

    // binary_search는 찾는 값의 존재 여부만 파악한다. (return 형식이 bool이다) O(logN)
    // 비교함수로 정렬이 어떤 방식으로 되어있는지 알려줘야 제대로 찾아준다.
    int find_val = 3;
    if(binary_search(inputs.begin(), inputs.end(), find_val, [](auto a, auto b){\
        // 조건 함수를 추가할 수 있다.
        //return a<b; // 오름차순 정렬된 곳에서 찾기
        return a>b; // 내림차순 정렬된 곳에서 찾기
    }))
        cout << "found: " << find_val << endl;
    else
        cout << find_val << " not found..." << endl;


    return 0;
}