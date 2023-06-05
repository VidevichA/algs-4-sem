#include <vector>
#include <fstream>

struct Edge
{
    int source, target, capacity, cost, flow;
};

const int INF = 1e9;
const int MAXN = 30;
int n;
std::vector<Edge> flow_edges;
std::vector<int> network[30];
int pred[MAXN];
int dist[MAXN];

int source(int e)
{
    return flow_edges[e].source;
}

int target(int e)
{
    return flow_edges[e].target;
}

int cost(int e)
{
    return flow_edges[e].cost;
}

int available(int e)
{
    Edge edge = flow_edges[e];
    return edge.capacity - edge.flow;
}

void push(int e, int flow)
{
    Edge &edge = flow_edges[e];
    edge.flow += flow;
    Edge &edge_ = flow_edges[e ^ 1];
    edge_.flow -= flow;
}

void push_path(const std::vector<int> &path, int flow)
{
    for (int e : path)
    {
        push(e, flow);
    }
}

int path_capacity(const std::vector<int> &path)
{
    int res_cap = available(path[0]);
    for (int v : path)
    {
        res_cap = std::min(available(v), res_cap);
    }
    return res_cap;
}

std::vector<int> restore_path(int v)
{
    std::vector<int> path;
    while (pred[v] < INF)
    {
        int e = pred[v];
        path.push_back(e);
        v = source(e);
    }
    return path;
}

void find_path(int s)
{
    dist[s] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int e = 0; e < flow_edges.size(); e++)
        {
            int v = source(e);
            int u = target(e);
            int c = cost(e);

            if (dist[v] >= INF || available(e) == 0)
            {
                continue;
            }

            if (dist[u] >= INF || dist[u] > dist[v] + c)
            {
                dist[u] = dist[v] + c;
                pred[u] = e;
            }
        }
    }
}

int path_cost(const std::vector<int> &path)
{
    int res = 0;
    for (int e : path)
    {
        res += cost(e);
    }
    return res;
}

std::pair<int, int> min_cost_max_flow(int s, int t)
{
    int result_flow = 0;
    int result_cost = 0;
    while (true)
    {
        for (int i = 0; i < MAXN; i++)
        {
            pred[i] = INF;
            dist[i] = INF;
        }
        find_path(s);
        if (dist[t] >= INF)
        {
            break;
        }
        auto path = restore_path(t);
        int flow = path_capacity(path);
        int pcost = path_cost(path);
        push_path(path, flow);
        result_flow += flow;
        result_cost += pcost * flow;
    }
    return {result_flow, result_cost};
}

void add_edge(int a, int b, int u, int c)
{
    network[a].push_back(flow_edges.size());
    flow_edges.push_back({a, b, u, c, 0});
    network[b].push_back(flow_edges.size());
    flow_edges.push_back({b, a, 0, -c, 0});
}

int main()
{
    std::ifstream fin("individual/graphs/excursion/input.txt");
    std::ofstream ofStream("individual/graphs/excursion/output.txt");
    int s, t;
    fin >> n >> s >> t;
    s--;
    t--;
    int a, b, u, c;
    while (fin >> a >> b >> u >> c)
    {
        a--;
        b--;
        add_edge(a, b, u, c);
        add_edge(b, a, u, c);
    }
    std::pair<int, int> res;
    if (s > t)
    {
        res = min_cost_max_flow(t, s);
    }
    else
    {
        res = min_cost_max_flow(s, t);
    }
    ofStream << res.first << "\n"
             << res.second;
    return 0;
}