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
};

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    Tree t;
    int temp;
    while (in >> temp)
    {
        t.Insert(temp);
    }
    t.Detour(out);
    return 0;
}