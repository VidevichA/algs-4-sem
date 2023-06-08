#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>

using namespace std;

typedef pair<int, int> Pair;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

bool isValid(int x, int y, int rows, int cols)
{
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

long long dijkstra(int startX, int startY, int endX, int endY, int K, const vector<vector<int>> &heights)
{
    int rows = heights.size(), cols = heights[0].size();
    vector<vector<long long>> distance(rows, vector<long long>(cols, numeric_limits<long long>::max()));

    priority_queue<pair<long long, Pair>, vector<pair<long long, Pair>>, greater<pair<long long, Pair>>> pq;
    distance[startX][startY] = 0;
    pq.push({0, {startX, startY}});

    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();

        int x = current.second.first, y = current.second.second;

        if (x == endX && y == endY)
        {
            return distance[endX][endY];
        }

        for (int i = 0; i < 4; ++i)
        {
            int newX = x + dx[i], newY = y + dy[i];

            if (isValid(newX, newY, rows, cols))
            {
                long long cost = abs(heights[newX][newY] - heights[x][y]) + K;

                if (distance[x][y] + cost < distance[newX][newY])
                {
                    distance[newX][newY] = distance[x][y] + cost;
                    pq.push({distance[newX][newY], {newX, newY}});
                }
            }
        }
    }

    return -1;
}

int main()
{

    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    int n, m;
    in >> n >> m;

    vector<vector<int>> heights(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            in >> heights[i][j];
        }
    }

    int K;
    in >> K;

    int startX, startY, endX, endY;
    in >> startX >> startY >> endX >> endY;
    --startX, --startY, --endX, --endY;

    long long shortestPath = dijkstra(startX, startY, endX, endY, K, heights);

    out << shortestPath << endl;

    return 0;
}