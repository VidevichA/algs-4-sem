#include <iostream>
#include <vector>
#include <fstream>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream ofStream("output.txt");
    int i, j, M, N, coin, S;
    int sum = 0;
    fin >> N >> M >> S;
    std::vector<int> buy_coins(N);
    for (i = 0; i < N; i++)
    {
        fin >> buy_coins[i];
        sum += buy_coins[i];
    }
    std::vector<bool> can(sum + 1, false);
    can[0] = true;
    for (i = 0; i < N; i++)
    {
        for (j = sum - 1; j >= 0; j--)
        {
            if (can[j] && j + buy_coins[i] <= sum)
            {
                can[j + buy_coins[i]] = true;
            }
        }
        can[buy_coins[i]] = true;
    }

    for (i = 0; i < M; i++)
    {
        fin >> coin;
        for (j = 0; j <= sum; j++)
        {
            if (can[j] > 0 && j - coin >= 0)
            {
                can[j - coin] = true;
            }
        }
    }

    if (S < 0 || S > sum)
    {
        ofStream << "No";
    }
    else if (!can[S])
    {
        ofStream << "No";
    }
    else
    {
        ofStream << "Yes";
    }
    return 0;
}