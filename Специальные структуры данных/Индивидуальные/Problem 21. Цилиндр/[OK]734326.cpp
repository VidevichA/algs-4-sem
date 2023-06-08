#include <queue>
#include <fstream>

const int MAXN = 1005;
int n, m;
int a[MAXN][MAXN];
bool used[MAXN][MAXN];

bool is_adjacent(int x1, int y1, int x2, int y2)
{
    if (x1 == x2 && abs(y1 - y2) == 1)
        return true;
    if (y1 == y2 && (x1 + 1) % n == x2)
        return true;
    if (y1 == y2 && (x2 + 1) % n == x1)
        return true;
    return false;
}

void bfs(int x, int y)
{
    std::queue<std::pair<int, int>> q;
    q.emplace(x, y);
    used[x][y] = true;
    while (!q.empty())
    {
        int x1 = q.front().first, y1 = q.front().second;
        q.pop();
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx == 0 && dy == 0)
                    continue;
                int x2 = (x1 + dx + n) % n, y2 = (y1 + dy + m) % m;
                if (a[x1][y1] == 0 && a[x2][y2] == 0 && is_adjacent(x1, y1, x2, y2) && !used[x2][y2])
                {
                    q.emplace(x2, y2);
                    used[x2][y2] = true;
                }
            }
        }
    }
}

int count_pieces()
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] == 0 && !used[i][j])
            {
                bfs(i, j);
                cnt++;
            }
        }
    }
    return cnt;
}

int main()
{
    std::ifstream fin("common/kr2/task2/in.txt");
    std::ofstream ofStream("common/kr2/task2/out.txt");
    fin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fin >> a[i][j];
        }
    }
    ofStream << count_pieces();
    return 0;
}