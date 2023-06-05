#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("../common/lis/input.txt");
    std::ofstream ofStream("../common/lis/output.txt");
    int n;
    fin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        fin >> a[i];
    }
    std::vector<int> dp(n + 1, INT32_MAX);
    dp[0] = INT32_MIN;
    for (int i = 0; i < n; i++)
    {
        int j = std::lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        if (a[i] < dp[j] && a[i] > dp[j - 1])
        {
            dp[j] = a[i];
        }
    }
    ofStream << lower_bound(dp.begin(), dp.end(), INT32_MAX) - dp.begin() - 1;
    return 0;
}