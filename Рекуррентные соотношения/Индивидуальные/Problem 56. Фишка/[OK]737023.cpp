#include <iostream>
#include <vector>
#include <fstream>
#include <vector>
#include <cmath>

long long const MOD = pow(10, 9) + 7;

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int t = 0;
    in >> t;
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < t; ++i)
    {
        int n, k;
        in >> n >> k;
        pairs.push_back({n, k});
    }

    for (auto a : pairs)
    {
        int n = a.first;
        int k = a.second;

        std::vector<long long> dp(n + 1);
        std::vector<long long> pref(n + 1);
        pref[0] = 0;
        pref[1] = 1;
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; i++)
        {

            int startIndex = (i - k - 1) > 0 ? i - k - 1 : 0;

            dp[i] = (pref[i - 1] - pref[startIndex] + MOD) % MOD;
            pref[i] = (pref[i - 1] + dp[i]) % MOD;
        }
        out << dp[n] << '\n';
    }
}