#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <string>

typedef long long number;

std::vector<bool> visited;
std::vector<number> dist;
std::vector<std::vector<std::pair<number, number>>> list;

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

std::vector<number> temp;
std::vector<number> deg;

void Distances(long long start)
{
    auto cmp = [](std::pair<long long, long long> f, std::pair<long long, long long> s)
    {
        return f.second > s.second;
    };
    std::priority_queue<std::pair<long long, long long>, std::vector<std::pair<long long, long long>>, decltype(cmp)>
        q(cmp);
    q.push(std::make_pair(start, 0));
    while (!q.empty())
    {
        auto v = q.top();
        q.pop();
        if (v.second > dist[v.first])
        {
            continue;
        }
        for (auto p : list[v.first])
        {
            if (!visited[p.first] && v.second + p.second + deg[p.first] < dist[p.first])
            {
                dist[p.first] = v.second + p.second + deg[p.first];
                q.push(std::make_pair(p.first, v.second + p.second + deg[p.first]));
                temp[p.first] = v.first;
            }
        }
    }
}

int main()
{
    std::ifstream in("input.in");
    std::ofstream out("output.out");

    number n, k;
    in >> n >> k;
    number s, f;
    in >> s >> f;
    list = std::vector<std::vector<std::pair<number, number>>>(n);
    deg = std::vector<long long>(n, 0);
    visited = std::vector<bool>(n, 0);
    dist = std::vector<long long>(n, LONG_LONG_MAX);
    temp = std::vector<number>(n, -1);
    for (number i = 0; i < k; ++i)
    {
        number k1, k2, k3;
        in >> k1 >> k2 >> k3;
        list[k1 - 1].push_back({k2 - 1, k3});
        list[k2 - 1].push_back({k1 - 1, k3});
        deg[k1 - 1]++;
        deg[k2 - 1]++;
    }

    Distances(s - 1);
    std::vector<number> path;
    number cur = f - 1;
    path.push_back(f - 1);
    while (temp[cur] != -1 && cur != s - 1)
    {
        cur = temp[cur];
        path.push_back(cur);
    }

    out << dist[f - 1] - deg[f - 1] << '\n';
    std::reverse(path.begin(), path.end());
    for (auto el : path)
    {
        out << el + 1 << ' ';
    }
    return 0;
}