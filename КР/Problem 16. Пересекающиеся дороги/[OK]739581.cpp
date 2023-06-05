#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

long long dijkstra(long long n, long long start, long long end,
                   const std::vector<std::vector<std::pair<long long, long long>>> &adj_list, std::vector<long long> &prev)
{
    std::vector<bool> marked(n, false);
    std::vector<long long> dist(n, INT64_MAX);
    dist[start] = 0;
    marked[start] = true;
    std::set<std::pair<long long, long long>> border;
    border.emplace(0, start);
    while (!border.empty())
    {
        auto current = *border.begin();
        long long d = current.first;
        long long v = current.second;
        marked[v] = true;
        border.erase(current);
        if (v == end)
        {
            return d;
        }
        if (d > dist[v])
        {
            continue;
        }
        for (auto &[u, l] : adj_list[v])
        {
            if (marked[u])
            {
                continue;
            }
            long long temp = d + l + adj_list[u].size();
            if (temp < dist[u])
            {
                border.erase({dist[u], u});
                dist[u] = temp;
                border.emplace(temp, u);
                prev[u] = v;
            }
        }
    }
    return -1;
}

int main()
{
    std::ifstream fin("common/kr3/task3/input.in");
    std::ofstream ofStream("common/kr3/task3/output.out");
    long long n, k;
    long long u, v;
    fin >> n >> k;
    fin >> u >> v;

    std::vector<std::vector<std::pair<long long, long long>>> adj_list(n);
    int in, to, length;
    for (long long i = 0; i < k; i++)
    {
        fin >> in >> to >> length;
        adj_list[in - 1].emplace_back(to - 1, length);
        adj_list[to - 1].emplace_back(in - 1, length);
    }

    std::vector<long long> prev(n, -1);
    long long ans = dijkstra(n, u - 1, v - 1, adj_list, prev);
    ans -= adj_list[v - 1].size();
    if (ans == -1)
    {
        ofStream << 0;
    }
    else
    {
        ofStream << ans << "\n";
        std::vector<long long> path;
        v--;
        while (v != -1)
        {
            path.push_back(v);
            v = prev[v];
        }
        std::reverse(path.begin(), path.end());
        for (auto item : path)
        {
            ofStream << item + 1 << " ";
        }
    }
    return 0;
}