/*
2021 토스 NEXT 개발자로 입사하게된 김토스는 유저들을 위해 홈 화면에 유용한 금융 정보를 보여주기로 했습니다.
유용한 정보라도 너무 자주 보여주면 유저들에게 불편함을 줄 수 있어, 빈도를 조절하여 적절히 노출하려 합니다.
다음과 같은 방법으로 노출을 결정하는 코드를 작성해 주세요.

?:
유용한 금융정보는 하루에 여러 번 노출 될 수 있습니다.
M일 동안 N회 노출이 되었거나 유저가 거부하면, 더 이상 노출하지 않으며, 다음날부터 M일까지 유용한 금융 정보를 노출하지 않습니다.
만약 규격에 맞지 않는 줄 입력이 들어오는 경우, 이 줄은 무시하고 ERROR 를 출력합니다.
*/

#include <string>
#include <vector>
#include <sstream>      // istringstream

using namespace std;

vector<string> parse_string(string parseStr)
{
    vector<string> parsed;
    istringstream iss(parseStr);
    string buffer;
    while(getline(iss, buffer, '\n'))
    {
        parsed.push_back(buffer);
    }
    
    return parsed;  // 반환형이 참조형이면 삭제된 벡터에 대한 접근으로 에러가 발생한다
}

string solution(string input) {
    string answer = "";

    // parsing
    vector<string> parsed = parse_string(input);

    int M, N;
    M = stoi(parsed[0].substr(0,1));
    N = stoi(parsed[0].substr(2,1));

    int cnt = 0;
    int noday = 0;
    bool neg = false;

    answer += parsed[0] + "\n";
    for(int i=1; i<parsed.size(); ++i)
    {
        if(parsed[i] == "SHOW")
        {
            if(cnt < N && (noday == 0) && !neg)
            {   // show : 1
                answer += "1\n";
                cnt++;
                if(cnt == N)
                    noday = M+1;
            }
            else    // show : 0
                answer += "0\n";

        }
        else if(parsed[i] == "NEGATIVE")
        {
            answer += "0\n";
             neg = true;
        }
        else if(parsed[i] == "NEXT")
        {
            answer += "-\n";
            cnt = 0;
            noday--;
            if(noday < 0)
                noday = 0;
        }
        else if(parsed[i] == "EXIT")
        {
            answer += "BYE";
        }
        else
        {   // ERROR 출력
            answer += "ERROR\n";
        }
    }
    return answer;
}

int main()
{
    string input = "1 2\nSHOW\nSHOW\nNEXT\nSHOW\nNEXT\nSHOW\nNEXT\nSHOW\nEXIT";

    solution(input);

    return 0;
}