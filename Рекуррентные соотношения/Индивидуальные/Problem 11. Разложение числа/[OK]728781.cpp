#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

bool IsPrimeNumber(size_t n)
{
    if (n == 1)
    {
        return false;
    }
    for (long long i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

void FillInDividers(std::vector<long long> &dividers, long long a)
{
    for (long long i = 1; i <= sqrt(a); i++)
    {
        if (a % i == 0)
        {
            dividers.push_back(i);
        }
    }

    for (long long i = dividers.size() - 1; i >= 0; i--)
    {
        dividers.push_back(a / dividers[i]);
    }
}

int main()
{
    long long a, b, c;
    std::ifstream fin;
    std::ofstream fout;
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    fin.open(inputPath);
    fin >> a;
    fin >> b;
    fin >> c;
    fin.close();
    fout.open(outputPath);

    if (b == 1 && c == 1)
    {
        fout << -1;
        return 0;
    }
    if (a >= b && a <= c)
    {
        fout << 1;
        return 0;
    }
    else if (IsPrimeNumber(a))
    {
        fout << -1;
        return 0;
    }

    std::vector<long long> dividers;
    FillInDividers(dividers, a);
    long long size = dividers.size();
    std::vector<long long> F(size, 0);
    long long min = LONG_LONG_MAX - 1;
    for (long long i = 1; i < size; i++)
    {
        if (dividers[i] >= b && dividers[i] <= c)
        {
            F[i] = 1;
        }
        else
        {
            min = LONG_LONG_MAX - 1;
            for (long long j = i - 1; j >= 0; j--)
            {
                if (dividers[i] % dividers[j] == 0 && dividers[i] / dividers[j] >= b && dividers[i] / dividers[j] <= c && min > F[j])
                {
                    min = F[j];
                }
            }
            F[i] = min + 1;
        }
    }
    std::cout << std::endl;
    for (int j = 0; j < size; j++)
    {
        std::cout << F[j] << " ";
    }
    if (F[size - 1] == LONG_LONG_MAX)
    {
        fout << -1;
        return 0;
    }
    fout << F[size - 1];
    fout.close();
    return 0;
}