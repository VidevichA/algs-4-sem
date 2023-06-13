#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::ifstream fin("in.txt");
std::ofstream out("out.txt");

std::vector<std::vector<int>> a;
std::vector<std::vector<bool>> visited;
std::vector<std::vector<int>> way;

struct Point
{
    int x;
    int y;
    Point(int x_, int y_)
    {
        this->x = x_;
        this->y = y_;
    }
};

void bfs(Point start)
{
    visited[start.x][start.y] = true;
    std::queue<Point> queue;
    way[start.x][start.y] = a[start.x][start.y];
    queue.push(start);
    while (!queue.empty())
    {
        Point curr = queue.front();
        queue.pop();
        int x = curr.x;
        int y = curr.y;

        if (x > 0)
        {
            if (a[x - 1][y] < a[x][y] && !visited[x - 1][y])
            {
                queue.push(Point(x - 1, y));
                way[x - 1][y] = a[x - 1][y];
                visited[x - 1][y] = true;
            }
        }

        if (x + 1 < a.size())
        {
            if (a[x + 1][y] < a[x][y] && !visited[x + 1][y])
            {
                queue.push(Point(x + 1, y));
                way[x + 1][y] = a[x + 1][y];
                visited[x + 1][y] = true;
            }
        }

        if (y + 1 < a.size())
        {
            if (a[x][y + 1] < a[x][y] && !visited[x][y + 1])
            {
                queue.push(Point(x, y + 1));
                way[x][y + 1] = a[x][y + 1];
                visited[x][y + 1] = true;
            }
        }

        if (y > 0)
        {
            if (a[x][y - 1] < a[x][y] && !visited[x][y - 1])
            {
                queue.push(Point(x, y - 1));
                way[x][y - 1] = a[x][y - 1];
                visited[x][y - 1] = true;
            }
        }
    }
}

int main()
{
    int n, x1, y1, x2, y2;
    fin >> n;
    a = std::vector<std::vector<int>>(n, std::vector<int>(n));
    way = std::vector<std::vector<int>>(n, std::vector<int>(n));
    visited = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));

    fin >> x1 >> y1 >> x2 >> y2;
    x1--;
    y1--;
    x2--;
    y2--;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fin >> a[i][j];
        }
    }

    bfs(Point(x1, y1));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n - 2; j++)
        {
            out << way[i][j] << " ";
        }
        out << way[i][n - 1];
        out << "\n";
    }
    return 0;
}