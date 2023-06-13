#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <iterator>
#include <algorithm>

struct CompareFirst
{
    bool operator()(const std::pair<int, int> &left, const std::pair<int, int> &right) const
    {
        return left.first > right.first;
    }
};

int main()
{
    FILE *input = fopen("input.txt", "r");
    int n, m;
    fscanf(input, "%d %d", &n, &m);
    std::vector<int> t(n);
    for (int i = 0; i < n; i++)
    {
        fscanf(input, "%d", &t[i]);
    }
    fclose(input);

    std::sort(t.begin(), t.end(), [](int a1, int a2)
              { return a1 > a2; });
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, CompareFirst> queue;

    std::vector<int> end_time(m, 0);
    std::vector<int> assignments(n);

    for (int i = 0; i < m; ++i)
    {
        queue.push(std::make_pair(0, i));
    }
    for (int i = 0; i < n; i++)
    {
        std::pair<int, int> p = queue.top();
        queue.pop();
        int min_time = p.first;
        int min_index = p.second;
        min_time += t[i];
        queue.push(std::make_pair(min_time, min_index));
        end_time[min_index] += t[i];
        assignments[i] = min_index + 1;
    }
    int max_time = 0;
    for (int i = 0; i < end_time.size(); ++i)
    {
        if (end_time[i] > max_time)
        {
            max_time = end_time[i];
        }
    }

    std::ofstream out("output.txt");
    out << max_time << std::endl;
    std::copy(assignments.begin(), assignments.end(), std::ostream_iterator<int>(out, " "));
    return 0;
}