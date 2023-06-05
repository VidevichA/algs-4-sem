#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::vector<bool> processed;
std::vector<long long> dist;
std::vector<std::vector<std::pair<long long, long long>>> mat;

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
        if (processed[v.first])
        {
            continue;
        }
        processed[v.first] = true;
        dist[v.first] = v.second;
        for (auto p : mat[v.first])
        {
            if (!processed[p.first] && v.second + p.second < dist[p.first])
            {
                q.push(std::make_pair(p.first, p.second + v.second));
            }
        }
    }
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n, m;
    in >> n >> m;
    mat = std::vector<std::vector<std::pair<long long, long long>>>(n);
    processed = std::vector<bool>(n, false);
    dist = std::vector<long long>(n, LONG_LONG_MAX);
    for (long long i = 0; i < m; ++i)
    {
        long long k1, k2, k3;
        in >> k1 >> k2 >> k3;
        mat[k1 - 1].push_back(std::make_pair(k2 - 1, k3));
        mat[k2 - 1].push_back(std::make_pair(k1 - 1, k3));
    }
    Distances(0);
    out << dist[dist.size() - 1];
    return 0;
}