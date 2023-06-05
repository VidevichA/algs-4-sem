#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<__int128> InitParquet(std::ifstream &fin, int n, int m);

__int128 DynamicByProfile(int n, int m, const std::vector<__int128> &parquet);

bool IsTransitionPossible(int i, __int128 p, __int128 q, int m, const std::vector<__int128> &parquet);

bool CanBeCoveredWithVerticals(__int128 mask, int m);

std::string toString(__int128 num)
{
    std::string str;
    do
    {
        int digit = num % 10;
        str = std::to_string(digit) + str;
        num = (num - digit) / 10;
    } while (num != 0);
    return str;
}

int main()
{
    std::ifstream fin("../30.triangle/input.txt");
    std::ofstream ofStream("../30.triangle/output.txt");
    int n, m;
    fin >> n >> m;
    std::vector<__int128> parquet = InitParquet(fin, n, m);
    __int128 result = DynamicByProfile(n, m, parquet);
    ofStream << toString(result);
}

__int128 DynamicByProfile(int n, int m, const std::vector<__int128> &parquet)
{
    std::vector<std::vector<__int128>> dp;
    dp.resize(n + 1, std::vector<__int128>(1 << m));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (__int128 p = 0; p < (1 << m); p++)
        {
            for (__int128 q = 0; q < (1 << m); q++)
            {
                if (IsTransitionPossible(i, p, q, m, parquet))
                {
                    dp[i + 1][q] += dp[i][p];
                }
            }
        }
    }
    return dp[n][0];
}

bool IsTransitionPossible(int i, __int128 p, __int128 q, int m, const std::vector<__int128> &parquet)
{
    if ((parquet[i] & p) != 0)
    {
        return false;
    }
    if (((p | parquet[i]) & q) != 0)
    {
        return false;
    }
    return CanBeCoveredWithVerticals(p | parquet[i] | q, m);
}

bool CanBeCoveredWithVerticals(__int128 mask, int m)
{
    for (int i = 0; i < m;)
    {
        if ((mask >> (m - 1 - i)) % 2 == 1)
        {
            i++;
        }
        else if (i + 1 == m || ((mask >> (m - i - 2)) % 2 == 1))
        {
            return false;
        }
        else
        {
            i += 2;
        }
    }
    return true;
}

std::vector<__int128> InitParquet(std::ifstream &fin, int n, int m)
{
    std::vector<__int128> parquet;
    int layer = 0;
    int tmp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fin >> tmp;
            layer += tmp << (m - 1 - j);
        }
        parquet.push_back(layer);
        layer = 0;
    }
    return parquet;
}