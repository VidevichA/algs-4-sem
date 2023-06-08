#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> graph;
vector<vector<int>> rgraph;
vector<int> terminals;
vector<bool> visited;
vector<vector<int>> a;
vector<int> component;
vector<int> order;
int components;
vector<int> minVert;

void dfs(int v)
{
    if (visited[v])
    {
        return;
    }
    visited[v] = true;
    for (int i = 0; i < graph[v].size(); i++)
    {
        int to = graph[v][i];
        if (!visited[to])
        {
            dfs(to);
        }
    }
    order.push_back(v);
}

void dfsR(int v)
{
    if (visited[v])
    {
        return;
    }
    visited[v] = true;
    component[v] = components;
    for (int i = 0; i < rgraph[v].size(); i++)
    {
        int to = rgraph[v][i];
        if (!visited[to])
        {
            dfsR(to);
        }
    }
}

void success(vector<int> &comp)
{
    int u = comp[0];
    for (int i = 1; i < comp.size(); i++)
    {
        if (terminals[u] > terminals[comp[i]])
        {
            u = comp[i];
        }
    }
    minVert.push_back(u);
}

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> n;

    graph = vector<vector<int>>(n);
    rgraph = vector<vector<int>>(n);
    terminals = vector<int>(n);

    for (int i = 0; i < n; i++)
    {
        in >> terminals[i];
    }

    int u;
    int v;

    for (; true;)
    {
        in >> u;
        in >> v;
        if (u == 0 && v == 0)
        {
            break;
        }
        graph[u - 1].push_back(v - 1);
        rgraph[v - 1].push_back(u - 1);
    }

    visited = vector<bool>(n, false);
    component = vector<int>(n, -1);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }

    visited = vector<bool>(n, false);
    components = 0;
    for (int i = 0; i < order.size(); i++)
    {
        int vert = order[n - i - 1];
        if (component[vert] == -1)
        {
            dfsR(vert);
            components++;
        }
    }

    int kolComp = components;

    a = vector<vector<int>>(kolComp);

    for (int i = 0; i < component.size(); i++)
    {
        int k = component[i];
        a[k].push_back(i);
    }

    for (int i = 0; i < kolComp; i++)
    {
        success(a[i]);
    }

    order = vector<int>(0);

    vector<int> finalVect;
    visited = vector<bool>(n, false);

    for (int i = 0; i < minVert.size(); i++)
    {
        int vert = minVert[i];
        if (!visited[vert])
        {
            finalVect.push_back(vert);
            dfs(vert);
        }
    }

    out << finalVect.size() << endl;

    for (int &item : finalVect)
    {
        out << item + 1 << " ";
    }
}