#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

std::ofstream out("out.txt");
std::vector<int> deeps;
std::vector<int> currentKeys;

struct Node
{
    int value;
    Node *right;
    Node *left;
    int deep;
    int numberR = 0;
    int numberL = 0;
};

Node *minNode(Node *node)
{
    if (node->left == nullptr)
    {
        return node;
    }
    return minNode(node->left);
}

Node *del(Node *node, int val)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (val < node->value)
    {
        node->left = del(node->left, val);
        return node;
    }
    else if (val > node->value)
    {
        node->right = del(node->right, val);
        return node;
    }
    else if (node->left == nullptr)
    {
        return node->right;
    }
    if (node->right == nullptr)
    {
        return node->left;
    }
    Node *min = minNode(node->right);
    node->value = min->value;
    node->right = del(node->right, min->value);
    return node;
}

void dlb(Node *&head)
{
    if (!head)
    {
        return;
    }
    else
    {
        out << head->value << "\n";
        dlb(head->left);
        dlb(head->right);
    }
}

void add(int data, Node *&head, int deep)
{
    if (!head)
    {
        head = new Node;
        head->value = data;
        head->left = 0;
        head->right = 0;
        head->deep = deep;
        deeps.push_back(deep);
        return;
    }
    else
    {
        if (head->value > data)
        {
            head->numberL += 1;
            add(data, head->left, deep + 1);
        }
        if (head->value < data)
        {
            head->numberR += 1;
            add(data, head->right, deep + 1);
        }
    }
}

void findNodes(Node *head, int deep)
{
    if (!head)
    {
        return;
    }
    if (head->deep == deep)
    {
        if (head->numberL > head->numberR)
        {
            currentKeys.push_back(head->value);
            return;
        }
        // std::cout << head->numberL << " " << head->numberR << std::endl;
    }
    else
    {
        findNodes(head->left, deep);
        findNodes(head->right, deep);
        return;
    }
}

int main()
{
    std::ifstream in("in.txt");

    Node *root = 0;

    int tmp;
    int tmpDeep = 0;

    std::vector<int> hights;

    while (in >> tmp)
    {
        add(tmp, root, tmpDeep);
    }

    int hight = deeps[0];

    for (int &item : deeps)
    {
        hight = hight < item ? item : hight;
    }

    int currentDeep = hight - std::floor(hight / 2);

    findNodes(root, currentDeep);

    if (currentKeys.size() % 2 == 0)
    {
        dlb(root);
        return 0;
    }
    else
    {
        std::sort(currentKeys.begin(), currentKeys.end());
        root = del(root, currentKeys[std::floor(currentKeys.size() / 2)]);
        dlb(root);
    }
}