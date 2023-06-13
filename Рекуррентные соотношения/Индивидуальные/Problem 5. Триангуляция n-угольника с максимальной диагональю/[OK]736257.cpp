#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

struct Point
{
    int x;
    int y;
};

int n;
std::vector<int> xs;
std::vector<int> ys;
std::vector<Point> points;
std::vector<std::vector<double>> diags;

double get_diag(Point a, Point b)
{
    int delta_x = std::abs(a.x - b.x);
    int delta_y = std::abs(a.y - b.y);
    double current_diag = std::sqrt(std::pow(delta_x, 2) + std::pow(delta_y, 2));
    return current_diag;
}

double algo()
{
    std::vector<double> curr_diags;
    if (n == 3)
    {
        return 0;
    }

    if (n == 4)
    {
        return std::min(get_diag(points[0], points[2]), get_diag(points[1], points[3]));
    }
    else
    {
        --n;
        for (int p = 2; p <= n; ++p)
        {
            for (int i = 1; i <= n - p + 1; ++i)
            {
                int j = i + p - 1;
                diags[i][j] = INT_MAX;
                for (int k = i; k <= j - 1; ++k)
                {
                    double d1 = get_diag(points[i - 1], points[k]);
                    double d2 = get_diag(points[j], points[k]);
                    double d3 = get_diag(points[i - 1], points[j]);
                    double d = std::max(d1, d2);
                    d = std::max(d, d3);
                    double dMax = std::max(std::max(diags[i][k], diags[k + 1][j]), d);
                    if (dMax < diags[i][j])
                    {
                        diags[i][j] = dMax;
                    }
                }
            }
        }
    }
    return diags[1][n];
}

int main()
{
    std::ifstream fin("input.txt");
    fin >> n;
    xs.resize(n);
    ys.resize(n);
    points.resize(n);
    diags.resize(n + 1, std::vector<double>(n));

    int x, y;
    for (int i = 0; i < n; ++i)
    {
        fin >> x >> y;
        points[i] = {x, y};
    }
    fin.close();

    std::ofstream fout("output.txt");
    fout << std::setprecision(4) << std::fixed << algo();
    fout.close();

    return 0;
}
