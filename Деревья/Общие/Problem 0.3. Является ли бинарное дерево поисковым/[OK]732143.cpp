#include <fstream>
#include <vector>
#include <iostream>
#include <string>

class Node
{
public:
    Node(long long val) : val(val)
    {
    }
    long long val;
    Node *l = nullptr;
    Node *r = nullptr;
};

int main()
{
    std::ifstream in("bst.in");
    std::ofstream out("bst.out");
    std::string temp;
    long long size;
    in >> temp;
    size = std::stol(temp);
    in >> temp;
    long long root = std::stol(temp);
    if (size == 1)
    {
        out << "YES";
        return 0;
    }
    Node *tree = new Node(root);
    std::vector<Node *> nodes(size);
    std::vector<long long> f;
    std::vector<std::pair<long long, long long>> borders(size);
    borders[0] = std::make_pair(-9223372036854775807, 9223372036854775807);
    nodes[0] = tree;
    bool flag = true;
    for (long long i = 0; i < size - 1; ++i)
    {
        long long val;
        in >> val;
        long long n;
        in >> n;
        std::string side;
        in >> side;
        if (side == "L")
        {
            nodes[n - 1]->l = new Node(val);
            nodes[i + 1] = nodes[n - 1]->l;
            borders[i + 1] = std::make_pair(borders[n - 1].first, nodes[n - 1]->val - 1);
        }
        else
        {
            nodes[n - 1]->r = new Node(val);
            nodes[i + 1] = nodes[n - 1]->r;
            borders[i + 1] = std::make_pair(nodes[n - 1]->val, borders[n - 1].second);
        }
    }
    for (int i = 0; i < borders.size(); ++i)
    {
        if (nodes[i]->val > borders[i].second || nodes[i]->val < borders[i].first)
        {
            flag = false;
            break;
        }
    }
    out << (flag ? "YES" : "NO");
    return 0;
}