#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input.txt");

    int n, m, value, sum(0);

    in >> n >> m;

    std::vector<int> money(n);

    for (int i = 0; i < n; ++i)
    {
        in >> money[i];
        sum += money[i];
    }

    for (int i = 0; i < m; ++i)
    {
        in >> value;
        money.push_back(value);
    }
    in.close();

    std::vector<bool> r(sum, false);

    r[sum - 1] = true;

    for (int i = 0; i < n + m; ++i)
    {
        for (int j = 0; j < sum - money[i]; ++j)
        {
            if (r[j + money[i]])
                r[j] = true;
        }
    }

    std::ofstream out("output.txt");
    for (int i = sum - 1; i >= 0; --i)
    {
        if (!r[i])
        {
            out << "NO\n"
                << i + 1;
            return 0;
        }
    }

    out << "YES";
    out.close();

    return 0;
}