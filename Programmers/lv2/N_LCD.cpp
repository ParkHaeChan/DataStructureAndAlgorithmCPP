/*
N개의 최소공배수
https://programmers.co.kr/learn/courses/30/lessons/12953

두 수의 최소공배수(Least Common Multiple)란 입력된 두 수의 배수 중 공통이 되는 가장 작은 숫자를 의미합니다. 
예를 들어 2와 7의 최소공배수는 14가 됩니다. 정의를 확장해서, 
n개의 수의 최소공배수는 n 개의 수들의 배수 중 공통이 되는 가장 작은 숫자가 됩니다. 
n개의 숫자를 담은 배열 arr이 입력되었을 때 이 수들의 최소공배수를 반환하는 함수, solution을 완성해 주세요.

!!!:
arr은 길이 1이상, 15이하인 배열입니다.
arr의 원소는 100 이하인 자연수입니다.

시도1)
두 수에서의 최소 공배수 = (두 수의 곱 / 두 수의 최대 공약수)로 구할 수 있다
n 개에서의 최소 공배수 = (arr[0] / n개 수의 최대 공약수) * (arr[1]...) * ... * 최대 공약수가
답이될 것 같아서 해봤다
0점 떠서 1,2,4,8 입력해봤는데 정답 8인데, 64가 나오는 문제가 있다.
1은 제외하는 처리가 필요한 것 같다.

시도2)
들어온 입력을 차례로 최소 공배수를 만들도록 변경
구한 최소공배수를 재귀로 다음 입력으로 보냄
통과
*/

#include <string>
#include <vector>

using namespace std;

int make_LCM(int a, int b)
{
    int ret = a*b;
    // get GCD
    if(a < b)
        swap(a, b);
    while(b > 0)
    {
        int temp = b;
        b = a%b;
        a = temp;
    }
    int GCD = a;

    return ret / GCD;
}

int recur(vector<int>& arr, int depth, int LCM)
{
    if(depth == arr.size())
        return LCM;

    int new_LCM = make_LCM(arr[depth], LCM);
    
    return recur(arr, depth+1, new_LCM);
}

int solution(vector<int> arr) {
    int answer;

    answer = recur(arr, 0, 1);

    return answer;
}

int main()
{
    vector<int> arr = {2,6,8,14};
    //vector<int> arr = {1,2,4,8};
    solution(arr);

    return 0;
}