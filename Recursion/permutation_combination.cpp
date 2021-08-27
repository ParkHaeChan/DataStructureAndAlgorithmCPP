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

// 조합
void combination(vector<int>& arr, int r, int depth, int start, vector<int>& selected)
{   // 중복도 안되고 이전 위치를 다시 가는 것도 막아야한다
    // (예: {2:1}, {3:2}, ... 이 경우는 각각 {1:2}, {2:3}인 경우의 순서만 바꾼 것)
    if(depth == r)
    {
        for(int e : selected)
            cout << e << " : ";
        cout << endl;
        COUNTER++;
        return;
    }
    if(start >= arr.size())
        return;

    // start부터 시작하는 것과 다음 위치로 i+1을 지정하는 것을 주의
    for(int i=start; i<arr.size(); ++i)
    {
        selected.push_back(arr[i]);
        combination(arr, r, depth+1, i+1, selected);    // 다음 시작위치: (i+1)
        selected.pop_back();
    }
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


// 순열
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

//


// 중복 조합
void comb_with_reputation(vector<int>& arr, int r, int depth, int start, vector<int>& selected)
{
    if(depth == r)
    {
        for(int e : selected)
            cout << e << " : ";
        cout << endl;
        COUNTER++;
        return;
    }

    for(int i=start; i<arr.size(); ++i)
    {
        selected.push_back(arr[i]);
        // 이번 선택은 중복해서 할 수 있으나 이전은 못하도록
        // 그냥 조합의 start 자리 i+1을 중복을 허용할 수 있도록 i로 변경 
        comb_with_reputation(arr, r, depth+1, i, selected);
        selected.pop_back();
    }
}


int main()
{
    vector<int> selected;
    // 확인하기 쉽게 정렬된 상태로 줬지만 정렬 여부는 상관없다.
    vector<int> arr = {1,2,3,4,5};
    int r = 2;
    combination(arr, r, 0, 0, selected);
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