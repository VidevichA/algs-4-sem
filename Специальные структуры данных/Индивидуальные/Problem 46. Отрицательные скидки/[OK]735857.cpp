#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::ifstream fin;
std::ofstream fout;

int main()
{
    fin.open("input.txt");
    long long n, k;
    fin >> n >> k;
    std::vector<long long> A(n, 0), B(n, 0);
    std::vector<long long> coefficients(n, 0);
    std::priority_queue<std::pair<long long, long long>> queue;
    for (long long i = 0; i < n; i++)
    {
        fin >> A[i] >> B[i];
    }
    fin.close();
    fout.open("output.txt");
    long long cost = 0, index = 0;

    for (long long i = 0; i < n; i++)
    {
        queue.push(std::make_pair(-A[i], i));
    }

    for (long long i = 0; i < k; i++)
    {
        cost += (-1 * queue.top().first);
        index = queue.top().second;
        coefficients[index]++;
        queue.pop();
        queue.push(std::make_pair(-1 * (A[index] + coefficients[index] * B[index]), index));
    }

    fout << cost;
    fout.close();

    return 0;
}