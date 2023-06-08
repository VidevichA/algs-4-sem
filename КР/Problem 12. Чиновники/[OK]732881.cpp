#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <stack>

using namespace std;

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{

    ifstream in("in.txt");
    ofstream out("out.txt");

    int n;
    in >> n;

    vector<vector<vector<int>>> officials(n + 1);
    vector<int> pay(n + 1, INT_MAX);
    pay[0] = 0;

    for (int i = 1; i < n + 1; i++)
    {
        int k;
        in >> k;
        int l;
        in >> l;

        vector<vector<int>> person(l, vector<int>(2));

        for (int j = 0; j < l; j++)
        {
            int a;
            in >> a;
            int b;
            in >> b;

            person[j][0] = a;
            person[j][1] = b;
        }

        officials[k] = person;
    }

    std::stack<std::pair<int, int>> stack;
    stack.push({1, 0});

    while (stack.size() != 0)
    {

        int i = stack.top().first;
        int j = stack.top().second;

        stack.pop();

        if (j < officials[i].size())
        {
            stack.push({i, j + 1});
            stack.push({officials[i][j][0], 0});
        }
        else
        {
            if (j == 0)
            {
                pay[i] = 0;
            }
            else
            {
                for (int j = 0; j < officials[i].size(); ++j)
                {
                    pay[i] = min(pay[i], pay[officials[i][j][0]] + officials[i][j][1]);
                }
            }
        }
    }

    out << pay[1] << std::endl;
    out << 1;
    int i = 1;
    while (pay[i] != 0)
    {
        for (int j = 0; j < officials[i].size(); ++j)
        {
            if (pay[i] - officials[i][j][1] == pay[officials[i][j][0]])
            {
                out << " " << officials[i][j][0];
                i = officials[i][j][0];
                break;
            }
        }
    }
    out << std::endl;
}