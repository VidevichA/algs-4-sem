#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct component
{
    vector<int> left;
    vector<int> right;
};

bool compar(component &c1, component &c2)
{
    if (abs((int)c1.left.size() - (int)c1.right.size()) > abs((int)c2.left.size() - (int)c2.right.size()))
    {
        return true;
    }
    return false;
}

int main()
{
    ifstream cin("input.in");
    ofstream cout("output.out");
    int n;
    cin >> n;
    vector<bool> visit(n);
    vector<int> par(n);
    for (int i = 0; i < n; i++)
    {
        visit[i] = false;
        par[i] = 0;
    }
    std::vector<std::vector<int>> gr(n);
    for (int i = 0; i < n; i++)
        gr[i].resize(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int tmp;
            cin >> tmp;
            if (i == j)
                gr[i][j] = 0;
            else
            {
                if (tmp == 0)
                    gr[i][j] = 1;
                else
                    gr[i][j] = 0;
            }
        }
    }

    queue<int> q;
    par[0] = 1;
    vector<component> comp;
    vector<int> f;
    vector<int> s;
    component com{};
    com.left.push_back(1);
    for (int i = 0; i < n; i++)
    {
        if (q.empty())
        {
            if (!visit[i])
            {
                par[i] = 1;
                if (i != 0)
                    com.left.push_back(i + 1);
                q.push(i);
            }
            visit[i] = true;
        }
        if (!q.empty())
        {
            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                for (int j = 0; j < n; j++)
                {
                    int cur = gr[v][j];
                    if (cur == 1 && !visit[j])
                    {
                        par[j] = 3 - par[v];
                        if (par[j] == 1)
                            com.left.push_back(j + 1);
                        else
                            com.right.push_back(j + 1);
                        q.push(j);
                        visit[j] = true;
                    }
                    if (cur == 1 && visit[j])
                    {
                        if (par[v] == par[j])
                        {
                            cout << "NO";
                            return 0;
                        }
                    }
                }
            }
            comp.push_back(com);
            com.left.resize(0);
            com.right.resize(0);
        }
    }
    vector<int> team1;
    vector<int> team2;
    team1.resize(0);
    team2.resize(0);
    sort(comp.begin(), comp.end(), compar);
    for (int i = 0; i < comp.size(); i++)
        if (team1.size() > team2.size())
        {
            if (comp[i].left.size() > comp[i].right.size())
            {
                for (int j = 0; j < comp[i].left.size(); j++)
                {
                    team2.push_back(comp[i].left[j]);
                }
                for (int j = 0; j < comp[i].right.size(); j++)
                {
                    team1.push_back(comp[i].right[j]);
                }
            }
            else
            {
                for (int j = 0; j < comp[i].right.size(); j++)
                {
                    team2.push_back(comp[i].right[j]);
                }
                for (int j = 0; j < comp[i].left.size(); j++)
                {
                    team1.push_back(comp[i].left[j]);
                }
            }
        }
        else
        {
            if (comp[i].left.size() > comp[i].right.size())
            {
                for (int j = 0; j < comp[i].left.size(); j++)
                {
                    team1.push_back(comp[i].left[j]);
                }
                for (int j = 0; j < comp[i].right.size(); j++)
                {
                    team2.push_back(comp[i].right[j]);
                }
            }
            else
            {
                for (int j = 0; j < comp[i].right.size(); j++)
                {
                    team1.push_back(comp[i].right[j]);
                }
                for (int j = 0; j < comp[i].left.size(); j++)
                {
                    team2.push_back(comp[i].left[j]);
                }
            }
        }
    if ((double)max(team1.size(), team2.size()) / (double)min(team1.size(), team2.size()) > 2.0)
    {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    if (team1.size() <= team2.size())
        swap(team1, team2);
    sort(team1.begin(), team1.end());
    for (int i : team1)
    {
        cout << i << " ";
    }

    return 0;
}