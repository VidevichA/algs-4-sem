#include <fstream>
#include <iostream>
#include <algorithm>

long long m_node1 = -1;
long long m_node2 = 1e10 + 7;
long long del = 0;
long long max(long long a, long long b) { return a > b ? a : b; }

std::ofstream out("out.txt");
std::ifstream in("in.txt");

class Node
{
public:
    Node(long long &_data, Node *lPtr = nullptr, Node *rPtr = nullptr)
        : data(_data), left(lPtr), right(rPtr){};
    ~Node() = default;
    long long data;
    Node *left;
    Node *right;
    int hei = 0;
    int maxlength = 0;
    int minimum1 = 0;
    int minimum2 = 0;
    int leftlevel = 0;
    int rightlevel = 0;
    void print()
    {
        std::cout << data << "\n";
    }
};

class BTree
{
public:
    Node *root;
    BTree() : root(nullptr) {}
    BTree(long long &key) : root(new Node(key)) {}
    ~BTree() { deleteTree(root); }

    void deleteTree(Node *root)
    {
        if (root != nullptr)
        {
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
        else
            return;
    }

    void print()
    {
        if (root != nullptr)
        {
            print(root);
        }
    }
    void print(Node *root)
    {
        if (root != nullptr)
        {
            out << root->data << "\n";
            print(root->left);
            print(root->right);
        }
        else
            return;
    }
    void add(long long &data)
    {
        if (root == nullptr)
        {
            Node *newRoot = new Node(data);
            root = newRoot;
        }
        Node *pr = nullptr;
        Node *temp = root;
        int weigh = 0;
        while (temp != nullptr)
        {
            pr = temp;
            weigh = data - temp->data;
            if (weigh > 0)
            {
                temp = temp->right;
            }
            else if (weigh < 0)
            {
                temp = temp->left;
            }
            else if (weigh == 0)
            {
                return;
            }
        }
        if (weigh > 0)
        {
            pr->right = new Node(data);
        }
        else
        {
            pr->left = new Node(data);
        }
    }

    int height(Node *node)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            node->hei = 0;
        }
        else if (node->right == nullptr)
        {
            node->hei = height(node->left) + 1;
        }
        else if (node->left == nullptr)
        {
            node->hei = height(node->right) + 1;
        }
        else
        {
            node->hei = max(height(node->right), height(node->left)) + 1;
        }
        return node->hei;
    }

    void findMax(Node *node, int root)
    {
        if (node == nullptr)
            return;
        if ((node->left == nullptr || node->right == nullptr) && node->data != root)
        {
            node->maxlength = 0;
        }
        else if (node->data == root)
        {
            if (node->left == nullptr)
                node->maxlength = node->right->hei + 1;
            else if (node->right == nullptr)
                node->maxlength = node->left->hei + 1;
            else
                node->maxlength = node->left->hei + node->right->hei + 2;
        }
        else
        {
            node->maxlength = node->right->hei + node->left->hei + 2;
        }
        if (node->maxlength > m_node1)
            m_node1 = node->maxlength;
        findMax(node->left, root);
        findMax(node->right, root);
    }

    Node *erase(Node *root, long long &key)
    {
        Node *temp = nullptr;
        if (root == nullptr)
        {
            return nullptr;
        }
        else if (key < root->data)
        {
            root->left = erase(root->left, key);
        }
        else if (key > root->data)
        {
            root->right = erase(root->right, key);
        }
        else
        {
            temp = root;
            if (root->left == nullptr)
            {
                temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                temp = root->left;
                delete root;
                return temp;
            }
            Node *tempKids = findEdgeLeft(root->right);
            root->data = tempKids->data;
            root->right = erase(root->right, tempKids->data);
        }
        return root;
    }
    Node *findEdgeLeft(Node *root)
    {
        Node *current = root;
        while (current != nullptr && current->left != nullptr)
            current = current->left;
        return current;
    }
    void findMaxSemiPathNode(Node *node, int key)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            node->minimum1 = node->data;
            node->minimum2 = node->data;
        }
        else if (node->left == nullptr)
        {
            findMaxSemiPathNode(node->right, key);
            if (node->right->leftlevel > node->right->rightlevel)
            {
                node->minimum1 = node->right->minimum1;
                node->minimum2 = node->right->minimum1;
            }
            else if (node->right->leftlevel < node->right->rightlevel)
            {
                node->minimum1 = node->right->minimum2;
                node->minimum2 = node->right->minimum2;
            }
            else
            {
                node->minimum1 = std::min(node->right->minimum1, node->right->minimum2);
                node->minimum2 = std::min(node->right->minimum1, node->right->minimum2);
            }
            node->rightlevel = max(node->right->leftlevel, node->right->rightlevel) + 1;
            node->leftlevel = max(node->right->leftlevel, node->right->rightlevel) + 1;
        }
        else if (node->right == nullptr)
        {
            findMaxSemiPathNode(node->left, key);
            if (node->left->leftlevel > node->left->rightlevel)
            {
                node->minimum1 = node->left->minimum1;
                node->minimum2 = node->left->minimum1;
            }
            else if (node->left->leftlevel < node->left->rightlevel)
            {
                node->minimum1 = node->left->minimum2;
                node->minimum2 = node->left->minimum2;
            }
            else
            {
                node->minimum1 = std::min(node->left->minimum1, node->left->minimum2);
                node->minimum2 = std::min(node->left->minimum1, node->left->minimum2);
            }
            node->leftlevel = max(node->left->leftlevel, node->left->rightlevel) + 1;
            node->rightlevel = max(node->left->leftlevel, node->left->rightlevel) + 1;
        }
        else
        {
            findMaxSemiPathNode(node->left, key);
            findMaxSemiPathNode(node->right, key);
            if (node->left->leftlevel > node->left->rightlevel)
            {
                node->leftlevel = node->left->leftlevel + 1;
                node->minimum1 = node->left->minimum1;
            }
            else if (node->left->leftlevel < node->left->rightlevel)
            {
                node->leftlevel = node->left->rightlevel + 1;
                node->minimum1 = node->left->minimum2;
            }
            else
            {
                node->leftlevel = node->left->leftlevel + 1;
                node->minimum1 = std::min(node->left->minimum1, node->left->minimum2);
            }
            if (node->right->leftlevel > node->right->rightlevel)
            {
                node->rightlevel = node->right->leftlevel + 1;
                node->minimum2 = node->right->minimum1;
            }
            else if (node->right->leftlevel < node->right->rightlevel)
            {
                node->rightlevel = node->right->rightlevel + 1;
                node->minimum2 = node->right->minimum2;
            }
            else
            {
                node->rightlevel = node->right->leftlevel + 1;
                node->minimum2 = std::min(node->right->minimum1, node->right->minimum2);
            }
        }
        if (node->data == key && node->minimum1 == node->minimum2)
            node->minimum1 = node->data;
        if (node->maxlength == m_node1)
        {
            if (node->minimum1 + node->minimum2 < m_node2)
            {
                m_node2 = node->minimum1 + node->minimum2;
                del = node->data;
            }
        }
    }
};

int main()
{
    BTree MyTree = *(new BTree());
    long long key;
    while (in >> key)
    {
        MyTree.add(key);
    }
    MyTree.height(MyTree.root);
    MyTree.findMax(MyTree.root, MyTree.root->data);
    MyTree.findMaxSemiPathNode(MyTree.root, MyTree.root->data);

    if (del != (MyTree.root->data))
    {
        MyTree.erase(MyTree.root, del);
    }
    else
    {
        if (MyTree.root->left == nullptr)
        {
            MyTree.root = MyTree.root->right;
        }
        else if (MyTree.root->right == nullptr)
        {
            MyTree.root = MyTree.root->left;
        }
        else
        {
            Node *curr = MyTree.root->right;
            while (curr->left != nullptr)
            {
                curr = curr->left;
            }
            MyTree.root->data = curr->data;
            MyTree.erase(MyTree.root, curr->data);
        }
    }
    MyTree.print();
    return 0;
}