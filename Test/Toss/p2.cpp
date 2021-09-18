/*
여러 대의 서버로 부하를 분산하는 로드밸런서를 만들고자 합니다. 
해당 로드밸런서는 기본적으로는 라운드 로빈 방식으로 요청을 서버로 분배합니다. 
다만 요청의 sticky 옵션이 true인 경우 이전에 분배된 서버로 요청이 분배되어야 합니다.
이러한 동작을 수행하는 함수를 구현해보세요.
*/

#include <string>
#include <vector>
#include <map>

using namespace std;

vector<vector<int>> solution(int servers, bool sticky, vector<int> requests) {
    vector<vector<int>> answer(servers);
    map<int, int> req_server_map;

    if(sticky)
    {   // 같은 작업이면 같은 서버에서 처리되어야 한다
        int servernum = 0;
        for(int i=0; i<requests.size(); ++i)
        {
            if(req_server_map.find(requests[i]) != req_server_map.end())
            {
                answer[req_server_map[requests[i]]].push_back(requests[i]);
            }
            else
            {   // 처음 들어온 값
                req_server_map[requests[i]] = servernum%servers;
                answer[req_server_map[requests[i]]].push_back(requests[i]);
                servernum++;
            }
        }

    }
    else
    {   // 돌아가면서 하나씩 처리
        for(int i=0; i<requests.size(); ++i)
        {
            answer[i%servers].push_back(requests[i]);
        }
    }

    return answer;
}

int main()
{
    int servers = 2;
    bool sticky = true;
    vector<int> requests = {1,1,2,2};

    solution(servers, sticky, requests);

    return 0;
}