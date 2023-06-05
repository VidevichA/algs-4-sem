#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int kmp(const string &s, const string &t)
{
    int n = t.size();
    vector<int> pi(n, 0);
    for (int i = 1, j = 0; i < n; i++)
    {
        while (j > 0 && t[i] != t[j])
        {
            j = pi[j - 1];
        }
        if (t[i] == t[j])
        {
            j++;
        }
        pi[i] = j;
    }
    int i = 0, j = 0;
    int s_len = s.size(), t_len = t.size();
    while (i < s_len)
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
            if (j == t_len)
            {
                return i - t_len;
            }
        }
        else if (j > 0)
        {
            j = pi[j - 1];
        }
        else
        {
            i++;
        }
    }
    return -1;
}

int main()
{
    std::ifstream fin("common/string/cyclic_shift/input.txt");
    std::ofstream ofStream("common/string/cyclic_shift/output.txt");
    int n;
    fin >> n;
    string s1, s2;
    fin >> s1 >> s2;
    int k = kmp(s1 + s1, s2);
    ofStream << k;
    return 0;
}