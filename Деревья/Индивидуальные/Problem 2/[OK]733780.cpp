#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>

typedef long long number;

class Dsu
{
public:
    Dsu()
    {
    }
    void MakeSet(number rootVal)
    {
        if (parents.size() <= rootVal + 1)
        {
            parents.resize(rootVal + 1);
        }
        if (rank.size() <= rootVal + 1)
        {
            rank.resize(rootVal + 1);
        }
        parents[rootVal] = rootVal;
        rank[rootVal] = 0;
        ++size;
    }
    number FindParent(int val)
    {
        if (parents.size() <= val)
        {
            return 0;
        }
        if (val == parents[val])
        {
            return val;
        }
        return parents[val] = FindParent(parents[val]);
    }
    void MergeSets(int a, int b)
    {
        a = FindParent(a);
        b = FindParent(b);
        if (a == b)
        {
            return;
        }
        if (rank[a] < rank[b])
        {
            parents[a] = b;
        }
        else
        {
            parents[b] = a;
            if (rank[a] == rank[b])
            {
                ++rank[a];
            }
        }
        --size;
    }
    number GetSize()
    {
        return size;
    }

private:
    std::vector<number> parents;
    std::vector<number> rank;
    number size = 0;
};

template <typename T>
void PrintVector(const std::vector<T> &v)
{
    std::cout << '\n';
    for (auto el : v)
    {
        std::cout << el << ' ';
    }
    std::cout << '\n';
}

template <typename T>
void PrintMatrix(const std::vector<std::vector<T>> &m)
{
    std::cout << '\n';
    for (auto r : m)
    {
        for (auto c : r)
        {
            std::cout << c << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

class Node
{
public:
    Node(int key) : key(key)
    {
    }
    int key;
    Node *r = nullptr;
    Node *l = nullptr;
    int height = -1;
};

class Tree
{
public:
    Tree()
    {
    }
    ~Tree()
    {
        DestroyNode(root);
    }
    void Insert(int val)
    {
        Node **cur = &root;
        while (*cur)
        {
            Node &node = **cur;
            if (val < node.key)
            {
                cur = &node.l;
            }
            else if (val > node.key)
            {
                cur = &node.r;
            }
            else
            {
                return;
            }
        }
        *cur = new Node(val);
    }
    void DeleteNode(int val)
    {
        if (root == nullptr)
        {
            return;
        }
        root = Delete(root, val);
    }
    void Detour(std::ofstream &out)
    {
        Detour(root, out);
    }
    void SetHeights()
    {
        SetHeights(root);
    }
    std::vector<int> findSuitableNodes()
    {
        std::vector<int> nodes;
        FindSuitableNodes(root, nodes);
        return nodes;
    }

private:
    void FindSuitableNodes(Node *node, std::vector<int> &v)
    {
        if (node == nullptr)
        {
            return;
        }
        FindSuitableNodes(node->l, v);
        if (node->l == nullptr && node->r == nullptr)
        {
            return;
        }
        if (node->l == nullptr)
        {
            if (node->r->height != -1)
            {
                v.push_back(node->key);
            }
        }
        else if (node->r == nullptr)
        {
            if (node->l->height != -1)
            {
                v.push_back(node->key);
            }
        }
        else
        {
            if (node->l->height - node->r->height != 0)
            {
                v.push_back(node->key);
            }
        }
        FindSuitableNodes(node->r, v);
    }
    void SetHeights(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        SetHeights(node->l);
        SetHeights(node->r);
        if (node->l == nullptr && node->r == nullptr)
        {
            node->height = 0;
        }
        else if (node->l == nullptr)
        {
            node->height = 1 + node->r->height;
        }
        else if (node->r == nullptr)
        {
            node->height = 1 + node->l->height;
        }
        else
        {
            node->height = 1 + std::max(node->l->height, node->r->height);
        }
    }
    Node *Min(Node *node)
    {
        if (node->l == nullptr)
        {
            return node;
        }
        return Min(node->l);
    }
    Node *Delete(Node *node, int val)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (val < node->key)
        {
            node->l = Delete(node->l, val);
            return node;
        }
        else if (val > node->key)
        {
            node->r = Delete(node->r, val);
            return node;
        }
        else if (node->l == nullptr)
        {
            return node->r;
        }
        if (node->r == nullptr)
        {
            return node->l;
        }
        Node *min = Min(node->r);
        node->key = min->key;
        node->r = Delete(node->r, min->key);
        return node;
    }
    void Detour(Node *node, std::ofstream &out)
    {
        if (node == nullptr)
        {
            return;
        }
        out << node->key << '\n';
        Detour(node->l, out);
        Detour(node->r, out);
    }
    static void DestroyNode(Node *node)
    {
        if (node)
        {
            DestroyNode(node->l);
            DestroyNode(node->r);
            delete node;
        }
    }
    Node *root = nullptr;
};

int main()
{
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    Tree t;
    number temp;
    while (in >> temp)
    {
        t.Insert(temp);
    }
    t.SetHeights();
    auto v = t.findSuitableNodes();
    if (v.size() % 2 != 0)
    {
        t.DeleteNode(v[v.size() / 2]);
    }
    t.Detour(out);
    return 0;
}