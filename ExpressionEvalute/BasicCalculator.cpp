#include <string>
#include <sstream>
#include <iostream>
#include <stack>
using namespace std;

static int calulate_util(const string &expr, int &index)
{
    if (index < 0)
    {
        return -1;
    }
    stack<int> operand;
    char curr_op;
    int curr_num = 0;
    int multiplier = 1;
    while (index >= 0)
    {
        char c = expr[index];

        if (isdigit(c))
        {
            curr_num += multiplier * (expr[index] - '0');
            multiplier *= 10;
        }
        else if (c == ')')
        {
            curr_num = calulate_util(expr, --index);
            // operand.push(res);

            multiplier = 1;
        }
        else
        {
            multiplier = 1;
            if (c != '*' && c != '/' && c != '-' && c != '+' && !isspace(c) && c != '(')
            {
                throw runtime_error("Invalid character in the expr");
            }

            if (!isspace(c))
            {

                if (c == '(')
                {
                    break;
                }
                else
                {
                    switch (curr_op)
                    {
                    case '*':
                    {
                        int op1 = operand.top();
                        operand.pop();
                        curr_num *= op1;
                    }
                    break;

                    case '/':
                    {
                        int op2 = operand.top();
                        operand.pop();
                        curr_num = curr_num / op2;
                    }
                    break;

                    case '-':
                    {
                        int op2 = operand.top();
                        operand.pop();
                        curr_num = curr_num - op2;
                    }

                    default:
                        break;
                    }
                }

                curr_op = c;
                operand.push(curr_num);
                curr_num = 0;
            }
        }

        --index;
    }

    if (curr_op == '-')
    {
        int op2 = operand.top();
        operand.pop();
        curr_num = curr_num - op2;
    }

    while (!operand.empty())
    {
        curr_num += operand.top();
        operand.pop();
    }

    return curr_num;
}

// static int calculate(const string &expr, int start, int end)
// {
//     stack<int> operand;
//     stack<int> bracket;
//     char curr_op = '+';
//     int curr_num = 0;
//     for (int it = start; it <= end; ++it)
//     {
//         char c = expr[it];

//         if (isdigit(c))
//         {
//             curr_num += curr_num * 10 + (c - '0');
//         }
//         else if (c == '(')
//         {
//             bracket.push(it);
//         }
//         else if (c == ')')
//         {
//             auto begin_bracket = bracket.top();
//             bracket.pop();
//             curr_num = calculate(expr, ++begin_bracket, --it);
//         }
//         else
//         {
//             if (c != '*' && c != '/' && c != '-' && c != '+' && !isspace(c))
//             {
//                 throw runtime_error("Invalid character in the expr");
//             }

//             if (isspace(c))
//                 continue;

//             switch (curr_op)
//             {
//             case '*':
//             {
//                 int op1 = operand.top();
//                 operand.pop();
//                 curr_num *= op1;
//             }
//             break;

//             case '/':
//             {
//                 int op1 = operand.top();
//                 operand.pop();
//                 curr_num = op1 / curr_num;
//             }
//             break;

//             case '-':
//                 curr_num = -curr_num;
//             default:
//                 break;
//             }
//             curr_op = c;
//             operand.push(curr_num);
//             curr_num = 0;
//         }
//     }

//     if (curr_op == '-')
//     {
//         curr_num = -curr_num;
//     }

//     while (!operand.empty())
//     {
//         curr_num += operand.top();
//         operand.pop();
//     }

//     return curr_num;
// }

static int calculate(const string &st)
{
    int index = st.size() - 1;
    return calulate_util(st, index);
}
int main(int argc, char const *argv[])
{
    // string exp = "(1+(4+5+2)-3)+(6+8)";
    string exp = "2147483647";
    cout << calculate(exp) << endl;
    return 0;
}
