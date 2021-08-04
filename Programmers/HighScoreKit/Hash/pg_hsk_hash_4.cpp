/*
베스트 엘범
https://programmers.co.kr/learn/courses/30/lessons/42579
스트리밍 사이트에서 장르 별로 가장 많이 재생된 노래를 두 개씩 모아 베스트 앨범을 출시하려 합니다. 노래는 고유 번호로 구분하며, 노래를 수록하는 기준은 다음과 같습니다.

속한 노래가 많이 재생된 장르를 먼저 수록합니다.
장르 내에서 많이 재생된 노래를 먼저 수록합니다.
장르 내에서 재생 횟수가 같은 노래 중에서는 고유 번호가 낮은 노래를 먼저 수록합니다.

노래의 장르를 나타내는 문자열 배열 genres와 노래별 재생 횟수를 나타내는 정수 배열 plays가 주어질 때,
베스트 앨범에 들어갈 노래의 고유 번호를 순서대로 return 하도록 solution 함수를 완성하세요.

genres[i]는 고유번호가 i인 노래의 장르입니다.
plays[i]는 고유번호가 i인 노래가 재생된 횟수입니다.
genres와 plays의 길이는 같으며, 이는 1 이상 10,000 이하입니다.
장르 종류는 100개 미만입니다.
장르에 속한 곡이 하나라면, 하나의 곡만 선택합니다.
모든 장르는 재생된 횟수가 다릅니다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;

    // 장르별 순위를 먼저 알아본 다음
    map<string, int> genresmap;
    multimap<string, pair<int, int>> idmap;
    for(int i=0; i<genres.size(); ++i)
    {
        genresmap[genres[i]] += plays[i];
        idmap.insert({genres[i], {i, plays[i]}});
    }

    // genresmap을 벡터로 옮긴후 조회수 기준으로 정렬한다.
    vector<pair<string,int>> genrevect;
    copy(genresmap.begin(), genresmap.end(), back_inserter(genrevect));
    sort(genrevect.begin(), genrevect.end(), [](auto a, auto b){
        return a.second > b.second;
    });

    // 장르 내에서 1,2 순위 곡을 엘범에 넣는다 (1개 뿐이면 하나만 넣고 같은 조회수면 고유번호가 빠른 순으로 넣는다)
    for(auto e: genrevect)
    {
        string genre = e.first;
        auto piter = idmap.equal_range(genre);
        vector<pair<int,int>> idvect;
        for(auto it = piter.first; it!=piter.second; ++it)
        {
            idvect.push_back(it->second);
        }
        sort(idvect.begin(), idvect.end(), [](auto a, auto b){
            if(a.second == b.second)
            {   // 조회수 같으면 id 빠른 순
                return a.first < b.first;
            }
            else    // 조회수 많은 순
                return a.second > b.second;
        });
        if(idvect.size() == 1)
            answer.push_back(idvect[0].first);
        else
        {
            answer.push_back(idvect[0].first);
            answer.push_back(idvect[1].first);
        }
    }

    return answer;
}

int main()
{
    vector<string> genres = {"classic", "pop", "classic", "classic", "pop"};
    vector<int> plays= {500, 600, 150, 800, 2500};

    solution(genres, plays);

    return 0;
}