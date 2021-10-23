/*
codeground 나 구름ide 같은 환경에서 코딩 테스트를 치는 경우
파일에서 읽어오는 식으로 예제 입력을 구성해야할 때가 있다.
*/

#include <iostream>
#include <string>

freopen("파일명.txt", "r", stdin);  // 파일명.txt 파일을 읽기 모드로 stdin 스트림에 연결
// 이후로 cin 등을 사용하면 키보드 입력 대신 파일에서 읽는다.
// cin 만 사용하면 공백을 기준으로 끊어 읽는다. (자료형은 container에 맞으면 자동으로 맞춰진다)
// 한 줄을 통째로 읽고 싶은 경우 getline(cin, string)을 사용한다.

// 한 줄 읽기
std::string temp;
std::getline(cin, temp); // 3번째 인자로 파싱할 문자열을 넣어 끊을 수 있음. (StringOperation.cpp 파싱 예제 참고)

// getline과 cin을 같이 쓸 때 주의 사항
/*
2차원 배열을 입력으로 할 때, (숫자인 경우는 cin으로 다 처리 가능하므로 문자열이 원소라 가정)
3 4
a b c d
ax bx bx dx
z y x v
이런 식의 입력을 사용하는 경우가 있다.
이 때 맨 윗줄 3 4를 
int R, C;
cin >> R >> C; 로 받고,
이어서는
getline()으로 한 줄씩 읽어서 처리하려 할 떄,
cin >> R >> C;로 처리하면 다음에 한 줄 읽기를 위해 실행한 getline(cin, buff);의 
buff의 상태가 "a b c d"가 아닌 ""인 상태가 된다.
파일 오프셋 위치가 아직 맨 윗줄에 문자열 끝(string::npos)에 존재하는데 getline이 호출된 상황인 것 같다.
이런 문제를 미리 숙지하여 맨 윗줄도 getline으로 파싱하거나,
처음 getline은 "" 인 경우를 처리하도록 두고,
다음 getline 부터가 제대로 다음 줄을 읽는다는 점을 숙지해 두자.
*/