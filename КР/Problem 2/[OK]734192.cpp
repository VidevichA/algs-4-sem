#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Node
{
public:
    explicit Node(long long key) : key_(key){};
    long long key_;
    long long height_;
    bool interesting_ = false;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
};

class BST
{

private:
    Node *root_;
    std::vector<long long> nodes_;

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

    void postOrderTraversal()
    {
        postOrderTraversal(root_);
    }

    void markHeightAndMSL(Node *node)
    {
        if (node->left_ == nullptr)
        {
            if (node->right_ == nullptr)
            {
                node->height_ = 0;
            }
            else
            {
                node->height_ = node->right_->height_ + 1;
                node->interesting_ = true;
            }
        }
        else if (node->right_ == nullptr)
        {
            node->height_ = node->left_->height_ + 1;
            node->interesting_ = true;
        }
        else
        {
            node->height_ = std::max(node->left_->height_, node->right_->height_) + 1;
            if (node->left_->height_ != node->right_->height_)
            {
                node->interesting_ = true;
            }
        }
    }

    void postOrderTraversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        postOrderTraversal(node->left_);
        postOrderTraversal(node->right_);
        markHeightAndMSL(node);
    }

    void preOrderTraversal(std::ofstream &ofStream)
    {
        preOrderTraversal(root_, ofStream);
    }

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

    void findAverage()
    {
        findAverage(root_);
        if (nodes_.size() % 2 == 0)
        {
            return;
        }
        remove(nodes_[nodes_.size() / 2]);
    }

    void findAverage(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        findAverage(node->left_);
        if (node->interesting_)
        {
            nodes_.push_back(node->key_);
        }
        findAverage(node->right_);
    }
};

int main()
{
    std::ifstream fin("common/kr2/task1/in.txt");
    std::ofstream ofStream("common/kr2/task1/out.txt");
    BST tree;
    std::string line;
    while (getline(fin, line))
    {
        tree.insert(stoi(line));
    }
    tree.postOrderTraversal();
    tree.findAverage();
    tree.preOrderTraversal(ofStream);
    return 0;
};