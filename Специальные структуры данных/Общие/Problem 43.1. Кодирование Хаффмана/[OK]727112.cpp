#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int main()
{
    std::ifstream in("huffman.in");
    std::ofstream out("huffman.out");
    long long size;
    in >> size;
    std::vector<long long> vals(size);
    for (int i = 0; i < size; ++i)
    {
        long long temp;
        in >> temp;
        vals[i] = temp;
    }
    long long sum = 0;
    std::priority_queue<long long, std::vector<long long>, std::greater<>> pVals(vals.begin(), vals.end());
    while (pVals.size() != 1)
    {
        long long a = pVals.top();
        pVals.pop();
        long long b = pVals.top();
        pVals.pop();
        sum += a + b;
        pVals.push(a + b);
    }
    out << sum << '\n';
    return 0;
}