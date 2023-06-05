#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

void Bfs(std::vector<std::vector<bool>> &a, int start, std::vector<long long> &res, std::vector<bool> visited)
{
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n;
    in >> n;
    std::vector<std::vector<bool>> a(n, std::vector<bool>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            bool temp;
            in >> temp;
            a[i][j] = temp;
        }
    }
    std::vector<long long> vec(n, 0);
    std::vector<bool> visited(a.size(), false);
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (visited[i])
        {
            continue;
        }
        std::queue<long long> q;
        visited[i] = true;
        q.push(i);
        while (!q.empty())
        {
            long long v = q.front();
            q.pop();
            vec[v] = ++count;
            for (int j = 0; j < a.size(); ++j)
            {
                if (a[v][j] && !visited[j])
                {
                    visited[j] = true;
                    q.push(j);
                }
            }
        }
    }
    for (auto el : vec)
    {
        out << el << ' ';
    }
    return 0;
}