#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

std::vector<std::vector<long long>> mat;
std::vector<bool> visited;
std::vector<long long> last;
void Dfs(long long start)
{
    std::stack<long long> stack;
    stack.push(start);
    while (!stack.empty())
    {
        auto v = stack.top();
        visited[v] = true;
        bool isTop = true;
        while (last[v] < mat[v].size())
        {
            auto u = mat[v][last[v]];
            last[v] += 1;
            if (!visited[u])
            {
                stack.push(u);
                isTop = false;
                break;
            }
        }
        if (isTop)
        {
            stack.pop();
        }
    }
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n, m;
    in >> n >> m;
    visited = std::vector<bool>(n);
    mat = std::vector<std::vector<long long>>(n);
    last = std::vector<long long>(n, 0);
    for (long long i = 0; i < m; ++i)
    {
        long long k1, k2;
        in >> k1 >> k2;
        mat[k1 - 1].push_back(k2 - 1);
        mat[k2 - 1].push_back(k1 - 1);
    }
    long long count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            Dfs(i);
            ++count;
        }
    }
    out << count - 1;
    return 0;
}