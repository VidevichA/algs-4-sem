#include <iostream>
#include <vector>
#include "fstream"
#include "list"

// using namespace std;

int main()
{
    std::ifstream cin("input.txt");
    std::ofstream cout("output.txt");
    std::string s1;
    std::string s2;
    cin >> s1;
    cin >> s2;
    std::list<char> list;
    list.push_back(s1[0]);
    for (int i = 0; i < s2.length(); i++)
    {
        if (s2[i] == 'A')
        {
            list.push_front('A');
        }
        if (s2[i] == 'T')
        {
            list.push_back('T');
        }
        if (s2[i] == 'C')
        {
            if (list.front() == 'A')
            {
                list.push_back('C');
            }
            else
            {
                list.push_front('C');
            }
        }
        if (s2[i] == 'G')
        {
            if (list.front() == 'A' || list.front() == 'C')
            {
                list.push_back('G');
            }
            else
            {
                list.push_front('G');
            }
        }
    }
    auto iter = list.begin();
    for (iter = list.begin(); iter != list.end(); iter++)
    {
        cout << (*iter);
    }
    return 0;
}