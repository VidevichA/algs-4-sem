#include <vector>
#include <iostream>

#define mod 1000000007

using namespace std;

void manacher1(vector<int> &d1, string &s)
{
    int n = s.size();
    int l = 0, r = -1;
    int k;
    for (int i = 0; i < n; ++i)
    {
        if (i > r)
            k = 1;
        else
            k = min(d1[l + r - i], r - i + 1);
        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])
            ++k;
        d1[i] = k;
        if (i + k - 1 > r)
            l = i - k + 1, r = i + k - 1;
    }
}

void manacher2(vector<int> &d2, string &s)
{
    int n = s.size();
    int l = 0, r = -1;
    int k;
    for (int i = 0; i < n; ++i)
    {
        if (i > r)
            k = 0;
        else
            k = min(d2[l + r - i + 1], r - i + 1);
        while (i + k < n && i - k - 1 >= 0 && s[i + k] == s[i - k - 1])
            ++k;
        d2[i] = k;
        if (i + k - 1 > r)
            l = i - k, r = i + k - 1;
    }
}

int main()
{
    std::cin.tie();
    ios_base::sync_with_stdio(false);
    uint64_t res;
    res = 1;
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<bool>> pos(n, vector<bool>(26, true));
    vector<int> d1(n), d2(n);
    manacher1(d1, s);
    manacher2(d2, s);
    int count = 0;
    int next = 0;
    for (int i = 0; i < n; i++)
    {
        next = max(next, i + d2[i]);
        if (i == next)
        {
            count = 0;
            for (int j = 0; j < 26; j++)
                count += pos[i][j];
            res *= count;
            res %= mod;
        }
        next = max(next, i + d1[i]);
        if (i + d2[i] < n && i - d2[i] - 1 >= 0)
        {
            pos[i + d2[i]][s[i - d2[i] - 1] - 'a'] = false;
        }
        if (i + d1[i] < n && i - d1[i] >= 0)
        {
            pos[i + d1[i]][s[i - d1[i]] - 'a'] = false;
        }
        if (i + 1 < n)
        {
            pos[i + 1][s[i] - 'a'] = false;
        }
    }
    cout << res;
    return 0;
}