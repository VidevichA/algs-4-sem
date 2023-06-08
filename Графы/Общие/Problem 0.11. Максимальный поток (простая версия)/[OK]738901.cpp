#include <iostream>
#include <vector>

using namespace std;

long long miN(long long a, long long b)
{
    return a < b ? a : b;
}

vector<vector<long long>> edges;
vector<vector<int>> graph;
vector<int> visited;
int timer = 1;
long long n, m;

long long dfs(int v, long long min)
{
    if (v == n - 1)
    {
        return min;
    }
    visited[v] = timer;
    for (long long i : graph[v])
    {
        if (edges[i][2] - edges[i][1] == 0 || visited[edges[i][0]] == timer)
        {
            continue;
        }

        long long f = dfs(edges[i][0], miN(min, edges[i][2] - edges[i][1]));

        if (f)
        {
            edges[i][1] += f;
            edges[i ^ 1][1] -= f;
            return f;
        }
    }
    return 0;
}

int main()
{
    cin >> n;
    cin >> m;

    graph = vector<vector<int>>(n);
    visited = vector<int>(n);

    int v;
    int u;
    int capacity;

    for (int i = 0; i < m; ++i)
    {
        cin >> v;
        cin >> u;
        cin >> capacity;
        --v;
        --u;
        graph[v].push_back(edges.size());
        vector<long long> tmp(3);
        tmp[0] = u;
        tmp[1] = 0;
        tmp[2] = capacity;
        edges.push_back(tmp);
        graph[u].push_back(edges.size());
        tmp[0] = v;
        tmp[1] = 0;
        tmp[2] = 0;
        edges.push_back(tmp);
    }

    while (dfs(0, LLONG_MAX))
    {
        ++timer;
    }

    long long rez = 0;

    for (int i = 0; i < graph[0].size(); i++)
    {
        rez += edges[graph[0][i]][1];
    }

    cout << rez;
    return 0;
}