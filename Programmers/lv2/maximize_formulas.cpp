/*
수식 최대화
https://programmers.co.kr/learn/courses/30/lessons/67257

해커톤 대회에 참가하는 모든 참가자들에게는 숫자들과 3가지의 연산문자(+, -, *) 만으로 이루어진 연산 수식이 전달되며, 참가자의 미션은 전달받은 수식에 포함된 연산자의 우선순위를 자유롭게 재정의하여 만들 수 있는 가장 큰 숫자를 제출하는 것입니다.
단, 연산자의 우선순위를 새로 정의할 때, 같은 순위의 연산자는 없어야 합니다. 즉, + > - > * 또는 - > * > + 등과 같이 연산자 우선순위를 정의할 수 있으나 +,* > - 또는 * > +,-처럼 2개 이상의 연산자가 동일한 순위를 가지도록 연산자 우선순위를 정의할 수는 없습니다. 수식에 포함된 연산자가 2개라면 정의할 수 있는 연산자 우선순위 조합은 2! = 2가지이며, 연산자가 3개라면 3! = 6가지 조합이 가능합니다.
만약 계산된 결과가 음수라면 해당 숫자의 절댓값으로 변환하여 제출하며 제출한 숫자가 가장 큰 참가자를 우승자로 선정하며, 우승자가 제출한 숫자를 우승상금으로 지급하게 됩니다.

?:
참가자에게 주어진 연산 수식이 담긴 문자열 expression이 매개변수로 주어질 때, 우승 시 받을 수 있는 가장 큰 상금 금액을 return 하도록 solution 함수를 완성해주세요.

!!!:
expression은 길이가 3 이상 100 이하인 문자열입니다.
expression은 공백문자, 괄호문자 없이 오로지 숫자와 3가지의 연산자(+, -, *) 만으로 이루어진 올바른 중위표기법(연산의 두 대상 사이에 연산기호를 사용하는 방식)으로 표현된 연산식입니다. 잘못된 연산식은 입력으로 주어지지 않습니다.
즉, "402+-561*"처럼 잘못된 수식은 올바른 중위표기법이 아니므로 주어지지 않습니다.
expression의 피연산자(operand)는 0 이상 999 이하의 숫자입니다.
즉, "100-2145*458+12"처럼 999를 초과하는 피연산자가 포함된 수식은 입력으로 주어지지 않습니다.
"-56+100"처럼 피연산자가 음수인 수식도 입력으로 주어지지 않습니다.
expression은 적어도 1개 이상의 연산자를 포함하고 있습니다.
연산자 우선순위를 어떻게 적용하더라도, expression의 중간 계산값과 최종 결괏값은 절댓값이 263 - 1 이하가 되도록 입력이 주어집니다.
같은 연산자끼리는 앞에 있는 것의 우선순위가 더 높습니다.

시도1) stack으로 중위표기식을 후위표기식으로 변경하여 연산자 순으로 계산하게 구현
하지만, 같은 연산자끼리는 앞에 있는것을 먼저 처리해야 하므로 구현이 꼬인다...
시도2) 중위 표기식 상태로 연산자 우선 순위에 따라 처리하도록 변경
통과!
*/
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

map<string, int> G_OPORDER;
vector<string> G_OPS;

vector<string> parse_exp(string& exp)
{
    vector<string> ret;
    int last = 0;
    for(int i=0; i<exp.size(); ++i)
    {
        if(!isdigit(exp[i]))
        {
            ret.push_back(exp.substr(last, i-last));
            ret.push_back(exp.substr(i, 1));
            last = i+1;
        }
    }
    ret.push_back(exp.substr(last, exp.size()-last));
    return ret;
}

bool opOrder(string op1, string op2)    // stack, cur
{   // 같은 연산자 끼리는 먼저 들어온 연산자가 우선(stack에 있을 것임)
    return G_OPORDER[op1] >= G_OPORDER[op2];
}

