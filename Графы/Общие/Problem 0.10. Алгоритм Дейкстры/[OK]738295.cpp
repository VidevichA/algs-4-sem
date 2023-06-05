#include <fstream>
#include <vector>
#include <queue>
#include <limits>

const long long INF = std::numeric_limits<long long>::max();

long long dijkstra(const std::vector<std::vector<std::pair<long long, long long>>> &graph, int source, int target)
{
    std::vector<long long> dist(graph.size(), INF);
    dist[source] = 0;
    std::priority_queue<std::pair<long long, long long>, std::vector<std::pair<long long, long long>>, std::greater<>> pq;
    pq.push({0, source});
    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();
        long long dv = current.first;
        long long u = current.second;
        if (u == target)
        {
            break;
        }
        if (dist[u] < dv)
        {
            continue;
        }
        for (const auto &edge : graph[u])
        {
            long long v = edge.first;
            long long weight = edge.second;
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[target];
}

int main()
{
    std::ifstream fin("common/graphs/dijkstra/input.txt");
    std::ofstream ofStream("common/graphs/dijkstra/output.txt");
    int n, m;
    fin >> n >> m;
    std::vector<std::vector<std::pair<long long, long long>>> graph(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        fin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    ofStream << dijkstra(graph, 1, n);
    return 0;
}