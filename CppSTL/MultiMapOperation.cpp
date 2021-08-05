
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::multimap<std::string, int> mulmap;

    // multimap은 []를 사용할 수 없다. 대신 insert를 사용한다
    mulmap.insert({"hellow", 1});
    mulmap.insert({"hellow", 3});
    mulmap.insert({"hellow", 2});
    mulmap.insert({"hellow", 2});
    mulmap.insert({"hellow", 1});
    mulmap.insert({"hellow", 4});
    mulmap.insert({"hellow", 2});
    mulmap.insert({"hellow", 2});

    // 키에 대한 값들을 참고할 때는 equal_range(key)를 사용한다
    // 반환형은 pair<iter, iter> 로 각각 시작과 끝 반복자이다
    auto pair_it = mulmap.equal_range("hellow");
    // multimap은 들어온 순서대로 출력한다(정렬이 기본이 아니다)
    for(auto it = pair_it.first; it != pair_it.second; ++it)
    {   // it는 <key, value> pair이다.
        std::cout << it->first << ":" << it->second << std::endl;
    }

    // multimap을 정렬하고 싶은 경우
    // vector로 옮긴 후 정렬하여 다시 multimap으로 옮긴다
    std::vector<std::pair<std::string, int>> tempvect;
    std::copy(mulmap.begin(), mulmap.end(), std::back_inserter(tempvect));

    sort(tempvect.begin(), tempvect.end(), [](auto a, auto b){
        if(a.first == b.first)
            return a.second < b.second;
        return a.first < b.first;
    });

    // map으로 다시 복사한다 (inserter를 사용하면 원본을 안날리면 지정한 위치에 이어붙인다.)
    // std::back_inserter도 있다. 이 경우는 끝에서 이어 붙인다. inserter(container, container.end())와 같다
    std::copy(tempvect.begin(), tempvect.end(), std::inserter(mulmap, mulmap.begin()));

    pair_it = mulmap.equal_range("hellow");
    // multimap은 들어온 순서대로 출력한다(정렬이 기본이 아니다)
    for(auto it = pair_it.first; it != pair_it.second; ++it)
    {   // it는 <key, value> pair이다.
        std::cout << "sorted: " << it->first << ":" << it->second << std::endl;
    }

    return 0;
}