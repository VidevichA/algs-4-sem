#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n;
    in >> n;
    if (n == 1)
    {
        out << 0;
        return 0;
    }
    std::vector<long long> v(n, 0);
    for (long long i = 0; i < n; ++i)
    {
        long long k1, k2;
        in >> k1 >> k2;
        v[k2 - 1] = k1;
    }
    for (auto el : v)
    {
        out << el << ' ';
    }
    return 0;
}