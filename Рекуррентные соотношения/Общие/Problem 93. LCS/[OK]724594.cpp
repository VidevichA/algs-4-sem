#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int size;
    std::cin >> size;
    std::vector<int> a;
    std::vector<int> b;
    int temp;
    for (int i = 0; i < 2 * size; ++i)
    {
        std::cin >> temp;
        if (i < size)
        {
            a.push_back(temp);
        }
        else
        {
            b.push_back(temp);
        }
    }
    std::vector<std::vector<int>> f(size + 1, std::vector<int>(size + 1, 0));
    for (int i = 1; i <= size; ++i)
    {
        for (int j = 1; j <= size; ++j)
        {
            if (a[i - 1] == b[j - 1])
            {
                f[i][j] = f[i - 1][j - 1] + 1;
            }
            else
            {
                f[i][j] = std::max(f[i - 1][j], f[i][j - 1]);
            }
        }
    }
    std::cout << f[size][size];
    std::cout << "\n";
    std::vector<int> resultA;
    std::vector<int> resultB;
    int i = size;
    int j = size;
    while (i != 0 && j != 0 && f[i][j] != 0)
    {
        if (a[i - 1] == b[j - 1])
        {
            resultA.push_back(--i);
            resultB.push_back(--j);
        }
        else
        {
            if (f[i][j] == f[i - 1][j])
            {
                --i;
            }
            else
            {
                --j;
            }
        }
    }
    for (i = resultA.size() - 1; i >= 0; --i)
    {
        if (i == 0)
        {
            std::cout << resultA[i];
        }
        else
        {
            std::cout << resultA[i] << " ";
        }
    }
    std::cout << "\n";
    for (i = resultA.size() - 1; i >= 0; --i)
    {
        if (i == 0)
        {
            std::cout << resultB[i];
        }
        else
        {
            std::cout << resultB[i] << " ";
        }
    }
    return 0;
}