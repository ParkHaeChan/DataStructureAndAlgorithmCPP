/*
조이스틱
https://programmers.co.kr/learn/courses/30/lessons/42860

?:
조이스틱으로 알파벳 이름을 완성하세요. 맨 처음엔 A로만 이루어져 있습니다.
ex) 완성해야 하는 이름이 세 글자면 AAA, 네 글자면 AAAA
조이스틱을 각 방향으로 움직이면 아래와 같습니다.
▲ - 다음 알파벳
▼ - 이전 알파벳 (A에서 아래쪽으로 이동하면 Z로)
◀ - 커서를 왼쪽으로 이동 (첫 번째 위치에서 왼쪽으로 이동하면 마지막 문자에 커서)
▶ - 커서를 오른쪽으로 이동

만들고자 하는 이름 name이 매개변수로 주어질 때, 이름에 대해 조이스틱 조작 횟수의 최솟값을 return 하도록 solution 함수를 만드세요.

!!!:
name은 알파벳 대문자로만 이루어져 있습니다.
name의 길이는 1 이상 20 이하입니다.

ABCDE FGHIJ KLMNO PQRST UVWXY Z = 26글자이고 넘어가면 다시 A로 되돌아간다.
또는 뒤로 돌아가면 Z로 바로 갈 수 있다.
즉, 각 위치를 어느방향으로 이동하는게 이득인지 알아야한다.
A에서 시작하므로 중간지점이내는 순방향이 빠를 것이고, 중간지점 이후는 역방향이 빠를 것이다.
중간 지점의 기준은 13번째인 N은 순방향/역방향 모두 13회 이동이 필요하다.
N을 기준으로 이동횟수를 바로 계산하면 된다.
ex) N이내인 경우 : if(cur < 'N') cnt = cur - 'A';
    N보다 큰 경우: if(cur >= 'N') cnt = 26+'A' - cur;
그리고 다음 글자로 넘어갈 떄도 하나씩 추가된다.
이때도 AAAAAAZA 같은 경우를 주의해야한다.
이 경우도 뒤로 돌아가는게 빠르다.
이런 경우를 처리하려면 이미 앞에 글자가 완성되어 있을 경우 다음 고칠 자리수로 갈때 앞으로 가는게 빠른지
뒤로가는게 빠른지를 매번 계산하면 된다.
ex)
앞이 이미 A인 경우, A가 아닌 값으로 고쳐야 하는 경우까지 앞을 계속 확인한다. (확인하면서 cnt 센다)
이후 그 위치까지 돌아서 가는게 빠른지 그대로 가는게 빠른지 확인한다.    (현위치까지 이동수 + (끝 위치-고칠 위치))

시도2) AAAAAAAZAAA 같은 경우 첨부터 뒤로 돌아 Z로 가는데
이후로 ZAAA를 또 가게된다. 하지만 돌아왔기 때문에 Z만 보고 끝내는게 최적이다.
확실한 방법은 입력 string 길이가 짧기 때문에, 처음 시작할 떄 AAA...인 string을 두고 직접 변환해가면서
name과 같아지면 바로 종료시키면 된다.

시도3)
A로 시작하는 경우 바로 뒤로 돌아가면 +1회가 추가되어야 한다.
이유는 A가 아닌 것으로 시작해서 A가 나온 경우로 이동한 다음을 고려한 상태이기 때문에,
다시 -1을 해준 상태인데 시작부터 A에서 시작하면 그걸 다시 +1회 하여 없에야한다.
이게 귀찮으면 다른 방법을 생각해봐야한다.

시도4)
처음 부터 다시 정리하면, 이 문제는 탐욕법이 적용 가능한 문제로
차례로 가는 경우와 돌아서 가는 2가지 경우를 모두 고려한 뒤
둘중 최적의 방식을 계속 선택해 나가는 식으로 풀면 된다.
문제가 탐욕법이라 하면, 왜 탐욕법인지도 알아야한다.

예를들어 ????AAAAAA....AAAAAA?????인 경우가 주어졌다고 가정하면, (?는 A가 아닌 알파벳)
최적의 경우는 돌아서 가든 똑바로 가든, 매번 제일 가깝게 고칠게 있는 곳으로 이동하면
결국 최소로 이동하게 된다. 이때 AAAA...AAA에 도달한 경우 돌아서 가는게 빠른지,
AAA...AAA를 넘어서 가는게 빠른지만 확인되면 된다.

시도5)
마지막 테스트 케이스에서 실패했다
입력이 ABAAAAAAAAABB 인 경우 앞을 먼저 갔다가
뒤를 가면 7회만에 끝낼 수 있는데, 이 코드는 처음에 거리가 같으면
뒤쪽을 먼저가도록 구현되어서 이 경우 8회가 나오게 된다.
즉, 초반에 거리가 같은 두 군데가 있는 경우는 그 다음 이동시 어디가 더 짧은지를 알아야한다.
그러면 재귀가 필요할 것 같은데 문제의 의도와 달리 그리디가 아닌것 같다.

시도6) <통과힘>
재귀를 활용한 완전탐색으로 풀었다.
그리디 문제로 내려면 조건을 더 넣던가 아니면
그냥 완전탐색 문제로 내야될 것 같다.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int updown(string& name, int pos)
{
    if(name[pos] > 'N')
    {
        return 26-(name[pos]-'A');
    }
    else
    {
        return name[pos]-'A';
    }
}

int recur(string& name, string& init, int cur)
{
    int N = name.size();
    // 탈출조건
    if(name == init)
    {
        return 0;
    }

    // 앞: A가 아닌 경우까지 cnt를 세본다
    int frontCnt = 0;
    while(name[(cur + frontCnt)%N] == 'A')
    {
        frontCnt++;
    }
    // 뒤: A가 아닌 경우까지 cnt를 세본다
    int backCnt = 0;
    int bidx = backCnt + cur;
    while(name[(bidx)%N] == 'A')
    {
        backCnt++;
        bidx--;
        if(bidx < 0)
            bidx += N;
    }

    // 시도6: 앞, 뒤 모두 시도해 보고 최소값 반환
    int ud = 0;    // updown cnt
    int f, b; // front, back
    char temp;
    temp = name[(cur+frontCnt)%N];
    ud = updown(name, (cur+frontCnt)%N);
    name[(cur+frontCnt)%N] = 'A';
    f = recur(name, init, (cur+frontCnt)%N) + ud + frontCnt;
    name[(cur+frontCnt)%N] = temp;

    temp = name[bidx];
    ud = updown(name, bidx);
    name[bidx] = 'A';
    b = recur(name, init, bidx) + ud + backCnt;
    name[bidx] = temp;

    if(f > b)
        return b;
    return f;
    
}

int solution(string name) {
    int answer = 0;
    int N = name.size();

    string init(N, 'A');    // 초기화 인자 주의(size, initial num)

    // 시도2: 완성된 경우 종료
    int cur = 0;

    answer = recur(name, init, cur);
    /*
    while(init != name)
    {
        // 시도4: 모든 상태에서 앞,뒤로 가는 최적의 경우를 선택한다
        // 앞: A가 아닌 경우까지 cnt를 세본다
        int frontCnt = 0;
        while(name[(cur + frontCnt)%N] == 'A')
        {
            frontCnt++;
        }
        // 뒤: A가 아닌 경우까지 cnt를 세본다
        int backCnt = 0;
        int bidx = backCnt + cur;
        while(name[(bidx)%N] == 'A')
        {
            backCnt++;
            bidx--;
            if(bidx < 0)
                bidx += N;
        }
        
        // 둘 중 더 빨리 갈 수 있는 곳으로 이동한다
        // 시도5: 같은 경우 둘 다 각각 이동했을 떄 다음 거리가 짧은 경우를 선택한다
        if(frontCnt == backCnt)
        {

        }
        else if(frontCnt < backCnt)
        {
            answer += frontCnt;
            cur = (cur+frontCnt)%N;
        }
        else
        {
            answer += backCnt;
            cur = bidx;
        }
        // 최소 updown 횟수로 target으로 바꾼다
        answer += updown(name, cur);
        // 두번 방문하는 일이 없도록 막는다.
        name[cur] = 'A';
    }*/

    return answer;
}

int main()
{
    string name = "JEROEN";

    cout << solution(name) << endl;

    return 0;
}