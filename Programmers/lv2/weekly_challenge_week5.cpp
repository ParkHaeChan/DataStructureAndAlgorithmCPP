/*
모음 사전
https://programmers.co.kr/learn/courses/30/lessons/84512

시도 1)
경우의 수가 적어서 전부 구성해보고 순서를 찾으면 될 것 같다.
AEIOU를 사용하여 1~5글자를 모두 생성하여 정렬 후,
몇번째인지 출력하도록 구성
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void make_words(string& vowels, set<string>& words, int depth, string& w)
{
    if(depth == 5)
    {
        if(!w.empty())
            words.insert(w);
        return;
    }
    
    // 선택안하는 경우
    make_words(vowels, words, depth+1, w);
    
    // 선택하는 경우
    for(int i=0; i<vowels.size(); ++i)
    {
        w += vowels[i];
        make_words(vowels, words, depth+1, w);
        //  w = w.substr(0, depth); 이 경우 문자열 크기가 일정하지 않으므로 문제 생길 수 있다
        w = w.substr(0, w.size()-1);
    }
}

int solution(string word) {
    int answer = 0;
    string w = "";
    string vowels = "AEIOU";
    set<string> words;
    make_words(vowels, words, 0, w);

    /*
    for(auto e: words)
    {
        answer++;
        cout << e << endl;
        if(e == word)
            break;
    }
    */
    // set.find 이용: cppreference참고해봤는데 정렬되있어서 그런지 로그시간에 작동한다. Logarithmic in the size of the container.
    auto it = words.find(word);
    if(it != words.end())
    {
        answer = std::distance(words.begin(), it);  // std::distance(start, target) : target 이터레이터의 인덱스 번호를 계산할 수 있다.
        answer++; // 인덱스 번호+1이 실제 위치
    }
    
    return answer;
}

int main()
{
    string word = "EIO";

    solution(word);

    return 0;
}