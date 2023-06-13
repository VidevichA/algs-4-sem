#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

int n, m;
std::vector<std::vector<double>> input;

bool bigger(std::vector<double> &a, std::vector<double> &b)
{
    for (int i = 0; i < n; ++i)
    {
        if (a[i] < b[i])
        {
            return false;
        }
    }
    return true;
}

int get_count()
{
    std::vector<int> includes(m);

    for (int i = 0; i < m; ++i)
    {
        includes[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            if (bigger(input[i], input[j]))
            {
                includes[i] = std::max(includes[i], 1 + includes[j]);
            }
        }
    }

    return includes[std::max_element(includes.begin(), includes.end()) - includes.begin()];
}

int main()
{
    std::ifstream fin("input.txt");
    fin >> n >> m;
    input.resize(m, std::vector<double>(n + 1));

    int x;
    double volume;
    for (int i = 0; i < m; ++i)
    {
        volume = 0;
        for (int j = 0; j < n; ++j)
        {
            fin >> x;
            input[i][j] = x;
            volume += log10(x);
        }
        input[i][n] = volume;
    }
    fin.close();

    for (int i = 0; i < m; ++i)
    {
        std::sort(input[i].begin(), input[i].end() - 1);
    }

    std::sort(input.begin(), input.end(), [](std::vector<double> &a, std::vector<double> &b)
              { return a[n] < b[n]; });

    std::ofstream fout("output.txt");
    fout << get_count();
    fout.close();

    return 0;
}
