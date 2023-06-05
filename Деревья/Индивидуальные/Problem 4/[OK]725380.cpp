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
    int depth = -1;
    int level = -1;
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
    int SetDepthsAndGetHeight()
    {
        int startDepth = -1;
        SetDepthsAndUpdateHeight(root, startDepth);
        return height;
    }
    void SetLevels()
    {
        SetLevels(root);
    }
    void FindNodes()
    {
        FindNodes(root, height / 2);
    }
    std::vector<int> GetSuitableKeys()
    {
        std::vector<int> keys;
        for (int i = 0; i < suitableNodes.size(); ++i)
        {
            keys.push_back(suitableNodes[i]->key);
        }
        return keys;
    }
    void Delete(int val)
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

private:
    void SetDepthsAndUpdateHeight(Node *node, int prevDepth)
    {
        if (node == nullptr)
        {
            return;
        }
        node->depth = prevDepth + 1;
        if (node->depth > height)
        {
            height = node->depth;
        }
        SetDepthsAndUpdateHeight(node->l, prevDepth + 1);
        SetDepthsAndUpdateHeight(node->r, prevDepth + 1);
    }
    void SetLevels(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        node->level = height - node->depth;
        SetLevels(node->l);
        SetLevels(node->r);
    }
    void FindNodes(Node *node, int heightToFind)
    {
        if (node == nullptr || node->level < heightToFind)
        {
            return;
        }
        if (node->level > heightToFind)
        {
            FindNodes(node->l, heightToFind);
            FindNodes(node->r, heightToFind);
        }
        if (node->level == heightToFind)
        {
            if (CountNodes(node->l) > CountNodes(node->r))
            {
                suitableNodes.push_back(node);
            }
        }
    }
    int CountNodes(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + CountNodes(node->r) + CountNodes(node->l);
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
    int height = 0;
    std::vector<Node *> suitableNodes;
};

int main()
{
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    Tree t;
    int temp;
    while (in >> temp)
    {
        t.Insert(temp);
    }
    t.SetDepthsAndGetHeight();
    t.SetLevels();
    t.FindNodes();
    std::vector<int> keys = t.GetSuitableKeys();
    if (keys.size() % 2 != 0)
    {
        t.Delete(keys[keys.size() / 2]);
    }
    t.Detour(out);
    return 0;
}