/*
입력으로 R이 주어질 때, 원점 (0,0)을 중심으로 하는 반지름 R인 원 내부에 존재하는 정수 좌표를 갖는 점들의 개수를 출력하는 프로그램을 작성하시오.
참고로 원의 경계 위에 놓인 점들은 생각하지 않는다.

예를 들어 R=2인 경우, 점이 원의 내부에 존재하는 정수 좌표를 갖는 점들은 모두 (0,0), (0,1), (1, 0) (-1, 0), (0, -1), (1, 1), (1, -1), (-1, 1), (-1, -1)로 9개가 된다.

!!!:
각 테스트 케이스는 첫 줄에 정수 R이 주어진다. (1≤R≤200,000)

시도1)
직접 세는 방법이 있고, 수식으로 바로 계산가능한 방식이 있을 것 같다.
일단 직접 세는 방식을 작은 입력에 대해 시험해보면서 규칙성이 존재하는지 알아본다.

*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long Answer;

int main(int argc, char** argv)
{
	int T, test_case;

	freopen("input1.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
        long long R;  // 원의 반지름
		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		cin >> R;
        // cmath의 pow() 함수를 사용할 경우 pow함수의 반환형인 double형을 long long형으로 변환 할 떄 값이 바뀔 수 있음에 주의한다.
        // 예를들면 pow(5,2)는 25인데 double형으로 받으면 25이지만, int나 long long형으로 받으면 24로 받아진다.
        // 이 경우 lround() 함수를 사용하면 가장 가까운 값으로 변환시켜준다. 또는 floor 나 ceil 함수를 적절히 사용한다.
        long long point = lround(pow(3+2*(R-1),2))- (long long)8*R;

        long long points = (long long)(3+2*(R-1))*(long long)(3+2*(R-1)) - (long long)8*R;
        // i가 4이상일때 넘어가는 경우가 발생한다
        // 1사분면에 대해 넘어가는 수를 세서 *4를한 뒤 빼준다.
        //(<1~R-1>, R-1)와 (R-1, <1~R-1>)인 경우의 길이가 R이내인지 확인(X)
        // R넣으면 큰일난다 i가 매번 R의 크기이므로 i로 계산해야된다.
        long long x,y, sum=0;
        for(y=R-1; y>=1; --y)
        {   
            long long cnt=0;
            long long xstart=sqrt(R*R-y*y);
            for(x=xstart; x<R; ++x)
            {
                if(x*x + y*y >= R*R)
                {   
                    // R인 경우는 어차피 넘으므로 R-1에서 뺀 걸 센다
                    cnt = (R-1)-(x-1);
                    // cnt = cnt*2-1;  // 한쪽을 계산하면 나머지는 쪽은 겹치는 모서리 부분 1개만 제외한다.(cnt=1 인경우는 그대로 1로 나온다)
                    // Y를 줄일때 같이 고려된다
                    sum += cnt;
                    break;
                }
            }
            // 안나오면 더 확인할 필요가 없음
            if(cnt == 0)
                break;
        }
        //cout << sum << endl;
        if(sum > 0)
        {    // 4사분면 모두에 대해 계산
            sum *= 4;
        }
        points -= sum;
        Answer = points;
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}