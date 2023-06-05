#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

class Suffix
{
public:
    int index;
    int ranks[2];
};

bool cmp(Suffix first, Suffix second)
{
    if (first.ranks[0] == second.ranks[0])
    {
        if (second.ranks[1] > first.ranks[1])
        {
            return true;
        }
        return false;
    }
    if (first.ranks[0] < second.ranks[0])
    {
        return true;
    }
    return false;
}

std::vector<int> buildSuffixArray(std::string str)
{
    std::vector<Suffix> v(str.length());
    for (int i = 0; i < str.length(); ++i)
    {
        v[i].index = i;
        v[i].ranks[0] = str[i] - 'a';
        v[i].ranks[1] = ((i + 1) < str.length()) ? (str[i + 1] - 'a') : -1;
    }
    std::sort(v.begin(), v.end(), cmp);
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
        std::sort(v.begin(), v.end(), cmp);
    }

    std::vector<int> suffixArr(str.length());
    for (int i = 0; i < str.length(); ++i)
    {
        suffixArr[i] = v[i].index;
    }
    return suffixArr;
}

int main()
{
    std::string text;
    std::cin >> text;
    auto suffixArr = buildSuffixArray(text);
    std::cout << text.length() << '\n';
    for (auto el : suffixArr)
    {
        std::cout << el + 1 << ' ';
    }
    return 0;
}