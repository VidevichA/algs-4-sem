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

    bool insert(long long val)
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

    void preOrderTraversal(std::ofstream &ofStream)
    {
        preOrderTraversal(root_, ofStream);
    }

    void remove(long long val)
    {
        Node *parent = nullptr;
        auto v = root_;
        while (v != nullptr && v->key_ != val)
        {
            parent = v;
            if (val < v->key_)
            {
                v = v->left_;
            }
            else
            {
                v = v->right_;
            }
        }
        if (v == nullptr)
        {
            return;
        }
        Node *result = nullptr;
        if (v->left_ == nullptr)
        {
            result = v->right_;
        }
        else if (v->right_ == nullptr)
        {
            result = v->left_;
        }
        else
        {
            auto min_node_parent = v;
            auto min_node = v->right_;
            while (min_node->left_ != nullptr)
            {
                min_node_parent = min_node;
                min_node = min_node->left_;
            }
            if (min_node_parent != v)
            {
                min_node_parent->left_ = min_node->right_;
                min_node->right_ = v->right_;
            }
            min_node->left_ = v->left_;
            result = min_node;
        }
        if (parent == nullptr)
        {
            root_ = result;
        }
        else if (parent->left_ == v)
        {
            parent->left_ = result;
        }
        else
        {
            parent->right_ = result;
        }
        delete v;
    }

private:
    Node *root_;

    void preOrderTraversal(Node *node, std::ofstream &ofStream)
    {
        if (node == nullptr)
        {
            return;
        }
        ofStream << node->key_ << "\n";
        preOrderTraversal(node->left_, ofStream);
        preOrderTraversal(node->right_, ofStream);
    }

    void replaceChild(Node *parent, Node *old, Node *new_child)
    {
        if (parent == nullptr)
        {
            root_ = new_child;
        }
        else if (parent->left_ == old)
        {
            parent->left_ = new_child;
        }
        else if (parent->right_ == old)
        {
            parent->right_ = new_child;
        }
    }
};

int main()
{
    BST tree;
    std::ifstream fin("common/trees/build_tree/input.txt");
    std::ofstream ofStream("common/trees/build_tree/output.txt");
    std::string line;
    getline(fin, line);
    long long key = stoi(line);
    getline(fin, line);
    while (getline(fin, line))
    {
        tree.insert(stoi(line));
    }
    fin.close();
    tree.remove(key);
    tree.preOrderTraversal(ofStream);
    return 0;
}