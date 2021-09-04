/*
재귀로 순열, 조합 구성하기

조합: n개에서 순서에 상관없이 r개를 뽑는 것  nCr로 나타냄

순열: 순서가 다르면 서로 다른 것으로 취급한다. nPr로 나타내며 nPr = nCr * r! 이다.

중복순열: 중복을 허용하여 n개에서 r개를 뽑음. n^r 가지가 나온다. n (Pi) r로 나타낸다.

중복조합: n개 중 중복을 허용하여 r개를 뽑는다. 메뉴가 n개인 식당에 r명이 주문하는 경우
나올 수 있는 메뉴 구성을 나타낼 수 있다.
예를 들면 5명이 짜장 / 짬뽕 / 볶음밥 중 하나를 각각 주문하는 경우를 생각해보면 된다.

즉, r 명을 n 분할 하는 경우로 생각 할 수 있다.
{짜장 둘/ 짬뽕 둘/볶음밥} 하나 이런 식이다.
r명 + n-1개의 칸막이를 넣고 조합을 수행한 것과 같다. 
(단, 각자 다른걸 하나씩 시킨다는 조건이 있는지 주의할 것--> 이 경우는 각각 메뉴 하나씩 채운것으로 가정하고, 남은 인원+칸막이로 조합 수행한 경우를 계산한다.)
n+r-1 C r = n H r 로 나타낸다.

본 예제는 하나의 contain에 있는 값들을 위 연산을 적용하여 모두 일일이 출력하는 경우를 살펴본다.

여러 container(vector, set 등...)에서 하나씩 값을 가져와서 연산을 수행해야 할 경우에는
container vector의 각 원소를 이 방식으로 접근하여 안의 값을 하나씩 selected에 넣고, 다음 재귀를 수행하도록 구현하면 된다.
(permutation_container.cpp 참고)

*/

#include <iostream>
#include <vector>

using namespace std;

int COUNTER = 0;

// 조합: n개(arr.size)중 r개를 (순서 상관 없이) 뽑는다
// 모든 원소를 이번에 선택할지 말지를 매 재귀함수 실행시 결정한다.
// 재귀 종료 조건은 depth가 선택지의 끝에 도달한 경우: depth == arr.size 가 된다
// 선택하는 경우를 먼저 수행할지, 선택하지 않는 경우를 먼저 수행할지는 순회 순서만 바꾼다(문제에 따라 적절하게 적용하자)
void combination(vector<int>& arr, int r, int depth, vector<int>& selected)
{   // 중복도 안되고 이전 위치를 다시 가는 것도 막아야한다
    // (예: {2:1}, {3:2}, ... 이 경우는 각각 {1:2}, {2:3}인 경우의 순서만 바꾼 것)
    if(depth == arr.size())
    {
        // selected 크기 확인: 이 조건이 없으면
        // r개와 상관없이 0에서 arr.size까지 사용하여 구성가능한 모든 경우를 조사한다
        // 그 경우 각 원소를 선택O,X의 두가지 경우의 제곱으로 2^arr.size 가지가 나온다 (아무것도 선택 안하는 경우도 포함)
        if(selected.size() != r)
            return;

        for(int e : selected)
            cout << e << " : ";
        cout << endl;
        COUNTER++;
        return;
    }

    // 이번 depth에서 선택을 하는 경우: selected에 arr[depth]를 추가하여 재귀 진입
    selected.push_back(arr[depth]);
    combination(arr, r, depth+1, selected);    // 다음 시작위치: (i+1)
    selected.pop_back();

    // 이번 depth에서 선택을 안하는 경우: selected를 현재 상태로 재귀 진입
    combination(arr, r, depth+1, selected);
}


// 조합 반복문 구현: r값이 작고 고정이면 반복문으로도 구현 가능하다 (r번 중첩for문을 만든다)
// EX) r = 3인 경우
void comb_for(vector<int>& arr)
{
    for(int i=0; i<arr.size(); ++i)
    {
        for(int j=i+1; j<arr.size(); ++j)
        {
            for(int k=j+1; k<arr.size(); ++k)
            {
                cout << arr[i] << arr[j] << arr[k] << endl;
            }
        }
    }
    cout << "combination with fixed r: 3" << endl;
}


