/*
가장 큰 수
https://programmers.co.kr/learn/courses/30/lessons/42746

?:
0 또는 양의 정수가 담긴 배열 numbers가 매개변수로 주어질 때, 
순서를 재배치하여 만들 수 있는 가장 큰 수를 문자열로 바꾸어 return 하도록 solution 함수를 작성해주세요.

예를 들어, 주어진 정수가 [6, 10, 2]라면 [6102, 6210, 1062, 1026, 2610, 2106]를 만들 수 있고, 이중 가장 큰 수는 6210입니다.

!!!:
numbers의 길이는 1 이상 100,000 이하입니다.
numbers의 원소는 0 이상 1,000 이하입니다.
정답이 너무 클 수 있으니 문자열로 바꾸어 return 합니다.

시도1)
한자리 수로 이루어져 있었다면 그냥 큰 수가 앞에 오도록 정렬하면 된다.
하지만, 이 문제는 각 숫자가 0~1000 까지 가능하다.
앞자리 수가 큰 순으로 정렬하면 될 것 같지만, 앞 자리수는 같은데 전체 숫자의 자리수가 다른 경우에는 비교가 애매해진다. 
이때는 정렬할 때 문자로 고친 후 합쳐본 다음 다시 숫자로 바꿨을 때 더 커지는 순으로 정렬하도록 비교함수를 작성하면
실제로 문자열을 나열했을 떄 상태의 숫자가 증가하도록 정렬시킬 수 있다.
이 생각을 못했다면 푸는데 엄청 오래 걸렸을 것 같다.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool comp(int a, int b)
{
	string A, B;
	A = to_string(a);
	B = to_string(b);

    //둘 다 더해서 시도해 보고 큰쪽이 앞에 오도록 반환
	int AB = stoi(A + B);
	int BA = stoi(B + A);
	return AB > BA;
}

string solution(vector<int> numbers) {
	string answer = "";

	sort(numbers.begin(), numbers.end(), comp);
    /*
    for(int i=0; i<numbers.size(); ++i)
        cout << numbers[i] << " ";
    cout << endl;
    */
	for (int i = 0; i<numbers.size(); ++i)
		answer += to_string(numbers[i]);

    // 예외 case: 000...000이 아닌 0하나만 나오도록 고쳐야한다.
    if(answer[0] == '0')
        answer = "0";
    
	return answer;
}

int main()
{
    vector<int> numbers = {3, 30, 34, 5, 9};
    cout << solution(numbers) << endl;
    return 0;
}