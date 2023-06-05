#include <iostream>

const long long MOD = 1e9 + 7;

long long powmod(long long a, long long b, int mod)
{
    long long res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

long long binom(int n, int k)
{
    if (k == 0 || k == n)
    {
        return 1;
    }

    long long numerator = 1;
    long long denominator = 1;
    for (int i = 0; i < k; i++)
    {
        numerator = (numerator * (n - i)) % MOD;
        denominator = (denominator * (i + 1)) % MOD;
    }

    long long inv_denom = powmod(denominator, MOD - 2, MOD);

    return (numerator * inv_denom) % MOD;
}

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::cout << binom(n, k);
}