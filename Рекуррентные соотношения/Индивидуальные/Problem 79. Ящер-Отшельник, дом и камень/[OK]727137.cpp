#include <iostream>
#include <vector>

long long MaxPartOfArray(std::vector<long long> &sum)
{
    long long max = 0;
    long long temp = 0;
    for (long long s : sum)
    {
        temp += s;
        max = std::max(max, temp);
        if (temp < 0)
        {
            temp = 0;
        }
    }
    return max;
}

long long FindArea(std::vector<std::vector<long>> &matrix)
{

    if (matrix.empty() || matrix[0].empty())
    {
        return 0;
    }
    long long max = 0;
    std::vector<long long> sum(matrix[0].size());
    for (int i = 0; i < matrix.size(); ++i)
    {
        sum = std::vector<long long>(matrix[0].size());
        for (int j = i; j < matrix.size(); ++j)
        {
            for (int k = 0; k < matrix[0].size(); ++k)
            {
                sum[k] += matrix[j][k];
            }
            max = std::max(max, MaxPartOfArray(sum));
        }
    }
    return max;
}

int main()
{
    long n, m, num;
    std::vector<std::vector<long>> matrix;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        std::vector<long> row;
        matrix.push_back(row);
        for (int j = 0; j < m; ++j)
        {
            std::cin >> num;
            matrix[i].push_back(num);
        }
    }
    std::cout << FindArea(matrix);
    return 0;
}