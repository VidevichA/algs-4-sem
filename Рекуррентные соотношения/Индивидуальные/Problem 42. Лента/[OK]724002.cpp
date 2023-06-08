#include <vector>
#include <fstream>

std::vector<std::vector<long long>> turns;

long long sum(std::vector<long long> v, long long begin, long long end)
{
    long long summ = 0;
    for (long long i = begin; i <= end; i++)
    {
        summ += v[i];
    }

    return summ;
}

long long min(long long a, long long b)
{
    return a < b ? a : b;
}

void game(int j, int n)
{
    if (turns.size() != n)
    {
        std::vector<long long> tmp;

        for (int i = 0; i < turns[j - 1].size() - 1; ++i)
        {
            tmp.push_back(sum(turns[0], i, i + j) - min(turns[j - 1][i], turns[j - 1][i + 1]));
        }

        turns.push_back(tmp);
        j += 1;
        game(j, n);
    }
    else
    {
        return;
    }
}

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    long long n;
    fin >> n;

    std::vector<long long> lenta;
    long long temp;
    turns.push_back(lenta);

    while (fin >> temp)
    {
        turns[0].push_back(temp);
    }

    int j = 1;
    game(j, n);

    fout << turns[n - 1][0];

    return 0;
}