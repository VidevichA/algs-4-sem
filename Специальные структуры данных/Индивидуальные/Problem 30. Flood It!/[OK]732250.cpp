#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <unordered_map>
// O(nm*(log(nm)+log(t)+coins))
int main()
{
    std::ifstream fin("individual/data_structure/flood_it/floodit.in");
    std::ofstream ofStream("individual/data_structure/flood_it/floodit.out");
    std::ios_base::sync_with_stdio(false);
    int n, m, k, t;
    fin >> n >> m >> k >> t;

    std::set<std::pair<int, std::pair<int, int>>> flood;
    std::vector<std::vector<int>> field(n, std::vector<int>(m));
    std::vector<std::vector<int>> dist(n, std::vector<int>(m));
    flood.insert({0, {0, 0}});
    dist[0][0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fin >> field[i][j];
            if (i == 0 && j == 0)
            {
                continue;
            }
            else
            {
                dist[i][j] = INT_MAX;
            }
        }
    }

    std::unordered_map<int, std::vector<int>> when;
    when[field[0][0]].push_back(0);
    int c;
    for (int i = 0; i < t; i++)
    {
        fin >> c;
        when[c].push_back(i + 1);
    }
    field[0][0] = -1;

    while (!flood.empty())
    {
        auto current = *flood.begin();
        flood.erase(current);
        int i = current.second.first;
        int j = current.second.second;
        int d = current.first;
        for (int di = -1; di <= 1; di++)
        {
            for (int dj = -1; dj <= 1; dj++)
            {
                if (di * dj == 0 && di != dj)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if ((ni < n && ni >= 0 && nj < m && nj >= 0) &&
                        when.count(field[ni][nj]) && when[field[ni][nj]].back() >= d)
                    {
                        int p = *std::lower_bound(when[field[ni][nj]].begin(),
                                                  when[field[ni][nj]].end(), d);
                        dist[ni][nj] = std::min(p, dist[ni][nj]);
                        flood.insert({dist[ni][nj], {ni, nj}});
                        field[ni][nj] = -1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ofStream << (field[i][j] == -1 ? c : field[i][j]) << " ";
        }
        ofStream << "\n";
    }
    return 0;
}