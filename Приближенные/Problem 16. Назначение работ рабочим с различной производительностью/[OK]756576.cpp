#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

long long n, m, p[4000], c = 1;
double ans;
vector<pair<pair<long long, long long>, long long>> workers;
vector<pair<long long, long long>> job;

bool cmp1(pair<long long, long long> l, pair<long long, long long> r)
{
    return l.first > r.first;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> n;
    for (long long i = 1; i <= n; i++)
    {
        long long x;
        cin >> x;
        job.emplace_back(x, i);
    }

    cin >> m;
    for (long long i = 1; i <= m; i++)
    {
        long long x;
        cin >> x;
        workers.emplace_back(make_pair(x, i), 0);
    }

    sort(job.begin(), job.end(), cmp1);
    for (const auto &j : job)
    {
        c = j.first;
        long long best = 0;
        for (long long i = 0; i < m; i++)
        {
            if (((c + workers[best].second) * workers[i].first.first == (c + workers[i].second) * workers[best].first.first && workers[best].first.first > workers[i].first.first) || (c + workers[best].second) * workers[i].first.first > (c + workers[i].second) * workers[best].first.first)
            {
                best = i;
            }
        }
        p[j.second] = workers[best].first.second;
        workers[best].second += j.first;
        //        ans = max(ans, ((double) w.second / w.first.first));
    }

    for (const auto &w : workers)
    {
        ans = max(ans, ((double)w.second / w.first.first));
    }

    cout << fixed << setprecision(5) << ans << "\n";
    for (long long i = 1; i <= n; i++)
    {
        cout << p[i] << " ";
    }
}