/*
뉴스 클러스터링
https://programmers.co.kr/learn/courses/30/lessons/17677

자카드 유사도는 집합 간의 유사도를 검사하는 여러 방법 중의 하나로 알려져 있다. 
두 집합 A, B 사이의 자카드 유사도 J(A, B)는 두 집합의 교집합 크기를 두 집합의 합집합 크기로 나눈 값으로 정의된다.

예를 들어 집합 A = {1, 2, 3}, 집합 B = {2, 3, 4}라고 할 때, 교집합 A ∩ B = {2, 3}, 합집합 A ∪ B = {1, 2, 3, 4}이 되므로, 
집합 A, B 사이의 자카드 유사도 J(A, B) = 2/4 = 0.5가 된다. 
집합 A와 집합 B가 모두 공집합일 경우에는 나눗셈이 정의되지 않으니 따로 J(A, B) = 1로 정의한다.

자카드 유사도는 원소의 중복을 허용하는 다중집합에 대해서 확장할 수 있다. 
다중집합 A는 원소 "1"을 3개 가지고 있고, 다중집합 B는 원소 "1"을 5개 가지고 있다고 하자. 
이 다중집합의 교집합 A ∩ B는 원소 "1"을 min(3, 5)인 3개, 합집합 A ∪ B는 원소 "1"을 max(3, 5)인 5개 가지게 된다. 
다중집합 A = {1, 1, 2, 2, 3}, 다중집합 B = {1, 2, 2, 4, 5}라고 하면, 교집합 A ∩ B = {1, 2, 2}, 합집합 A ∪ B = {1, 1, 2, 2, 3, 4, 5}가 되므로, 
자카드 유사도 J(A, B) = 3/7, 약 0.42가 된다.

이를 이용하여 문자열 사이의 유사도를 계산하는데 이용할 수 있다. 
문자열 "FRANCE"와 "FRENCH"가 주어졌을 때, 이를 두 글자씩 끊어서 다중집합을 만들 수 있다. 
각각 {FR, RA, AN, NC, CE}, {FR, RE, EN, NC, CH}가 되며, 교집합은 {FR, NC}, 합집합은 {FR, RA, AN, NC, CE, RE, EN, CH}가 되므로, 
두 문자열 사이의 자카드 유사도 J("FRANCE", "FRENCH") = 2/8 = 0.25가 된다.

입력 형식
입력으로는 str1과 str2의 두 문자열이 들어온다. 각 문자열의 길이는 2 이상, 1,000 이하이다.
입력으로 들어온 문자열은 <두 글자씩 끊어서 다중집합의 원소로 만든다.> 
<이때 영문자로 된 글자 쌍만 유효하고, 기타 공백이나 숫자, 특수 문자가 들어있는 경우는 그 글자 쌍을 버린다.> 
예를 들어 "ab+"가 입력으로 들어오면, "ab"만 다중집합의 원소로 삼고, "b+"는 버린다.
다중집합 원소 사이를 비교할 때, <대문자와 소문자의 차이는 무시한다. "AB"와 "Ab", "ab"는 같은 원소로 취급한다.>

출력 형식
입력으로 들어온 두 문자열의 자카드 유사도를 출력한다. 유사도 값은 0에서 1 사이의 실수이므로, 
이를 다루기 쉽도록 65536을 곱한 후에 소수점 아래를 버리고 정수부만 출력한다.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

map<string, int> cluster(string input)
{
    map<string, int> ret;
    for(int i=0; i<input.size()-1; i++)
    {
        char f = input[i];
        char b = input[i+1];
        if(isalpha(f) && isalpha(b))
        {
            string temp = "";
            temp += f;
            temp += b;
            ret[temp]++;
        }
    }
    return ret;
}

int solution(string str1, string str2) {
    int answer = 0;

    // 모두 소문자로 변환
    transform(str1.begin(), str1.end(), str1.begin(), [](auto e){return tolower(e);});
    transform(str2.begin(), str2.end(), str2.begin(), [](auto e){return tolower(e);});

    // 2글자씩 분해하여 집합에 포함
    map<string, int> cluster1 = cluster(str1);
    map<string, int> cluster2 = cluster(str2);

    // 자카드 유사도 계산
    map<string, int> union_set;
    for(auto e: cluster1)
        union_set.insert(e);
    for(auto e: cluster2)
    {
        if(union_set.find(e.first) != union_set.end())
        {
            if(union_set[e.first] < e.second)
                union_set[e.first] = e.second;
        }
        else
            union_set[e.first]=e.second;
    }
    map<string, int> intersection_set;
    for(auto e: cluster1)
        intersection_set.insert(e);
    for(auto e: cluster2)
    {
        if(intersection_set.find(e.first) != intersection_set.end())
        {
            if(intersection_set[e.first] > e.second)
                intersection_set[e.first] = e.second;
        }
    }
    vector<string> dels;
    for(auto e: intersection_set)
    {   // 교집합에는 존재하는게 cluster2에는 존재하지 않으면 삭제
        if(cluster2.find(e.first) == cluster2.end())
            dels.push_back(e.first);
    }
    for(auto e: dels)
        intersection_set.erase(e);
    
    int unionsum = 0;
    for(auto e: union_set)
        unionsum += e.second;
    int intersum = 0;
    for(auto e: intersection_set)
        intersum += e.second;

    if(intersum == 0 && unionsum == 0)
        answer = 65536;
    else
    {
        double jakad = (double)intersum/unionsum;
        jakad *= 65536;
        jakad = floor(jakad);
        answer = lround(jakad);
    }
    return answer;
}

int main()
{
    string str1 = "E=M*C^2";
    string str2 = "e=m*c^2";

    cout << solution(str1, str2) << endl;

    return 0;
}