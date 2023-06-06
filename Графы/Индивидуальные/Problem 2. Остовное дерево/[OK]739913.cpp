#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

void dfs(int node, std::vector<bool> &visited, const std::vector<std::vector<int>> &graph, std::vector<std::pair<int, int>> &edges)
{
    visited[node] = true;
    for (size_t i = 0; i < graph[node].size(); ++i)
    {
        if (graph[node][i] && !visited[i])
        {
            edges.emplace_back(node + 1, i + 1);
            dfs(i, visited, graph, edges);
        }
    }
}

int main()
{

    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n;
    in >> n;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            in >> graph[i][j];
        }
    }

    std::vector<bool> visited(n, false);
    std::vector<std::pair<int, int>> edges;
    dfs(0, visited, graph, edges);

    if (std::count(visited.begin(), visited.end(), true) != n)
    {
        out << -1;
    }
    else
    {
        out << edges.size() << std::endl;
        for (const auto &edge : edges)
        {
            out << edge.first << " " << edge.second << '\n';
        }
    }

    return 0;
}