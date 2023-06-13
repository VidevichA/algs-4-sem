#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::ifstream fin("../in.txt");
std::ofstream out("../out.txt");

std::vector<std::pair<char, int>> words;

int LowerBound(char c)
{
    int l = 0;
    int r = words.size();
    while (l < r)
    {
        int k = (l + r) / 2;
        if (c <= words[k].first)
        {
            r = k;
        }
        else
        {
            l = k + 1;
        }
    }
    return l;
}

int main()
{
    int k;
    std::string str;
    std::cin >> k;
    std::cin >> str;
    words.push_back(std::make_pair(str[0], 1));
    k -= str[0] - 'A';
    for (int i = 1; i < str.size(); ++i)
    {
        char s = str[i];
        int index = LowerBound(s);
        if (index == 0)
        {
            if (words[0].first != s)
            {
                words.insert(words.begin(), std::make_pair(s, 1));
            }
            else
            {
                words[0].second++;
            }
            k -= s - 'A';
        }
        else
        {
            k -= s - words[index - 1].first - 1;
            if (words[index - 1].second == 1)
            {
                words[index - 1] = std::make_pair(s, 1);
            }
            else
            {
                words[index - 1].second--;
                words.insert(words.begin() + index, std::make_pair(s, 1));
            }
        }
        if (k < 0)
        {
            std::cout << -1;
            return 0;
        }
    }

    int count = 0;
    for (std::pair<char, int> word : words)
    {
        // std::cout << word.first << " " << word.second << "\n";
        count += word.second;
    }
    std::cout << count;
    return 0;
}