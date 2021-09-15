/*
숫자 게임
https://programmers.co.kr/learn/courses/30/lessons/12987

N명씩 두 팀
먼저 모든 사원이 무작위로 자연수를 하나씩 부여받습니다.
각 사원은 딱 한 번씩 경기를 합니다.
각 경기당 A팀에서 한 사원이, B팀에서 한 사원이 나와 서로의 수를 공개합니다. 그때 숫자가 큰 쪽이 승리하게 되고, 승리한 사원이 속한 팀은 승점을 1점 얻게 됩니다.
만약 숫자가 같다면 누구도 승점을 얻지 않습니다.

A팀은 빠르게 출전순서를 정했고 자신들의 출전 순서를 B팀에게 공개해버렸습니다. 
B팀은 그것을 보고 자신들의 최종 승점을 가장 높이는 방법으로 팀원들의 출전 순서를 정했습니다. 
이때의 B팀이 얻는 승점을 구해주세요.

시도1)
B에서 큰 숫자를 가진 사람과 A에서 알맞게 이길 수 있는 매칭만 우선적으로 찾아 적용한다.
그리디 문제로 볼 수 있다.
통과
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = 0;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int Bidx = B.size()-1;
    int Aidx = A.size()-1;
    while(Bidx >= 0 && Aidx >= 0)
    {
        if(B[Bidx] <= A[Aidx])
        {   // A를 이길 수 있는 B가 없으므로 남겨뒀다가 낮은 점수와 매칭 시킨다
            Aidx--;
        }
        else
        {   // 점수 획득, 다음 원소끼리 비교
            answer++;
            Bidx--;
            Aidx--;
        }
    }
    return answer;
}

int main()
{
    vector<int> A = {5,1,3,7};
    vector<int> B = {2,2,6,8};

    solution(A, B);

    return 0;
}