#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("../common/easy/input.txt");
    std::ofstream ofStream("../common/easy/output.txt");
    int s;
    fin >> s;
    std::vector<int> n(s);
    std::vector<int> m(s);
    for (int i = 0; i < s; i++)
    {
        fin >> n[i] >> m[i];
    }
    std::vector<std::vector<long long>> dp(s, std::vector<long long>(s));
    dp[s - 1][s - 1] = 0;
    for (int i = 0; i < s - 1; i++)
    {
        dp[i][i] = 0;
        dp[i][i + 1] = n[i] * m[i] * m[i + 1];
    }
    for (int j = 2; j < s; j++)
    {
        for (int i = j - 2; i >= 0; i--)
        {
            for (int k = i; k < j; k++)
            {
                long long min = dp[i][k] + dp[k + 1][j] + n[i] * m[k] * m[j];
                if (min < dp[i][j] || dp[i][j] == 0)
                {
                    dp[i][j] = min;
                }
            }
        }
    }
    ofStream << dp[0][s - 1];
}