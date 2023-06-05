#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

template <typename T>
void PrintVector(const std::vector<T> &v)
{
    std::cout << '\n';
    for (auto el : v)
    {
        std::cout << el << ' ';
    }
    std::cout << '\n';
}

template <typename T>
void PrintMatrix(const std::vector<std::vector<T>> &m)
{
    std::cout << '\n';
    for (auto r : m)
    {
        for (auto c : r)
        {
            std::cout << c << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
typedef long long number;

number Mod(number n, number m)
{
    if (n % m < 0)
    {
        return n % m + m;
    }
    return n % m;
}

int main()
{
    number size;
    std::cin >> size;
    std::vector<number> el(size);
    std::vector<number> sum(size);
    for (number i = 0; i < size; ++i)
    {
        number temp;
        std::cin >> temp;
        el[i] = temp;
        if (i == 0)
        {
            sum[i] = el[i];
        }
        else
        {
            sum[i] = sum[i - 1] + el[i];
        }
    }
    std::vector<std::vector<number>> dp(size, std::vector<number>(size, 0));
    number s = 0;
    for (int j = 1; j < size; ++j)
    {
        for (int i = j - 1; i >= 0; --i)
        {
            dp[i][j] = std::min(dp[i + 1][j] + Mod(20 * (sum[j] - sum[i + 1] + el[i + 1]) - 23 * el[i], 1000000007), dp[i][j - 1] + Mod(20 * (sum[j - 1] - sum[i] + el[i]) - 23 * el[j], 1000000007));
        }
    }
    std::cout << dp[0][size - 1];
    number i = 0;
    number j = size - 1;
    std::vector<number> answer;
    while (answer.size() < size - 1)
    {
        if (dp[i][j] - dp[i][j - 1] == Mod(20 * (sum[j - 1] - sum[i] + el[i]) - 23 * el[j], 1000000007))
        {
            answer.push_back(j-- + 1);
        }
        else
        {
            answer.push_back(++i);
        }
    }
    answer.push_back(i + 1);
    std::cout << '\n';
    for (number i = answer.size() - 1; i >= 0; --i)
    {
        std::cout << answer[i] << " ";
    }
    return 0;
}