#include <iostream>
#include <vector>
#include <cmath>

const int mod = 1000000007;

long long binPow(long long a, long long n)
{
    int res = 1;
    while (n)
    {
        if (n & 1)
        {
            res = res * a % mod;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main()
{
    int n, k;
    std::cin >> n;
    std::cin >> k;
    if (k > n)
    {
        std::cout << 0;
        return 0;
    }
    if (k == 0)
    {
        std::cout << 1;
        return 0;
    }
    long long fn = 1;
    for (int i = 2; i <= n; ++i)
    {
        fn = fn * i % mod;
    }
    long long fk = 1;
    for (int i = 2; i <= k; ++i)
    {
        fk = fk * i % mod;
    }
    long long fnmk = 1;
    for (int i = n - k; i > 0; --i)
    {
        fnmk = fnmk * i % mod;
    }
    std::cout << (fn * (binPow(fk * fnmk % mod, mod - 2) % mod)) % mod;
    return 0;
}