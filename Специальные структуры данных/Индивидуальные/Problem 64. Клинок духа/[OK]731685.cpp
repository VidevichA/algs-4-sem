#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int MOD = pow(10, 9) + 7;

long long fact[100000];

void initFact(int n)
{
    fact[0] = 0;
    long long ans = 1;
    for (int i = 1; i <= n; i++)
    {
        ans = ((ans % MOD) * (i % MOD)) % MOD;
        fact[i] = ans;
    }
}

void update(vector<long long> &tree, int i, int lb, int rb, int num)
{
    if (lb == num && rb == num)
    {
        tree[i] = 1;
        return;
    }

    if (num < lb || num > rb)
    {
        return;
    }

    int mid = (lb + rb) >> 1;
    update(tree, 2 * i, lb, mid, num);
    update(tree, 2 * i + 1, mid + 1, rb, num);

    tree[i] = tree[2 * i] + tree[2 * i + 1];
}

int count(vector<long long> &tree, int i, int l,
          int r, int lb, int rb)
{
    if (lb <= l and r <= rb)
    {
        return tree[i];
    }
    if (l > rb or r < lb)
    {
        return 0;
    }
    int mid = (l + r) >> 1;
    return count(tree, 2 * i, l,
                 mid, lb, rb) +
           count(tree, 2 * i + 1,
                 mid + 1, r, lb, rb);
}

int main()
{
    int n;
    cin >> n;
    auto *arr = new long long[n];
    for (int i = n - 1; i >= 0; i--)
    {
        long long temp;
        cin >> temp;
        arr[i] = n - temp;
    }
    initFact(n);
    vector<long long> tree(6 * n, 0);
    long long ans = 1;
    for (int i = 0; i < n; ++i)
    {
        long long temp = count(tree, 1, 1, n, arr[i] + 1, n);
        update(tree, 1, 1, n, arr[i]);
        ans = (ans % MOD + ((temp % MOD) * (fact[i] % MOD)) % MOD) % MOD;
    }
    cout << ans;
    return 0;
}
