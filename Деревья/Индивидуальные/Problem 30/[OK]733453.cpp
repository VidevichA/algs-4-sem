#include <fstream>
#include <vector>
#include <iostream>

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
        destroyNode(root);
    }
    void insert(int val)
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
    void deleteNode(int val)
    {
        if (root == nullptr)
        {
            return;
        }
        root = deleteNode(root, val);
    }
    void rlr(std::ofstream &out)
    {
        rlr(root, out);
    }
    void setHeights()
    {
        setHeights(root);
    }
    std::vector<int> findSuitableNodes()
    {
        std::vector<int> nodes;
        findSuitableNodes(root, nodes);
        return nodes;
    }

private:
    void findSuitableNodes(Node *node, std::vector<int> &v)
    {
        if (node == nullptr)
        {
            return;
        }
        findSuitableNodes(node->l, v);
        if (node->l == nullptr && node->r == nullptr)
        {
            return;
        }
        if (node->l == nullptr)
        {
            if (node->r->height + 1 == 2)
            {
                v.push_back(node->key);
            }
        }
        else if (node->r == nullptr)
        {
            if (node->l->height + 1 == 2)
            {
                v.push_back(node->key);
            }
        }
        else
        {
            if (abs(node->l->height - node->r->height) == 2)
            {
                v.push_back(node->key);
            }
        }
        findSuitableNodes(node->r, v);
    }
    void setHeights(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        setHeights(node->l);
        setHeights(node->r);
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
    Node *max(Node *node)
    {
        if (node->r == nullptr)
        {
            return node;
        }
        return max(node->r);
    }
    Node *deleteNode(Node *node, int val)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (val < node->key)
        {
            node->l = deleteNode(node->l, val);
            return node;
        }
        else if (val > node->key)
        {
            node->r = deleteNode(node->r, val);
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
        Node *maxNode = max(node->l);
        node->key = maxNode->key;
        node->l = deleteNode(node->l, maxNode->key);
        return node;
    }
    void rlr(Node *node, std::ofstream &out)
    {
        if (node == nullptr)
        {
            return;
        }
        out << node->key << '\n';
        rlr(node->l, out);
        rlr(node->r, out);
    }
    static void destroyNode(Node *node)
    {
        if (node)
        {
            destroyNode(node->l);
            destroyNode(node->r);
            delete node;
        }
    }
    Node *root = nullptr;
};

int main()
{
    std::ofstream out("tst.out");
    std::ifstream in("tst.in");
    Tree t;
    int temp;
    while (in >> temp)
    {
        t.insert(temp);
    }
    t.setHeights();
    auto v = t.findSuitableNodes();
    for (auto el : v)
    {
        std::cout << el << ' ';
    }
    if (v.size() % 2 == 1)
    {
        t.deleteNode(v[v.size() / 2]);
    }
    t.rlr(out);
    return 0;
}