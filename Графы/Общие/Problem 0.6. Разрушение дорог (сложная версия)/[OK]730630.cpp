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
    // void UnmergeSet(long long a, long long b)
    // {
    //     long long temp1 = FindParent(a);
    //     long long temp2 = FindParent(b);
    //     if(temp1 != temp2)
    //     {
    //         return;
    //     }

    // }
    long long GetSize()
    {
        return size;
    }

private:
    std::vector<long long> parents;
    std::vector<long long> rank;
    long long size = 0;
};

#include <string>

int main()
{
    long long t = 2;
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n;
    in >> n;
    long long m;
    in >> m;
    long long q;
    in >> q;
    Dsu dsu;
    std::vector<std::pair<long long, long long>> v(m);
    std::vector<long long> v1(q);
    std::vector<bool> d(m, false);
    for (long long i = 0; i < n; ++i)
    {
        dsu.MakeSet(i + 1);
    }
    for (long long i = 0; i < m; ++i)
    {
        long long a;
        in >> a;
        long long b;
        in >> b;
        v[i] = std::make_pair(a, b);
    }
    for (long long i = 0; i < q; ++i)
    {
        long long temp;
        in >> temp;
        d[temp - 1] = true;
        v1[i] = temp;
    }
    for (long long i = 0; i < m; ++i)
    {
        if (!d[i])
        {
            dsu.MergeSets(v[i].first, v[i].second);
        }
    }
    std::string res = "";
    for (long long i = q - 1; i >= 0; --i)
    {
        if (dsu.GetSize() >= 2)
        {
            res += "0";
        }
        else
        {
            res += "1";
        }
        dsu.MergeSets(v[v1[i] - 1].first, v[v1[i] - 1].second);
    }
    for (long long i = res.length() - 1; i >= 0; --i)
    {
        out << res[i];
    }
    return 0;
}