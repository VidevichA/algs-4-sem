#include <fstream>
#include <vector>

int n;
std::vector<bool> visited;
std::vector<std::vector<int>> a;

void dfs(int v)
{
    visited[v] = true;
    for (int i = 0; i < n; i++)
    {
        if (a[v][i] && !visited[i])
        {
            dfs(i);
        }
    }
}

int main()
{
    std::ifstream fin("common/kr3/task1/input.in");
    std::ofstream ofStream("common/kr3/task1/output.out");
    fin >> n;
    visited = std::vector<bool>(n);
    a.resize(n, std::vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> a[i][j];
        }
    }
    dfs(0);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            ofStream << "NO";
            return 0;
        }
    }

    ofStream << "YES";

    return 0;
}