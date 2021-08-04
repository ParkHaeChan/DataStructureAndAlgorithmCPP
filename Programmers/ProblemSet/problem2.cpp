#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;

    //yellow의 약수를 찾아 시도
    int row, col;
    for(int i=1; i*i<=yellow; ++i)  // i*i<=yellow로 같을 때도 처리해줘야 yellow=1일 때를 처리할 수 있다
    {
        if(yellow%i != 0)
            continue;
        
        int another = yellow/i;

        if(i > another)
        {
            row = i;
            col = another;
        }
        else
        {
            row = another;
            col = i;
        }
        if(row*2+col*2+4 == brown)
            break;
    }
    answer.push_back(row+2);
    answer.push_back(col+2);

    return answer;
}

int main()
{
    int brown = 8;

    int yellow = 1;

    vector<int> ans = solution(brown, yellow);

    return 0;
}