#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    int *a = new int[n];
    int *b = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> b[i];
    }
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[0][i] = 0;
        dp[i][0] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int len = dp[n][n];
    int index_a[len];
    int index_b[len];
    for (int i = n, j = n, idx = len - 1; i > 0 && j > 0;)
    {
        if (a[i - 1] == b[j - 1])
        {
            i--;
            j--;
            index_a[idx] = i;
            index_b[idx] = j;
            idx--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    delete[] a;
    delete[] b;
    std::cout << dp[n][n] << "\n";
    for (int i = 0; i < len; i++)
    {
        std::cout << index_a[i] << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < len; i++)
    {
        std::cout << index_b[i] << " ";
    }
}