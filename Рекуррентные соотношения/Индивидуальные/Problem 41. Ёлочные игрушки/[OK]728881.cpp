#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream fin("input.txt");
std::ofstream out("output.txt");

int main()
{
    int s, n, m, capacity, d, t;

    fin >> s >> n >> m;
    capacity = n * m;
    std::vector<std::vector<long long>> dp(s + 1, std::vector<long long>(capacity + 1));
    std::vector<long long> dim;
    std::vector<long long> time;
    for (int i = 0; i < s; ++i)
    {
        fin >> d >> t;
        dim.push_back(d);
        time.push_back(t);
    }

    for (int i = 1; i <= s; ++i)
    {
        for (int j = 1; j <= capacity; ++j)
        {
            if (dim[i - 1] <= j)
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - dim[i - 1]] + time[i - 1]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    std::vector<int> kits;
    int i = s, j = capacity;
    while (i >= 0 && j >= 0 && dp[i][j] != 0)
    {
        if (dp[i][j] == dp[i - 1][j])
        {
            i -= 1;
        }
        else
        {
            kits.push_back(i);
            i -= 1;
            j -= dim[i];
        }
    }

    std::sort(kits.begin(), kits.end());
    out << kits.size() << "\n";
    for (int i : kits)
    {
        out << i << " ";
    }
    //    std::cout << "\n";
    //    for(std::vector<long long> row : dp){
    //        for(long long el : row){
    //            std::cout << el << " ";
    //        }
    //        std::cout << "\n";
    //    }

    return 0;
}