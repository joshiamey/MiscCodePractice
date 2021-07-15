#include<iostream>
#include<string>
#include<stack>
using namespace std;

string balancedbrackets(const string& brac)
{
    stack<char> bracket_stack;

    for(char c : brac)
    {
        if(c == '{' || c == '[' || c == '(')
        {
            bracket_stack.push(c);
        }
        else
        {
            // encountered closing bracket, pop opening bracket 
            if(bracket_stack.empty())
                return "NO"; // encountered closing bracket before opening one
            auto b = bracket_stack.top();
            
            auto matched = (c == '}' && b == '{') || (c == ')' && b == '(') || (c == ']' && b == '[');
            if(!matched)
            {
                return "NO";
            }
            
            bracket_stack.pop();
        }
    }

    return bracket_stack.empty() ? "YES" : "NO";
}

int main()
{
    cout << "Balanced: " << balancedbrackets("{[(())]}") <<endl;
    cout << "Balanced: " << balancedbrackets("{[((]))}") <<endl;
    cout << "Balanced: " << balancedbrackets("{[](())[]}") <<endl;

}