
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_vect(vector<bool>& vect, string& ret)
{
    for(int i=1; i<vect.size(); ++i)
        ret += to_string(vect[i]);
}

bool InRange(int val, int minv, int maxv)
{
    if(val >= minv && val <= maxv)
        return true;
    
    return false;
}

vector<bool> B;
vector<bool> A;
vector<bool> Done;

int main(int argc, char** argv)
{
	int T, test_case;

	freopen("input2.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
        int n, t;
        cin >> n >> t;
        B = vector<bool>(n+1, 0);
        A = vector<bool>(n+1, 0);
        Done = vector<bool>(n+1, false);
        string b;
        cin >> b;
        for(int i=1; i<=n; ++i)
        {
            B[i] = b[i-1]-'0';
        }
		/////////////////////////////////////////////////////////////////////////////////////////////
        // 확정된 경우 먼저 처리
        for(int i=1; i<=t; ++i)
        {
            if(InRange(i+t,1,n))
            {
                A[i+t] = B[i];
                Done[i+t] = true;
            }
        }
        for(int i=n-t+1; i<=n; ++i)
        {
            if(InRange(i-t,1,n))
            {
                A[i-t] = B[i];
                Done[i-t] = true;
            }
        }
        for(int i=t+1; i<=n-t; ++i)
        {
            if(B[i] == 0)
            {
                if(InRange(i+t,1,n))
                {
                    A[i+t] = 0;
                    Done[i+t] = true;
                }
                if(InRange(i-t,1,n))
                {
                    A[i-t] = 0;
                    Done[i-t]= true;
                }
            }
        }
        // 그외 경우는 채워나가야 함
        for(int i=t+1; i<=n-t; ++i)
        {
            if(B[i] == 1)
            {
                if(InRange(i+t, 1, n))
                {
                    if(InRange(i-t, 1, n))
                    {
                        // i+t, i-t 둘 다 접근 가능한 경우
                        if(A[i-t] == 1 || A[i+t] == 1)
                            continue;   // 이미 1이 존재하므로 넘긴다.
                        // 방문 안한쪽을 1로 바꾼다.
                        if(!Done[i+t])  
                        {
                            Done[i+t] = true;
                            A[i+t] = 1;
                        }
                        else
                        {
                            Done[i-t] = true;
                            A[i-t] = 1;
                        }
                    }
                    else    // i+t만 접근 가능한 경우
                    {
                        Done[i+t] = true;
                        A[i+t] = 1; // 무조건 1이어야 한다.
                    }

                }
                else if(InRange(i-t, 1, n))
                {
                    // i-t만 접근 가능한 경우
                    Done[i-t] = true;
                    A[i-t] = 1; // 무조건 1이어야 한다.
                }
            }
        }
        string answer = "";
        print_vect(A, answer);
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}