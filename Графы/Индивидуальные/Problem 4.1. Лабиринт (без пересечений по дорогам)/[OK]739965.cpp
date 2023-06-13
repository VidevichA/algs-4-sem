#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

std::ifstream fin("input.in");
std::ofstream out("output.out");

struct Edge
{
    int source;
    int target;
    int capacity;
    int flow;

    Edge(int s, int t, int c, int f)
    {
        this->source = s;
        this->target = t;
        this->capacity = c;
        this->flow = f;
    }
};

int n;
std::vector<std::vector<int>> network;
std::vector<Edge> flow_edges;
std::vector<bool> visited;
std::vector<int> pred;

std::vector<int> edges(int v)
{
    return network[v];
}

int source(int e)
{
    return flow_edges[e].source;
}

int target(int e)
{
    return flow_edges[e].target;
}

bool remained(int e)
{
    return flow_edges[e].capacity - flow_edges[e].flow > 0;
}

void push(int e, int f)
{
    flow_edges[e].flow += f;
    int ind = e % 2 == 0 ? e + 1 : e - 1;
    flow_edges[ind].flow -= f;
}

void bfs(int start)
{
    std::queue<int> queue;
    visited[start] = true;
    queue.push(start);
    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();
        for (int e : edges(v))
        {
            int u = target(e);
            if (!visited[u] && remained(e))
            {
                visited[u] = true;
                pred[u] = e;
                queue.push(u);
            }
        }
    }
}

int max_flow(int start, int target)
{
    int max_flow = 0;
    while (true)
    {
        visited = std::vector<bool>(n + 2, false);
        pred = std::vector<int>(n + 2);
        bfs(start);

        if (!visited[target])
        {
            break;
        }
        std::vector<int> path;
        pred[0] = -1;
        int curr = n + 1;
        while (pred[curr] != -1)
        {
            int e = pred[curr];
            path.push_back(e);
            curr = source(e);
        }
        int min_cap = flow_edges[path[0]].capacity - flow_edges[path[0]].flow;
        for (int p : path)
        {
            min_cap = std::min(min_cap, flow_edges[p].capacity - flow_edges[p].flow);
        }
        for (int p : path)
        {
            push(p, min_cap);
        }
        max_flow += min_cap;
    }

    return max_flow;
}

int main()
{
    int p, k;
    fin >> n >> p >> k;
    network = std::vector<std::vector<int>>(n + 2);
    visited = std::vector<bool>(n, false);
    pred = std::vector<int>(n);
    std::vector<int> entries(p);
    std::vector<int> exits(k);
    std::vector<int> b(n);
    std::vector<std::vector<int>> g(n + 2);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int num;
            fin >> num;
            if (num == 1)
            {
                g[i + 1].push_back(j + 1);
                b[j]++;
            }
        }
    }

    for (int i = 0; i < p; ++i)
    {
        fin >> entries[i];
        g[0].push_back(entries[i]);
    }
    for (int i = 0; i < k; ++i)
    {
        fin >> exits[i];
        g[exits[i]].push_back(n + 1);
    }

    for (int i = 0; i < n + 2; ++i)
    {
        for (int j = 0; j < g[i].size(); ++j)
        {
            int cu = 1;
            if (i == 0)
            {
                cu = g[g[i][j]].size();
            }
            if (g[i][j] == n + 1)
            {
                cu = b[i - 1];
            }
            network[i].push_back(flow_edges.size());
            flow_edges.push_back(Edge(i, g[i][j], cu, 0));
            network[g[i][j]].push_back(flow_edges.size());
            flow_edges.push_back(Edge(g[i][j], i, 0, 0));
        }
    }

    out << max_flow(0, n + 1);
    return 0;
}