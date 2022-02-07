#include <iostream>
#include <string>
#include <stack>

using namespace std;

static int evaluate_util(const string &expr, int index, int &new_index)
{
    if (index <= 0)
    {
        return -1;
    }
    stack<char> bracket_stack;
    stack<int> operand_stack;
    char curr_op;

    while (index >= 0)
    {   
        char c = expr[index];

        if (isdigit(c))
        {
            operand_stack.push(c - '0');
        }
        else if (c == ')')
        {
            if (bracket_stack.empty())
            {
                bracket_stack.push(c);
            }
            else
            {
                int res_index;
                int res = evaluate_util(expr, index, res_index);
                operand_stack.push(res);
                index = res_index;
            }
        }
        else if (c == '(')
        {
            // if bracket_stack is emtpy throw an exception
            bracket_stack.pop();
            new_index = index;
            switch (curr_op)
            {
            case '+':
            {
                int tmp = 0;
                while (!operand_stack.empty())
                {
                    tmp += operand_stack.top();
                    operand_stack.pop();
                }

                operand_stack.push(tmp);
            }
            break;

            case '*':
            {
                int ans = 1;
                while (!operand_stack.empty())
                {
                    ans *= operand_stack.top();
                    operand_stack.pop();
                }

                operand_stack.push(ans);
            }
            break;

            default:
                break;
            }

            break;
        }
        else
        {
            curr_op = c;
        }

        --index;
    }

    int final_answer = operand_stack.top();
    operand_stack.pop();
    return final_answer;
}

static int evaluate(const string &expr)
{
    int index;
    return evaluate_util(expr, expr.length() - 1, index);
}

int main(int argc, char const *argv[])
{
    string expr = "(+ 2 3(* 4 5))";

    cout << evaluate(expr) << endl;
    return 0;
}
