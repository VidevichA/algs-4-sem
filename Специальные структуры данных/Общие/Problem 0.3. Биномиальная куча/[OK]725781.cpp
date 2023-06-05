#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long n;
    in >> n;
    if (n == 0)
    {
        out << -1;
        return 0;
    }
    int rank = 0;
    while (n > 0)
    {
        int temp = n & 1;
        if (temp == 1)
        {
            out << rank << "\n";
        }
        n = n >> 1;
        ++rank;
    }
    return 0;
}