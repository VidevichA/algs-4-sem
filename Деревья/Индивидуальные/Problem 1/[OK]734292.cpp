#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

std::ofstream out("out.txt");

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

std::vector<Node *> daddiesL;
std::vector<Node *> daddiesR;

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

void add(int data, Node *&head)
{
    if (!head)
    {
        head = new Node;
        head->value = data;
        head->left = 0;
        head->right = 0;
        for (int i = 0; i < daddiesL.size(); i++)
        {
            daddiesL[i]->numberL += 1;
        }
        for (int i = 0; i < daddiesR.size(); i++)
        {
            daddiesR[i]->numberR += 1;
        }
        return;
    }
    else
    {
        if (head->value > data)
        {
            daddiesL.push_back(head);
            add(data, head->left);
        }
        if (head->value < data)
        {
            daddiesR.push_back(head);
            add(data, head->right);
        }
    }
}

void findNodes(Node *head)
{
    if (!head)
    {
        return;
    }
    if (head->numberL != head->numberR)
    {
        currentKeys.push_back(head->value);
    }
    findNodes(head->left);
    findNodes(head->right);
    return;
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
        daddiesL.clear();
        daddiesR.clear();
        add(tmp, root);
    }

    findNodes(root);

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