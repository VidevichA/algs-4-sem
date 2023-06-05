#include <fstream>
#include <vector>

int main()
{
    std::fstream fin("../common/25/in.txt");
    std::ofstream ofStream("../common/25/out.txt");
    int x, y, z;
    std::string A;
    std::string B;
    fin >> x >> y >> z >> A >> B;
    fin.close();
    int n = A.length();
    int m = B.length();

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = i * x;
    }
    for (int j = 1; j <= m; j++)
    {
        dp[0][j] = j * y;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = std::min(dp[i - 1][j - 1] + z,
                                    std::min(dp[i][j - 1] + y, dp[i - 1][j] + x));
            }
        }
    }
    ofStream << dp[n][m];
    return 0;
}