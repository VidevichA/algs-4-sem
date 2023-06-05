#include <fstream>
#include <queue>

int n;
std::vector<bool> visited(n);
int next_idx = 1;
std::vector<int> ord(n);

void dfs(std::vector<std::vector<int>> matrix, int start)
{
    visited[start] = true;
    ord[start] = next_idx;
    next_idx++;
    for (int u = 0; u < n; u++)
    {
        if (matrix[start][u] && !visited[u])
        {
            dfs(matrix, u);
        }
    }
}

int main()
{
    std::ifstream fin("common/graphs/dfs/input.txt");
    std::ofstream ofStream("common/graphs/dfs/output.txt");
    fin >> n;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    visited.resize(n);
    ord.resize(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(matrix, i);
        }
    }
    for (int i : ord)
    {
        ofStream << i << " ";
    }
    return 0;
}