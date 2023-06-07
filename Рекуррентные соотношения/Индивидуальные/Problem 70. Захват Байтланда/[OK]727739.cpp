#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    fstream cin("input.txt");
    ofstream cout("output.txt");
    int n, m;
    cin >> n;
    cin >> m;
    if (m == n - 1)
    {
        cout << 0;
        return 0;
    }
    int **value;
    value = new int *[n];
    for (int i = 0; i < n; i++)
    {
        value[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            value[i][j] = 0;
        }
    }

    int **vars;
    vars = new int *[n];
    for (int i = 0; i < n; i++)
    {
        vars[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            vars[i][j] = 0;
        }
    }
    int *st = new int[n];
    int t = 0;
    while (t < n)
    {
        cin >> st[t];
        t++;
    }

    // Исправленный вариант заполнения массива
    ///////////////////////////
    for (int i = 0; i < n; i++)
    {
        value[i][i] = 0;
        for (int j = i + 1; j < n; j++)
        {
            value[j][i] = value[j - 1][i];
            for (int k = i; k < j; k++)
                value[j][i] += st[j] * st[k];
        }
    }
    //////////////////////////

    if (m == 0)
    {
        cout << value[n - 1][0];
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        vars[i][i] = 0;
        vars[i][0] = value[i][0];
    }
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            vars[j][i] = INT32_MAX;
            for (int k = 0; k < j; k++)
            {
                int best = vars[k][i - 1];
                int way = value[j][k + 1];
                vars[j][i] = min(best + way, vars[j][i]);
                ans = vars[j][i];
            }
        }
    }
    cout << ans;
    return 0;
}