#include <iostream>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

int n;
int m;
int k;
int l;

vector<bool> color;
bool c;

vector<vector<int>> rezW;
vector<vector<int>> rezB;

int ready(vector<int> &A)
{
    vector<int> tmp;
    int f = 0;

    for (int i = c ? 0 : 1; i < A.size(); i++)
    {
        if (color[i] == c)
        {
            if (A[i] == 0)
            {
                f = -1;
                break;
            }
            else if (A[i] == 2)
            {
                tmp.push_back(i + 1);
                f++;
            }
        }
    }

    if (f != -1 && tmp.size() <= l)
    {
        if (c)
        {
            rezW.push_back(tmp);
            l = tmp.size();
        }
        else
        {
            rezB.push_back(tmp);
            l = tmp.size();
        }
    }
    return f;
}

void go(vector<int> B, int index, int s)
{

    for (int i = index; i < B.size(); i++)
    {
        if (color[i] == c && (B[i] == 0 || B[i] == 1))
        {
            vector<int> A = B;
            int y;
            y = i;
            while ((A[y] == 0 || A[y] == 1) && y < n * m)
            {
                A[y] = 1;
                y += (m + 1);
                if (y >= n * m || y % m == 0)
                    break;
            }
            y = i;
            while ((A[y] == 0 || A[y] == 1) && y >= 0)
            {
                A[y] = 1;
                y -= (m + 1);
                if (y < 0 || (y + 1) % m == 0)
                    break;
            }
            y = i;
            while ((A[y] == 0 || A[y] == 1) && y < n * m)
            {
                A[y] = 1;
                y += (m - 1);
                if (y >= n * m || (y + 1) % m == 0)
                    break;
            }
            y = i;
            while ((A[y] == 0 || A[y] == 1) && y >= 0)
            {
                A[y] = 1;
                y -= (m - 1);
                if (y < 0 || y % m == 0)
                    break;
            }
            A[i] = 2;
            int f = ready(A);
            if (f > l)
            {
                return;
            }
            else if (s + 2 <= l)
            {
                go(A, i, s + 1);
            }
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    float start = clock();

    in >> n;
    in >> m;
    in >> k;

    vector<int> A(n * m, 0);

    color = vector<bool>(n * m);

    bool vvv = true;

    for (int i = 0; i < m; i++)
    {
        color[i] = vvv;
        vvv = !vvv;
    }

    for (int i = m; i < n * m; i++)
    {
        color[i] = !color[i - m];
    }

    for (int i = 0; i < k; i++)
    {
        int pos;
        in >> pos;
        A[pos - 1] = 3;
    }
    int w;
    int b;
    c = true;
    l = INT_MAX;
    go(A, 0, 0);

    w = l;
    c = false;
    l = INT_MAX;
    go(A, 1, 0);
    b = l;

    long long counter = 0;
    std::vector<std::vector<int>> results;
    for (long long i = 0; i < rezW.size(); ++i)
    {
        if (rezW[i].size() == w)
        {
            for (long long j = 0; j < rezB.size(); ++j)
            {
                if (rezB[j].size() == b)
                {
                    auto el = rezW[i];
                    for (long long r = 0; r < rezB[j].size(); ++r)
                    {
                        el.push_back(rezB[j][r]);
                        std::sort(el.begin(), el.end());
                    }
                    results.push_back(el);
                    ++counter;
                }
            }
        }
    }
    std::sort(results.begin(), results.end(), [](const std::vector<int> &f, const std::vector<int> &s)
              {
            for (long long i = 0; i < f.size(); ++i) {
                if (f[i] > s[i]) {
                    return false;
                }
                else if (f[i] < s[i])
                {
                    return true;
                }
            }
            return true; });
    for (auto r : results)
    {
        for (auto c : r)
        {
            out << c << ' ';
        }
        out << '\n';
    }
    out << counter;
}