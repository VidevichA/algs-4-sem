#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int size;
    in >> size;
    std::vector<int> elements(size);
    for (int i = 0; i < size; ++i)
    {
        int temp;
        in >> temp;
        elements[i] = temp;
    }
    bool flag = true;
    for (int i = 0; i < size; ++i)
    {
        if (2 * i + 1 < size && elements[i] > elements[2 * i + 1] || 2 * i + 2 < size && elements[i] > elements[2 * i + 2])
        {
            flag = false;
            break;
        }
    }
    out << (flag ? "Yes" : "No");
    return 0;
}