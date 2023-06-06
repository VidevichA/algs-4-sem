#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

const int SIZE = 27;
const int DELTA = 96;
int n;
vector<vector<int>> graph(SIZE, vector<int>(SIZE, 0));
vector<int> ind(SIZE, 0);
vector<int> outd(SIZE, 0);
vector<vector<string>> words(10000);

void input()
{
    ifstream in("input.txt");
    in >> n;
    for (int i = 0; i < n; ++i)
    {
        string word;
        in >> word;

        int first_char = word[0];
        int last_char = word[word.length() - 1];
        first_char -= DELTA;
        last_char -= DELTA;
        words[(first_char * SIZE) + last_char].push_back(word);
        graph[first_char][last_char]++;
        ind[last_char]++;
        outd[first_char]++;
    }
}

vector<vector<int>> get_trans(const vector<vector<int>> &g)
{
    vector<vector<int>> temp(SIZE, vector<int>(SIZE));
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            temp[i][j] = g[j][i];
        }
    }
    return temp;
}

void dfs(int v, vector<bool> &visited, const vector<vector<int>> &g)
{
    visited[v] = true;
    for (int u = 0; u < SIZE; ++u)
    {
        if (graph[v][u] > 0 && !visited[u])
        {
            dfs(u, visited, g);
        }
    }
}

int start = 0;

bool is_euler()
{
    for (int i = 0; i < SIZE; ++i)
    {
        if (ind[i] != outd[i])
        {
            return false;
        }
    }

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (graph[i][j] > 0)
            {
                start = i;
                break;
            }
        }
        if (start != 0)
        {
            break;
        }
    }

    vector<bool> visited(SIZE, false);
    dfs(start, visited, graph);
    for (int i = 0; i < SIZE; ++i)
    {
        if (!visited[i] && (ind[i] > 0 || outd[i] > 0))
        {
            return false;
        }
    }

    visited = vector<bool>(SIZE, false);
    vector<vector<int>> trans_graph = get_trans(graph);
    dfs(start, visited, trans_graph);
    for (int i = 0; i < SIZE; ++i)
    {
        if (!visited[i] && (ind[i] > 0 || outd[i] > 0))
        {
            return false;
        }
    }

    return true;
}

vector<int> get_cycle()
{
    vector<int> cycle;
    stack<int> st;
    st.push(start);
    while (!st.empty())
    {
        int v = st.top();
        int next = -1;
        for (int u = 0; u < SIZE; ++u)
        {
            if (graph[v][u])
            {
                next = u;
                break;
            }
        }
        if (next == -1)
        {
            cycle.push_back(v);
            st.pop();
        }
        else
        {
            --graph[v][next];
            st.push(next);
        }
    }

    return cycle;
}

void output_cycle(ofstream &out, vector<int> &cycle)
{
    for (unsigned int i = cycle.size() - 1; i >= 1; --i)
    {
        int pos = cycle[i] * SIZE + cycle[i - 1];
        out << words[pos][words[pos].size() - 1] << endl;
        words[pos].pop_back();
    }
}

void final_output()
{
    ofstream out("output.txt");
    if (!is_euler())
    {
        out << "No\n";
    }
    else
    {
        out << "Yes\n";
        vector<int> cycle = get_cycle();
        output_cycle(out, cycle);
    }
    out.close();
}

int main()
{
    input();
    final_output();
    return 0;
}
