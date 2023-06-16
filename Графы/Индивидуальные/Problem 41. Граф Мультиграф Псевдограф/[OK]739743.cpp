#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    int n, m, a, b;
    bool g(true), mg(true);
    std::ifstream in("input.txt");
    in >> n >> m;
    std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i < m; ++i)
    {
        in >> a >> b;
        if (matrix[a][b] || matrix[b][a])
        {
            g = false;
        }
        if (a == b)
        {
            g = false;
            mg = false;
        }
        matrix[a][b] = 1;
        matrix[b][a] = 1;
    }
    std::ofstream out("output.txt");
    out << (g ? "Yes" : "No");
    out << std::endl;
    out << (mg ? "Yes" : "No");
    out << std::endl;
    out << "Yes";

    return 0;
}