/*
후보키
https://programmers.co.kr/learn/courses/30/lessons/42890

관계 데이터베이스에서 릴레이션(Relation)의 튜플(Tuple)을 유일하게 식별할 수 있는 속성(Attribute) 또는 속성의 집합 중,
다음 두 성질을 만족하는 것을 후보 키(Candidate Key)라고 한다.

유일성(uniqueness) : 릴레이션에 있는 모든 튜플에 대해 유일하게 식별되어야 한다.
최소성(minimality) : 유일성을 가진 키를 구성하는 속성(Attribute) 중 하나라도 제외하는 경우 유일성이 깨지는 것을 의미한다. 
즉, 릴레이션의 모든 튜플을 유일하게 식별하는 데 꼭 필요한 속성들로만 구성되어야 한다.

제이지를 위해, 아래와 같은 학생들의 인적사항이 주어졌을 때, 후보 키의 최대 개수를 구하라.

!!!:
relation은 2차원 문자열 배열이다.
relation의 컬럼(column)의 길이는 1 이상 8 이하이며, 각각의 컬럼은 릴레이션의 속성을 나타낸다.
relation의 로우(row)의 길이는 1 이상 20 이하이며, 각각의 로우는 릴레이션의 튜플을 나타낸다.
relation의 모든 문자열의 길이는 1 이상 8 이하이며, 알파벳 소문자와 숫자로만 이루어져 있다.
relation의 모든 튜플은 유일하게 식별 가능하다.(즉, 중복되는 튜플은 없다.)

시도1)
입력이 비교적 적으므로 재귀를 사용하여 가능한 경우를 만들어 본다.
하나의 열에 겹치는 값이 없는지 확인하고,
2개 열의 조합에 대해 후보키가 가능한지 확인하고 ... 하는 식으로 간다.

최소성을 판별하기 위해서는 이미 시도했던 하위조합으로 후보키가 생성된 경우는 제외해야한다.
ex) 학번이 후보키이면, 학번과 함께 한 다른 모든 경우는 유일성을 만족하지만 최소성에서 탈락이다.
점수: 40점

시도2)
재귀 내부에서 이번에 추가할 속성이 후보키이면 이후로 시도하지 않도록 추가
점수: 64점

시도3)
그냥 지금까지 구성한 조합에서 다시 모든 경우를 조사하여 후보키 사용되었으면 종료하도록 변경
통과!
*/
#include <string>
#include <vector>
#include <set>

using namespace std;

set<vector<int>> candidate_keySet;

// 후보키 들었으면 true 안들었으면 false
bool check_combination(vector<int>& arr, int depth, vector<int>& selected)
{
    if(depth == arr.size())
    {
        if(candidate_keySet.find(selected) != candidate_keySet.end())
            return true;
        return false;
    }

    if(check_combination(arr, depth+1, selected))
        return true;

    selected.push_back(arr[depth]);
    if(check_combination(arr, depth+1, selected))
        return true;
    selected.pop_back();

    return false;
}

void recur(vector<vector<string>>& attrs, int depth, vector<int>& selected)
{
    if(depth == attrs.size())
    {
        if(selected.size() == 0)
            return;

        // 지금까지 선택의 조합에 후보키가 들어가면 시도X (최소성)
        vector<int> t;
        if(check_combination(selected, 0, t))
            return;

        // 후보키 가능성 확인(유일성)
        // 속성 조합해서 set에 넣고 중복 발생하는지 확인해본다.
        vector<string> temp;
        copy(attrs[selected[0]].begin(), attrs[selected[0]].end(), back_inserter(temp));
        for(int i=1; i<selected.size(); ++i)
        {
            for(int j=0; j<attrs[i].size(); ++j)
            {   // string 상태로 이어 붙인다
                temp[j] += attrs[selected[i]][j];
            }
        }
        set<string> candidateSet;
        for(auto& s: temp)
        {
            candidateSet.insert(s);
        }
        if(candidateSet.size() == temp.size())
        {   // 후보키임
            candidate_keySet.insert(selected);
            return;
        }
        else
            return;
    }

    // 포함X
    recur(attrs, depth+1, selected);

    // 지금까지 선택의 조합에 후보키가 들어가면 시도X (최소성)
    vector<int> temp;
    if(check_combination(selected, 0, temp))
        return;

    // 포함O
    selected.push_back(depth);
    recur(attrs, depth+1, selected);
    selected.pop_back();
}

int solution(vector<vector<string>> relation) {
    int answer = 0;

    int RECORDSIZE = relation.size();
    int ATTRSIZE = relation[0].size();

    // attribute 끼리 묶는다
    vector<vector<string>> attributes(ATTRSIZE);
    for(int i=0; i<ATTRSIZE; ++i)
    {
        for(int j=0; j<RECORDSIZE; ++j)
        {
            attributes[i].push_back(relation[j][i]);
        }
    }
    // 가능한 조합 짝지어 본다
    vector<int> temp;
    recur(attributes, 0, temp);

    answer = candidate_keySet.size();

    return answer;
}

int main()
{
    //vector<vector<string>> relation = {{"100","ryan","music","2"},{"200","apeach","math","2"},{"300","tube","computer","3"},{"400","con","computer","4"},{"500","muzi","music","3"},{"600","apeach","music","2"}};
    vector<vector<string>> relation = {{"a","1","aaa","c","ng"},{"b","1","bbb","c","g"},{"c","1","aaa","d","ng"},{"d","2","bbb","d","ng"}};
 
    solution(relation);

    return 0;
}