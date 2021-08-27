/*
같은 것이 있는 순열 (같은 것 끼리는 순서를 따지지 않는다)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> overlaping_permutations;

void overlaping_permutation(std::string& inputstr, int current_index)
{
	//탈출 조건: 현재 위치가 문자열 끝인 경우
	if (current_index == inputstr.size() - 1)
	{
		//std::cout << inputstr << std::endl;
		overlaping_permutations.emplace_back(inputstr);
		return;
	}

	// 현재 문자로 시작하는 경우
	// 현재 문자 위치 포함해서 정렬
	// 예시 입력: aaa..bbb..ccc..dddd...
	std::sort(inputstr.begin() + current_index, inputstr.end());

	// a로 시작하는 모든 case를 여기서 처리
	overlaping_permutation(inputstr, current_index + 1);
	
	// 완료 후 현재 문자 위치 재외하고 다시 정렬하여 다음 재귀 진입 준비
	// 현상태 예시: a(ddd..ccc..bb..aaaa...) --> 정렬 후: a(aa..bbb..ccc..ddd...)
	std::sort(inputstr.begin() + current_index + 1, inputstr.end());

	// 현재 문자로 시작하지 않는 경우 처리하는 법: 각 자리 문자와 현재 문자 위치 바꿔서 출력
	for (int i = current_index + 1; i < inputstr.size(); ++i)
	{
		//서로 같은 원소이면 바꿔도 겹치므로 넘어간다
		if (inputstr[current_index] == inputstr[i])
			continue;

		// 현재 문자가 순서상 다음 문자보다 작으면 현재 문자 위치와 다음 문자 위치 교환
		if (inputstr[current_index] < inputstr[i])
			std::swap(inputstr[current_index] ,inputstr[i]);
		
		//b(xxx), c(xxx), d(xxx)로 시작하는 모든 case를 처리
		overlaping_permutation(inputstr, current_index + 1);
		// 현재 문자 위치 제외하고 다시 정렬(xxx부분)하여 다음 재귀 진입
		std::sort(inputstr.begin() + current_index + 1, inputstr.end());
	}
}

void print_permutations()
{
	for (auto e : overlaping_permutations)
		std::cout << e << std::endl;
}

int main()
{
	std::string inputstring = "cababc";

	overlaping_permutation(inputstring, 0);

	print_permutations();

	return 0;
}