#include <string>
#include <vector>
#include <iostream>

using namespace std;

int answer = 0;
int Target;

// DFS로 모든 경우를 순회하며 개수를 세본다.
void DFS(vector<int>& nums, int val, int depth)
{
    if(depth == nums.size())
    {
        if(val == Target)
            answer++;
            
        return;
    }

    DFS(nums, val+nums[depth], depth+1);
    DFS(nums, val-nums[depth], depth+1);
}


int solution(vector<int> numbers, int target) {
    Target = target;
    DFS(numbers, 0, 0);

    return answer;
}

int main()
{
    vector<int> numbers = {1,1,1,1,1};
    int target = 3;

    cout << solution(numbers, target) << endl;

    return 0;
}