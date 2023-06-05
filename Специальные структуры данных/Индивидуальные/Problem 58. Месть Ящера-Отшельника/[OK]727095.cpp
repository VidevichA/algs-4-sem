#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long n;
    std::cin >> n;
    long long k;
    std::cin >> k;
    std::multiset<long long> stones;
    std::priority_queue<long long> channels;
    for (int i = 0; i < n; ++i)
    {
        long long temp;
        std::cin >> temp;
        stones.insert(temp);
    }
    for (int i = 0; i < n; ++i)
    {
        long long temp;
        std::cin >> temp;
        channels.push(temp);
    }
    std::cout << '\n';
    long long sum = 0;
    std::vector<std::pair<long long, long long>> s;

    while (!channels.empty())
    {
        auto it = stones.lower_bound(channels.top());
        if (it != stones.end())
        {
            s.push_back(std::make_pair(*it, channels.top()));
            stones.erase(it);
        }
        else
        {
            if (k > 0)
            {
                sum += channels.top();
                --k;
            }
            else
            {
                std::cout << -1;
                return 0;
            }
        }
        channels.pop();
    }
    std::sort(s.begin(), s.end(), [](std::pair<long long, long long> a, std::pair<long long, long long> b)
              { return a.first - a.second > b.first - b.second; });
    for (int i = 0; i < s.size(); ++i)
    {
        if (i < k)
        {
            sum += s[i].second;
        }
        else
        {
            sum += s[i].first;
        }
    }
    std::cout << sum;
    return 0;
}