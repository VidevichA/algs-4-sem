#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    int value;
    int numberOfChildren = 0;
    bool isLeftChild = true;
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    Node(int _value) : value(_value){};
    static int findMin(Node *root)
    {
        Node *cur = root;
        while (cur)
        {
            root = cur;
            cur = cur->right;
        }
        return root->value;
    }
    static Node *insert(Node *root, int value)
    {
        if (root == nullptr)
            return new Node(value);
        if (value < root->value)
            root->left = insert(root->left, value);
        if (value > root->value)
            root->right = insert(root->right, value);
        return root;
    };
    static Node *deleteNode(Node *root, int value)
    {
        if (root == nullptr)
            return nullptr;
        if (value < root->value)
        {
            root->left = deleteNode(root->left, value);
            return root;
        }
        else if (value > root->value)
        {
            root->right = deleteNode(root->right, value);
            return root;
        }
        if (root->right == nullptr)
            return root->left;
        if (root->left == nullptr)
            return root->right;
        value = findMin(root->left);
        root->value = value;
        root->left = deleteNode(root->left, value);
        return root;
    };
    static int countNodes(Node *node)
    {
        node->numberOfChildren = 1;
        if (node->left != nullptr)
        {
            node->numberOfChildren += countNodes(node->left);
            node->left->isLeftChild = true;
            node->left->parent = node;
        }
        if (node->right != nullptr)
        {
            node->numberOfChildren += countNodes(node->right);
            node->right->isLeftChild = false;
            node->right->parent = node;
        }
        return node->numberOfChildren;
    };
    void print(ostream &os)
    {
        os << value << endl;
        if (left != nullptr)
            left->print(os);
        if (right != nullptr)
            right->print(os);
    };
};

bool checkStructure(Node *node1, Node *node2)
{
    if (node1 == nullptr || node2 == nullptr)
    {
        if (node1 == nullptr && node2 == nullptr)
            return true;
        return false;
    }
    bool l = checkStructure(node1->left, node2->left);
    bool r = checkStructure(node1->right, node2->right);
    return l & r;
};

int getChildren(Node *node)
{
    if (node == nullptr)
        return -1;
    return node->numberOfChildren;
}

Node *findNode(Node *node1, Node *node2)
{
    if (node2 == nullptr)
        return node1;
    int l1, l2, r1, r2;
    l1 = getChildren(node1->left);
    l2 = getChildren(node2->left);
    r1 = getChildren(node1->right);
    r2 = getChildren(node2->right);
    if (l1 == l2 && r1 != -1)
        return findNode(node1->right, node2->right);
    if (r1 == r2 && l1 != -1)
        return findNode(node1->left, node2->left);
    return node1;
};

Node *tryLeftDelete(Node *node)
{
    Node *parent, *curr;
    parent = node->parent;
    curr = node;
    while (parent && !curr->isLeftChild)
    {
        curr = parent;
        parent = parent->parent;
    }
    if (parent)
    {
        if (curr->isLeftChild && parent->right)
            curr = parent;
        else if (parent->isLeftChild && parent->parent && parent->parent->right)
            curr = parent->parent;
    }
    if (curr->value > node->value)
        return curr;
    return node;
}

Node *leftChildDelete(Node *node)
{
    Node *parent = node->parent;
    while (parent && parent->right == nullptr)
    {
        node = parent;
        parent = parent->parent;
    }
    parent = tryLeftDelete(node);
    if (parent->value > node->value)
        return parent;
    return node;
}

Node *deleteMaxNode(Node *node)
{
    Node *parent;
    bool isLeaf = node->left == nullptr && node->right == nullptr;
    if (isLeaf)
    {
        if (node->isLeftChild)
            return leftChildDelete(node);
        return tryLeftDelete(node);
    }
    if (node->isLeftChild)
    {
        if (node->right)
            return node;
        return leftChildDelete(node);
    }
    return tryLeftDelete(node);
}

class Tree
{
    Node *root = nullptr;

public:
    void insert(int value)
    {
        if (root == nullptr)
            root = new Node(value);
        else
            root = Node::insert(root, value);
    }
    void deleteNode(int value)
    {
        if (root == nullptr)
            return;
        root = Node::deleteNode(root, value);
    }
    void print(ostream &os)
    {
        if (root != nullptr)
            root->print(os);
    }
    int countNodes()
    {
        if (root == nullptr)
            return 0;
        return Node::countNodes(root);
    }
    friend Node *findNode(Tree &t1, Tree &t2)
    {
        return findNode(t1.root, t2.root);
    }
    friend bool checkStructure(Tree &t1, Tree &t2)
    {
        return checkStructure(t1.root, t2.root);
    }
};

int main()
{
    Tree t, t2, temp;
    ifstream fin("tst.in");
    ofstream fout("tst.out");

    string str;
    fin >> str;
    while (str[0] != '*')
    {
        t.insert(stoi(str));
        fin >> str;
    }
    fin >> str;
    while (!fin.eof())
    {
        t2.insert(stoi(str));
        fin >> str;
    }
    t2.insert(stoi(str));
    fin.close();
    int nodesInFirst, nodesInSecond;
    nodesInFirst = t.countNodes();
    nodesInSecond = t2.countNodes();
    if (nodesInFirst < nodesInSecond)
    {
        nodesInFirst ^= nodesInSecond;
        nodesInSecond ^= nodesInFirst;
        nodesInFirst ^= nodesInSecond;
        temp = t;
        t = t2;
        t2 = temp;
    }
    if (nodesInFirst - nodesInSecond > 1 || nodesInFirst == nodesInSecond)
    {
        fout << "NO\n";
        fout.close();
        return 0;
    }
    Node *wrongNode = findNode(t, t2);
    wrongNode = deleteMaxNode(wrongNode);
    int value = wrongNode->value;
    wrongNode = nullptr;
    t.deleteNode(value);
    if (checkStructure(t, t2))
        fout << "YES\n"
             << value;
    else
        fout << "NO\n";
    fout.close();
    return 0;
}