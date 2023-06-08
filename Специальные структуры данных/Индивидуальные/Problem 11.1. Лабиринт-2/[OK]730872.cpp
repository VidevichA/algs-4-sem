#include <fstream>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <ctime>
std::ofstream out("output.txt");

int n;
int m;

void print(std::vector<std::vector<int>> maze)
{
    out << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < m + 1; j++)
        {
            out << maze[i][j] << " ";
        }
        out << '\n';
    }
}

int main()

{

    FILE *in;
    fopen_s(&in, "input.txt", "r");

    int k;
    fscanf_s(in, "%d", &n);
    fscanf_s(in, "%d", &m);
    fscanf_s(in, "%d", &k);
    std::vector<int> enter(k);
    std::vector<int> exit(k);
    std::vector<std::vector<int>> maze(n + 1, std::vector<int>(m + 2));
    std::vector<int> ex_win(m + 2, 0);

    int count = 0;

    for (int i = 0; i < k; i++)
    {
        fscanf_s(in, "%d", &enter[i]);
    }
    for (int i = 0; i < k; i++)
    {
        fscanf_s(in, "%d", &exit[i]);
    }

    for (int i = 0; i < m + 1; i++)
    {
        maze[n][i] = 1;
    }
    for (int i = 0; i < n + 1; i++)
    {
        maze[i][0] = 1;
        maze[i][m + 1] = 1;
    }
    bool can = true;
    for (int i = 0; i < n; i++)
    {
        bool hasO = false;
        for (int j = 1; j < m + 1; j++)
        {
            fscanf_s(in, "%d", &maze[i][j]);
            if (maze[i][j] == 0)
            {
                hasO = true;
            }
        }
        if (hasO == false)
        {
            can = false;
        }
    }
    if (can)
    {

        for (int &item : exit)
        {
            maze[n - 1][item] = -1;
        }

        int winner = 2;

        int player = 1;

        std::vector<int> strategy(4);
        int l;
        for (int &item : enter)
        {
            ++player;
            std::stack<std::pair<char, std::pair<int, int>>> way;
            std::stack<std::pair<char, std::pair<int, int>>> wrongWay;
            bool win = false;
            int j = item;
            int i = 0;
            if (maze[i][j] == -1)
            {
                win = true;
                ex_win[j] = player;
                break;
            }
            else if (maze[i][j] >= 1)
            {
                break;
            }

            maze[i][j] = player;
            way.push({'t', {0, item}});
            while (maze[i][j] != -1)
            {
                if (way.top().first == 't')
                {
                    l = 3;
                }
                else if (way.top().first == 'r')
                {
                    l = 2;
                }
                else if (way.top().first == 'l')
                {
                    l = 0;
                }
                else if (way.top().first == 'b')
                {
                    l = 1;
                }
                strategy[0] = maze[i + 1][j];
                strategy[1] = maze[i][j + 1];
                if (i - 1 >= 0)
                {
                    strategy[2] = maze[i - 1][j];
                }
                else
                {
                    strategy[2] = 111;
                }
                strategy[3] = maze[i][j - 1];

                int abc = 0;

                while (strategy[l] > 0 && abc < 3)
                {
                    ++l;
                    if (l == 4)
                    {
                        l = 0;
                    }
                    ++abc;
                }

                if (abc == 3)
                {
                    if (way.size() == 1)
                    {
                        break;
                    }

                    wrongWay.push(way.top());
                    way.pop();
                    i = way.top().second.first;
                    j = way.top().second.second;
                }

                if (strategy[l] < 1)
                {
                    switch (l)
                    {
                    case 0:

                        ++i;
                        if (maze[i][j] == -1)
                        {
                            break;
                        }
                        maze[i][j] = player;
                        way.push({'t', {i, j}});
                        break;
                    case 1:

                        ++j;
                        if (maze[i][j] == -1)
                        {
                            break;
                        }
                        maze[i][j] = player;
                        way.push({'l', {i, j}});
                        break;
                    case 2:
                        --i;
                        if (maze[i][j] == -1)
                        {
                            break;
                        }

                        maze[i][j] = player;
                        way.push({'b', {i, j}});
                        break;
                    case 3:

                        --j;
                        if (maze[i][j] == -1)
                        {
                            break;
                        }
                        maze[i][j] = player;
                        way.push({'r', {i, j}});
                        break;
                    default:
                        break;
                    }
                }

                if (maze[i][j] == -1)
                {
                    win = true;
                }
            }
            if (win)
            {
                ex_win[j] = player;
                ++count;
            }
            while (!wrongWay.empty())
            {
                maze[wrongWay.top().second.first][wrongWay.top().second.second] = 0;
                wrongWay.pop();
            }
            while (!win && !way.empty())
            {
                std::pair<int, int> tmp = way.top().second;
                maze[tmp.first][tmp.second] = 0;
                way.pop();
            }
        }

        for (int i = 1; i < m + 1; i++)
        {
            if (maze[n - 1][i] == -1)
            {
                maze[n - 1][i] = ex_win[i];
            }
        }
    }
    out << count;
    print(maze);
    return 0;
}