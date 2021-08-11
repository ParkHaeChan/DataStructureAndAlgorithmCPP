/*
평면 상에 놓인 8개의 점에 관한 좌표와 정수 K가 주어질 때, 
이들을 이동하여 길이가  K인 직8각형을 만들기 위해 필요한 점들의 
이동거리 합의 최소값을 출력하는 프로그램을 작성하시오.
좌표 (xs,ys)에 놓인 한 점을 좌표 (xt,yt)로 이동할 때,
이동거리는 |xs−xt|+|ys−yt|이다. 여기서 |a|는 a의 절대값을 의미한다.

입력 파일에는 여러 테스트 케이스가 포함될 수 있다.
파일의 첫째 줄에 테스트 케이스의 개수를 나타내는 자연수 T 가 주어지고, 이후 차례로  T 개의 테스트 케이스가 주어진다. (1≤T≤200)

각 테스트 케이스의 첫 줄에는 정수 K(1≤K≤10^8) 가 주어진다.
이어지는 8개의 각 줄에는 점의 좌표xi,yi (1≤i≤8, −10^8≤xi,yi≤10^8)가 공백으로 구분되어 주어진다.
모든 점의 좌표는 정수이며, 평면 상에서 서로 다른 점이다.

시도1)
일단 주어진 점들의 중심에 위치해야 각 점들이 각각의 8각형 모서리로 이동하는 평균이 줄어들 것이라 생각할 수 있다.
중심은 점들의 각 좌표별 평균으로 구할 수 있다.

*/

#include <iostream>
#include <vector>

using namespace std;

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;

	freopen("input2.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
        int K;
        using point = pair<int, int>;
        vector<point> points;
        cin >> K;
        for(int i=0; i<8; ++i)
        {
            int x, y;
            cin >> x >> y;
            points.push_back({x,y});
        }

		Answer = 0;
		// 각 점들의 좌표의 평균을 구해본다
        int ax=0, ay=0;
        for(auto e : points)
        {
            ax += e.first;
            ay += e.second;
        }
        point center = {ax, ay};
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}