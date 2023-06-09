#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    ifstream reader("input.txt");
    int n;
    reader >> n;
    vector<int> cards(n);
    for (int i = 0; i < n; ++i)
    {
        int current;
        reader >> current;
        cards[current - 1] = i;
    }

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < n - i; ++j)
        {
            int temp = INT32_MAX;
            for (int k = 0; k < i; ++k)
            {
                temp = min(temp, matrix[j][j + k] + matrix[j + k + 1][j + i] + abs(cards[j + k] - cards[j + i]));
            }
            matrix[j][j + i] = temp;
        }
    }
    ofstream writer("output.txt");
    writer << matrix[0][n - 1];
    int temp = 0;
    for (int i = 1; i < n + 1; ++i)
    {
        temp += i;
    }
}