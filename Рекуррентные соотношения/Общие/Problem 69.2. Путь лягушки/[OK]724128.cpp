#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int size;
    std::cin >> size;
    std::vector<int> elements;
    for (int i = 0; i < size; ++i)
    {
        int temp;
        std::cin >> temp;
        elements.push_back(temp);
    }
    if (elements.size() == 1)
    {
        std::cout << elements[0] << "\n"
                  << 1;
        return 0;
    }
    if (elements.size() == 2)
    {
        std::cout << -1;
        return 0;
    }
    std::vector<int> f(size);
    f[0] = elements[0];
    f[1] = INT_MIN;
    f[2] = elements[2] + f[0];
    for (int i = 3; i < elements.size(); ++i)
    {
        f[i] = std::max(f[i - 2], f[i - 3]) + elements[i];
    }
    std::cout << f[size - 1];
    if (f[size - 1] != -1)
    {
        std::cout << '\n';
        int toFind = f[size - 1] - elements[size - 1];
        int lastIndex = size - 1;
        std::vector<int> resultElements;
        resultElements.push_back(lastIndex + 1);
        for (int i = size - 1; i >= 0; --i)
        {
            if (lastIndex - i == 2 && f[i] == toFind || lastIndex - i == 3 && f[i] == toFind)
            {
                toFind -= elements[i];
                lastIndex = i;
                resultElements.push_back(lastIndex + 1);
            }
        }
        for (int i = resultElements.size() - 1; i >= 0; --i)
        {
            if (i != 0)
            {
                std::cout << resultElements[i] << " ";
            }
            else
            {
                std::cout << resultElements[i];
            }
        }
    }
    return 0;
}