#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class Trie
{
private:
    class Node
    {
    public:
        std::vector<Node *> childs;
        char c;
        std::string str;
        Node() : c(' '), childs() {}

        Node *FindChild(char s)
        {
            if (childs.empty())
            {
                return nullptr;
            }
            for (int i = 0; i < childs.size(); i++)
            {
                if (childs[i]->c == s)
                {
                    return childs[i];
                }
            }
            return nullptr;
        }
    };

    Node *root;

    void GetStrings(Node *current, std::vector<std::string> &strings)
    {
        if (current->childs.empty())
        {
            strings.push_back(current->str);
            return;
        }
        else
        {
            for (int i = 0; i < current->childs.size(); i++)
            {
                GetStrings(current->childs[i], strings);
            }
        }
    }

    void DestroyTrie(Node *current)
    {
        for (int i = 0; i < current->childs.size(); i++)
        {
            DestroyTrie(current->childs[i]);
        }
        delete current;
    }

public:
    Trie()
    {
        root = new Node();
    }
    ~Trie()
    {
        DestroyTrie(root);
    }

    void Add(std::string &str)
    {
        Node *current = root;
        for (int i = 0; i < str.size(); i++)
        {
            if (current->FindChild(str[i]) == nullptr)
            {
                Node *child = new Node();
                current->childs.push_back(child);
                child->c = str[i];
                current = child;
            }
            else
            {
                current = current->FindChild(str[i]);
            }
        }
        current->str = str;
    }

    void GetStrings(std::vector<std::string> &strings)
    {
        GetStrings(root, strings);
    }
};

void SortNumbersInStringsByNonDecreasing(std::vector<std::string> &strings)
{
    for (int i = 0; i < strings.size(); i++)
    {
        for (int j = i + 1; j < strings.size(); j++)
        {
            if (std::stoi(strings[i]) > std::stoi(strings[j]))
            {
                std::swap(strings[i], strings[j]);
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    std::cin >> N;
    std::map<std::string, std::vector<std::string>> pokemons;
    std::string str;
    std::string name;
    int amount;
    std::vector<std::string> numbers;
    std::vector<std::string> names;

    for (int i = 0; i < N; i++) // считывание и добавление в мэп
    {
        std::cin >> name;
        std::cin >> amount;
        for (int j = 0; j < amount; j++)
        {
            std::cin >> str;
            numbers.push_back(str);
        }
        std::map<std::string, std::vector<std::string>>::iterator it = pokemons.find(name);
        if (it != pokemons.end())
        {
            for (int k = 0; k < numbers.size(); k++)
            {
                it->second.push_back(numbers[k]);
            }
        }
        else
        {
            pokemons.emplace(name, numbers);
            names.push_back(name);
        }
        numbers.clear();
    }

    for (int i = 0; i < names.size(); i++) // меняем порядок всех строк на противоположный
    {
        Trie trie;
        std::map<std::string, std::vector<std::string>>::iterator it = pokemons.find(names[i]);

        for (int j = 0; j < it->second.size(); j++)
        {
            std::reverse(it->second[j].begin(), it->second[j].end());
        }

        for (int j = 0; j < it->second.size(); j++)
        {
            trie.Add(it->second[j]);
        }

        it->second.clear();
        trie.GetStrings(it->second);

        for (int j = 0; j < it->second.size(); j++)
        {
            std::reverse(it->second[j].begin(), it->second[j].end());
        }

        SortNumbersInStringsByNonDecreasing(it->second);
    }

    std::sort(names.begin(), names.end());
    std::cout << names.size() << '\n';

    for (int i = 0; i < names.size(); i++)
    {
        std::map<std::string, std::vector<std::string>>::iterator it = pokemons.find(names[i]);
        std::cout << it->first << " ";
        std::cout << it->second.size() << " ";
        for (int j = 0; j < it->second.size(); j++)
        {
            std::cout << it->second[j] << " ";
        }
        std::cout << '\n';
    }

    return 0;
}