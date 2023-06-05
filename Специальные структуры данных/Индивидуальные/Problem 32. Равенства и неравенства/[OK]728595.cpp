#include <fstream>
#include <set>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

class Dsu
{
public:
    Dsu()
    {
    }
    void MakeSet(long long rootVal)
    {
        if (parents.size() <= rootVal + 1)
        {
            parents.resize(rootVal + 1);
        }
        if (rank.size() <= rootVal + 1)
        {
            rank.resize(rootVal + 1);
        }
        parents[rootVal] = rootVal;
        rank[rootVal] = 0;
    }
    long long FindParent(int val)
    {
        if (parents.size() <= val)
        {
            return 0;
        }
        if (val == parents[val])
        {
            return val;
        }
        return parents[val] = FindParent(parents[val]);
    }
    void MergeSets(int a, int b)
    {
        a = FindParent(a);
        b = FindParent(b);
        if (a == b)
        {
            return;
        }
        if (rank[a] < rank[b])
        {
            parents[a] = b;
        }
        else
        {
            parents[b] = a;
            if (rank[a] == rank[b])
            {
                ++rank[a];
            }
        }
    }

private:
    std::vector<long long> parents;
    std::vector<long long> rank;
};

int main()
{
    std::ifstream in("equal-not-equal.in");
    std::ofstream out("equal-not-equal.out");
    long long n;
    in >> n;
    long long m;
    in >> m;
    Dsu dsu;
    std::vector<long long> va(m);
    std::vector<long long> vb(m);
    std::vector<std::string> vop(m);
    for (int i = 0; i < m; ++i)
    {
        std::string a;
        std::string b;
        std::string op;
        in >> a;
        in >> op;
        in >> b;
        long long na = std::stoll(a.substr(1));
        long long nb = std::stoll(b.substr(1));
        if (dsu.FindParent(na) == 0)
        {
            dsu.MakeSet(na);
        }
        if (dsu.FindParent(nb) == 0)
        {
            dsu.MakeSet(nb);
        }
        va[i] = na;
        vb[i] = nb;
        vop[i] = op;
    }
    for (int i = 0; i < m; ++i)
    {
        if (vop[i] == "==")
        {
            dsu.MergeSets(va[i], vb[i]);
        }
    }
    for (int i = 0; i < m; ++i)
    {
        if (vop[i] == "!=" && dsu.FindParent(va[i]) == dsu.FindParent(vb[i]))
        {
            out << "No";
            return 0;
        }
    }
    out << "Yes";
    return 0;
}