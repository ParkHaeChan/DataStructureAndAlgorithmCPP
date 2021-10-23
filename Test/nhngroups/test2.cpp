#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    freopen("input2.txt", "r", stdin);
    int N, K;
    cin >> N >> K;
    string temp;
    getline(cin, temp);
    vector<int> ARY(21, 0);
    for(int i=0; i<N; ++i)
    {
        getline(cin, temp);
        istringstream iss(temp);
        string buff;
        set<int> tset;
        getline(iss, buff, ' ');
        int n = stoi(buff);
        while(getline(iss, buff, ' '))
        {
            tset.insert(stoi(buff));
        }
        for(auto& e: tset)
            ARY[e]++;
    }
    vector<pair<int, int>> PARY;
    for(int i=1; i<=20; i++)
    {
        int s = ARY[i];
        PARY.push_back({s,i});
    }
    sort(PARY.begin(), PARY.end(), [](auto back, auto front){
        return back.first > front.first;
    });
    int answer = 0;
    for(int i=0; i<K; ++i)
        answer += PARY[i].first;
    
    cout << answer;

    return 0;
}