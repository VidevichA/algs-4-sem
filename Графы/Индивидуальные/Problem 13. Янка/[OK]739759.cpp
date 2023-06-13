#include <fstream>
#include <vector>

std::vector<std::vector<int>> matrix;
std::vector<bool> visited;
std::vector<int> link;
int n, k;

bool kuhn(int vertex)
{
    if (visited[vertex])
    {
        return false;
    }

    visited[vertex] = true;
    for (int i = 1; i < n + 1; ++i)
    {
        if (matrix[vertex][i] == 1)
        {
            if (link[i] == -1 || kuhn(link[i]))
            {
                link[i] = vertex;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::ifstream fin("input.in");
    fin >> n >> k;
    matrix.resize(n + 1, std::vector<int>(n + 1, 0));
    link.resize(n + 1, -1);

    int x;
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            fin >> x;
            matrix[x][i] = 1;
        }
    }
    fin.close();

    for (int i = 1; i < n + 1; ++i)
    {
        visited.assign(n + 1, false);
        kuhn(i);
    }

    std::ofstream fout("output.out");
    for (int i = 1; i < n + 1; ++i)
    {
        fout << link[i] << ' ';
    }
    fout.close();
    return 0;
}