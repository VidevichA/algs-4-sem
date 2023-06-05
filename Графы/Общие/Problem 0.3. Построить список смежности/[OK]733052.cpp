#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n, m;
    in >> n >> m;
    std::vector<std::vector<long long>> mat(n);
    for (long long i = 0; i < m; ++i)
    {
        long long k1, k2;
        in >> k1 >> k2;
        mat[k1 - 1].push_back(k2);
        mat[k2 - 1].push_back(k1);
    }
    for (auto r : mat)
    {
        out << r.size() << ' ';
        for (auto c : r)
        {
            out << c << ' ';
        }
        out << '\n';
    }
    return 0;
}