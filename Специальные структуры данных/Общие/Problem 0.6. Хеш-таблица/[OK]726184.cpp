#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long size;
    in >> size;
    long long c;
    in >> c;
    long long n;
    in >> n;
    std::vector<long long> v(size, -1);
    for (long long i = 0; i < n; ++i)
    {
        long long key;
        in >> key;
        auto it = std::find(v.begin(), v.end(), key);
        if (it != v.end())
        {
            continue;
        }
        for (long long j = 0; j < size; ++j)
        {
            long long temp = ((key % size) + c * j) % size;
            if (v[temp] == -1)
            {
                v[temp] = key;
                break;
            }
        }
    }
    for (auto el : v)
    {
        out << el << " ";
    }
    return 0;
}