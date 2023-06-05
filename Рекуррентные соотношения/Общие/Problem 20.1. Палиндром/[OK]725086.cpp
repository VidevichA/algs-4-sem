#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

#include <iostream>

int main()
{
    std::ofstream out("output.txt");
    std::ifstream in("input.txt");
    std::string inString;
    in >> inString;
    if (inString.empty())
    {
        out << 0 << "\n"
            << "";
        return 0;
    }
    int size = inString.size();
    std::vector<std::vector<int>> f(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i)
    {
        f[i][i] = 1;
        if (i == size - 1)
        {
            continue;
        }
        f[i][i + 1] = inString[i] == inString[i + 1] ? 2 : 1;
    }
    for (int j = 2; j < size; ++j)
    {
        for (int i = j - 2; i >= 0; --i)
        {
            if (inString[i] == inString[j])
            {
                f[i][j] = f[i + 1][j - 1] + 2;
            }
            else
            {
                f[i][j] = std::max(f[i + 1][j], f[i][j - 1]);
            }
        }
    }
    if (f[0][size - 1] == 1)
    {
        out << 1 << "\n"
            << inString[0];
        return 0;
    }
    out << f[0][size - 1];
    int i = 0;
    int j = size - 1;
    std::string result = "";
    while (f[i][j] != 0)
    {
        if (inString[i] == inString[j])
        {
            result += inString[i];
            ++i;
            --j;
        }
        else
        {
            if (f[i][j] == f[i][j - 1])
            {
                --j;
            }
            else
            {
                ++i;
            }
        }
    }
    std::string temp = "";
    for (int i = 0; i < f[0][size - 1] - result.size(); ++i)
    {
        temp += result[i];
    }
    std::reverse(temp.begin(), temp.end());
    out << "\n"
        << result + temp;
    return 0;
}