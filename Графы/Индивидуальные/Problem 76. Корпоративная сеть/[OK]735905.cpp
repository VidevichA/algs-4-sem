#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#pragma comment(linker, "/STACK:66777216")

using namespace std;

vector<pair<int, int>> p;

void makeSet(int v)
{
    p[v] = {v, 0};
}

pair<int, int> findSet(int v)
{
    if (v != p[v].first)
    {
        int length = p[v].second;
        p[v] = findSet(p[v].first);
        p[v].second = p[v].second + length;
    }
    return p[v];
}

void unionSet(int a, int b)
{
    if (a != b)
    {
        p[a] = {b, abs(a - b) % 1000};
    }
}

int n;

void calc()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> n;
    p = vector<pair<int, int>>(n);
    for (int i = 0; i < n; ++i)
    {
        makeSet(i);
    }
    while (!in.eof())
    {
        char c;
        int x, y, z;
        in >> c;
        if (c == 'E')
        {
            in >> z;
            pair<int, int> pr = findSet(z - 1);
            out << pr.second << endl;
        }
        else if (c == 'I')
        {
            in >> x >> y;
            unionSet(x - 1, y - 1);
        }
        else if (c == 'O')
        {
            break;
        }
    }
    in.close();
    out.close();
}

int main()
{
    calc();
    return 0;
}
