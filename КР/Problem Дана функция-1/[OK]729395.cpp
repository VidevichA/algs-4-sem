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

std::vector<number> results;
std::vector<number> el;

number Mod(number n, number m)
{
    if (n % m < 0)
    {
        return n % m + m;
    }
    return n % m;
}

number Calc(number n, number l, number k)
{
    if (n == 0)
    {
        return results[0];
    }
    if (n < 0)
    {
        return 0;
    }
    if (results[n] != LONG_LONG_MIN)
    {
        return results[n];
    }
    if (n % 2 == 1 && n >= 1)
    {
        results[n] = Mod(Mod(Calc(n - 1, l, k), 1000000007) + Mod(n, 1000000007), 1000000007);
        return results[n];
    }
    else if (n % 2 == 0 && n >= 2)
    {
        number sum = 0;
        for (int i = 0; i < k; ++i)
        {
            sum += Mod(el[i] * Calc(n / 2 - i, l, k), 1000000007);
        }
        results[n] = Mod(sum, 1000000007);
        return results[n];
    }
}

int main()
{
    number n;
    std::cin >> n;
    number k;
    std::cin >> k;
    number l;
    std::cin >> l;
    results = std::vector<number>(n + 1, LONG_LONG_MIN);
    results[0] = Mod(l, 1000000007);
    el = std::vector<number>(k);
    for (number i = 0; i < k; ++i)
    {
        number temp;
        std::cin >> temp;
        el[i] = temp;
    }
    std::cout << Mod(Calc(n, l, k), 1000000007);
    return 0;
}