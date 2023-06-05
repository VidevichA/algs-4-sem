#include <fstream>
#include <vector>
#include <string>

#include <iostream>
int main()
{
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    int x;
    in >> x;
    int y;
    in >> y;
    int z;
    in >> z;
    std::string firstStr;
    in >> firstStr;
    std::string secondStr;
    in >> secondStr;
    std::vector<std::vector<int>> f(firstStr.size() + 1, std::vector<int>(secondStr.size() + 1));
    for (int i = 0; i < secondStr.size() + 1; ++i)
    {
        f[0][i] = i * y;
    }
    for (int i = 0; i < firstStr.size() + 1; ++i)
    {
        f[i][0] = i * x;
    }
    for (int i = 1; i < firstStr.size() + 1; ++i)
    {
        for (int j = 1; j < secondStr.size() + 1; ++j)
        {
            f[i][j] = std::min(f[i - 1][j] + x, std::min(f[i][j - 1] + y, f[i - 1][j - 1] + z * (firstStr[i - 1] == secondStr[j - 1] ? 0 : 1)));
        }
    }
    out << f[f.size() - 1][f[0].size() - 1];
    return 0;
}