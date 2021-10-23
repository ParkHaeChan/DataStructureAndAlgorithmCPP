#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input3.txt", "r", stdin);
    int N;
    cin >> N;
    string temp;
    getline(cin, temp);
    vector<string> patterns;
    for(int i=0; i<N; ++i)
    {
        getline(cin, temp);
        int a = temp[0]-'0';
        int b = temp[2]-'0';
        string pattern = "";
        pattern = to_string(a)+to_string(b);
        patterns.push_back(pattern);
        pattern = to_string(b)+to_string(a);
        patterns.push_back(pattern);
    }
    string childs = "12345678";
    int answer = 0;
    do
    {
        bool able = true;
        for(auto& e: patterns)
        {
            if(childs.find(e) != string::npos)
            {
                able = false;
                break;
            }
        }
        if(able)
        {
            answer++;
        }
    } while (next_permutation(childs.begin(), childs.end()));
    cout << answer << endl;

    return 0;
}