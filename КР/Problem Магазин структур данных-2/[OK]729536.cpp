#include <vector>
#include <iostream>
#include <fstream>

long long p = 1000000007;
std::vector<long long> nums;
std::vector<long long> suff;

void print(std::vector<std::vector<long long>> M)
{
    for (auto &item : M)
    {
        for (auto &el : item)
        {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
}

long long mod(long long x)
{
    long long y = x % p;
    if (y < 0)
    {
        return y + p;
    }
    else
    {
        return y;
    }
}

long long min(long long a, long long b)
{
    return a < b ? a : b;
}

long long money(long long i, long long j, long long k)
{
    long long cut = 0;
    cut = suff[j] - suff[i] + nums[i];
    return mod(21 * cut - mod(17 * nums[k]) - 1);
}

int main()
{

    long long n;
    std::cin >> n;
    suff = std::vector<long long>(n);

    std::vector<std::vector<long long>> F(n, std::vector<long long>(n, 0));

    nums = std::vector<long long>(n);

    for (long long i = 0; i < n; i++)
    {
        std::cin >> nums[i];
    }

    suff[0] = mod(nums[0]);
    for (long long i = 1; i < n; i++)
    {
        suff[i] = mod(suff[i - 1] + mod(nums[i]));
    }

    for (int i = 0; i < n; i++)
    {
        F[i][i] = 0;
    }

    std::vector<long long> way;

    for (int j = 1; j < n; j++)
    {
        for (int i = j - 1; i >= 0; i--)
        {
            F[i][j] = min(F[i][j - 1] + money(i, j - 1, j), F[i + 1][j] + money(i + 1, j, i));
        }
    }

    long long i = 0;
    long long j = n - 1;

    while (way.size() < n - 1)
    {

        if (F[i][j] == F[i + 1][j] + money(i + 1, j, i))
        {
            way.push_back(i + 1);
            i++;
        }
        else if (F[i][j] == F[i][j - 1] + money(i, j - 1, j))
        {
            way.push_back(j + 1);
            j--;
        }
    }

    way.push_back(i + 1);

    std::cout << F[0][n - 1] << std::endl;
    ;

    for (long long i = way.size() - 1; i > -1; i--)
    {
        std::cout << way[i] << " ";
    }
}