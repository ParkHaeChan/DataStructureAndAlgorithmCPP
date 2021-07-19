#include <iostream>
#include <vector>
using namespace std;

int Answer;

void print_vect(vector<int>& vect)
{
    for(auto e: vect)
        cout << e << " ";
    cout << endl;
}

int main(int argc, char** argv)
{
	int T, test_case;

	//freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
        int N;
        cin >> N;
        vector<int> D(N+1);
        for(int i=1; i<=N; ++i)
            cin >> D[i];
        
        // 친구 저장하는 벡터
        vector<int> NextFriend(N+1, 0);   //
		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		for(int i=1; i<=N; ++i)
        {
            if(i+D[i] <= N) // 범위 이내면 친구
            {
                NextFriend[i] = i+D[i];
            }
        }

        // 가장 번호 큰 친구만 가르키도록 갱신
        for(int i = N; i>=1; --i)
        {
            if(NextFriend[i] > 0)   // 가리키는 친구가 있으면
            {
                int parent = NextFriend[i]; 
                if(NextFriend[parent] > 0)  // 그 친구의 친구가 있으면
                    NextFriend[i] = NextFriend[parent]; // 젤 번호가 큰 친구만 저장됨.
            }
        }
        // i = 1부터 0인 것만 센다.
        for(int i=1; i<=N; ++i)
        {
            if(NextFriend[i] == 0)
                Answer++;
        }
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}