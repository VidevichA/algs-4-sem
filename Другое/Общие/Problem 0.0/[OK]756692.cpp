#include <fstream>
#include <hash_set>
#include <string>

#include <iostream>
int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    __gnu_cxx::hash_set<long> hs;
    std::string temp;
    while (in >> temp)
    {
        hs.insert(std::stoi(temp));
    }
    long long sum = 0;
    for (int el : hs)
    {
        std::cout << el << " ";
        sum += el;
    }
    out << sum;
    return 0;
}