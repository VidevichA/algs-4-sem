#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    int n, m, a, b;
    std::ifstream in("input.txt");
    in >> n >> m;
    std::vector<int> vector(n + 1);
    for (int i = 0; i < m; ++i)
    {
        in >> a >> b;
        vector[a - 1] += 1;
        vector[b - 1] += 1;
    }

    std::sort(vector.begin(), vector.end());
    std::reverse(vector.begin(), vector.end());

    std::ofstream out("output.txt");
    for (int i = 0; i < n; ++i)
    {
        out << vector[i] << ' ';
    }

    return 0;
}