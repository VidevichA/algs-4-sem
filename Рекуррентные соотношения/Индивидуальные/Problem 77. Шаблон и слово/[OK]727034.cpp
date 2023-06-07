#include <iostream>
#include <fstream>
using namespace std;
std::string w, p;
int check(int pp, int wp)
{
    // cout<<pp<<" "<<wp<<"\n";
    if (pp >= p.length() || wp >= w.length())
    {
        if (pp != p.length() && wp >= w.length())
        {
            for (int i = pp; i < p.length(); i++)
            {
                //  cout<<3;
                if (p[i] == '?' || (p[i] != '?' && p[i] != '*'))
                {
                    //  cout<<1;
                    return 0;
                }
            }
            //  cout<<2;
            return 1;
        }
        else if (pp == p.length() && wp == w.length())
            return 1;
        else
            return 0;
    }
    else if (p[pp] == '?')
        return check(pp + 1, wp + 1);
    else if (p[pp] != '?' && p[pp] != '*')
    {
        if (p[pp] == w[wp])
            return check(pp + 1, wp + 1);
        else
            return 0;
    }
    else if (p[pp] == '*')
    {
        int t = pp + 1;
        while (p[t] == '*' || p[t] == '?')
        {
            t++;
            pp++;
            if (p[pp] == '?')
                wp++;
        }
        if (wp > w.length())
        {
            return 0;
        }
        if (t == p.length())
            return 1;
        pp = t;
        for (int i = wp; i < w.length(); i++)
        {
            if (check(pp, i))
                return 1;
        }
    }
    return 0;
}

int main()
{
    //  ifstream cin("input.txt");
    //   ofstream cout("output.txt");
    cin >> w;
    cin >> p;
    if (w != "" && p == "")
    {
        cout << "NO";
        return 0;
    }
    int ok1 = 0;
    int ok2 = 0;
    for (char i : w)
        if (i == '*' || i == '?')
            ok1 = 1;
    for (char i : p)
        if (i == '*' || i == '?')
            ok2 = 1;
    if (ok1 == 0 && ok2 == 0)
    {
        if (p != w)
            cout << "NO";
        else
            cout << "YES";
        return 0;
    }
    else
    {
        if (ok1 == 1 && ok2 == 0)
        {
            std::string tmp = w;
            w = p;
            p = tmp;
        }
    }
    if (w[0] != '?' && w[0] != '*' && p[0] != '?' && p[0] != '*' && p[0] != w[0] || w[w.length() - 1] != '?' && w[w.length() - 1] != '*' && p[p.length() - 1] != '?' && p[p.length() - 1] != '*' && p[p.length() - 1] != w[w.length() - 1])
    {
        cout << "NO";
        return 0;
    }
    int qc = 0;
    for (char i : p)
        if (i == '?')
            qc++;
    if (qc > w.length())
    {
        cout << "NO";
        return 0;
    }
    if (check(0, 0) == 1)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}