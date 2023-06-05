#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("common/trees/is_search/bst.in");
    std::ofstream ofStream("common/trees/is_search/bst.out");
    int n, m;
    fin >> n >> m;

    std::vector<int> nodes(n);
    std::vector<std::pair<long long, long long>> border(n, {INT64_MIN, INT64_MAX});
    nodes[0] = m;

    int value, parentIndex;
    char childType;
    for (int i = 1; i < n; i++)
    {
        fin >> value >> parentIndex >> childType;
        nodes[i] = value;
        if (childType == 'L')
        {
            border[i].second = nodes[parentIndex - 1];
            border[i].first = border[parentIndex - 1].first;
        }
        else
        {
            border[i].first = nodes[parentIndex - 1];
            border[i].second = border[parentIndex - 1].second;
        }
        if (border[i].first > value || border[i].second <= value)
        {
            fin.close();
            ofStream << "NO";
            ofStream.close();
            return 0;
        }
    }
    ofStream << "YES";
    fin.close();
    ofStream.close();
    return 0;
}