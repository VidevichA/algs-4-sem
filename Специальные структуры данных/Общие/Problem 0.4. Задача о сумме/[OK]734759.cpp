#include <vector>
#include <cmath>
#include <iostream>

void Add(std::vector<long long> &a, std::vector<long long> &b, int i, int x, int k)
{
    a[i] += x;
    b[i / k] += x;
}

long long FindSum(std::vector<long long> &a, std::vector<long long> &b, int l, int r, int k)
{
    int jl = l / k;
    int jr = (r - 1) / k;
    long long sum = 0;
    if (jl == jr)
    {
        for (int i = l; i < r; i++)
        {
            sum += a[i];
        }
        return sum;
    }
    else
    {
        for (int i = l; i < (jl + 1) * k; i++)
        {
            sum += a[i];
        }
        for (int i = jl + 1; i < jr; i++)
        {
            sum += b[i];
        }
        for (int i = jr * k; i < r; i++)
        {
            sum += a[i];
        }
        return sum;
    }
}

int main()
{
    int n, q;
    std::cin >> n;
    int k = floor(std::sqrt(n));
    std::vector<long long> a(n);
    std::vector<long long> b(std::ceil(n / static_cast<double>(k)));
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i += k)
    {
        long long bsum = 0;
        for (int j = i; j < std::min(i + k, n); j++)
        {
            bsum += a[j];
        }
        b[i / k] = bsum;
    }
    std::cin >> q;
    for (int i = 0; i < q; i++)
    {
        std::string op;
        std::cin >> op;
        if (op == "Add")
        {
            int idx, x;
            std::cin >> idx >> x;
            Add(a, b, idx, x, k);
        }
        else
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << FindSum(a, b, l, r, k) << "\n";
        }
    }
    return 0;
}