// 순열: n개(arr.size) 중 r개를 뽑아 나열하는 경우의 수 (순서가 다르면 서로 다른 경우이다)
// 2가지 방식이 가능하다: visitd(used) bool형 vector로 사용 여부를 확인하는 방법 : O(1) 단, arr.size가 크면 메모리 부담
// 이때 까지 선택한 depth를 set에 저장후 이미 존재하는지 확인하는 방법 : O(log(N)) 선택된 경우만 저장하여 메모리 효율적 (즉, r 값이 작을때 좋다)
// selected는 실제 방문 순서를 저장하기 위해 사용된다 (used나 set만으로는 추가된 순서를 알 수 없기 때문)
// used나 set을 쓰지 않을 경우 selected vector를 pair로 depth를 함께 저장하게 만들어 매번 중복확인하여 선택하도록 구현해야한다
void permutation(vector<int>& arr, int r, int depth, vector<bool>& used, vector<int>& selected)
{// 조합과 달리 순서가 다르면 다른 값이 되기 때문에 중복이 아닌 경우 제외하고 앞에 값 사용 할 수 있음
    if(depth == r)
    {
        for(int e : selected)
            cout << e << " : ";
        cout << endl;
        COUNTER++;
        return;
    }
    
    for(int i=0; i<arr.size(); ++i)
    {
        if(used[i]) // 중복 사용 막기
            continue;
        used[i] = true;
        selected.push_back(arr[i]);
        permutation(arr, r, depth+1, used, selected);
        // 사용 후 원래대로 둔다
        used[i] = false;
        selected.pop_back();
    }
}

// 순열 반복문 구현: 조합 반복문 구현과 마찬가지로 r이 고정된 경우에만 사용할 수 있다. r만큼 중첩 발생
// r = 2 인 경우
// 하지만 이렇게 쓰느니 정렬후 std::next_permutation(begin, end)을 쓰는게 낫다 (#include <algorithm>)
void perm_for(vector<int>& arr)
{
    vector<bool> used(arr.size(), false);
    vector<int> selected;
    for(int i=0; i<arr.size(); ++i)
    {
        used[i] = true;
        selected.push_back(arr[i]);
        for(int j=0; j<arr.size(); ++j)
        {
            if(used[j])
                continue;
            used[j] = true;
            selected.push_back(arr[j]);
            for(auto e: selected)
                cout << e << " : ";
            cout << endl;
            selected.pop_back();
            used[j] = false;
        }
        selected.pop_back();
        used[i] = false;
    }
    cout << "perm_with_fixed r = 2" << endl;
}

// 중복 순열
void perm_with_reputation(vector<int>& arr, int r, int depth, vector<int>& selected)
{   // 순열에서 중복 선택 막는 부분 없에면 됨
    if(depth == r)
    {
        for(int e : selected)
            cout << e << " : ";
        cout << endl;
        COUNTER++;
        return;
    }
    
    for(int i=0; i<arr.size(); ++i)
    {
        selected.push_back(arr[i]);
        perm_with_reputation(arr, r, depth+1, selected);
        selected.pop_back();
    }
}

// 중복 조합
// 조합인데 이전 선택을 연속해서 할 수 있어야 하므로 start가 추가됨
// 그리고 이때 선택 안하는 경우가 depth를 소모하므로 원래 깊이까지 도달하려면
// depth == (arr.size + r-1) 이 탈출조건이 되어야 한다는 것 주의!!!!!!!!!!
void comb_with_reputation(vector<int>& arr, int r, int depth, int start, vector<int>& selected)
{
    if(depth == arr.size()+(r-1))   // 탈출 조건 다른 것 주의(추가로 중복 가능한 만큼 depth가 소모된다)
    {
        if(selected.size() != r)    // selected는 r개인 경우만 고려
            return;

        for(int e : selected)
            cout << e << " : ";
        cout << endl;
        COUNTER++;
        return;
    }

    // 중복 선택 가능하므로 start 그대로
    selected.push_back(arr[start]);
    comb_with_reputation(arr, r, depth+1, start, selected);
    selected.pop_back();
    // 이번꺼 선택 안하는 경우 (depth가 소모되고 위의 start로 재진입)
    comb_with_reputation(arr, r, depth+1, start+1, selected);
}


int main()
{
    vector<int> selected;
    // 확인하기 쉽게 정렬된 상태로 줬지만 정렬 여부는 상관없다.
    vector<int> arr = {1,2,3,4,5};
    int r = 2;
    combination(arr, r, 0, selected);
    cout << arr.size() << " Combination " << r << " = " << COUNTER << endl;
    comb_for(arr);

    selected.clear();
    COUNTER = 0;
    vector<bool> used(arr.size(), false);
    permutation(arr, r, 0, used, selected);
    cout << arr.size() << " Permutation " << r << " = " << COUNTER << endl;
    perm_for(arr);

    selected.clear();
    COUNTER = 0;
    perm_with_reputation(arr, r, 0, selected);
    cout << arr.size() << " PI(Perm_with_reputation) " << r << " = " << COUNTER << endl;

    selected.clear();
    COUNTER = 0;
    comb_with_reputation(arr, r, 0, 0, selected);
    cout << arr.size() << " H(Comb_with_reputation) " << r << " = " << COUNTER << endl;

    return 0;
}