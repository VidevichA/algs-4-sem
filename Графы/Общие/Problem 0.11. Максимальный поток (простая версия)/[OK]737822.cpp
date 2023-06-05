#include <iostream>
#include <vector>

struct Edge
{
    long long v;
    long long flow;
    long long capacity;

    Edge()
    {
    }

    Edge(long long v, long long capacity)
        : v(v), flow(0), capacity(capacity) {}
};

std::vector<Edge> edges;
std::vector<std::vector<long long>> graph;
std::vector<long long> visited;
int timer = 1;
long long n, m;

void AddEdge(long long v, long long u, long long capacity)
{
    graph[v].emplace_back(edges.size());
    edges.emplace_back(u, capacity);
    graph[u].emplace_back(edges.size());
    edges.emplace_back(v, 0);
}
long long DFS(long long v, long long min)
{
    if (v == n - 1)
    {
        return min;
    }
    visited[v] = timer;
    for (long long i : graph[v])
    {
        if (edges[i].capacity - edges[i].flow == 0)
        {
            continue;
        }
        if (visited[edges[i].v] == timer)
        {
            continue;
        }
        long long d = DFS(edges[i].v, std::min(min, edges[i].capacity - edges[i].flow));
        if (d)
        {
            edges[i].flow += d;
            edges[i ^ 1].flow -= d;
            return d;
        }
    }
    return 0;
}

int main()
{
    std::cin >> n >> m;

    graph = std::vector<std::vector<long long>>(n);
    visited = std::vector<long long>(n);

    for (long long i = 0; i < m; ++i)
    {
        long long v, u, capacity;
        std::cin >> v >> u >> capacity;
        AddEdge(v - 1, u - 1, capacity);
    }
    while (DFS(0, LONG_LONG_MAX))
    {
        ++timer;
    }
    long long result = 0;
    for (int index : graph[0])
    {
        result += edges[index].flow;
    }
    std::cout << result;
    return 0;
}