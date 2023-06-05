#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream fin("../common/palindrome/input.txt");
    std::ofstream ofStream("../common/palindrome/output.txt");
    std::string s;
    fin >> s;
    fin.close();
    int n = s.length();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n));
    for (int i = 0; i < n - 1; i++)
    {
        dp[i][i] = 1;
        dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
    }
    dp[n - 1][n - 1] = 1;

    for (int j = 2; j < n; j++)
    {
        for (int i = j - 1; i >= 0; i--)
        {
            dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] + 2 : std::max(dp[i + 1][j], dp[i][j - 1]);
        }
    }

    std::string res;
    int i = 0, j = n - 1;
    while (i <= j)
    {
        if (s[i] == s[j])
        {
            res += s[i];
            i++;
            j--;
        }
        else if (dp[i + 1][j] <= dp[i][j - 1])
        {
            j--;
        }
        else
        {
            i++;
        }
    }

    std::string tmp = res;
    std::reverse(tmp.begin(), tmp.end());
    if (dp[0][n - 1] % 2 == 1)
    {
        tmp = tmp.substr(1);
    }
    res += tmp;

    ofStream << dp[0][n - 1] << "\n";
    ofStream << res;
}