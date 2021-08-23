/*
비밀지도
https://programmers.co.kr/learn/courses/30/lessons/17681

지도는 한 변의 길이가 n인 정사각형 배열 형태로, 각 칸은 "공백"(" ") 또는 "벽"("#") 두 종류로 이루어져 있다.
전체 지도는 두 장의 지도를 겹쳐서 얻을 수 있다. 각각 "지도 1"과 "지도 2"라고 하자. 
지도 1 또는 지도 2 중 어느 하나라도 벽인 부분은 전체 지도에서도 벽이다.
지도 1과 지도 2에서 모두 공백인 부분은 전체 지도에서도 공백이다.
"지도 1"과 "지도 2"는 각각 정수 배열로 암호화되어 있다.
암호화된 배열은 지도의 각 가로줄에서 벽 부분을 1, 공백 부분을 0으로 부호화했을 때 얻어지는 이진수에 해당하는 값의 배열이다.

입력으로 지도의 한 변 크기 n 과 2개의 정수 배열 arr1, arr2가 들어온다.

?:
원래의 비밀지도를 해독하여 '#', 공백으로 구성된 문자열 배열로 출력하라.

!!!:
1 ≦ n ≦ 16
arr1, arr2는 길이 n인 정수 배열로 주어진다.
정수 배열의 각 원소 x를 이진수로 변환했을 때의 길이는 n 이하이다. 즉, 0 ≦ x ≦ 2n - 1을 만족한다.

시도1)
이진수가 들어오고, '두 지도에서 어느 한쪽이라도 벽이면 벽이다'와 '두 지도에서 둘 다 공백인 부분은 공백이다'를 
비트 연산으로 나타내면 or에 속한다(0|0 인 경우를 제외하고 1). 이를 적용후 문제에서 원하는 출력값으로 변환하면 된다.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;

    // 두 맵을 비트 연산 |로 합친다
    vector<int> ans;
    for(int i=0; i<arr1.size(); ++i)
    {
        ans.push_back(arr1[i] | arr2[i]);
    }
    // 2진수로 바꿨을 떄 1인 부분을 #, 0인부분을 공백인 string으로 처리하여 answer에 추가
    for(int e: ans)
    {   // 2진수로 변환할 때 뒷자리 부터 계산됨을 주의
        string temp(n, ' ');    // 공백으로 초기화
        int cnt = n-1;  // 뒤에서 부터 채운다
        while(e > 0)
        {
            if(e%2 == 1)
            {
                temp[cnt] = '#';
            }
            e /= 2;
            cnt--;
        }
        answer.push_back(temp);
    }

    return answer;
}

int main()
{
    int n = 5;
    vector<int> arr1 = {9, 20, 28, 18, 11};
    vector<int> arr2 = {30, 1, 21, 17, 28};

    vector<string> ans = solution(n, arr1, arr2);

    return 0;
}