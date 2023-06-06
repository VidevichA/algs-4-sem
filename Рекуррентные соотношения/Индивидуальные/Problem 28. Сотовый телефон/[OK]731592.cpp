#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

void printDP(vector<vector<int>> dp)
{
    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = 0; j < dp[i].size(); j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

long long calc(int n, int m, vector<long long> lst)
{
    if (n >= m)
    {
        long long s = 0;
        for (int i = 0; i < m; i++)
        {
            s += lst[i];
        }
        return s;
    }
    if (n == 0 || m == 0)
    {
        return 0;
    }
    vector<vector<long long>> dp;
    for (int i = 0; i < n; i++)
    {
        vector<long long> temp;
        for (int j = 0; j < m; j++)
        {
            temp.push_back(0);
        }
        dp.push_back(temp);
    }

    dp[0][0] = lst[0];
    for (int i = 1; i < m; i++)
    {
        dp[0][i] = lst[i] * (i + 1) + dp[0][i - 1];
    }

    for (int i = 1; i < n; i++)
    {
        dp[i][i] = lst[i] + dp[i - 1][i - 1];
        for (int j = i + 1; j < m; j++)
        {
            dp[i][j] = lst[j] * (j - i + 1) + dp[i][j - 1];
        }
        for (int j = i + 1; j < m; j++)
        {
            long long s = dp[i - 1][j - 1];
            for (int k = j; k < m; k++)
            {
                s += lst[k] * (k - j + 1);
                if (dp[i][k] > s)
                {
                    dp[i][k] = s;
                }
            }
        }
    }
    return dp[n - 1][m - 1];
}

int main()
{
    ifstream in;
    in.open("in.txt");
    int n, m;
    in >> n;
    in >> m;
    vector<long long> data;
    for (int i = 0; i < m; i++)
    {
        int a;
        in >> a;
        data.push_back(a);
    }
    in.close();
    long long answer = calc(n, m, data);
    ofstream out;
    out.open("out.txt");
    out << answer;
    out.close();
    return 0;
}
