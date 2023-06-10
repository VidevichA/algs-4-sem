#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

std::ifstream fin;
std::ofstream fout;
long long minPayForLoan = 0;
long long k = 1;
std::stack<long long> stack;
std::vector<long long> nodesToStartBuildingTreeWith;

class Node
{
    long long number;
    long long size;
    long long minNodeInOrder;
    std::queue<long long> order;
};

void FillInAdjacencyListWithPriorities(std::vector<std::priority_queue<std::pair<long long, std::pair<long long, long long>>>> &adjacencyListWithPriorities,
                                       std::vector<std::vector<long long>> &adjacencyList, std::vector<long long> &sizes,
                                       std::vector<long long> &minNodesInSubtrees)
{
    for (long long i = 1; i < adjacencyList.size(); i++)
    {
        for (long long j : adjacencyList[i])
        {
            adjacencyListWithPriorities[i].push(std::make_pair(sizes[j], std::make_pair(-minNodesInSubtrees[j], -j)));
        }
    }
}

void FillInAdjacencyListWithSizePriorities(std::vector<std::priority_queue<std::pair<long long, long long>>> &adjacencyListWithSizePriorities,
                                           std::vector<std::vector<long long>> &adjacencyList, std::vector<long long> &sizes)
{
    for (long long i = 1; i < adjacencyList.size(); i++)
    {
        for (long long j : adjacencyList[i])
        {
            adjacencyListWithSizePriorities[i].push(std::make_pair(sizes[j], -j));
        }
    }
}

void DFSForSizes(long long start, std::vector<std::vector<long long>> &adjacencyList,
                 std::vector<bool> &visited, std::vector<long long> &sizes)
{
    visited[start] = true;
    if (adjacencyList[start].empty())
    {
        sizes[start] = 1;
        return;
    }
    for (long long v : adjacencyList[start])
    {
        if (!visited[v])
        {
            DFSForSizes(v, adjacencyList, visited, sizes);
            sizes[start] += sizes[v];
        }
    }
    sizes[start]++;
}

void DFSForMinNodesInSubtrees(long long start, std::vector<std::priority_queue<std::pair<long long, long long>>> &adjacencyListWithSizePriorities,
                              std::vector<bool> &visited, std::vector<long long> &sizes,
                              std::vector<long long> &minNodesInSubtrees)
{
    visited[start] = true;
    if (adjacencyListWithSizePriorities[start].empty())
    {
        minNodesInSubtrees[start] = start;
        return;
    }
    long long min = LONG_LONG_MAX;
    long long size = LONG_LONG_MIN;
    while (!adjacencyListWithSizePriorities[start].empty())
    {
        auto v = adjacencyListWithSizePriorities[start].top();
        adjacencyListWithSizePriorities[start].pop();
        if (!visited[-v.second])
        {
            DFSForMinNodesInSubtrees(-v.second, adjacencyListWithSizePriorities, visited, sizes, minNodesInSubtrees);
            if (min > minNodesInSubtrees[-v.second] && size <= sizes[-v.second])
            {
                min = minNodesInSubtrees[-v.second];
                size = sizes[-v.second];
            }
        }
    }
    minNodesInSubtrees[start] = min;
}

void DFSWithPriorities(long long start, std::vector<std::priority_queue<std::pair<long long, std::pair<long long, long long>>>> &adjacencyListWithPriorities,
                       std::vector<bool> &visited, std::vector<long long> &sizes, std::vector<long long> &numbers,
                       std::vector<std::vector<long long>> &adjacencyList)
{
    visited[start] = true;
    while (!adjacencyListWithPriorities[start].empty())
    {
        auto v = adjacencyListWithPriorities[start].top();
        adjacencyListWithPriorities[start].pop();
        if (!visited[-v.second.second])
        {
            DFSWithPriorities(-v.second.second, adjacencyListWithPriorities, visited, sizes, numbers, adjacencyList);
        }
    }
    if (adjacencyList[start].empty())
    {
        if (!stack.empty())
        {
            minPayForLoan += stack.size();
        }
        stack.push(start);
    }
    else
    {
        minPayForLoan += stack.size();
        for (long long i = 0; i < adjacencyList[start].size(); i++)
        {
            stack.pop();
        }
        stack.push(start);
    }
    numbers[k] = start;
    k++;
}

int main()
{
    fin.open("input.txt");
    long long N;
    fin >> N;
    long long numberOfNodeToAssembler;
    fin >> numberOfNodeToAssembler;
    std::vector<std::vector<long long>> adjacencyList(N + 1, std::vector<long long>());
    char c;
    long long value;

    for (int i = 1; i <= N; i++)
    {
        long long number, amount;
        fin >> number >> c >> amount;
        if (amount != 0)
        {
            fin >> c;
            for (int j = 0; j < amount - 1; j++)
            {
                fin >> value >> c;
                adjacencyList[number].push_back(value);
            }
            fin >> value;
            adjacencyList[number].push_back(value);
        }
    }
    fin.close();
    fout.open("output.txt");

    std::vector<long long> sizes(N + 1, 0);
    sizes[0] = LONG_LONG_MIN;
    std::vector<bool> visited(N + 1, false);

    DFSForSizes(numberOfNodeToAssembler, adjacencyList, visited, sizes);
    for (auto &&i : visited)
    {
        i = false;
    }

    std::vector<std::priority_queue<std::pair<long long, long long>>> adjacencyListWithSizePriorities(N + 1, std::priority_queue<std::pair<long long, long long>>());
    FillInAdjacencyListWithSizePriorities(adjacencyListWithSizePriorities, adjacencyList, sizes);

    std::vector<long long> minNodesInSubtrees(N + 1, 0);
    minNodesInSubtrees[0] = LONG_LONG_MIN;

    DFSForMinNodesInSubtrees(numberOfNodeToAssembler, adjacencyListWithSizePriorities, visited, sizes, minNodesInSubtrees);
    for (auto &&i : visited)
    {
        i = false;
    }

    std::vector<std::priority_queue<std::pair<long long, std::pair<long long, long long>>>> adjacencyListWithPriorities(N + 1, std::priority_queue<std::pair<long long, std::pair<long long, long long>>>());
    FillInAdjacencyListWithPriorities(adjacencyListWithPriorities, adjacencyList, sizes, minNodesInSubtrees);

    std::vector<long long> numbers(N + 1, 0);
    numbers[0] = LONG_LONG_MIN;
    std::vector<long long> assembled;
    DFSWithPriorities(numberOfNodeToAssembler, adjacencyListWithPriorities, visited, sizes, numbers, adjacencyList);

    for (long long i = 1; i < numbers.size(); i++)
    {
        if (visited[numbers[i]])
        {
            assembled.push_back(numbers[i]);
        }
    }
    fout << minPayForLoan << '\n';
    for (long long i = 0; i < assembled.size() - 1; i++)
    {
        fout << assembled[i] << " ";
    }
    fout << assembled[assembled.size() - 1];

    fout.close();
    return 0;
}