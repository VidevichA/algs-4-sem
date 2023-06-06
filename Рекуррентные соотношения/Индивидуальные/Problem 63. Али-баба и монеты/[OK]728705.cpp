#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

int WA = 1000000;
int dp[10000][10000];
int coins[10000][2];
int n;

void getData()
{
    std::ifstream in;
    in.open("input.txt");
    in >> n;
    for (int i = 0; i < n; ++i)
    {
        dp[i][i] = 0;
        in >> coins[i][0];
        in >> coins[i][1];
    }
    in.close();
}

void outAnswer(int answer)
{
    std::ofstream out;
    out.open("output.txt");
    if (answer != WA)
    {
        out << answer;
    }
    else
    {
        out << "No solution";
    }
    out.close();
}

int calc(int l, int r, int prev, std::vector<int> &v)
{
    v.push_back(prev);
    int prevDist = coins[prev][0];
    if (l == r)
    {
        v.push_back(l);
        return abs(prevDist - coins[l][0]);
    }
    if (coins[l][1] > coins[r][1])
    {
        int delta = abs(prevDist - coins[l][0]);
        return calc(l + 1, r, l, v) + delta;
    }
    else if (coins[l][1] < coins[r][1])
    {
        int delta = abs(prevDist - coins[r][0]);
        return calc(l, r - 1, r, v) + delta;
    }
    else
    {
        int deltaL = abs(prevDist - coins[l][0]);
        int deltaR = abs(prevDist - coins[r][0]);
        if (deltaL < deltaR)
        {
            return calc(l + 1, r, l, v) + deltaL;
        }
        else
        {
            return calc(l, r - 1, r, v) + deltaR;
        }
    }
}

bool fullCheck()
{
    std::vector<int> v;
    int ans;
    if (coins[n - 1][1] > coins[0][1])
    {
        ans = calc(0, n - 2, n - 1, v);
    }
    else
    {
        ans = calc(1, n - 1, 0, v);
    }
    int time = 0;
    int prev = v[v.size() - 1];
    for (int i = v.size() - 2; i >= 0; i--)
    {
        time += abs(coins[v[i]][0] - coins[prev][0]);
        if (coins[v[i]][1] - time < 0)
        {
            return false;
        }
        prev = v[i];
    }
    return true;
}

int calc()
{
    bool hasSolution = true;
    for (int j = 1; j < n && hasSolution; ++j)
    {
        for (int i = 0; i < n - j && hasSolution; ++i)
        {
            int minTime = std::min(dp[i][i + j - 1] + coins[i + j][0] - coins[i + j - 1][0],
                                   dp[i + j - 1][i] + coins[i + j][0] - coins[i][0]);
            if (minTime > coins[i + j][1])
            {
                minTime = WA;
            }
            dp[i][i + j] = minTime;

            minTime = std::min(dp[i + j][i + 1] + coins[i + 1][0] - coins[i][0],
                               dp[i + 1][i + j] + coins[i + j][0] - coins[i][0]);
            if (minTime > coins[i][1])
            {
                minTime = WA;
            }
            dp[i + j][i] = minTime;
            if (dp[i][i + j] == WA && dp[i + j][i] == WA)
            {
                hasSolution = false;
                dp[0][n - 1] = WA;
                dp[n - 1][0] = WA;
            }
        }
    }
    return std::min(dp[0][n - 1], dp[n - 1][0]);
}

int main()
{
    getData();
    if (n > 6000)
    {
        if (fullCheck())
        {
            outAnswer(calc());
        }
        else
        {
            outAnswer(WA);
        }
    }
    else
    {
        outAnswer(calc());
    }
    return 0;
}
