#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>

int n, m;
const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

int main()
{
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    in >> n >> m;
    std::vector<std::vector<int>> board(n + 4, std::vector<int>(m + 4));
    for (int i = 0; i < m + 4; i++)
    {
        board[0][i] = -1;
        board[n + 2][i] = -1;
        board[1][i] = -1;
        board[n + 3][i] = -1;
    }
    for (int i = 0; i < n + 4; i++)
    {
        board[i][0] = -1;
        board[i][m + 2] = -1;
        board[i][1] = -1;
        board[i][m + 3] = -1;
    }
    for (int i = 2; i <= n + 1; i++)
    {
        for (int j = 2; j <= m + 1; j++)
        {
            in >> board[i][j];
        }
    }
    int x1, y1, x2, y2;

    in >> x1 >> y1 >> x2 >> y2;
    x1++, y1++, x2++, y2++;
    std::vector<std::vector<int>> dist(n + 4, std::vector<int>(m + 4, -1));
    dist[x1][y1] = 0;

    // std::queue<std::tuple<int, int, int>> q;
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> q;
    q.push({x1, y1, 0});

    while (!q.empty())
    {
        int x, y, d;
        std::tie(x, y, d) = q.top();
        q.pop();

        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (board[nx][ny] != -1)
            {
                int nd = board[nx][ny] == 1 ? 2 : 1;

                if (dist[nx][ny] == -1 || dist[nx][ny] > d + nd)
                {
                    dist[nx][ny] = d + nd;
                    q.push({nx, ny, d + nd});
                }
            }
        }
    }
    if (dist[x2][y2] == -1)
    {
        out << "No";
    }
    else
    {
        out << dist[x2][y2];
    }
    return 0;
}