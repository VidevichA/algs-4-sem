#include <iostream>
#include <vector>

std::vector<int> findFingering(const std::vector<int> &a);

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
        std::cout << 1;
        return 0;
    }
    std::vector<int> fingers = findFingering(a);

    for (int finger : fingers)
    {
        std::cout << finger << " ";
    }
    return 0;
}

std::vector<int> findFingering(const std::vector<int> &a)
{
    size_t n = a.size();
    std::vector<int> fingers(n);
    if (a[0] < a[1])
    {
        fingers[0] = 1;
    }
    else if (a[0] > a[1])
    {
        fingers[0] = 5;
    }
    else
    {
        fingers[0] = 3;
    }
    int finger;
    for (int i = 1; i < n; i++)
    {
        if (a[i - 1] < a[i])
        {
            finger = fingers[i - 1] + 1;
            if (i <= n - 2 && a[i] > a[i + 1])
            {
                finger = 5;
            }
        }
        else if (a[i - 1] > a[i])
        {
            finger = fingers[i - 1] - 1;
            if (i <= n - 2 && a[i] < a[i + 1])
            {
                finger = 1;
            }
        }
        else /* (a[i - coins] == a[i]) */
        {
            finger = (fingers[i - 1] == 3) ? 2 : 3;
            if (i <= n - 2)
            {
                if (a[i] < a[i + 1])
                {
                    finger = (fingers[i - 1] == 1) ? 2 : 1;
                }
                else if (a[i] > a[i + 1])
                {
                    finger = (fingers[i - 1] == 5) ? 4 : 5;
                }
            }
        }
        fingers[i] = finger;
    }
    return fingers;
}