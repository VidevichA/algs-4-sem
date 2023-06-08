#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
using namespace std;
long long p = 3;

vector<vector<long long>> grass;
vector<long long> numbers;
long long n;

long long max(long long a, long long b)
{
    return a > b ? a : b;
}

long long mod(long long x)
{
    long long y = x % p;
    if (y < 0)
    {
        return y + p;
    }
    else
    {
        return y;
    }
}

void jump()
{
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < 3; j++)
        {
            if (grass[i][j] != LLONG_MIN)
            {
                if (i + 2 < n)
                {
                    long long tmp = grass[i][j] + numbers[i + 2];
                    grass[i + 2][mod(tmp)] = max(tmp, grass[i + 2][mod(tmp)]);
                }
                if (i + 5 < n)
                {
                    long long tmp = grass[i][j] + numbers[i + 5];
                    grass[i + 5][mod(tmp)] = max(tmp, grass[i + 5][mod(tmp)]);
                }
            }
        }
    }
}

int main()
{

    cin >> n;
    numbers = vector<long long>(n);

    for (long long i = 0; i < n; i++)
    {
        cin >> numbers[i];
    }

    for (long long i = 0; i < n; i++)
    {
        grass.push_back(vector<long long>(3, LLONG_MIN));
    }

    long long tmp = mod(numbers[0]);
    grass[0][tmp] = numbers[0];

    jump();

    if (grass[n - 1][0] == LLONG_MIN)
    {
        cout << -2023;
    }
    else
    {
        cout << grass[n - 1][0];
    }
}