#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

typedef long long number;

template <typename T>
void PrintVector(const std::vector<T> &v)
{
    std::cout << '\n';
    for (auto el : v)
    {
        std::cout << el << ' ';
    }
    std::cout << '\n';
}

class Edge
{
public:
    Edge()
    {
    }
    Edge(const number from, const number fTime, const number to, const number tTime, number index) : from(from), fTime(fTime), to(to), tTime(tTime), index(index)
    {
    }
    [[nodiscard]] number getFrom() const
    {
        return this->from;
    }
    [[nodiscard]] number getFTime() const
    {
        return this->fTime;
    }
    [[nodiscard]] number getTo() const
    {
        return this->to;
    }
    [[nodiscard]] number getTTime() const
    {
        return this->tTime;
    }
    [[nodiscard]] number getIndex() const
    {
        return this->index;
    }

public:
    number from;
    number fTime;
    number to;
    number tTime;
    number index;
};

int main()
{
    std::ifstream in("time.in");
    std::ofstream out("time.out");
    number n;
    in >> n;
    number from, to;
    in >> from >> to;
    number k;
    in >> k;
    std::vector<Edge> data(k + 1);
    auto cmp = [](const Edge &a, const Edge &b)
    {
        return a.getFTime() > b.getFTime();
    };
    std::vector<std::multiset<Edge, decltype(cmp)>> data1(n + 1, std::multiset<Edge, decltype(cmp)>(cmp));
    std::vector<bool> visited(k + 1);
    data[0] = Edge(0, 0, from, 0, 0);
    for (number i = 1; i <= k; ++i)
    {
        number k1, k2, k3, k4;
        in >> k1 >> k2 >> k3 >> k4;
        Edge edge(k1, k2, k3, k4, i);
        data[i] = edge;
        data1[k1].insert(edge);
    }
    auto q = std::queue<Edge>();
    visited[0] = true;
    q.push(data[0]);
    number result = from == to ? 0 : LONG_LONG_MAX;
    while (!q.empty())
    {
        Edge v = q.front();
        q.pop();
        number count = 0;
        for (auto edge : data1[v.to])
        {
            if (edge.fTime < v.tTime)
            {
                break;
            }
            ++count;
            if (!visited[edge.index])
            {
                visited[edge.index] = true;
                q.push(edge);
                if (edge.to == to && edge.tTime < result)
                {
                    result = edge.tTime;
                }
            }
        }
        for (number i = 0; i < count; ++i)
        {
            data1[v.to].erase(data1[v.to].begin());
        }
    }
    out << result;
    return 0;
}