#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("common/data_struct/is_heap/input.txt");
    std::ofstream ofStream("common/data_struct/is_heap/output.txt");
    int n;
    fin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        fin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        if (2 * i <= n && a[i - 1] > a[2 * i - 1])
        {
            ofStream << "No";
            return 0;
        }
        if (2 * i + 1 <= n && a[i - 1] > a[2 * i])
        {
            ofStream << "No";
            return 0;
        }
    }
    ofStream << "Yes";
    return 0;
}