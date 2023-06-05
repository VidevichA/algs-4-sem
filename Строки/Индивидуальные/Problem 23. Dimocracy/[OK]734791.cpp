#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

class Suffix
{
public:
    int index;
    std::vector<int> ranks = std::vector<int>(2);
};

bool Cmp(const Suffix &first, const Suffix &second)
{
    if (first.ranks[0] == second.ranks[0])
    {
        return second.ranks[1] > first.ranks[1];
    }
    return first.ranks[0] < second.ranks[0];
}

std::vector<int> BuildSuffixArray(const std::string &str)
{
    std::vector<Suffix> v(str.length());
    for (int i = 0; i < str.length(); ++i)
    {
        v[i].index = i;
        v[i].ranks[0] = str[i];
        v[i].ranks[1] = ((i + 1) < str.length()) ? (str[i + 1]) : -1;
    }
    std::sort(v.begin(), v.end(), Cmp);
    std::vector<int> ind(str.length());
    for (int i = 4; i < 2 * str.length(); i *= 2)
    {
        int rank = 0;
        int prevRank = v[0].ranks[0];
        v[0].ranks[0] = rank;
        ind[v[0].index] = 0;
        for (int j = 1; j < str.length(); ++j)
        {
            if (v[j].ranks[0] == prevRank && v[j].ranks[1] == v[j - 1].ranks[1])
            {
                prevRank = v[j].ranks[0];
                v[j].ranks[0] = rank;
            }
            else
            {
                prevRank = v[j].ranks[0];
                v[j].ranks[0] = ++rank;
            }
            ind[v[j].index] = j;
        }
        for (int j = 0; j < str.length(); ++j)
        {
            int nextIndex = v[j].index + i / 2;
            v[j].ranks[1] = (nextIndex < str.length()) ? v[ind[nextIndex]].ranks[0] : -1;
        }
        std::sort(v.begin(), v.end(), Cmp);
    }
    std::vector<int> suffixArr(str.length());
    for (int i = 0; i < str.length(); ++i)
    {
        suffixArr[i] = v[i].index;
    }
    return suffixArr;
}

std::string in;

std::vector<int> lcp(std::string str, std::vector<int> sa)
{
    std::vector<int> lcp(sa.size(), 0);
    std::vector<int> invSuff(sa.size(), 0);
    for (int i = 0; i < sa.size(); ++i)
    {
        invSuff[sa[i]] = i;
    }
    int prevLcp = 0;
    for (int i = 0; i < sa.size(); ++i)
    {
        if (invSuff[i] == sa.size() - 1)
        {
            prevLcp = 0;
            continue;
        }
        int j = sa[invSuff[i] + 1];
        while (i + prevLcp < sa.size() && j + prevLcp < sa.size() && str[i + prevLcp] == str[j + prevLcp])
        {
            ++prevLcp;
        }
        lcp[invSuff[i]] = prevLcp;
        if (prevLcp > 0)
        {
            --prevLcp;
        }
    }
    return lcp;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> in;
    auto sa = BuildSuffixArray(in);
    auto lcpAr = lcp(in, sa);
    std::cout << *std::max_element(lcpAr.begin(), lcpAr.end()) + 1;
    return 0;
}