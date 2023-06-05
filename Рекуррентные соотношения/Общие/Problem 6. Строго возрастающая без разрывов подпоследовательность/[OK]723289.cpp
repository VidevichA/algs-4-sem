#include <fstream>
#include <vector>
#include <cmath>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    std::string temp;
    in >> temp;
    std::vector<int> elements;
    while (in >> temp)
    {
        elements.push_back(std::stoi(temp));
    }
    if (elements.empty())
    {
        out << 0;
        return 0;
    }
    if (elements.size() == 1)
    {
        out << 1;
        return 0;
    }
    std::vector<int> f;
    f.push_back(INT_MIN);
    for (int i = 1; i < elements.size(); ++i)
    {
        f.push_back(INT_MAX);
    }
    int maxLength = 1;
    for (int i = 0; i < elements.size(); ++i)
    {
        int l = 0;
        int r = f.size();
        while (l < r)
        {
            int mid = (l + r) / 2;
            if (elements[i] < f.at(mid))
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
        if (elements[i] > f[l - 1])
        {
            f[l] = elements[i];
            maxLength = std::max(maxLength, l);
        }
    }
    out << maxLength;
    return 0;
}