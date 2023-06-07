#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
struct way
{
    long long u;
    long long v;
    long long p;
};

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    long long n, m, u, v, p, k;
    cin >> n >> m >> k;
    vector<way> ways;
    vector<vector<pair<long long, long long>>> gr(n);
    vector<vector<pair<long long, long long>>> grR(n);
    vector<bool> visited(n, false);
    vector<bool> visitedR(n, false);
    vector<long long> price(n, INT64_MAX);
    vector<long long> priceR(n, INT64_MAX);
    vector<long long> par(n, 0), parR(n, 0);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> p;
        way w{u - 1, v - 1, p};
        ways.push_back(w);
        gr[u - 1].emplace_back(v - 1, p);
        grR[v - 1].emplace_back(u - 1, p);
    }
    par[0] = -1;
    parR[n - 1] = -1;
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<>> queue1;
    queue1.emplace(0, 0);
    while (!queue1.empty())
    {
        pair<long long, long long> pair1 = queue1.top();
        queue1.pop();
        if (!visited[pair1.second])
            visited[pair1.second] = true;
        else
            continue;
        price[pair1.second] = pair1.first;
        for (auto &i : gr[pair1.second])
        {
            if (!visited[i.first] && i.second + pair1.first < price[i.first])
            {
                par[i.first] = pair1.second;
                queue1.emplace(i.second + pair1.first, i.first);
            }
        }
    }
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<>> queue1R;
    queue1R.emplace(0, n - 1);
    while (!queue1R.empty())
    {
        pair<long long, long long> pair1 = queue1R.top();
        queue1R.pop();
        if (!visitedR[pair1.second])
            visitedR[pair1.second] = true;
        else
            continue;
        priceR[pair1.second] = pair1.first;
        for (auto &i : grR[pair1.second])
        {
            if (!visitedR[i.first] && i.second + pair1.first < priceR[i.first])
            {
                parR[i.first] = pair1.second;
                queue1R.emplace(i.second + pair1.first, i.first);
            }
        }
    }
    int count = 0;
    vector<int> ans;
    for (int i = 0; i < m; i++)
    {
        if (price[ways[i].v] + priceR[ways[i].v] <= price[n - 1] + k &&
            price[ways[i].u] + priceR[ways[i].u] <= price[n - 1] + k &&
            price[ways[i].u] + ways[i].p + priceR[ways[i].v] <= price[n - 1] + k && price[ways[i].u] != INT64_MAX &&
            priceR[ways[i].u] != INT64_MAX)
        {
            count++;
            ans.push_back(i + 1);
        }
    }
    cout << count << "\n";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << "\n";
    }
    return 0;
}