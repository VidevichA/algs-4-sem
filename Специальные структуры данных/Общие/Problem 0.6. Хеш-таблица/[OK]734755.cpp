#include <vector>
#include <fstream>

int main()
{
    std::ifstream fin("common/data_struct/hash/input.txt");
    std::ofstream ofStream("common/data_struct/hash/output.txt");
    int m, c, n;
    fin >> m >> c >> n;

    std::vector<int> table(m, -1);
    std::vector<bool> unq(1e9 + 1);

    for (int i = 0; i < n; i++)
    {
        int key;
        fin >> key;
        if (unq[key])
        {
            continue;
        }
        unq[key] = true;
        int index = key % m;
        int j = 0;
        while (table[index] != -1)
        {
            j++;
            index = (key % m + c * j) % m;
        }
        table[index] = key;
    }

    for (int i = 0; i < m; i++)
    {
        ofStream << table[i] << " ";
    };

    return 0;
}