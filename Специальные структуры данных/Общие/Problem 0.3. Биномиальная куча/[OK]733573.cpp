#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

std::vector<int> findBinomialTrees(long long n)
{
    std::vector<int> heights;
    for (int i = 0; n > 0; i++)
    {
        if (n & 1)
        {
            heights.push_back(i);
        }
        n >>= 1;
    }

    return heights;
}

int main()
{
    std::ifstream fin("common/data_struct/bin_heap/input.txt");
    std::ofstream ofStream("common/data_struct/bin_heap/output.txt");
    long long n;
    fin >> n;

    std::vector<int> heights = findBinomialTrees(n);
    for (int height : heights)
    {
        ofStream << height << "\n";
    }

    return 0;
}