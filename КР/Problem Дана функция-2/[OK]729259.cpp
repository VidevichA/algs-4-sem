#include <iostream>
#include <vector>

using namespace std;
vector<long long> F;

long long p = 1000000007;
long long a;

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

long long f(long long n, vector<int> &b)
{
    if (n < 0)
    {
        return 1;
    }
    else if (n == 0)
    {
        return F[0];
    }
    else if (n % 2 == 1 && n >= 1)
    {
        if (F[n] == -1)
        {
            F[n] = mod((f(n - 1, b)) + 1 - n);
        }
        return F[n];
    }
    else if (n % 2 == 0 && n >= 2)
    {
        if (F[n] == -1)
        {
            long long sum = 0;
            for (long long i = 0; i < b.size(); i++)
            {
                sum += mod(b[i] * f((n / 2) - i, b));
            }
            F[n] = mod(sum);
        }
        return F[n];
    }
}

int main()
{
    long long n;
    long long k;
    cin >> n;
    cin >> k;
    cin >> a;
    F = vector<long long>(n + 1, -1);
    F[0] = mod(a);
    vector<int> b(k);
    for (long long i = 0; i < k; i++)
    {
        cin >> b[i];
    }

    cout << mod(f(n, b));
}