/* 시도1
vector<string> inorder2postorder(vector<string> inorder)
{
    vector<string> post;
    stack<string> opStack;

    for(string s: inorder)
    {
        if(isdigit(s[0]))
        {   // 피연산자는 스택에 넣지 않고 그냥 출력
            post.push_back(s);
        }
        else
        {   // 연산자는 스택이 비었으면 스택에 push
            if(opStack.empty())
                opStack.push(s);
            else    // 연산자는 스택이 비어있지 않으면
            {   // 스택에 있는 연산자와의 우선순위를 비교해 스택에 있는 연산자의 우선순위가 같거나 크다면(여기선 우선순위가 같은 경우는 없다)
                if(opOrder(opStack.top(), s))
                {   // 스택에 있는 연산자를 pop을 한 후 출력하고 현재 연산자는 스택에 push
                    string op = opStack.top(); opStack.pop();
                    post.push_back(op);
                    opStack.push(s);
                }
                else    // 우선순위가 현재 연산자가 더 크면 현재 연산자를 push
                    opStack.push(s);
            }
        }
    }
    // 수식이 끝나면 스택이 빌 때 까지 pop을 한 후 출력
    while(!opStack.empty())
    {
        string op = opStack.top(); opStack.pop();
        post.push_back(op);
    }
    return post;
}

long long calcpost(vector<string>& post)
{
    stack<long long> numStack;
    bool once = true;
    for(string s: post)
    {
        if(isdigit(s[0]))
        {   // 피연산자면 스택에 push
            numStack.push(stoll(s));
        }
        else
        {   // 연산자를 만나면 pop을 두번하고 각각 값을 저장한 후, 연산자에 맞는 계산을 한다
            long long a = numStack.top(); numStack.pop();
            long long b = numStack.top(); numStack.pop();
            // 계산을 한 뒤, 결과 값은 다시 스택에 넣는다
            switch (s[0])
            {
            case '+':
                numStack.push(b+a);
                break;
            case '-':
                numStack.push(a-b); // - 인 경우는 원래대로 돌렸으므로 a-b로 계산해야 순서대로 계산됨
                break;
            case '*':
                numStack.push(b*a);
                break;
            }
        }
    }
    // 수식이 끝났다면 스택에 마지막 남은 값이 결과 값
    return numStack.top();
}
*/

long long calcin(vector<string> inorder)
{
    vector<string> temp;
    for(int i=0; i<G_OPS.size(); ++i)
    {
        for(int s=0; s<inorder.size(); ++s)
        {
            if(inorder[s] == G_OPS[i])
            {
                long long a = stoll(temp[temp.size()-1]);
                temp.pop_back();
                long long b = stoll(inorder[s+1]);
                string calc;
                switch (inorder[s][0])
                {
                case '+':
                    calc = to_string(a+b);
                    break;
                case '-':
                    calc = to_string(a-b);
                    break;
                case '*':
                    calc = to_string(a*b);
                    break;
                }
                ++s;
                temp.push_back(calc);
            }
            else
                temp.push_back(inorder[s]);
        }
        inorder = temp;
        temp.clear();
    }
    return stoll(inorder[0]);
}

long long solution(string expression) {
    long long answer = 0;

    // 수식 parsing
    vector<string> parsed = parse_exp(expression);

    // 사용된 연산자 종류 파악
    set<string> opset;
    for(auto op : parsed)
    {
        if(isdigit(op[0]))
            continue;
        opset.insert(op);
    }
    
    G_OPS.clear();
    for(auto s: opset)
        G_OPS.push_back(s);

    // 연산자 우선순위 변경: 순열로 가능한 경우 모두 구성
    do
    {   // 이번에 시도할 순서
        for(int i=0; i<G_OPS.size(); ++i)
        {
            G_OPORDER[G_OPS[i]] = i;
        }
        /* 시도1
        // 중위 표기식을 후위 표기식으로 변경
        vector<string> post = inorder2postorder(parsed);
        // 후위 표기식을 계산
        long long ans = calcpost(post);
        ans = abs(ans);
        answer = max(answer, ans);
        */
        // 시도2: 중위 표기식 상태로 우선 순위 연산자를 수행
        long long ans = calcin(parsed);
        ans = abs(ans);
        answer = max(answer, ans);
    }
    while(next_permutation(G_OPS.begin(), G_OPS.end()));

    return answer;
}

int main()
{
    string expression = "100-200*300-500+20";
    //string expression = "50*6-3*2";

    cout << solution(expression) << endl;

    return 0;
}