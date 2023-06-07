#include "fstream"
#include "vector"
#include "stack"
#include "iostream"
#include <algorithm>

using namespace std;
int rec = 0;
vector<vector<int>> ans;
vector<int> bad;
int n, m, k;

void setQueen(vector<int> &v);

bool isFull(vector<int> &v)
{
    int i = 0;
    while (i < n * m)
    {
        if (v[i] == 0)
        {
            return false;
        }
        i += 1;
    }
    return true;
}

int fill(vector<int> &v, int &x, bool isMax, bool need, bool b)
{

    vector<int> prev;
    if (need || b)
        prev = v;
    int ty;
    int count = 0;
    int free = 0;
    ty = x;
    // вверх
    while (ty >= 0 && (v[ty] == 0 || v[ty] == 1))
    {
        if (v[ty] == 0)
            free++;
        v[ty] = 1;
        ty -= m;
        count++;
    }
    ty = x;
    // вниз
    while (ty < n * m && (v[ty] == 0 || v[ty] == 1))
    {
        if (v[ty] == 0)
            free++;
        v[ty] = 1;
        ty += m;
        count++;
    }
    // влево
    ty = x;
    while (v[ty] == 0 || v[ty] == 1)
    {
        if (ty % m == 0)
        {
            if (v[ty] == 0)
                free++;
            v[ty] = 1;
            count++;
            break;
        }
        if (need)
            count++;
        if (v[ty] == 0)
            free++;
        v[ty] = 1;
        ty--;
    }
    // вправо
    ty = x;
    while (v[ty] == 0 || v[ty] == 1)
    {
        if (v[ty] == 0)
            free++;
        v[ty] = 1;
        count++;
        ty++;
        if (ty % m == 0)
            break;
    }
    // влево вверх
    ty = x;
    while (ty >= 0 && (v[ty] == 0 || v[ty] == 1))
    {
        if (v[ty] == 0)
            free++;
        v[ty] = 1;
        count++;
        ty++;
        ty -= m;
        if (ty % m == 0)
            break;
    }
    // вправо вниз
    ty = x;
    while (ty < n * m && (v[ty] == 0 || v[ty] == 1))
    {
        if (v[ty] == 0)
            free++;
        v[ty] = 1;
        ty++;
        count++;
        ty += m;
        if (ty % m == 0)
            break;
    }
    // влево вверх
    ty = x;
    while (ty >= 0 && (v[ty] == 0 || v[ty] == 1))
    {
        if (v[ty] == 0)
            free++;
        v[ty] = 1;
        count++;
        ty--;
        ty -= m;
        if ((ty + 1) % m == 0)
            break;
    }
    ty = x;
    while (ty < n * m && (v[ty] == 0 || v[ty] == 1))
    {
        if (v[ty] == 0)
            free++;
        v[ty] = 1;
        count++;
        ty--;
        ty += m;
        if ((ty + 1) % m == 0)
            break;
    }
    if (!isMax && need || b)
        v = prev;
    if (!need)
        return free;
    return count;
}

int c_record(vector<int> &f)
{
    while (!isFull(f))
    {
        rec += 1;
        setQueen(f);
    }
    return rec;
}

void setQueen(vector<int> &v)
{
    int x;
    int max = -1;
    for (int i = 0; i < n * m; i++)
    {
        if (v[i] != -1 && v[i] != 1)
        {
            int c1 = fill(v, i, false, true, false);
            if (c1 > max)
            {
                max = c1;
                x = i;
            }
        }
    }
    fill(v, x, true, false, false);
}

void findAnswer(vector<int> &f, int &size, int &x, vector<int> &cur, int &free)
{
    stack<int> pos;
    int j = n * m - 1;
    while (j >= x)
    {
        if (f[j] != -1)
            pos.push(j);
        j -= 1;
    }
    int c = 0;
    int cf = free;
    while (!pos.empty())
    {
        free = cf;
        cur.push_back(pos.top());
        size += 1;

        pos.pop();
        if (size <= rec)
        {
            vector<int> prev = f;

            c = fill(prev, cur[size - 1], true, false, false);
            if (c == 0)
            {
                cur.pop_back();
                size -= 1;
            }
            else
            {
                free -= c;
                if (free != 0)
                {
                    if (size == rec)
                    {
                        free += c;
                        cur.pop_back();
                        size -= 1;
                    }
                    else
                    {
                        if (!pos.empty())
                            findAnswer(prev, size, pos.top(), cur, free);
                        else
                        {
                            free += c;
                            cur.pop_back();
                            size -= 1;
                        }
                    }
                }
                else
                {
                    if (size == rec)
                    {
                        free += c;
                        ans.push_back(cur);
                        cur.pop_back();
                        size -= 1;
                    }
                    else if (size < rec)
                    {
                        free += c;
                        ans.clear();
                        rec = size;
                        ans.push_back(cur);
                        cur.pop_back();
                        size -= 1;
                    }
                    else
                    {
                        free += c;
                        cur.pop_back();
                        size -= 1;
                    }
                }
            }
        }
        else
        {
            free += c;
            cur.pop_back();
            size -= 1;
        }
    }
    if (!cur.empty())
    {
        free = cf;
        cur.pop_back();
        size -= 1;
    }
}

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    std::ios_base::sync_with_stdio(false);
    int f;
    cin >> n >> m >> k;
    int x = 0;
    int free = n * m - k;
    if (free == 0)
    {
        cout << 1;
        return 0;
    }
    vector<int> field(n * m);
    for (int i = 0; i < k; i++)
    {
        cin >> f;
        if (x == f)
        {
            x++;
        }
        field[f - 1] = -1;
    }
    if (free == 1)
    {
        for (int i = 0; i < n * m; i++)
        {
            if (field[i] == 0)
            {
                cout << i + 1 << "\n"
                     << 1;
                return 0;
            }
        }
    }
    for (int i = 0; i < n * m; i++)
    {
        int c2 = 0;
        if (field[i] != -1)
            c2 = fill(field, i, false, false, true);
        if (c2 == 1)
            bad.push_back(i);
    }
    for (int i = 0; i < bad.size(); i++)
    {
        field[bad[i]] = -1;
    }
    free -= bad.size();
    vector<int> field_rec = field;
    c_record(field_rec);
    vector<int> c1;
    int sz = 0;
    findAnswer(field, sz, x, c1, free);
    if (ans.empty())
    {
        for (int i = 0; i < bad.size(); i++)
        {
            cout << bad[i] + 1 << " ";
        }
        cout << "\n"
             << 1;
        return 0;
    }
    if (!bad.empty())
    {
        for (int i = 0; i < ans.size(); i++)
        {
            for (int j = 0; j < bad.size(); j++)
            {
                ans[i].push_back(bad[j]);
            }
            sort(ans[i].begin(), ans[i].end());
        }
    }
    sz = ans.size();
    rec += bad.size();
    int i = 0;
    int j = 0;
    while (i < sz)
    {
        j = 0;
        while (j < rec)
        {
            cout << ans[i][j] + 1 << " ";
            j += 1;
        }
        i += 1;
        cout << "\n";
    }
    cout << sz << "\n";
}