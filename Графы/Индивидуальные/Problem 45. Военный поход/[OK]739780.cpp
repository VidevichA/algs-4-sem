#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <queue>

std::ifstream fin("campaign.in");
std::ofstream out("campaign.out");

struct Road
{
    int num;
    int start_town;
    int destination_town;
    int owner;
    long long price;

    Road(int n, int s, int d, int own, long long price)
    {
        this->num = n;
        this->start_town = s;
        this->destination_town = d;
        this->owner = own;
        this->price = price;
    }
};

int main()
{
    int n, m, a, b, owner, cost;
    long long sum = 0;
    fin >> n >> m;
    std::vector<std::vector<Road>> g(n);
    std::vector<int> towns_cost(n);
    std::vector<long long> dist(n, LONG_LONG_MAX);
    std::vector<bool> visited(n, false);
    std::vector<int> pred(n);
    std::set<int> to_buy;
    std::set<int> my_roads;

    for (int i = 0; i < n; ++i)
    {
        fin >> towns_cost[i];
    }
    for (int i = 0; i < m; ++i)
    {
        fin >> a >> b >> owner >> cost;
        a--;
        b--;
        owner--;
        if (owner == 0)
        {
            my_roads.insert(i + 1);
            sum += cost;
        }
        g[a].push_back(Road(i + 1, a, b, owner, cost));
        g[b].push_back(Road(i + 1, b, a, owner, cost));
    }

    dist[0] = 0;
    for (int i = 0; i < n; ++i)
    {
        int v = INT32_MIN;
        for (int j = 0; j < n; ++j)
        {
            if (!visited[j] && (v == INT32_MIN || dist[j] < dist[v]))
            {
                v = j;
            }
        }

        if (dist[v] == LONG_LONG_MAX)
        {
            visited[v] = true;
            continue;
        }

        visited[v] = true;
        for (Road road : g[v])
        {
            int destination = road.destination_town;
            long long d = dist[v] + road.price + towns_cost[road.destination_town];
            if (d < dist[destination])
            {
                dist[destination] = d;
                pred[destination] = v;
            }
        }
    }
    // std::cout << dist[n - 1] << "\n";
    if (dist[n - 1] > sum)
    {
        out << -1;
        return 0;
    }

    std::vector<int> path;
    for (int v = n - 1; v > 0; v = pred[v])
    {
        path.push_back(v);
    }
    path.push_back(0);

    for (int i = path.size() - 1; i >= 0; i--)
    {
        for (Road road : g[path[i]])
        {
            if (road.destination_town == path[i - 1])
            {
                if (road.owner != 0)
                {
                    to_buy.insert(road.num);
                }
                else
                {
                    my_roads.erase(road.num);
                }
            }
        }
    }

    out << my_roads.size() << " ";
    for (int t : my_roads)
    {
        out << t << " ";
    }
    out << "\n"
        << to_buy.size() << " ";
    for (int t : to_buy)
    {
        out << t << " ";
    }
    out << "\n";

    for (int i = path.size() - 1; i >= 0; i--)
    {
        out << path[i] + 1 << " ";
    }

    return 0;
}