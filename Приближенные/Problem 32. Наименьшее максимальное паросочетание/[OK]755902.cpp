#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream fin;
std::ofstream fout;

int main()
{
    fin.open("input.txt");
    int n, m;
    fin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList(n + 1, std::vector<std::pair<int, int>>());
    std::vector<int> powers(n + 1, 0);
    powers[0] = INT_MIN;
    std::vector<int> maxMatch;
    std::vector<bool> used(n + 1, false);
    for (int i = 1; i <= m; i++)
    {
        int x(0), y(0);
        fin >> x >> y;
        powers[x]++;
        powers[y]++;
        adjacencyList[x].emplace_back(y, i);
        adjacencyList[y].emplace_back(x, i);
    }
    fin.close();
    fout.open("output.txt");
    for (int i = 1; i <= n; i++)
    {
        std::sort(adjacencyList[i].begin(), adjacencyList[i].end(),
                  [&powers](auto &f, auto &s)
                  {
                      return powers[f.first] < powers[s.first];
                  });
    }
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            for (int j = 0; j < adjacencyList[i].size(); j++)
            {
                if (!used[adjacencyList[i][j].first])
                {
                    used[i] = true;
                    used[adjacencyList[i][j].first] = true;
                    maxMatch.push_back(adjacencyList[i][j].second);
                    break;
                }
            }
        }
    }
    fout << maxMatch.size() << '\n';
    for (int i : maxMatch)
    {
        fout << i << '\n';
    }
    fout.close();
    return 0;
}