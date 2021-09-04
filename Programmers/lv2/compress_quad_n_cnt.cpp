/*
쿼드압축 후 개수 세기
https://programmers.co.kr/learn/courses/30/lessons/68936

0과 1로 이루어진 2^n x 2^n 크기의 2차원 정수 배열 arr이 있습니다. 당신은 이 arr을 쿼드 트리와 같은 방식으로 압축하고자 합니다. 구체적인 방식은 다음과 같습니다.

당신이 압축하고자 하는 특정 영역을 S라고 정의합니다.
만약 S 내부에 있는 모든 수가 같은 값이라면, S를 해당 수 하나로 압축시킵니다.
그렇지 않다면, S를 정확히 4개의 균일한 정사각형 영역(입출력 예를 참고해주시기 바랍니다.)으로 쪼갠 뒤, 각 정사각형 영역에 대해 같은 방식의 압축을 시도합니다.
arr이 매개변수로 주어집니다. 위와 같은 방식으로 arr을 압축했을 때, 배열에 최종적으로 남는 0의 개수와 1의 개수를 배열에 담아서 return 하도록 solution 함수를 완성해주세요.

시도1)
재귀 방식으로 접근하였다.
4분할을 하면서 최종적으로는 하나의 칸에 접근하게 되고, 이 값을 반환하여
바로 윗 단계에서 4개 값을 수합하여, 한 군집에 0과 1이 몇개인지 세는 방식으로 구현하였다.
모두 0이거나 모두 1이면 일일이 세지않고 그대로 1을 반환하여 윗단계에서 수합되면서 값이 세지도록 하였다.
0과 1이 공존할 때만 각각 전역 변수에 추가하여 저장한 뒤 윗 단계에 -1을 반환해 주도록 하였다.
테케 절번 정도만 성공함

시도2)
size == N일때 탈출조건에서 0, 1이면 개수 세도록 수정
점수 소폭 상승, 전체적으로 손봐야할 부분이 있는거 같다

시도3)
size == N을 따로 처리하지 않도록 재귀 수정
allsame에서 모두 -1인 경우도 가능함을 인지함
수정 후 통과

*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> G_BOARD;
int N;
int ONES = 0;
int ZEROS = 0;

int recur(int row, int col, int size)
{
    if(size == 0)
    {   // 최대 깊이 도달
        return G_BOARD[row][col];
    }
    // 4분할
    int half = size/2;
    vector<int> results;
    results.push_back(recur(row, col, half));
    results.push_back(recur(row, col+half, half));
    results.push_back(recur(row+half, col, half));
    results.push_back(recur(row+half, col+half, half));

    bool allsame = true;
    for(auto e: results)
    {
        if(e != results[0])
        {
            allsame = false;
            break;
        }
    }
    if(allsame)
    {   // 다음 단계에서 1개로 보도록 각각 압축된 수 반환
        if(results[0] == 1)
            return 1;
        else if(results[0] == 0)
            return 0;
        else    // 다 -1인 경우도 가능
            return -1;
    }
    else
    {   // 각각 개수 세고 -1 반환
        for(auto e: results)
            if(e == 1)
                ONES++;
            else if(e == 0)
                ZEROS++;
        return -1;
    }
}

vector<int> solution(vector<vector<int>> arr) {
    vector<int> answer;
    G_BOARD = arr;
    N = arr.size();

    int ans = recur(0, 0, N);
    if(ans == 1)
        ONES++;
    else if(ans == 0)
        ZEROS++;
    else
    {
        // -1인 경우: None
    }

    return answer = {ZEROS, ONES};
}

int main()
{
    //vector<vector<int>> arr = {{1,1,0,0},{1,0,0,0},{1,0,0,1},{1,1,1,1}};
    vector<vector<int>> arr = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};

    solution(arr);

    return 0;
}