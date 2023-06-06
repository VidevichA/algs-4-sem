#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

int main()
{

    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long l;
    in >> l;
    std::string s1, s2;
    in >> s1 >> s2;

    if (s1 == s2)
    {
        out << "Yes\n"
            << 1 << ' ' << 1;
        return 0;
    }

    long long i1 = 0, i2 = s1.size();
    for (long long i = 0; i < s1.size(); ++i)
    {
        if (s1[i] != s2[i])
        {
            break;
        }
        ++i1;
    }

    for (long long i = s1.size() - 1; i >= 0; --i)
    {
        if (s1[i] != s2[i])
        {
            break;
        }
        --i2;
    }

    std::reverse(s1.begin() + i1, s1.begin() + i2);
    std::cout << s1;
    if (s1 == s2)
    {
        out << "Yes" << '\n'
            << i1 + 1 << ' ' << i2;
    }
    else
    {
        out << "No";
    }
    return 0;
}