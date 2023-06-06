#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Team
{
    int a1, a2, a3;
};

bool cmpFirst(const Team &t1, const Team &t2)
{
    return t1.a1 < t2.a1;
}

int n;

vector<Team> input()
{
    ifstream in("input.txt");
    in >> n;
    vector<Team> teams(n);
    for (int i = 0; i < n; ++i)
    {
        Team team;
        in >> team.a1;
        in >> team.a2;
        in >> team.a3;
        teams[i] = team;
    }
    in.close();
    return teams;
}

void out(int answer)
{
    ofstream out("output.txt");
    out << answer;
    out.close();
    return;
}

void printTeams(const vector<Team> &teams)
{
    for (int i = 0; i < n; ++i)
    {
        cout << teams[i].a1 << " " << teams[i].a2 << " " << teams[i].a3 << "\n";
    }
}

vector<int> tree;

int query(int l, int r, int v, int tl, int tr)
{
    if (l <= tl && tr <= r)
    {
        return tree[v];
    }
    if (tr < l || r < tl)
    {
        return INT32_MAX;
    }
    int tm = (tl + tr) / 2;
    return min(query(l, r, v * 2, tl, tm),
               query(l, r, v * 2 + 1, tm + 1, tr));
}

void update(int idx, int val, int v, int tl, int tr)
{
    if (idx <= tl && tr <= idx)
    {
        tree[v] = val;
        return;
    }
    if (tr < idx || idx < tl)
    {
        return;
    }
    int tm = (tl + tr) / 2;
    update(idx, val, v * 2, tl, tm);
    update(idx, val, v * 2 + 1, tm + 1, tr);
    tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int main()
{
    vector<Team> teams = input();
    sort(teams.begin(), teams.end(), cmpFirst);
    tree = vector<int>(4 * 3 * n, INT32_MAX);
    int answer = 0;
    for (int i = 0; i < n; i++)
    {
        int min = query(0, teams[i].a2 - 1, 1, 0, 3 * n - 1);
        update(teams[i].a2 - 1, teams[i].a3, 1, 0, 3 * n - 1);
        if (min > teams[i].a3)
        {
            answer++;
        }
    }
    out(answer);
    return 0;
}
