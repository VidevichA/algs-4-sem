#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::string str;
    std::ifstream fin;
    std::ofstream fout;
    std::string inputPath = "input.txt";
    std::string outputPath = "output.txt";
    fin.open(inputPath);
    if (fin.is_open())
    {
        std::getline(fin, str);
    }
    fin.close();
    fout.open(outputPath);
    if (str.empty())
    {
        fout << 0;
        return 0;
    }
    long long size = str.size();
    long long minimal = LONG_LONG_MAX;
    std::vector<std::vector<long long>> F(size, std::vector<long long>(size, 0));
    for (int i = 0; i < size - 1; i++)
    {
        F[i][i] = 1;
        if (str[i] != str[i + 1])
        {
            F[i][i + 1] = 2;
        }
        else
        {
            F[i][i + 1] = 1;
        }
    }
    F[size - 1][size - 1] = 1;
    for (long long j = 2; j < size; j++)
    {
        for (long long i = j - 2; i >= 0; i--)
        {
            if (str[j - 1] == str[j])
            {
                F[i][j] = F[i][j - 1];
            }
            else
            {
                for (long long k = i; k < j - 1; k++)
                {
                    if (str[j] == str[k] && minimal > F[i][k] + F[k + 1][j - 1])
                    {
                        minimal = F[i][k] + F[k + 1][j - 1];
                    }
                }
                if (minimal == LONG_LONG_MAX)
                {
                    F[i][j] = F[i][j - 1] + 1;
                }
                else
                {
                    F[i][j] = std::min(minimal, F[i][j - 1] + 1);
                }
                minimal = LONG_LONG_MAX;
            }
        }
    }

    fout << F[0][size - 1];
    fout.close();
    return 0;
}