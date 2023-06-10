#include <iostream>
#include <vector>
#include <algorithm>

// left right are int

long long LowerBound(const std::vector<long long> &array, long long element, long long l, long long r)
{
    long long leftBorder = l, rightBorder = r;
    while (leftBorder < rightBorder)
    {
        long long center = (leftBorder + rightBorder) >> 1;
        if (element <= array[center])
        {
            rightBorder = center;
        }
        else
        {
            leftBorder = center + 1;
        }
    }
    return leftBorder;
}

long long UpperBound(const std::vector<long long> &array, long long element, long long l, long long r)
{
    long long leftBorder = l, rightBorder = r;
    while (leftBorder < rightBorder)
    {
        long long center = (leftBorder + rightBorder) / 2;
        if (element < array[center])
        {
            rightBorder = center;
        }
        else
        {
            leftBorder = center + 1;
        }
    }
    return leftBorder;
}

void MaxAmounts(const std::vector<long long> &numbers, std::vector<long long> &maxAmounts, long long m)
{
    for (int i = 0; i < numbers.size() - 1; i++)
    {
        maxAmounts.push_back(numbers[i + 1] - numbers[i]);
    }
    maxAmounts.push_back(m - numbers.back() + 1);
}

void BuildTree(const std::vector<long long> &maxAmounts, std::vector<long long> &tree, long long index, long long left, long long right)
{
    if (right - left == 1)
    {
        tree[index] = maxAmounts[left];
    }
    else
    {
        long long k = (left + right) >> 1;
        BuildTree(maxAmounts, tree, 2 * index, left, k);
        BuildTree(maxAmounts, tree, 2 * index + 1, k, right);
        tree[index] = std::max(tree[2 * index], tree[2 * index + 1]);
    }
}

void Build(const std::vector<long long> &maxAmounts, std::vector<long long> &tree, long long n)
{
    BuildTree(maxAmounts, tree, 1, 0, n);
}

long long MakeQuery(const std::vector<long long> &tree, long long index, long long left, long long right, long long l_query, long long r_query)
{
    if (left == l_query && right == r_query)
    {
        return tree[index];
    }
    long long k = (left + right) >> 1;
    if (r_query <= k)
    {
        return MakeQuery(tree, 2 * index, left, k, l_query, r_query);
    }
    if (k <= l_query)
    {
        return MakeQuery(tree, 2 * index + 1, k, right, l_query, r_query);
    }
    return std::max(MakeQuery(tree, 2 * index, left, k, l_query, k), MakeQuery(tree, 2 * index + 1, k, right, k, r_query));
}

long long GetQuery(const std::vector<long long> &tree, long long l_query, long long r_query, long long n)
{
    return MakeQuery(tree, 1, 0, n, l_query, r_query);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long m;
    long long n, k;
    std::cin >> m >> n >> k;
    std::vector<long long> numbers(n, 0); ////
    numbers[0] = 1;
    for (long long i = 1; i < n; i++)
    {
        std::cin >> numbers[i];
    }
    std::vector<long long> L(k, 0), R(k, 0); ////
    for (long long i = 0; i < k; i++)
    {
        std::cin >> L[i] >> R[i];
    }

    std::vector<long long> tree(4 * n + 1, 0);
    std::vector<long long> maxAmounts;
    MaxAmounts(numbers, maxAmounts, m);
    tree[0] = LONG_LONG_MIN;
    Build(maxAmounts, tree, n);
    for (long long i = 0; i < k; i++)
    {
        if (L[i] == R[i])
        {
            std::cout << 1 << '\n';
        }
        else
        {
            long long L_U = UpperBound(numbers, L[i], 0, n), R_U = UpperBound(numbers, R[i], 0, n);
            if (L_U == R_U)
            {
                std::cout << R[i] - L[i] + 1 << '\n';
            }
            else if (abs(L_U - R_U) == 1)
            {
                std::cout << std::max(numbers[L_U] - L[i], R[i] - numbers[R_U - 1] + 1) << '\n';
            }
            else
            {
                long long amountLeft = numbers[L_U] - L[i];
                long long amountRight = R[i] - numbers[R_U - 1] + 1;
                std::cout << std::max(std::max(amountLeft, amountRight), GetQuery(tree, UpperBound(numbers, L[i] + amountLeft, 0, n) - 1,
                                                                                  UpperBound(numbers, R[i] - amountRight, 0, n), n));
                std::cout << '\n';
            }
        }
    }
    return 0;
}