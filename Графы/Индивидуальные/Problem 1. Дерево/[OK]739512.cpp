#include <fstream>
#include <vector>

int n;
std::vector<std::vector<int>> a;

void dfs_tree(int start, std::vector<bool> &cycle)
{
    if (cycle[start])
    {
        return;
    }
    cycle[start] = true;
    for (int i = 0; i < n; i++)
    {
        if (a[start][i])
        {
            dfs_tree(i, cycle);
        }
    }
}

bool is_tree()
{
    int edges = 0;
    for (const auto &r : a)
    {
        for (auto c : r)
        {
            if (c)
            {
                edges++;
            }
        }
    }
    if (edges / 2 != n - 1)
    {
        return false;
    }
    std::vector<bool> cycle(n, false);
    dfs_tree(0, cycle);
    for (int i = 0; i < n; i++)
    {
        if (!cycle[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::ifstream fin("common/kr3/task2/input.txt");
    std::ofstream ofStream("common/kr3/task2/output.txt");
    fin >> n;
    a.resize(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> a[i][j];
        }
    }
    if (is_tree())
    {
        ofStream << "YES";
    }
    else
    {
        ofStream << "NO";
    }
    return 0;
}