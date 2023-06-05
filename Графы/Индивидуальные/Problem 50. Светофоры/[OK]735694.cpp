#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

enum Color
{
    B,
    P
};

struct Node
{
    Color color_;
    int time_;
    int b_time_;
    int p_time_;

    int getTime(Color c) const
    {
        return c == B ? b_time_ : p_time_;
    }
};

Node makeNode(const Node &node, int time)
{
    Node newNode = {node.color_, 0, node.b_time_, node.p_time_};
    if (time < node.time_)
    {
        newNode.time_ = node.time_ - time;
    }
    else
    {
        int lcpTime = (time - node.time_) % (node.b_time_ + node.p_time_);
        Color change = node.color_ == B ? P : B;
        if (lcpTime < node.getTime(change))
        {
            newNode.color_ = change;
            newNode.time_ = node.getTime(change) - lcpTime;
        }
        else
        {
            newNode.time_ = node.getTime(node.color_) - lcpTime;
        }
    }
    return newNode;
}

int wait(const Node &u, const Node &v)
{
    if (u.color_ == v.color_)
    {
        return 0;
    }

    if (u.time_ != v.time_)
    {
        return std::min(u.time_, v.time_);
    }
    if (v.getTime(u.color_) != u.getTime(v.color_))
    {
        return u.time_ + std::min(v.getTime(u.color_), u.getTime(v.color_));
    }
    return -1;
}

int dijkstra(int n, int start, int end, const std::vector<Node> &nodes,
             const std::vector<std::vector<std::pair<int, int>>> &adj_list, std::vector<int> &prev)
{
    std::vector<bool> marked(n, false);
    std::vector<int> dist(n, INT32_MAX);
    dist[start] = 0;
    marked[start] = true;
    std::set<std::pair<int, int>> border;
    border.emplace(0, start);
    while (!border.empty())
    {
        auto current = *border.begin();
        int d = current.first;
        int v = current.second;
        marked[v] = true;
        border.erase(current);
        if (v == end)
        {
            return d;
        }
        if (d > dist[v])
        {
            continue;
        }
        for (auto &[u, l] : adj_list[v])
        {
            if (marked[u])
            {
                continue;
            }
            int time = wait(makeNode(nodes[u], d), makeNode(nodes[v], d));
            if (time == -1)
            {
                continue;
            }
            int temp = d + time + l;
            if (temp < dist[u])
            {
                border.erase({dist[u], u});
                dist[u] = temp;
                border.emplace(temp, u);
                prev[u] = v;
            }
        }
    }
    return -1;
}

int main()
{
    std::ifstream fin("individual/graphs/stoplights/lights.inp");
    std::ofstream ofStream("individual/graphs/stoplights/lights.out");
    int u, v;
    fin >> u >> v;
    int n, m;
    fin >> n >> m;
    std::vector<Node> nodes(n);
    char color;
    for (int i = 0; i < n; i++)
    {
        fin >> color;
        color == 'B' ? nodes[i].color_ = B : nodes[i].color_ = P;
        fin >> nodes[i].time_ >> nodes[i].b_time_ >> nodes[i].p_time_;
    }

    std::vector<std::vector<std::pair<int, int>>> adj_list(m);
    int in, to, length;
    for (int i = 0; i < m; i++)
    {
        fin >> in >> to >> length;
        adj_list[in - 1].emplace_back(to - 1, length);
        adj_list[to - 1].emplace_back(in - 1, length);
    }
    std::vector<int> prev(n, -1);
    int ans = dijkstra(n, u - 1, v - 1, nodes, adj_list, prev);
    if (ans == -1)
    {
        ofStream << 0;
    }
    else
    {
        ofStream << ans << "\n";
        std::vector<int> path;
        v--;
        while (v != -1)
        {
            path.push_back(v);
            v = prev[v];
        }
        std::reverse(path.begin(), path.end());
        for (auto item : path)
        {
            ofStream << item + 1 << " ";
        }
    }
    return 0;
}