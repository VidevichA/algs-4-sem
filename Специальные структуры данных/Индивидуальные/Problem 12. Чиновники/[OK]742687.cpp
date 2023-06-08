#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

std::vector<bool> used;
std::vector<long long> dist;
std::vector<std::vector<std::pair<long long, long long>>> g;
std::vector<long long> temp;

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

        for (auto p : g[v.first])
        {
            if (!used[p.first] && v.second + p.second < dist[p.first])
            {
                dist[p.first] = v.second + p.second;
                q.push(std::make_pair(p.first, v.second + p.second));
                temp[p.first] = v.first;
            }
        }
    }
}
int main()
{
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    long long n;
    in >> n;
    used = std::vector<bool>(n, false);
    g = std::vector<std::vector<std::pair<long long, long long>>>(n);
    dist = std::vector<long long>(n, LONG_LONG_MAX);
    temp = std::vector<long long>(n, -1);
    for (long long i = 0; i < n; ++i)
    {
        long long k1, k2;
        in >> k1 >> k2;
        --k1;
        for (long long j = 0; j < k2; ++j)
        {
            long long k3, k4;
            in >> k3 >> k4;
            --k3;
            g[k1].push_back({k3, k4});
        }
    }
    Distances(0);
    long long min = LONG_LONG_MAX;
    long long ind = 0;
    for (long long i = 0; i < n; ++i)
    {
        if (g[i].size() == 0 && dist[i] < min)
        {
            min = dist[i];
            ind = i;
        }
    }
    out << (min == LONG_LONG_MAX ? 0 : min) << '\n';
    std::vector<long long> path;
    long long cur = ind;
    path.push_back(ind);
    while (cur != 0)
    {
        cur = temp[cur];
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());
    for (auto el : path)
    {
        out << el + 1 << ' ';
    }
    return 0;
}