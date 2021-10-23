#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main()
{
    freopen("input1.txt", "r", stdin);
    int N;
    cin >> N;
    string temp;
    int start = 1;
    priority_queue<int, vector<int>, greater<int>> PQ;
    vector<bool> used(N+1, false);
    used[start] = true;

    for(int i=0; i<=N; ++i)
    {
        getline(cin, temp);
        if(temp[0] == 'b')
        {
            if(PQ.empty())
            {
                start++;
                used[start] = true;
            }
            else
            {
                int n = PQ.top(); PQ.pop();
                used[n] = true;
            }
        }
        else if(temp[0] == 'm')
        {
            int n = stoi(temp.substr(6));
            used[n] = false;
            PQ.push(n);
        }
    }
    for(int i=1; i<=N; ++i)
        if(used[i])
            cout << i << " ";

    return 0;
}