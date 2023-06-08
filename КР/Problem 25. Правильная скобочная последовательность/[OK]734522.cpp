#include <fstream>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    string s;

    in >> s;

    if (s == "")
    {
        out << "YES";
        return 0;
    }

    stack<char> stack;

    int p = 0;

    bool ex = false;

    for (int i = 0; i < s.length() && !ex; i++)
    {
        switch (s[i])
        {
        case ')':
            if (!stack.empty() && stack.top() == '(')
            {
                stack.pop();
                p = i + 1;
            }
            else if (stack.empty())
            {
                stack.push(s[i]);
                ex = true;
                p = i;
            }
            else
            {
                p = i;
                ex = true;
            }
            break;
        case '}':
            if (!stack.empty() && stack.top() == '{')
            {
                stack.pop();
                p = i + 1;
            }
            else if (stack.empty())
            {
                stack.push(s[i]);
                ex = true;
                p = i;
            }
            else
            {
                p = i;
                ex = true;
            }
            break;
        case ']':
            if (!stack.empty() && stack.top() == '[')
            {
                stack.pop();
                p = i + 1;
            }
            else if (stack.empty())
            {
                stack.push(s[i]);
                ex = true;
                p = i;
            }
            else
            {
                p = i;
                ex = true;
            }
            break;
        default:
            stack.push(s[i]);
            p = i + 1;
            break;
        }
    }

    if (stack.size() != 0)
    {
        out << "NO" << endl
            << p;
    }
    else
    {
        out << "YES";
    }
}