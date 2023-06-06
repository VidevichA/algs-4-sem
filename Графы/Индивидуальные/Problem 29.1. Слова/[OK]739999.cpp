#include <iostream>
#include <vector>
#include <fstream>

const int LETTER_COUNT = 27;
const int A_ASCII_CODE = 96;

std::vector<int> firstLetterCount(LETTER_COUNT, 0);
std::vector<int> lastLetterCount(LETTER_COUNT, 0);

void dfs(int v, std::vector<bool> &visited, std::vector<std::vector<int>> &g)
{
    visited[v] = true;
    for (int u = 0; u < LETTER_COUNT; ++u)
    {
        if (g[v][u] > 0 && !visited[u])
        {
            dfs(u, visited, g);
        }
    }
}

int firstNotNull(std::vector<std::vector<int>> g)
{
    int index = 0;

    for (int i = 0; i < LETTER_COUNT; ++i)
    {
        for (int j = 0; j < LETTER_COUNT; ++j)
        {
            if (g[i][j] > 0)
            {
                index = i;
                break;
            }
        }
        if (index != 0)
        {
            break;
        }
    }
    return index;
}

bool isEuler(std::vector<std::vector<int>> g)
{

    std::vector<bool> visited(LETTER_COUNT, false);

    dfs(firstNotNull(g), visited, g);

    for (int i = 0; i < visited.size(); i++)
    {
        if (!visited[i] && (firstLetterCount[i] != 0 || lastLetterCount[i] != 0))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::ifstream in("input.txt");
    int n;
    in >> n;
    std::vector<std::vector<int>> g(LETTER_COUNT, std::vector<int>(LETTER_COUNT, 0));

    for (int i = 0; i < n; ++i)
    {
        std::string word;
        in >> word;

        int firstLetter = word[0];
        int lastLetter = word.back();
        lastLetterCount[lastLetter - A_ASCII_CODE]++;
        firstLetterCount[firstLetter - A_ASCII_CODE]++;
        g[firstLetter - A_ASCII_CODE][lastLetter - A_ASCII_CODE]++;
    }

    std::ofstream out("output.txt");

    for (int i = 0; i < LETTER_COUNT; i++)
    {
        if (firstLetterCount[i] != lastLetterCount[i])
        {
            out << "No";
            return 0;
        }
    }

    if (isEuler(g))
    {
        out << "Yes";
    }
    else
    {
        out << "No";
    }
}