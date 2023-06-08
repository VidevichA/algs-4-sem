#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Position
{
    int x;
    int y;
};

double interval(Position &p1, Position &p2)
{
    Position temp = {
        p2.x - p1.x, p2.y - p1.y};
    return sqrt((double)temp.x * temp.x + (double)temp.y * temp.y);
}

double getSum(int n, std::vector<Position> &points, int i, int j, std::vector<std::vector<double>> &result)
{
    if (i + 1 == j)
    {
        return 0;
    }
    else if (result[i][j] >= 0)
    {
        return result[i][j];
    }
    else
    {
        double min_weight = INT_MAX;
        double temp_weight = 0;
        double weight;
        if (i > 0 || j < n - 1)
        {
            temp_weight = interval(points[i], points[j]);
        }
        for (int k = i + 1; k < j; ++k)
        {
            double weight_t = getSum(n, points, i, k, result) + getSum(n, points, k, j, result);
            min_weight = std::min(min_weight, weight_t);
        }
        weight = temp_weight + min_weight;
        result[i][j] = weight;
        return weight;
    }
}

int main()
{
    std::ifstream in("input.txt");
    int n;
    in >> n;
    std::vector<Position> points(n);
    for (int i = 0; i < n; ++i)
    {
        int temp1, temp2;
        in >> temp1 >> temp2;
        points.at(i).x = temp1;
        points.at(i).y = temp2;
    }
    std::vector<std::vector<double>> result(n, std::vector<double>(n, -1));
    std::ofstream out("output.txt");
    out << getSum(n, points, 0, n - 1, result) << "\n";
    return 0;
}