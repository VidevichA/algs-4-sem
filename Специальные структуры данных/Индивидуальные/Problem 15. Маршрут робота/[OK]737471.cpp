#include <fstream>
#include <queue>
#include <cmath>

struct Node
{
    int x;
    int y;
    int value;
    long long dist;
    bool processed;
};

class myComparator
{
public:
    int operator()(const Node &p1, const Node &p2)
    {
        return p1.dist > p2.dist;
    }
};

std::priority_queue<Node, std::vector<Node>, myComparator> queue;
std::vector<std::vector<Node>> matrix;
int n, m, k;

void distance(int i, int j)
{
    Node start = matrix[i][j];
    queue.push(start);
    while (!queue.empty())
    {
        Node current = queue.top();
        queue.pop();
        if (current.processed)
            continue;
        matrix[current.x][current.y].processed = true;
        if (current.x > 1 && !matrix[current.x - 1][current.y].processed)
        {
            Node node = matrix[current.x - 1][current.y];
            long long way = std::abs(current.value - node.value) + matrix[current.x][current.y].dist + k;
            if (way < matrix[node.x][node.y].dist)
            {
                matrix[node.x][node.y].dist = node.dist = way;
                queue.push(node);
            }
        }
        if (current.x < n && !matrix[current.x + 1][current.y].processed)
        {
            Node node = matrix[current.x + 1][current.y];
            long long way = std::abs(current.value - node.value) + matrix[current.x][current.y].dist + k;
            if (way < matrix[node.x][node.y].dist)
            {
                matrix[node.x][node.y].dist = node.dist = way;
                queue.push(node);
            }
        }
        if (current.y > 1 && !matrix[current.x][current.y - 1].processed)
        {
            Node node = matrix[current.x][current.y - 1];
            long long way = std::abs(current.value - node.value) + matrix[current.x][current.y].dist + k;
            if (way < matrix[node.x][node.y].dist)
            {
                matrix[node.x][node.y].dist = node.dist = way;
                queue.push(node);
            }
        }
        if (current.y < m && !matrix[current.x][current.y + 1].processed)
        {
            Node node = matrix[current.x][current.y + 1];
            long long way = std::abs(current.value - node.value) + matrix[current.x][current.y].dist + k;
            if (way < matrix[node.x][node.y].dist)
            {
                matrix[node.x][node.y].dist = node.dist = way;
                queue.push(node);
            }
        }
    }
}

int main()
{
    std::ifstream fin("in.txt");
    fin >> n >> m;
    matrix.resize(n + 1, std::vector<Node>(m + 1));

    int l;
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < m + 1; ++j)
        {
            fin >> l;
            matrix[i][j] = {i, j, l, LLONG_MAX, false};
        }
    }
    fin >> k;
    int startX, startY, endX, endY;
    fin >> startX >> startY;
    fin >> endX >> endY;
    matrix[startX][startY].dist = 0;
    distance(startX, startY);
    fin.close();

    std::ofstream fout("out.txt");
    fout << matrix[endX][endY].dist;
    fout.close();
    return 0;
}
