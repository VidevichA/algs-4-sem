#include <iostream>
#include <vector>

struct Edge
{
    long long from, to, capacity, flow;

    Edge(long long from, long long to, long long capacity) : from(from), to(to), capacity(capacity), flow(0) {}
};

const long long INF = 1e15;
long long n, m;
std::vector<Edge> flow_edges;
std::vector<std::vector<long long>> network;
std::vector<bool> visited;
std::vector<long long> pred;

void add_edge(long long u, long long v, long long c)
{
    network[u].push_back(flow_edges.size());
    flow_edges.push_back(Edge(u, v, c));
    network[v].push_back(flow_edges.size());
    flow_edges.push_back(Edge(v, u, 0));
}

long long available(long long e)
{
    return flow_edges[e].capacity - flow_edges[e].flow;
}

void find_path(long long s)
{
    visited[s] = true;
    for (long long e : network[s])
    {
        long long u = flow_edges[e].to;
        if (!visited[u] && available(e) > 0)
        {
            pred[u] = e;
            find_path(u);
        }
    }
}

std::vector<long long> restore_path(long long t)
{
    std::vector<long long> path;
    while (pred[t] < INF)
    {
        long long e = pred[t];
        path.push_back(e);
        t = flow_edges[e].from;
    }
    return path;
}

long long path_capacity(const std::vector<long long> &path)
{
    long long res_cap = available(path[0]);
    for (long long v : path)
    {
        res_cap = std::min(available(v), res_cap);
    }
    return res_cap;
}

void push(long long e, long long flow)
{
    Edge &edge = flow_edges[e];
    edge.flow += flow;
    Edge &edge_ = flow_edges[e ^ 1];
    edge_.flow -= flow;
}

void push_path(const std::vector<long long> &path, long long flow)
{
    for (long long e : path)
    {
        push(e, flow);
    }
}

long long max_flow(long long s, long long t)
{
    long long result_flow = 0;
    while (true)
    {
        pred.assign(n, INF);
        visited.assign(n, false);
        find_path(s);
        if (!visited[t])
        {
            break;
        }
        auto path = restore_path(t);
        if (path.empty())
        {
            continue;
        }
        long long flow = path_capacity(path);
        push_path(path, flow);
        result_flow += flow;
    }
    return result_flow;
}

int main()
{
    std::cin >> n >> m;
    network.resize(n);
    visited.resize(n);
    pred.resize(n);
    long long u, v, c;
    for (long long i = 0; i < m; i++)
    {
        std::cin >> u >> v >> c;
        u--;
        v--;
        add_edge(u, v, c);
    }
    std::cout << max_flow(0, n - 1);
    return 0;
}