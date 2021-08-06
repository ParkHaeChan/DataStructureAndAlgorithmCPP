/*
모의고사
https://programmers.co.kr/learn/courses/30/lessons/42840

1번 수포자가 찍는 방식: 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, ...
2번 수포자가 찍는 방식: 2, 1, 2, 3, 2, 4, 2, 5, 2, 1, 2, 3, 2, 4, 2, 5, ...
3번 수포자가 찍는 방식: 3, 3, 1, 1, 2, 2, 4, 4, 5, 5, 3, 3, 1, 1, 2, 2, 4, 4, 5, 5, ...

?:
1번 문제부터 마지막 문제까지의 정답이 순서대로 들은 배열 answers가 주어졌을 때, 
가장 많은 문제를 맞힌 사람이 누구인지 배열에 담아 return 하도록 solution 함수를 작성해주세요.

!!!:
시험은 최대 10,000 문제로 구성되어있습니다.
문제의 정답은 1, 2, 3, 4, 5중 하나입니다.
가장 높은 점수를 받은 사람이 여럿일 경우, return하는 값을 오름차순 정렬해주세요.

각각이 찍는데 사용하는 방식이 다르다.
여기서는 고정되어 있기 때문에 각자 따로 반복문을 구성해도 문제를 풀 수는 있지만 코드가 길어질 것이다.
그래서 문제의 취지인 완전탐색에 맞도록 재귀를 사용해서 하나의 함수로 모든 경우를 해결하도록 코드를 작성해 보았다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const vector<vector<int>> sp = {
    {1, 2, 3, 4, 5},
    {2, 1, 2, 3, 2, 4, 2, 5},
    {3, 3, 1, 1, 2, 2, 4, 4, 5, 5}};

// 정답을 맞춘 개수를 반환하는 재귀함수
// 정답 벡터는 const로 참조하고, 현재 어디까지 검사했는지를 current로 저장한다.
// 탈출조건: current가 answers 벡터의 끝까지 도달하면 지금까지의 정답을 반환한다.
int recur(const vector<int>& answers, int current, int correct, int studentID)
{
    // 탈출 조건
    if(current == answers.size())
        return correct;

    // 현재 answer와 찍는 번호가 정답인지 확인한다.
    int divisor = sp[studentID].size();
    if(answers[current] == sp[studentID][current%divisor])
    {
        return recur(answers, current+1, correct+1, studentID);
    }
    else
    {
        return recur(answers, current+1, correct, studentID);
    }
}


vector<int> solution(vector<int> answers) {
    vector<int> answer;

    vector<pair<int, int>> student_score;
    for(int i=0; i<sp.size(); ++i)
    {
        int ret = recur(answers, 0, 0, i);
        student_score.push_back({i+1, ret});    // first: studentID, second: score
    }
    // 점수 순으로 정렬하되 같은 점수이면 학생번호가 오름차순이 되로록 정렬
    sort(student_score.begin(), student_score.end(), [](auto a, auto b){
        if(a.second == b.second)
            return a.first < b.first;
        else
            return a.second > b.second;
    });

    // 점수가 이전과 같으면 answer에 추가 다르면 끝
    answer.push_back(student_score[0].first);
    for(int i=1; i<student_score.size(); ++i)
        if(student_score[i-1].second == student_score[i].second)
            answer.push_back(student_score[i].first);
        else
            break;

    return answer;
}

int main()
{
    vector<int> answers = {1,2,3,4,5};
    solution(answers);

    return 0;
}