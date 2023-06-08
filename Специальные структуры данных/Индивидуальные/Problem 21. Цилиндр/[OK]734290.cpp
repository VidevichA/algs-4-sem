#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>

typedef long long number;

class Dsu
{
public:
    Dsu()
    {
    }
    void MakeSet(number rootVal)
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
    number FindParent(int val)
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
    number GetSize()
    {
        return size;
    }

private:
    std::vector<number> parents;
    std::vector<number> rank;
    number size = 0;
};

template <typename T>
void PrintVector(const std::vector<T> &v)
{
    std::cout << '\n';
    for (auto el : v)
    {
        std::cout << el << ' ';
    }
    std::cout << '\n';
}

template <typename T>
void PrintMatrix(const std::vector<std::vector<T>> &m)
{
    std::cout << '\n';
    for (auto r : m)
    {
        for (auto c : r)
        {
            std::cout << c << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
#include <stack>

int main()
{
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    number n, m;
    in >> n >> m;
    Dsu dsu;
    std::vector<std::vector<number>> v(n, std::vector<number>(m));
    number temp;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            in >> temp;
            v[i][j] = temp;
            if (temp == 0)
            {
                dsu.MakeSet(i * m + j);
            }
        }
    }
    PrintMatrix(v);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cout << v[i][j] << ' ';
            if (v[i][j] == 0)
            {
                if (i == 0)
                {
                    if (v[n - 1][j] == 0)
                    {
                        dsu.MergeSets(i * m + j, (n - 1) * m + j);
                    }
                }
                else
                {
                    if (v[i - 1][j] == 0)
                    {
                        dsu.MergeSets(i * m + j, (i - 1) * m + j);
                    }
                }
                if (j != m - 1)
                {
                    if (v[i][j + 1] == 0)
                    {
                        dsu.MergeSets(i * m + j, i * m + j + 1);
                    }
                }
                if (j != 0)
                {
                    if (v[i][j - 1] == 0)
                    {
                        dsu.MergeSets(i * m + j, i * m + j - 1);
                    }
                }
                if (i != n - 1)
                {
                    if (v[i + 1][j] == 0)
                    {
                        dsu.MergeSets(i * m + j, (i + 1) * m + j);
                    }
                }
            }
        }
    }
    out << dsu.GetSize();
    return 0;
}