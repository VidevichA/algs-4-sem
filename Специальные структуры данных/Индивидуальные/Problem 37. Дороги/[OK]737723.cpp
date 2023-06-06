#include <iostream>
#include <vector>

class Dsu
{
public:
    Dsu(int n)
    {
        parents = std::vector<long long>(n + 1);
        rank = std::vector<long long>(n + 1);
    }
    void MakeSet(long long rootVal)
    {

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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;
    std::cin >> n;
    long long q;
    std::cin >> q;
    Dsu dsu(n);
    std::vector<std::pair<long long, long long>> v(q);
    for (long long i = 0; i < n; ++i)
    {
        dsu.MakeSet(i + 1);
    }
    for (long long i = 0; i < q; ++i)
    {
        long long a;
        std::cin >> a;
        long long b;
        std::cin >> b;
        v[i] = {a, b};
    }

    long long last = q;

    for (long long i = q - 1; i >= 0; --i)
    {

        dsu.MergeSets(v[i].first, v[i].second);
        if (dsu.GetSize() == 2)
        {
            last = i;
        }
    }
    std::cout << last;
    return 0;
}