#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
std::vector<std::string> permutations;

//이 함수는 정렬된 문자열을 입력으로 줘야 작동한다.
void permutation(std::string& inputstr, int current_index)
{
	//탈출 조건: 현재 위치가 문자열 끝인 경우
	if (current_index == inputstr.size() - 1)
	{
		std::cout << inputstr << std::endl;
		permutations.emplace_back(inputstr);
		return;
	}

	// 현재 문자로 시작하는 경우 출력
	permutation(inputstr, current_index + 1);

	// 현재 문자로 시작하지 않는 경우 출력(각 자리 문자와 현재 문자 위치 바꿔서 출력)
	for (int i = current_index+1; i < inputstr.size(); ++i)
	{
		// 현재 문자 위치 포함해서 정렬
		std::sort(inputstr.begin()+current_index, inputstr.end());

		// 현재 문자 위치와 다음 문자 위치 교환
		char temp = inputstr[current_index];
		inputstr[current_index] = inputstr[i];
		inputstr[i] = temp;
		
		// 교환 후 현재 문자 위치 재외하고 다시 정렬하여 재귀 진입
		std::sort(inputstr.begin() + current_index + 1, inputstr.end());
		permutation(inputstr, current_index + 1);
	}
}
/*
int main()
{
	std::string inputstring= "abcd";

	//같은 것이 있는 순열은 작동하지 않는다.
	permutation(inputstring, 0);

	return 0;
}
*/