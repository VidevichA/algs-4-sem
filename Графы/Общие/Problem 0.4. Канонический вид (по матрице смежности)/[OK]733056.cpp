#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n;
    in >> n;
    std::vector<long long> v(n);
    for (long long i = 0; i < n; ++i)
    {
        for (long long j = 0; j < n; ++j)
        {
            bool temp;
            in >> temp;
            if (temp)
            {
                v[j] = i + 1;
            }
        }
    }
    for (auto el : v)
    {
        out << el << ' ';
    }
    return 0;
}