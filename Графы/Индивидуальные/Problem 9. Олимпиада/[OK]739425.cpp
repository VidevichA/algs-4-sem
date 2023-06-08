#include <fstream>
#include <vector>

std::vector<std::vector<bool>> mat;
std::vector<bool> visited;
void Dfs(long long start)
{
    visited[start] = true;
    for (long long i = 0; i < mat.size(); ++i)
    {
        if (mat[start][i] && !visited[i])
        {
            Dfs(i);
        }
    }
}

int main()
{
    std::ifstream in("input.in");
    std::ofstream out("output.out");
    long long n;
    in >> n;
    visited = std::vector<bool>(n);
    mat = std::vector<std::vector<bool>>(n, std::vector<bool>(n));
    for (long long i = 0; i < n; ++i)
    {
        for (long long j = 0; j < n; ++j)
        {
            bool temp;
            in >> temp;
            mat[i][j] = temp;
        }
    }
    Dfs(0);
    for (auto el : visited)
    {
        if (!el)
        {
            out << "NO";
            return 0;
        }
    }
    out << "YES";
    return 0;
}