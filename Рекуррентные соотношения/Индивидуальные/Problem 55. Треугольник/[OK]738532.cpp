#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    std::ifstream fin("common/new_kr/triangle/input.txt");
    std::ofstream ofStream("common/new_kr/triangle/output.txt");
    int k;
    fin >> k;

    vector<vector<int>> a(k, vector<int>(k));
    vector<vector<int>> dp(k, vector<int>(k));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            fin >> a[i][j];
        }
    }

    dp[0][0] = a[0][0];
    for (int i = 1; i < k; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j == 0)
            {
                dp[i][j] = a[i][j] + dp[i - 1][j];
            }
            else if (j == i)
            {
                dp[i][j] = a[i][j] + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = a[i][j] + max(dp[i - 1][j - 1], dp[i - 1][j]);
            }
        }
    }
    int max_sum = 0;
    for (int j = 0; j < k; j++)
    {
        max_sum = max(max_sum, dp[k - 1][j]);
    }

    ofStream << max_sum;

    return 0;
}
