#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

int main()
{
    std::ifstream in("in.txt");
    std::stack<int> stack;
    int n = 0;
    int m = 0;
    in >> n >> m;
    std::vector<std::vector<int>> A(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            in >> A[i][j];
        }
    }
    int temp;
    for (int t = 0; t < m; t++)
    {
        in >> temp;
        for (;;)
        {
            if (!stack.empty())
            {
                int i = temp - 1;
                int j = stack.top() - 1;
                if (A[i][j] == 0)
                {
                    stack.push(temp);
                    break;
                }
                else
                {
                    stack.pop();
                    temp = A[i][j];
                }
            }
            else
            {
                stack.push(temp);
                break;
            }
        }
    }
    std::ofstream out("out.txt");
    for (int i = stack.size(); i > 1; i--)
    {
        out << stack.top() << " ";
        stack.pop();
    }
    out << stack.top();
    return 0;
}