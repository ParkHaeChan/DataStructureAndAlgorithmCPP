#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int solution(vector<int> x, vector<int> y, vector<int> r, vector<int> v) {
    int answer = 0;

    // 가장 큰 직사각형 구하기: 모든 원에 대한 r의 크기가 다름에 주의(x,y 좌표만으론 알 수 없음)
    // 모든 원의 위치에 대해 r까지 고려하여 i,r,b,t를 계산한다
    const int INF = 987654321;
    int R=0, T=0, I=INF, B=INF;
    for(int i=0; i<x.size(); ++i)
    {
        int cx = x[i];
        int cy = y[i];
        int cr = r[i];

        I = min(I, cx-cr);
        R = max(R, cx+cr);
        B = min(B, cy-cr);
        T = max(T, cy+cr);
    }
    //cout << I << R << B << T << endl;

    // 난수 2개씩 나오도록 pair로 관리 + 변환 수행
    vector<pair<int,int>> randpos;
    for(int i=0; i<v.size(); i+=2)
    {
        int x = v[i];
        int y = v[i+1];
        int tx = I + (x%(R-I));
        int ty = B + (y%(T-B));
        randpos.push_back({tx,ty});
        //cout << tx << ":" <<ty << endl;
    }

    // 변환된 좌표가 원 위에 있는지 검사
    int cnt = 0;
    for(auto e: randpos)
    {
        int rx = e.first;
        int ry = e.second;

        for(int i=0; i<x.size(); ++i)
        {   // 원 위에 포함 되었다면, (x-rx)^2 + (y-ry)^2 <= r^2
            if( (x[i]-rx)*(x[i]-rx) + (y[i]-ry)*(y[i]-ry) <= r[i]*r[i] )
            {
                cnt++;
                break;
            }
        }
    }

    // 비율을 계산하여 면적과 곱하여 구한다
    double K = (double)cnt / randpos.size();
    cout << K << endl;

    double ans = K*(R-I)*(T-B);
    answer = lround(floor(ans));   // 소수점 이하 삭제, 형변환

    return answer;
}

int main()
{
    vector<int> x = {3,4};
    vector<int> y = {3,5};
    vector<int> r = {2,3};
    vector<int> v = {12, 83, 54, 35, 686, 337, 258, 95, 170, 831, 8, 15};

    cout << solution(x, y, r, v) << endl;

    return 0;
}