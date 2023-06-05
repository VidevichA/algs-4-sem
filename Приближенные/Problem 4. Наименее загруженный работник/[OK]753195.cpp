#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n, m;
    in >> n >> m;
    std::vector<std::pair<long long, long long>> works(n);
    std::vector<long long> works2(n);
    for (long long i = 0; i < n; ++i)
    {
        long long temp;
        in >> temp;
        works[i] = {temp, i};
        works2[i] = temp;
    }
    std::sort(works.begin(), works.end(), [](const std::pair<long long, long long> &f, const std::pair<long long, long long> &s)
              { return f.first > s.first; });
    auto cmp = [](const std::pair<long long, std::vector<long long> *> &f,
                  const std::pair<long long, std::vector<long long> *> &s)
    {
        return f.first > s.first;
    };
    std::priority_queue<std::pair<long long, std::vector<long long> *>, std::vector<std::pair<long long, std::vector<long long> *>>, decltype(cmp)>
        q(cmp);
    std::vector<std::vector<long long>> vectors(m);
    for (long long i = 0; i < m; ++i)
    {
        std::vector<long long> v;
        vectors[i] = v;
        q.push({0, &vectors[i]});
    }
    for (long long i = 0; i < n; ++i)
    {
        auto el = q.top();
        q.pop();
        el.first += works[i].first;
        el.second->push_back(works[i].second);
        q.push(el);
    }

    out << q.top().first << '\n';

    long long current = m;
    while (!q.empty())
    {
        auto el = q.top();
        q.pop();
        for (long long i = 0; i < el.second->size(); ++i)
        {
            works2[el.second->at(i)] = current;
        }
        --current;
    }
    for (auto el : works2)
    {
        out << el << '\n';
    }
    return 0;
}