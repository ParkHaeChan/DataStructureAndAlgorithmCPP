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
        double R;  // 원의 반지름
		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		cin >> R;
        
        long long cnt = 0, sum = 0;
        int n = 0;
        double a = n;
        long double b = -(a + sqrt(2*(R*R)-(a*a)))/2;
        long double c = (-a + sqrt(2*(R*R)-(a*a)))/2;

        // b,c 둘 다 정수로 나오면 둘 다 포함안해야된다.
        int ib = b;
        int ic = c;
        if(abs(b-ib)<0.00000001)
            b = floor(b)+1;
        else
            b = floor(b);

        if(abs(c-ic)<0.00000001)
            c = floor(c)-1;
        else
            c = floor(c);

        cnt = c-b;
        if(cnt > 0)
            sum += cnt;

        long long tsum = 0;
        for(n=1; true; ++n)
        {
            a = n;
            b = -(a + sqrt(2*(R*R)-(a*a)))/2;
            c = (-a + sqrt(2*(R*R)-(a*a)))/2;

            // nan check
            if(b != b || c != c)
                break;

            ib = b;
            ic = c;
            if(abs(b-ib)<0.00000001)
                b = floor(b)+1;
            else
                b = floor(b);

            if(abs(c-ic)<0.00000001)
                c = floor(c);
            else
                c = floor(c);
            
            cnt = c-b;
            if(cnt > 0)
                tsum += cnt;
        }
        sum += tsum*2;

        Answer = sum;
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}