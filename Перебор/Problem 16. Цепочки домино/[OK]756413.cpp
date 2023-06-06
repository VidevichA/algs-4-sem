#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int N = 28;
vector<vector<bool>> visited(7, vector<bool>(7, false));

void generate(pair<int, int> cur, vector<pair<int, int>> cur_seq, int cur_length, int length, vector<vector<pair<int, int>>> &ans)
{
    if (cur_length == length && cur_seq[0].first == cur.second)
        ans.push_back(cur_seq);
    else if (cur_length >= length)
        return;
    int t = cur.second;
    for (int j = 0; j < 7; ++j)
    {
        if (not visited[t][j])
        {
            visited[t][j] = visited[j][t] = true;
            auto x = cur_seq;
            x.push_back({t, j});
            generate({t, j}, x, cur_length + 1, length, ans);
            visited[t][j] = visited[j][t] = false;
        }
    }
}

int main()
{
    ifstream fin("input.txt", ios::in);
    ofstream fout("output.txt", ios::out);
    int length;
    fin >> length;
    if (length <= 3 || length >= 29)
    {
        fout << "wrong count";
        return 0;
    }
    vector<vector<pair<int, int>>> ans;
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (!visited[i][j] && i != j)
            {
                visited[i][j] = visited[j][i] = true;
                vector<pair<int, int>> y = vector<pair<int, int>>(1, {i, j});
                generate({i, j}, y, 1, length, ans);
            }
        }
    }
    for (auto seq : ans)
    {
        for (int i = 0; i < length; ++i)
        {
            if (i != length - 1)
                fout << seq[i].first << "." << seq[i].second << " ";
            else
                fout << seq[i].first << "." << seq[i].second;
        }
        fout << endl;
    }
    fout << ans.size();
    fin.close();
    fout.close();
    return 0;
}