#include <vector>
#include <fstream>
#include <iostream>
#include <map>

int main()
{
    std::ifstream in("discount.in");
    std::ofstream out("discount.out");

    int n;
    in >> n;

    int prices[6][6][6][6][6];

    for (auto &i1 : prices)
    {
        for (auto &i2 : i1)
        {
            for (auto &i3 : i2)
            {
                for (auto &i4 : i3)
                {
                    for (auto &i5 : i4)
                    {
                        i5 = INT_MAX;
                    }
                }
            }
        }
    }

    int basket[5] = {0};

    int coast[105];

    std::map<int, int> id;

    for (int i = 0; i < n; i++)
    {
        int x;
        in >> x;
        id.insert(std::make_pair(x, i));
        in >> x;
        basket[i] = x;
        in >> x;
        coast[i] = x;
    }

    int s;
    in >> s;

    int sales[105][5] = {{0}};

    for (int i = 0; i < n; i++)
    {
        sales[i][i] = 1;
    }

    for (int i = n; i < n + s; i++)
    {
        int numberInSale;
        in >> numberInSale;
        for (int j = 0; j < numberInSale; j++)
        {
            int x;
            int y;
            in >> x;
            in >> y;
            sales[i][id[x]] = y;
        }
        in >> numberInSale;
        coast[i] = numberInSale;
    }

    for (int i = 0; i < n + s; i++)
    {
        prices[sales[i][0]][sales[i][1]][sales[i][2]][sales[i][3]][sales[i][4]] = coast[i];
    }
    prices[0][0][0][0][0] = 0;

    for (int i = 0; i < n + s; i++)
    {
        for (int a = 0; a <= basket[0]; a++)
        {
            for (int b = 0; b <= basket[1]; b++)
            {
                for (int c = 0; c <= basket[2]; c++)
                {
                    for (int d = 0; d <= basket[3]; d++)
                    {
                        for (int e = 0; e <= basket[4]; e++)
                        {
                            if (prices[a][b][c][d][e] != INT_MAX)
                            {
                                if (a + sales[i][0] <= 5 && b + sales[i][1] <= 5 && c + sales[i][2] <= 5 && d + sales[i][3] <= 5 && e + sales[i][4] <= 5)
                                {
                                    prices[a + sales[i][0]][b + sales[i][1]]
                                          [c + sales[i][2]][d + sales[i][3]]
                                          [e + sales[i][4]] = std::min(
                                              prices[a + sales[i][0]][b + sales[i][1]][c + sales[i][2]][d + sales[i][3]][e + sales[i][4]],
                                              prices[a][b][c][d][e] + coast[i]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    out << prices[basket[0]][basket[1]][basket[2]][basket[3]][basket[4]];
}