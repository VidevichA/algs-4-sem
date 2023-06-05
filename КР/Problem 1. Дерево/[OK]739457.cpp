#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <string>

typedef long long number;

std::vector<std::vector<number>> matrix;

template <typename T>
void PrintVector(const std::vector<T> &v)
{
    std::cout << '\n';
    for (auto el : v)
    {
        std::cout << el << ' ';
    }
    std::cout << '\n';
}

template <typename T>
void PrintMatrix(const std::vector<std::vector<T>> &m)
{
    std::cout << '\n';
    for (auto r : m)
    {
        for (auto c : r)
        {
            std::cout << c << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void DfsTree(number i, std::vector<bool> &col)
{
    if (col[i])
    {
        return;
    }
    col[i] = true;
    for (number j = 0; j < matrix.size(); ++j)
    {
        if (matrix[i][j])
        {
            DfsTree(j, col);
        }
    }
}

bool IsTree()
{
    number edges = 0;
    for (auto r : matrix)
    {
        for (auto c : r)
        {
            if (c)
            {
                ++edges;
            }
        }
    }
    if (edges / 2 != matrix.size() - 1)
    {
        return false;
    }
    std::vector<bool> col(matrix.size(), 0);
    DfsTree(0, col);
    for (number i = 0; i < matrix.size(); ++i)
    {
        if (!col[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    number n;
    in >> n;
    matrix = std::vector<std::vector<long long>>(n, std::vector<long long>(n, 0));
    for (number i = 0; i < n; ++i)
    {
        for (number j = 0; j < n; ++j)
        {
            in >> matrix[i][j];
        }
    }
    out << (IsTree() ? "Yes" : "No");
    return 0;
}