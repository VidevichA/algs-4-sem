#include <fstream>

class Node
{
public:
    Node(int key) : key(key)
    {
    }
    int key;
    Node *r = nullptr;
    Node *l = nullptr;
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
    void Detour(std::ofstream &out)
    {
        Detour(root, out);
    }
    void Delete(int val)
    {
        if (root == nullptr)
        {
            return;
        }
        root = Delete(root, val);
    }

private:
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
};
int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int key;
    in >> key;
    Tree t;
    int temp;
    while (in >> temp)
    {
        t.Insert(temp);
    }
    t.Delete(key);
    t.Detour(out);
    return 0;
}