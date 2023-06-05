#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

int k, lambda;
std::vector<int> b;
std::vector<int> memo;

int f(int n)
{
    if (n < 0)
    {
        return 0;
    }
    else if (n == 0)
    {
        return lambda;
    }
    else if (memo[n] != -1)
    {
        return memo[n];
    }
    else if (n % 2 == 1)
    {
        int result = (f(n - 1) + n) % MOD;
        memo[n] = result;
        return result;
    }
    else
    {
        int sum = 0;
        for (int j = 0; j < k; j++)
        {
            int index = n / 2 - j;
            if (index < 0)
            {
                break;
            }
            sum = (sum + (long long)b[j] * f(index)) % MOD;
        }
        memo[n] = sum;
        return sum;
    }
}

int main()
{
    int N;
    std::cin >> N >> k >> lambda;

    b.resize(k);
    for (int i = 0; i < k; i++)
    {
        std::cin >> b[i];
    }

    memo.resize(N + 1, -1);
    std::cout << f(N);
    return 0;
}