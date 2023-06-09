#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct criminal
{
    int side;
    int time;
};

struct action
{
    int side;
    int crime;
};

struct seg
{
    int begin;
    int end;
    int crime;

    seg(int l = 0, int r = 0, int v = 0, int p = 0) : begin(l), end(r), crime(v){};
};

bool cmpOut(seg l, seg r)
{
    return l.begin > r.begin;
}
bool cmpIn(seg l, seg r)
{
    return l.end < r.end;
}

vector<int> g[2020];

criminal info[2020];
action input[2020];
int used[2020];
int matching[2020];

bool dfs_kuhn(int v)
{
    if (used[v])
    {
        return false;
    }
    used[v] = true;
    for (auto next : g[v])
    {
        if (matching[next] == 0 || dfs_kuhn(matching[next]))
        {
            matching[next] = v;
            return true;
        }
    }
    return false;
}

void kuhn()
{
    for (int i = 1; i <= 2020; i++)
    {
        for (int j = 1; j <= 2020; j++)
        {
            used[j] = false;
        }
        if (input[i].side == 1)
        {
            dfs_kuhn(i);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //    freopen("crime.in", "r", stdin);
    //    freopen("crime.out", "w", stdout);

    vector<seg> segmentsIn;
    vector<seg> segmentsOut;

    int n_input = 0;
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        char c;
        int pl;
        int crim;
        cin >> c >> crim;

        pl = -1;
        if (c == 'E')
        {
            pl = 1;
            n_input++;
        }

        input[i].side = pl;
        input[i].crime = crim;

        if (crim == 0)
        {
            continue;
        }

        if (info[crim].side == pl)
        {
            if (pl == 1)
            {
                segmentsIn.emplace_back(info[crim].time, i, crim);
            }
            else
            { // pl == -1
                segmentsOut.emplace_back(info[crim].time, i, crim);
            }
        }

        info[crim].side = pl;
        info[crim].time = i;
    }

    sort(segmentsOut.begin(), segmentsOut.end(), cmpOut);
    sort(segmentsIn.begin(), segmentsIn.end(), cmpIn);

    for (const auto &segment : segmentsOut)
    {
        int check = true;
        for (int i = segment.end; i >= segment.begin; i--)
        {
            if (input[i].crime == 0 && input[i].side == 1)
            {
                input[i].crime = segment.crime;
                check = false;
                break;
            }
        }
        if (check)
        {
            cout << "CRIME TIME";
            return 0;
        }
    }

    for (const auto &segment : segmentsIn)
    {
        int check = true;
        for (int i = segment.begin; i <= segment.end; i++)
        {
            if (input[i].crime == 0 && input[i].side == -1)
            {
                input[i].crime = segment.crime;
                check = false;
                break;
            }
        }
        if (check)
        {
            cout << "CRIME TIME";
            return 0;
        }
    }

    // ставим рёбра
    for (int i = 1; i <= n; i++)
    {
        if (input[i].crime == 0)
        {
            unordered_set<int> s;
            for (int j = i; j <= n; j++)
            {
                if (input[i].side == -1 * input[j].side)
                {
                    if (input[j].crime == 0)
                    {
                        g[i].push_back(j);
                    }
                    else if (s.count(input[j].crime) == 0)
                    {
                        g[i].push_back(j);
                        s.insert(input[j].crime);
                    }
                }
            }
        }
        else
        {
            for (int j = i; j <= n; j++)
            {
                if (input[i].side == -1 * input[j].side && (input[j].crime == 0 || input[j].crime == input[i].crime))
                {
                    g[i].push_back(j);
                }
            }
        }
    }

    kuhn();

    int n_p = 0;
    for (int i = 1; i <= n; i++)
    {
        if (matching[i] != 0)
        {
            n_p++;
        }
    }

    cout << n_input - n_p;
}
