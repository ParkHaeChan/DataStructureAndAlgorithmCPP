#include <string>
#include <vector>

using namespace std;

int get_group(vector<int>& student, int start, int k)
{
    int cnt = 0;
    int ret = 0;
    for(int i=start; i<student.size(); ++i)
    {
        if(student[i] == 1)
        {
            cnt++;
        }
        if(cnt == k)
            ret++;
        if(cnt > k)
            return ret;
    }
    return ret;
}

int solution(vector<int> student, int k) {
    int answer = 0;
    
    for(int i=0; i<student.size(); ++i)
    {
        answer += get_group(student, i, k);
    }

    return answer;
}

int main()
{
    vector<int> student = {0, 1, 0};
    int k = 2;
    solution(student, k);
    return 0;
}