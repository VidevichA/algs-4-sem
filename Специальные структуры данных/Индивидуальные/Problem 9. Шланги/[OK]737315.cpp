#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::stack<std::pair<std::pair<double, double>, int>> stack;

    int n;
    in >> n;

    for (int i = 0; i < n; i++)
    {
        double x, y;
        int num;
        in >> x >> y >> num;

        if (stack.empty() || stack.top().second != num)
        {
            stack.push({{x, y}, num});
        }
        else
        {
            stack.pop();
        }
    }

    if (stack.empty())
    {
        out << "Yes";
    }
    else
    {
        out << "No";
    }
}