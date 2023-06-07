#include <iostream>
#include "fstream"
#include "algorithm"
#include "map"
#include <vector>
using namespace std;
int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, t;
    in >> n;
    vector<long> vec(n * n);
    map<long, long> map1;
    vector<long> ans;
    for (int i = 0; i < n * n; i++)
    {
        in >> vec[i];
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++)
    {
        map1[vec[i]]++;
    }
    ans.push_back(vec[0] / 2);
    if (map1[vec[0]] == 1)
    {
        map1.erase(vec[0]);
    }
    else
    {
        map1[vec[0]]--;
    }
    for (int i = 1; i < n; i++)
    {
        ans.push_back(map1.begin()->first - ans[0]);
        for (int j = 0; j < i; j++)
        {
            long tmp = ans[j] + ans[i];
            if (map1[tmp] > 2)
            {
                map1[tmp] -= 2;
            }
            else
            {
                map1.erase(tmp);
            }
        }
        if (map1[2 * ans[i]] == 1)
        {
            map1.erase(2 * ans[i]);
        }
        else
            map1[ans[i] * 2]--;
    }
    cout << map1.size() << "\n";
    for (int i = 0; i < ans.size(); i++)
    {
        out << ans[i] << "\n";
    }
    return 0;
}