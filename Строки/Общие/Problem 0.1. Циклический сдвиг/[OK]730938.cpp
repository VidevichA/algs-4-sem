#include <fstream>
#include <string>
#include <vector>
#include <iostream>

int main()
{
    std::ofstream out("output.txt");
    std::ifstream file("input.txt");
    std::string firstStr;
    std::string secondStr;
    long long n;
    file >> n;
    file >> firstStr;
    file >> secondStr;
    firstStr += firstStr;
    std::string temp = secondStr + " " + firstStr;
    std::vector<long long> p(temp.size());
    p[0] = 0;
    for (long long i = 1; i < temp.size(); ++i)
    {
        long long k = p[i - 1];
        while (k > 0 && temp[k] != temp[i])
        {
            k = p[k - 1];
        }
        if (temp[k] == temp[i])
        {
            p[i] = k + 1;
        }
        else
        {
            p[i] = k;
        }
    }
    for (long long i = 0; i < temp.size(); ++i)
    {
        if (p[i] == secondStr.size())
        {
            out << i - 2 * n;
            return 0;
        }
    }
    out << -1;
    return 0;
}