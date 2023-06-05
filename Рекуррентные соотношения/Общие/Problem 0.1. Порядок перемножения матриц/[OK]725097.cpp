#include <fstream>
#include <vector>
#include <cmath>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int nm;
    in >> nm;
    std::vector<int> sizes;
    for (int i = 0; i < nm; ++i)
    {
        int temp;
        if (i == 0)
        {
            in >> temp;
            sizes.push_back(temp);
            in >> temp;
            sizes.push_back(temp);
        }
        else
        {
            in >> temp;
            in >> temp;
            sizes.push_back(temp);
        }
    }
    int n = sizes.size() - 1;
    std::vector<std::vector<int>> m(n, std::vector<int>(n, 0));
    for (int l = 1; l < n; ++l)
    {
        for (int i = 0; i < n - l; ++i)
        {
            int j = i + l;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; ++k)
            {
                m[i][j] = std::min(m[i][j], m[i][k] + m[k + 1][j] + sizes[i] * sizes[k + 1] * sizes[j + 1]);
            }
        }
    }
    out << m[0][n - 1];
    return 0;
}