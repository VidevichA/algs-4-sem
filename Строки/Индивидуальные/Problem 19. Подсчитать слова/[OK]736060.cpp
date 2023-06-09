#include <iostream>

int main()
{
    int n, count = 0;
    std::string string;
    std::cin >> n;
    getline(std::cin, string);
    for (int j = 1; j <= n; j++)
    {
        getline(std::cin, string);
        if (string.length())
        {
            for (int i = 0; i <= string.length() - 1; i++)
            {
                if (string[i] > 32 && string[i] <= 126)
                {
                    count++;
                    while (string[i] > 32 && string[i] <= 126)
                    {
                        i++;
                    }
                }
            }
        }
    }
    std::cout << count;
}