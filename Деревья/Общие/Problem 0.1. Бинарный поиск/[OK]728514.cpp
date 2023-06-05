#include <iostream>
#include <vector>

bool binary_search(const std::vector<int> &a, int x)
{
    int q = 0, r = a.size();
    int mid;
    while (q < r)
    {
        mid = (q + r) / 2;
        if (a[mid] == x)
        {
            return true;
        }
        if (a[mid] < x)
        {
            q = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return false;
}

int lower_bound(const std::vector<int> &a, int x)
{
    int q = 0, r = a.size();
    int mid;
    while (q < r)
    {
        mid = (q + r) / 2;
        if (a[mid] < x)
        {
            q = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return q;
}

int upper_bound(const std::vector<int> &a, int x)
{
    int q = 0, r = a.size();
    int mid;
    while (q < r)
    {
        mid = (q + r) / 2;
        if (a[mid] > x)
        {
            r = mid;
        }
        else
        {
            q = mid + 1;
        }
    }
    return q;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    int k;
    std::cin >> k;
    std::vector<int> query(k);
    for (int i = 0; i < k; i++)
    {
        std::cin >> query[i];
    }
    for (int i = 0; i < k; i++)
    {
        std::cout << binary_search(a, query[i]) << " " << lower_bound(a, query[i]) << " " << upper_bound(a, query[i]) << "\n";
    }
    return 0;
}