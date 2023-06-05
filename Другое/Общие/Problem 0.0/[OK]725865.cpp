#include <iostream>
#include <fstream>

class Node
{
public:
    explicit Node(long long key) : key_(key){};
    long long key_;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
};

class BST
{
public:
    BST() : root_(nullptr) {}

    long long sum() const
    {
        return sum_;
    }

    bool insert(long long val);

    void preOrderTraversal();

private:
    Node *root_;

    long long sum_ = 0;

    void preOrderTraversal(Node *node);
};

void BST::preOrderTraversal()
{
    preOrderTraversal(root_);
}

void BST::preOrderTraversal(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    sum_ += node->key_;
    preOrderTraversal(node->left_);
    preOrderTraversal(node->right_);
}

bool BST::insert(long long val)
{
    auto w = new Node(val);
    if (root_ == nullptr)
    {
        root_ = w;
        return true;
    }
    auto current = root_;
    while (true)
    {
        if (val < current->key_)
        {
            if (current->left_ == nullptr)
            {
                current->left_ = w;
                return true;
            }
            else
            {
                current = current->left_;
            }
        }
        else if (val > current->key_)
        {
            if (current->right_ == nullptr)
            {
                current->right_ = w;
                return true;
            }
            else
            {
                current = current->right_;
            }
        }
        else
        {
            delete w;
            return false;
        }
    }
}

int main()
{
    BST tree;
    std::ifstream fin("../common/0.0/input.txt");
    std::ofstream ofStream("../common/0.0/output.txt");
    std::string line;
    while (getline(fin, line))
    {
        tree.insert(stoi(line));
    }
    fin.close();
    tree.preOrderTraversal();
    ofStream << tree.sum();
    return 0;
}