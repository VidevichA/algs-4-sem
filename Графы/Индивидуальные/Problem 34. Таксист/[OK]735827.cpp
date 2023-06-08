#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<long long> dist0N;
vector<long long> distN0;

long long n;

vector<vector<pair<long long, long long>>> graph;
vector<vector<pair<long long, long long>>> graphN;

vector<bool> processed1;
vector<bool> processed2;

class Comparator
{
public:
    bool operator()(pair<long long, long long> &p1, pair<long long, long long> &p2)
    {
        bool c = p1.second > p2.second;
        return c;
    }
};

void deikstra0N()
{
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, Comparator> q;

    q.push({1, 0});

    while (!q.empty())
    {

        long long k = q.top().first;
        long long u = q.top().second;
        q.pop();

        if (processed1[k])
        {
            continue;
        }
        processed1[k] = true;
        dist0N[k] = u;

        for (long long i = 0; i < graph[k].size(); i++)
        {
            long long v = graph[k][i].first;
            long long c = graph[k][i].second;

            if (!processed1[v] && dist0N[v] > c + u)
            {
                q.push({v, c + u});
            }
        }
    }
}

void deikstraN0()
{
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, Comparator> q;

    q.push({n, 0});

    while (!q.empty())
    {

        long long k = q.top().first;
        long long u = q.top().second;
        q.pop();

        if (processed2[k])
        {
            continue;
        }
        processed2[k] = true;
        distN0[k] = u;

        for (long long i = 0; i < graphN[k].size(); i++)
        {
            long long v = graphN[k][i].first;
            long long c = graphN[k][i].second;

            if (!processed2[v] && distN0[v] > c + u)
            {
                q.push({v, c + u});
            }
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    long long k;
    long long m;

    in >> n;
    in >> m;
    in >> k;

    graph = vector<vector<pair<long long, long long>>>(n + 1);
    graphN = vector<vector<pair<long long, long long>>>(n + 1);
    vector<pair<pair<long, long>, long long>> graphU = vector<pair<pair<long, long>, long long>>(m);
    dist0N = vector<long long>(n + 1, LLONG_MAX);
    distN0 = vector<long long>(n + 1, LLONG_MAX);
    processed1 = vector<bool>(n + 1, false);
    processed2 = vector<bool>(n + 1, false);
    vector<long long> rez;

    for (long long i = 0; i < m; i++)
    {

        long long u;
        long long v;
        long long w;

        in >> u;
        in >> v;
        in >> w;

        graph[u].push_back({v, w});
        graphN[v].push_back({u, w});
        graphU[i] = {{u, v}, w};
    }

    deikstra0N();
    deikstraN0();

    /*for (auto& item : dist0N) {
        cout << item << " ";
    }

    cout << endl;
    for (auto& item : distN0) {
        cout << item << " ";
    }

    cout << endl;*/

    for (long long i = 0; i < graphU.size(); i++)
    {
        long long a = graphU[i].first.first;
        long long b = graphU[i].first.second;
        long long l = graphU[i].second;

        if (dist0N[a] + distN0[b] + l <= dist0N[n] + k && dist0N[a] != LLONG_MAX && distN0[b] != LLONG_MAX)
        {
            rez.push_back(i + 1);
        }
    }

    out << rez.size() << endl;

    sort(rez.begin(), rez.end());

    for (auto &item : rez)
    {
        out << item << endl;
    }

    return 0;
}