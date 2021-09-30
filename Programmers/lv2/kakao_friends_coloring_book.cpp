/*
카카오 프렌즈 컬러링 북
https://programmers.co.kr/learn/courses/30/lessons/1829

그림에 몇 개의 영역이 있는지와 가장 큰 영역의 넓이는 얼마인지 계산하는 프로그램을 작성해보자.

입력은 그림의 크기를 나타내는 m과 n, 그리고 그림을 나타내는 m × n 크기의 2차원 배열 picture로 주어진다. 제한조건은 아래와 같다.

1 <= m, n <= 100
picture의 원소는 0 이상 2^31 - 1 이하의 임의의 값이다.
picture의 원소 중 값이 0인 경우는 색칠하지 않는 영역을 뜻한다.
리턴 타입은 원소가 두 개인 정수 배열이다. 그림에 몇 개의 영역이 있는지와 가장 큰 영역은 몇 칸으로 이루어져 있는지를 리턴한다.

시도1)
간단한 DFS나 BFS방식으로 영역의 개수와 크기를 구하면 되는 문제이다.
*/

#include <vector>
#include <algorithm>

using namespace std;
using pos = pair<int, int>;

vector<pos> DIRS = {{-1, 0}, {0,-1},{1,0},{0,1}};   // ULDR

bool InRange(pos p, int R, int C)
{
    int r = p.first, c = p.second;
    if(0<=r && r < R && 0<=c && c < C)
        return true;
    return false;
}

int DFS(pos start, vector<vector<bool>>& visited, vector<vector<int>>& picture)
{
    int r = start.first, c = start.second;
    int ret = 0;
    for(int d=0; d<DIRS.size(); ++d)
    {
        pos next = {r+DIRS[d].first, c+DIRS[d].second};

        if(!InRange(next, picture.size(), picture[0].size()))
            continue;   // 배열 범위 X
        if(visited[next.first][next.second])
            continue;   // 방문한적 있는 곳이면 X
        
        // 같은 영역만 방문한다
        if(picture[r][c] == picture[next.first][next.second])
        {
            visited[next.first][next.second] = true;
            ret += DFS(next, visited, picture)+1;
        }
    }
    return ret;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for(int row=0; row<m; ++row)
    {
        for(int col=0; col<n; ++col)
        {
            if(picture[row][col] == 0)
                continue;
            if(visited[row][col])
                continue;
            int area_size = DFS({row, col}, visited, picture);
            max_size_of_one_area = max(max_size_of_one_area, area_size);
            number_of_area++;
        }
    }
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}

int main()
{
    int m = 6;
    int n = 4;
    vector<vector<int>> picture = {{1, 1, 1, 0}, {1, 2, 2, 0}, {1, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 3}, {0, 0, 0, 3}};
    solution(m, n, picture);

    return 0;
}