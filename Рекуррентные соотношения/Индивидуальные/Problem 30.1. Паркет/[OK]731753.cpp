#include <iostream>
#include <fstream>
#include <vector>

#define MODULE 1000000007

int main()
{
    int n;
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    in >> n;
    in.close();
    if (n % 2 == 1)
    {
        out << '0';
        return 0;
    }

    std::vector<long long> f, g;
    f.push_back(1);
    f.push_back(0);
    f.push_back(5);
    f.push_back(0);
    g.push_back(1);
    g.push_back(0);
    g.push_back(1);
    g.push_back(0);
    for (int i = 4; i < n + 1; i += 2)
    {
        g.push_back((f[i - 2] + 2 * g[i - 2]) % MODULE);
        g.push_back(0);
        f.push_back((3 * f[i - 2] + 2 * g[i]) % MODULE);
        f.push_back(0);
    }

    out << f[n] % MODULE;
    out.close();
    return 0;
}