#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::vector<bool>> m;
std::vector<bool> visited;
std::vector<long long> res;
int count = 1;

void Dfs(int start)
{
    if (!visited[start])
    {
        visited[start] = true;
        res[start] = count++;
    }
    for (int i = 0; i < res.size(); ++i)
    {
        if (m[start][i] && !visited[i])
        {
            Dfs(i);
        }
    }
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n;
    in >> n;
    visited = std::vector<bool>(n);
    m = std::vector<std::vector<bool>>(n, std::vector<bool>(n));
    res = std::vector<long long>(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            bool temp;
            in >> temp;
            m[i][j] = temp;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        Dfs(i);
    }
    for (auto el : res)
    {
        out << el << ' ';
    }
    return 0;
}