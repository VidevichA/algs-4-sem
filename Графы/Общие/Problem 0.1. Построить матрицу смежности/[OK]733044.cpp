#include <fstream>
#include <vector>
#include <iostream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n, m;
    in >> n >> m;
    std::vector<std::vector<bool>> matrix(n, std::vector<bool>(n, 0));
    for (int i = 0; i < m; ++i)
    {
        long long k1, k2;
        in >> k1 >> k2;
        matrix[k1 - 1][k2 - 1] = 1;
        matrix[k2 - 1][k1 - 1] = 1;
    }
    for (auto r : matrix)
    {
        for (auto c : r)
        {
            out << c << ' ';
        }
        out << '\n';
    }
    return 0;
}