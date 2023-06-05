#include <fstream>
#include <queue>

int n;
std::vector<bool> visited(n);
int next_idx = 1;
std::vector<int> ord(n);

void bfs(std::vector<std::vector<int>> matrix, int start)
{
    std::queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        ord[v] = next_idx;
        next_idx++;
        for (int u = 0; u < n; u++)
        {
            if (matrix[v][u] && !visited[u])
            {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}

int main()
{
    std::ifstream fin("common/graphs/bfs/input.txt");
    std::ofstream ofStream("common/graphs/bfs/output.txt");
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
            bfs(matrix, i);
        }
    }
    for (int i : ord)
    {
        ofStream << i << " ";
    }
    return 0;
}