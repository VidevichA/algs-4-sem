#include <iostream>
#include <fstream>
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
        ++size;
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
        --size;
    }
    long long GetSize()
    {
        return size;
    }

private:
    std::vector<long long> parents;
    std::vector<long long> rank;
    long long size = 0;
};

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long c;
    in >> c;
    long long q;
    in >> q;
    Dsu dsu;
    for (long long i = 0; i < c; ++i)
    {
        dsu.MakeSet(i + 1);
    }
    for (long long i = 0; i < q; ++i)
    {
        long long a;
        in >> a;
        long long b;
        in >> b;
        dsu.MergeSets(a, b);
        out << dsu.GetSize() << '\n';
    }
    return 0;
}