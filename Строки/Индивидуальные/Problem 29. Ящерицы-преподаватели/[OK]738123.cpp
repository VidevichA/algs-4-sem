//! C++20

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    short n;
    string s;
    cin >> n >> s;

    const int k = 27;

    vector<unsigned long long> powers(n);
    powers[0] = 1;
    for (int i = 1; i < n; ++i)
    {
        powers[i] = (powers[i - 1] * k) % UINT64_MAX;
    }

    vector<vector<unsigned long long>> hashes;
    for (int i = 1; i <= n; ++i)
    {
        unsigned long long last = ((s[i - 1] - 'a' + 1) * powers[0]) % UINT64_MAX;
        vector<unsigned long long> current_hashes;
        current_hashes.push_back(last);
        for (int j = 0; j < n - i; ++j)
        {
            last = (((s[i + j] - 'a' + 1) * powers[j + 1]) % UINT64_MAX + last) % UINT64_MAX;
            current_hashes.push_back(last);
        }
        hashes.push_back(current_hashes);
    }

    long long all = 0;
    long long allNonEq = 0;
    for (int i = 1; i <= n; ++i)
    {
        unordered_map<unsigned long long, long long> results;
        for (int j = 0; j <= n - i; ++j)
        {
            if (!results.contains(hashes[j][i - 1]))
            {
                results[hashes[j][i - 1]] = 1;
            }
            else
            {
                results[hashes[j][i - 1]]++;
            }
        }
        for (const auto &item : results)
        {
            if (item.second != 1)
            {
                all += (item.second - 1) * item.second / 2;
            }
        }
        allNonEq += (n - i + 1) * (n - i) / 2;
    }

    cout << allNonEq - all;
}