#include <fstream>
#include <string>
#include <algorithm>

int main()
{
    int k;
    std::string input, result, current;
    std::ifstream fin("input.txt");
    fin >> k;
    std::getline(fin, input);
    std::getline(fin, input);
    fin.close();

    int start = 0;
    while (start < input.size())
    {
        current = input.substr(start, k);
        std::reverse(current.begin(), current.end());
        start += k;
        result += current;
    }

    std::ofstream fout("output.txt");
    fout << result;
    fout.close();
    return 0;
}
