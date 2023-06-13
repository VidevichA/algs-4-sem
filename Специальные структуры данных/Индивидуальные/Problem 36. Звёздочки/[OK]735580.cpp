#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin("input.txt");
std::ofstream out("output.txt");

std::vector<int> frequencies;
std::vector<int> t;

struct SegmentTree
{
public:
    void Build()
    {
        DoBuild(1, 0, frequencies.size());
    }

    void Add(int i, int x)
    {
        DoAdd(1, 0, frequencies.size(), i, x);
    }

    long long FindSum(int l, int r)
    {
        return DoFindSum(1, 0, frequencies.size(), l, r);
    }

private:
    void DoBuild(int v, int tl, int tr)
    {
        if (tr - tl == 1)
        {
            t[v] = frequencies[tl];
        }
        else
        {
            int m = (tl + tr) / 2;
            DoBuild(2 * v, tl, m);
            DoBuild(2 * v + 1, m, tr);
            t[v] = t[2 * v] + t[2 * v + 1];
        }
    }

    void DoAdd(int v, int tl, int tr, int i, int x)
    {
        if (tr - tl == 1)
        {
            t[v] += x;
            return;
        }
        int m = (tl + tr) / 2;
        if (i < m)
        {
            DoAdd(2 * v, tl, m, i, x);
        }
        else
        {
            DoAdd(2 * v + 1, m, tr, i, x);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    long long DoFindSum(int v, int tl, int tr, int l, int r)
    {
        if (l == tl && r == tr)
        {
            return t[v];
        }
        else
        {
            int m = (tl + tr) / 2;
            if (r <= m)
            {
                return DoFindSum(2 * v, tl, m, l, r);
            }
            if (m <= l)
            {
                return DoFindSum(2 * v + 1, m, tr, l, r);
            }

            return DoFindSum(2 * v, tl, m, l, m) + DoFindSum(2 * v + 1, m, tr, m, r);
        }
    }
};

struct Star
{
    int x;
    int y;

    Star(){};

    Star(int x_, int y_)
    {
        this->x = x_;
        this->y = y_;
    }
};

int main()
{
    int n, x, y;
    fin >> n;
    int x_max = 0;
    std::vector<Star> stars(n);
    for (int i = 0; i < n; ++i)
    {
        fin >> x >> y;
        stars[i] = Star(x, y);
        if (x > x_max)
        {
            x_max = x;
        }
    }
    SegmentTree tree;
    frequencies = std::vector<int>(x_max + 1);
    t = std::vector<int>(frequencies.size() * 4);
    tree.Build();
    std::vector<int> levels(n);
    for (int i = 0; i < n; ++i)
    {
        levels[tree.FindSum(0, stars[i].x + 1)]++;
        tree.Add(stars[i].x, 1);
    }

    for (int level : levels)
    {
        out << level << "\n";
    }

    return 0;
}