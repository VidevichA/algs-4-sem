#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
// adsfgdnfngjsdjfgdedsded

string s;
vector<int> p;
int n;
vector<int> lcp;
vector<pair<int, int>> rankPair(n);

int max(int a, int b)
{
    return a > b ? a : b;
}

bool comparatorS(int i, int j)
{
    bool rez = s[i] < s[j];
    return rez;
}

bool comparatorPair(int i, int j)
{
    return rankPair[i] < rankPair[j];
}

void makeSuffixArray()
{
    string s1 = s + '\0';

    iota(p.begin(), p.end(), 0);

    sort(p.begin(), p.end(), comparatorS);

    vector<int> rank(n);
    rank[p[0]] = 0;
    for (int i = 1; i < n; i++)
        rank[p[i]] = rank[p[i - 1]] + (s1[p[i]] != s1[p[i - 1]]);

    rankPair = vector<pair<int, int>>(n);
    for (int len = 1; len < n; len *= 2)
    {
        for (int i = 0; i < n; i++)
            rankPair[i] = {rank[i], rank[(i + len) % n]};

        sort(p.begin(), p.end(), comparatorPair);

        rank[p[0]] = 0;
        for (int i = 1; i < n; i++)
            rank[p[i]] = rank[p[i - 1]] + (rankPair[p[i]] != rankPair[p[i - 1]]);
    }
}

void makeLCP()
{
    vector<int> positionInP(n);
    for (int i = 0; i < n; i++)
    {
        positionInP[p[i]] = i;
    }
    for (int i = 0, len = 0; i < n - 1; i++, len = max(len - 1, 0))
    {
        int j = p[positionInP[i] - 1];
        while (s[i + len] == s[j + len])
        {
            len++;
        }
        lcp[positionInP[i]] = len;
    }
}

int maxInLcp()
{
    int max = lcp[0];
    for (int i = 1; i < lcp.size(); i++)
    {
        max = max > lcp[i] ? max : lcp[i];
    }
    return max;
}

int main()
{
    cin >> s;
    n = s.size() + 1;
    p = vector<int>(n);
    lcp = vector<int>(n);

    makeSuffixArray();

    makeLCP();

    cout << maxInLcp() + 1;
    return 0;
}