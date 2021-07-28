#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>    // std::find

using namespace std;

/*
=제한사항=
각 단어는 알파벳 소문자로만 이루어져 있습니다.
각 단어의 길이는 3 이상 10 이하이며 모든 단어의 길이는 같습니다.
words에는 3개 이상 50개 이하의 단어가 있으며 중복되는 단어는 없습니다.
begin과 target은 같지 않습니다.
변환할 수 없는 경우에는 0를 return 합니다.
*/

// 한글자만 다르고 나머지는 같으면 변환 가능
bool convertable(const string& a, const string& b)
{
    //모든 단어의 길이는 같다는 제한 있으므로 별도 처리 필요 없음
    int diff = 0;
    for(int i=0; i<a.size(); ++i)
    {
        if(a[i] != b[i])
            diff++;
    }
    if(diff == 1)
        return true;
    else
        return false;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;

    // DFS나 BFS로 다음으로 변환 가능한 단어를 모두 적용해가면서 확인해 보면된다.
    // 이때 문제에서 최소를 원하므로 가장 얕게 확인할 수 있는 BFS를 사용한다.
    queue<pair<string, int>> strQ;
    
    /* words에 begin이 존재하면 순환이 발생할 수 있으므로 찾아서 제외하려 했는데
    visited check에서 걸러져서 상관없어보임
    auto iter = find(words.begin(), words.end(), begin);
    if(iter != words.end())
    {
        words.erase(iter);
    }
    */
    int N = words.size();
    vector<bool> visited(N, false);
    strQ.push({begin, 0});

    while(!strQ.empty())
    {
        auto temp = strQ.front(); strQ.pop();

        if(temp.first == target)
        {
            answer = temp.second;
            break;
        }

        for(int i=0; i<N; ++i)
        {
            // 주의: 이미 고려한 단어는 제외한다(순환 발생할 수 있음)
            if(visited[i])
                continue;

            if(convertable(temp.first, words[i]))
            {
                strQ.push({words[i], temp.second+1});
                visited[i] = true;
            }
        }
    }

    return answer;
}

int main()
{
    string begin = "hit";
    string target = "cog";

    vector<string> words = {"hot", "dot", "dog", "lot", "log", "cog", "hit"};

    cout << solution(begin, target, words) << endl;

    return 0;
}