#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int temp;
    int size;
    in >> size;
    std::vector<int> numbers;
    while (in >> temp)
    {
        numbers.push_back(temp);
    }
    if (size == 1)
    {
        out << numbers[0];
        return 0;
    }
    if (size == 2)
    {
        out << std::max(numbers[0], numbers[1]);
        return 0;
    }
    std::vector<int> s(size);
    for (int i = 0; i < size; ++i)
    {
        if (i == 0)
        {
            s[i] = numbers[i];
        }
        else
        {
            s[i] = numbers[i] + s[i - 1];
        }
    }
    std::vector<std::vector<int>> f(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i)
    {
        f[i][i] = numbers[i];
        if (i == size - 1)
        {
            continue;
        }
        f[i][i + 1] = std::max(numbers[i], numbers[i + 1]);
    }

    for (int j = 2; j < size; ++j)
    {
        for (int i = j - 2; i >= 0; --i)
        {
            f[i][j] = s[j] - s[i] + numbers[i] - std::min(f[i + 1][j], f[i][j - 1]);
        }
    }
    out << f[0][size - 1];
    return 0;
}