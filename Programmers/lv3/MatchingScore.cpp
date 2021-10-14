/*
매칭 점수
https://programmers.co.kr/learn/courses/30/lessons/42893

검색어에 가장 잘 맞는 웹페이지를 보여주기 위해 아래와 같은 규칙으로 검색어에 대한 웹페이지의 매칭점수를 계산

한 웹페이지에 대해서 기본점수, 외부 링크 수, 링크점수, 그리고 매칭점수를 구할 수 있다.
한 웹페이지의 기본점수는 해당 웹페이지의 텍스트 중, 검색어가 등장하는 횟수이다. (대소문자 무시)
한 웹페이지의 외부 링크 수는 해당 웹페이지에서 다른 외부 페이지로 연결된 링크의 개수이다.
한 웹페이지의 링크점수는 해당 웹페이지로 링크가 걸린 다른 웹페이지의 기본점수 ÷ 외부 링크 수의 총합이다.
한 웹페이지의 매칭점수는 기본점수와 링크점수의 합으로 계산한다.

?:
검색어 word와 웹페이지의 HTML 목록인 pages가 주어졌을 때, 매칭점수가 가장 높은 웹페이지의 index를 구하라. 
만약 그런 웹페이지가 여러 개라면 그중 번호가 가장 작은 것을 구하라.

!!!:
pages는 HTML 형식의 웹페이지가 문자열 형태로 들어있는 배열이고, 길이는 1 이상 20 이하이다.
한 웹페이지 문자열의 길이는 1 이상 1,500 이하이다.
웹페이지의 index는 pages 배열의 index와 같으며 0부터 시작한다.
한 웹페이지의 url은 HTML의 <head> 태그 내에 <meta> 태그의 값으로 주어진다.
예를들어, 아래와 같은 meta tag가 있으면 이 웹페이지의 url은 https://careers.kakao.com/index 이다.
<meta property="og:url" content="https://careers.kakao.com/index" />
한 웹페이지에서 모든 외부 링크는 <a href="https://careers.kakao.com/index"\>의 형태를 가진다.
<a> 내에 다른 attribute가 주어지는 경우는 없으며 항상 href로 연결할 사이트의 url만 포함된다.
위의 경우에서 해당 웹페이지는 https://careers.kakao.com/index 로 외부링크를 가지고 있다고 볼 수 있다.
모든 url은 https:// 로만 시작한다.
검색어 word는 하나의 영어 단어로만 주어지며 알파벳 소문자와 대문자로만 이루어져 있다.
word의 길이는 1 이상 12 이하이다.
검색어를 찾을 때, 대소문자 구분은 무시하고 찾는다.
예를들어 검색어가 blind일 때, HTML 내에 Blind라는 단어가 있거나, BLIND라는 단어가 있으면 두 경우 모두 해당된다.
검색어는 단어 단위로 비교하며, 단어와 완전히 일치하는 경우에만 기본 점수에 반영한다.
단어는 알파벳을 제외한 다른 모든 문자로 구분한다.
예를들어 검색어가 "aba" 일 때, "abab abababa"는 단어 단위로 일치하는게 없으니, 기본 점수는 0점이 된다.
만약 검색어가 "aba" 라면, "aba@aba aba"는 단어 단위로 세개가 일치하므로, 기본 점수는 3점이다.
결과를 돌려줄때, 동일한 매칭점수를 가진 웹페이지가 여러 개라면 그중 index 번호가 가장 작은 것를 리턴한다
즉, 웹페이지가 세개이고, 각각 매칭점수가 3,1,3 이라면 제일 적은 index 번호인 0을 리턴하면 된다.

시도1)
문제가 상당히 길다...
바로 풀기가 막막해서 문자열 다루는 여러 방법을 많이 참고하였다...
우선 문자열 파싱 방법 부터 이전에 봐왔던 문제들과 차이가 있다.
정확히는 파싱이 아닌 string에서 원하는 값을 찾아오는 패턴 매칭이 필요하다.
그리고 URL을 분리하여 정수와 매핑하여 비교하는 방식으로 링크 수를 찾아
링크 점수와 매칭점수를 계산하여 매칭 점수 내림차순 정렬(같은 경우 idx큰게 앞)

참고: 
전역 namespace --> ::tolower 같은 경우의 사용 예
namespace NamespaceA{
    int x;
}

int x;

int main() {
    int x;

    // the x in main()
    x = 0;
    // The x in the global namespace
    ::x = 1;

    // The x in the A namespace
    NamespaceA::x = 2;
}


*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <cctype> string에 간접포함 된 듯 tolower, toupper ...
#include <map>

using namespace std;

struct page
{
    int idx;
    int basicscore;
    vector<string> extlinks;
    double linkscore = 0.0;
    double matchscore = 0.0;
};

void UpperCase(string& str)
{   // tolower 앞에 :: 안쓰면 에러 --> 전역 네임스페이스를 참조(전역에 정의된 것을 사용)
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

string GetURL(string& page)
{   // <head> 태그 내에 <meta> 태그의 값으로 주어진다 (<head> 내부 인지는 안봐도 되는 듯...)
    string target = "<meta property=\"og:url\" content=\"https://"; // 모든 url은 https:// 로만 시작
    int target_idx = page.find(target); // target문자열의 시작 index 반환
    target_idx += target.length();  // 실제 URL 시작 index
    int check = target_idx;
    string ret = "";
    while(page[check] != '\"')
    {   // URL 끝위치 찾기
        ret += page[check];
        check++;
    }
    return ret;
}

vector<string> GetExternalLink(string& page)
{   // 외부 링크는 <a href="https://careers.kakao.com/index"\>의 형태
    // 링크가 여러개 있을 수 있으므로 string.find를 반복적으로 수행
    // 이전에 찾은 위치는 제외해야 하므로 substr 사용
    string target = "<a href=\"https://";
    vector<string> ret;
    while(page.find(target) != string::npos)
    {
        int target_idx = page.find(target); // target문자열의 시작 index 반환
        target_idx += target.length();  // 실제 URL 시작 index
        int check = target_idx;
        string temp = "";
        while(page[check] != '\"')
        {   // URL 끝위치 찾기
            temp += page[check];
            check++;
        }
        if(temp != "")
            ret.push_back(temp);
        page = page.substr(target_idx); // substr(idx): idx부터 끝까지의 부분 문자열 반환
    }
    
    return ret;
}

int GetBasicScore(string& page, string word)
{
    // body 구간에서 word가 얼마나 사용되는지 찾는다 (html전체로 찾아야 될 수도 있음)
    string front_target = "<body>";
    string back_target = "</body>";
    int f = page.find(front_target);
    f += front_target.length();
    int b = page.find(back_target);
    string body = page.substr(f, b-f);

    // body에 word가 있는지 확인
    // 주의할 점: "aba" 일 때, "abab abababa"는 단어 단위로 일치하는게 없어 0점
    // "aba@aba aba"는 단어 단위로 세개가 일치
    string temp = "";   // 앞에서 부터 일치하면 추가하고, 불일치하면 빈 문자열로 초기화
    int ret = 0;
    for(int i=0; i<body.length(); ++i)
    {
        if(isalpha(body[i]) == 0)   // isalpha: 대문자(1), 소문자(2), 그외(0)
        {   //  알파벳 아닌 경우 현재까지 구성한 단어를 검사
            if(temp == word)
            {
                ret++;
            }
            temp = "";
        }
        else    // 알파벳인 경우 단어를 구성
            temp += body[i];
    }
    return ret;
}

int solution(string word, vector<string> pages) {
    int answer = 0;

    // 대소문자 구분X: 다 소문자로 변환
    UpperCase(word);
    for(int i=0; i<pages.size(); ++i)
        UpperCase(pages[i]);

    // URL 구하기, 기본 점수 구하기, 구조체 배열에 저장
    map<string, int> URL_MAP;
    int idx=0;
    vector<page> pageVect;
    for(auto& s: pages)
    {
        page p;
        string URL = GetURL(s);
        int basic_score = GetBasicScore(s, word);
        vector<string> extlink = GetExternalLink(s);
        p.idx = idx;
        p.basicscore = basic_score;
        copy(extlink.begin(), extlink.end(), back_inserter(p.extlinks));
        URL_MAP[URL] = idx++;
        pageVect.push_back(p);
    }
    // 링크 점수 계산
    // 링크점수는 해당 웹페이지로 링크가 걸린 다른 웹페이지의 기본점수 ÷ 외부 링크 수의 총합
    for(auto& e: pageVect)
    {
        for(auto& url: e.extlinks)
        {
            if(URL_MAP.find(url) == URL_MAP.end())
                continue; // 관계 없는 외부 링크
            int linked = URL_MAP[url];
            pageVect[linked].linkscore += (double)e.basicscore/e.extlinks.size();
        }
    }
    // 매칭 점수 계산
    for(auto& e: pageVect)
        e.matchscore = e.basicscore + e.linkscore;

    // 정렬
    sort(pageVect.begin(), pageVect.end(), [](auto back, auto front){
        if(back.matchscore == front.matchscore)
            return back.idx < front.idx;
        else
            return back.matchscore > front.matchscore;
    });
    answer = pageVect[0].idx;

    return answer;
}

int main()
{
    string word = "Muzi";
    vector<string> pages = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>"};
    // string word = "blind";
    // vector<string> pages = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>"};
    solution(word, pages);

    return 0;
}