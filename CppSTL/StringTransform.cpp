

#include <string>
#include <iostream>

#include <algorithm>    // transform

using namespace std;

enum class CASE
{
    UPPER,
    LOWER,
};

void TransformString(string& inputStr, CASE c)
{
    // transform(begin, end, writing pos, func) => writing pos: 변환 결과가 들어갈 자리, func: 변환 적용할 함수
    transform(inputStr.begin(), inputStr.end(), inputStr.begin(), [&](auto element) -> unsigned char{
        // 이 람다식이 inputStr의 각각의 요소에 적용되는 변환 함수이다
        // []안에 &:참조 연산자 안쓰면 외부 변수인 CASE c를 capture하는데 실패하므로 주의
        switch (c)
        {
            case CASE::UPPER:
                return toupper(element);
            case CASE::LOWER:
                return tolower(element);
            default:
                return element; // -> unsigned char로 반환형 명시 하지 않으면 (int, char) 두 가지로 모호함이 발생하여 컴파일 에러가 발생함.
        }
    });
}

int main()
{
    string lowerCase = "hello world";
    TransformString(lowerCase, CASE::UPPER);
    cout << lowerCase << endl;
    TransformString(lowerCase, CASE::LOWER);
    cout << lowerCase << endl;

    return 0;
}