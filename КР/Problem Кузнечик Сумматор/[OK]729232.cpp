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

int main()
{
    number size;
    std::cin >> size;
    std::vector<number> elements(size);
    for (int i = 0; i < size; ++i)
    {
        number temp;
        std::cin >> temp;
        elements[i] = temp;
    }
    std::vector<std::vector<number>> dp(size, std::vector<number>(3, LONG_LONG_MIN));
    if (elements[0] < 0)
    {
        if (elements[0] % 3 == 0)
        {
            dp[0][elements[0] % 3] = elements[0];
        }
        else
        {
            dp[0][elements[0] % 3 + 3] = elements[0];
        }
    }
    else
    {
        dp[0][elements[0] % 3] = elements[0];
    }
    for (number i = 0; i < size; ++i)
    {
        for (number j = 0; j < 3; ++j)
        {
            if (dp[i][j] != LONG_LONG_MIN)
            {
                if (i + 2 < size)
                {
                    if (dp[i][j] + elements[i + 2] < 0)
                    {
                        if ((dp[i][j] + elements[i + 2]) % 3 == 0)
                        {
                            dp[i + 2][(dp[i][j] + elements[i + 2]) % 3] = std::max(dp[i + 2][(dp[i][j] + elements[i + 2]) % 3], dp[i][j] + elements[i + 2]);
                        }
                        else
                        {
                            dp[i + 2][(dp[i][j] + elements[i + 2]) % 3 + 3] = std::max(dp[i + 2][(dp[i][j] + elements[i + 2]) % 3 + 3], dp[i][j] + elements[i + 2]);
                        }
                    }
                    else
                    {
                        dp[i + 2][(dp[i][j] + elements[i + 2]) % 3] = std::max(dp[i + 2][(dp[i][j] + elements[i + 2]) % 3], dp[i][j] + elements[i + 2]);
                    }
                }
                if (i + 5 < size)
                {
                    if (dp[i][j] + elements[i + 5] < 0)
                    {
                        if ((dp[i][j] + elements[i + 5]) % 3 == 0)
                        {
                            dp[i + 5][(dp[i][j] + elements[i + 5]) % 3] = std::max(dp[i + 5][(dp[i][j] + elements[i + 5]) % 3], dp[i][j] + elements[i + 5]);
                        }
                        else
                        {
                            dp[i + 5][(dp[i][j] + elements[i + 5]) % 3 + 3] = std::max(dp[i + 5][(dp[i][j] + elements[i + 5]) % 3 + 3], dp[i][j] + elements[i + 5]);
                        }
                    }
                    else
                    {
                        dp[i + 5][(dp[i][j] + elements[i + 5]) % 3] = std::max(dp[i + 5][(dp[i][j] + elements[i + 5]) % 3], dp[i][j] + elements[i + 5]);
                    }
                }
            }
        }
        // PrintMatrix(dp);
    }
    if (dp[size - 1][0] != LONG_LONG_MIN)
    {
        std::cout << dp[size - 1][0];
    }
    else
    {
        std::cout << -2023;
    }
    return 0;
}