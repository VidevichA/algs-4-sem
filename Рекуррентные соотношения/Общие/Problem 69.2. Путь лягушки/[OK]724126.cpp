#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }

    if (n == 1)
    {
        std::cout << a[0] << "\n"
                  << 1;
        return 0;
    }
    if (n == 2)
    {
        std::cout << -1;
        return 0;
    }
    std::vector<int> f(n);
    std::vector<int> lilies;
    f[0] = a[0];
    f[1] = -1;
    for (int i = 2; i < n; i++)
    {
        if (i < 3)
        {
            f[i] = f[i - 2] + a[i];
        }
        else
        {
            f[i] = std::max(f[i - 2], f[i - 3]) + a[i];
        }
    }
    std::cout << f[n - 1] << "\n";
    lilies.push_back(n);
    for (int i = n - 1; i >= 0;)
    {
        if (i == 2 || i == 3)
        {
            lilies.push_back(1);
            break;
        }
        if (f[i - 2] > f[i - 3])
        {
            lilies.push_back(i - 1);
            i -= 2;
        }
        else
        {
            lilies.push_back(i - 2);
            i -= 3;
        }
    }

    for (int i = lilies.size() - 1; i >= 0; i--)
    {
        std::cout << lilies[i] << " ";
    }
    return 0;
}