#include <iostream>
#include <fstream>

template <class T>
class Node
{
public:
    explicit Node(T key) : key_(key), height_(0), msl_(0){};
    T key_;
    int height_;
    int msl_;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
};

template <typename T>
class BST
{
public:
    BST() : root_(nullptr), msl_root_(nullptr), msl_(0) {}

    bool insert(T val);

    bool search(T val) const;

    void remove(T val);

    void postOrderTraversal();

    void preOrderTraversal(std::ofstream &file);

    void findMinRoot();

    int msl();

    void dfs();

private:
    Node<T> *root_;

    Node<T> *msl_root_;
    int msl_;

    int count_left = 0;
    int count_right = 0;

    void findMinRoot(Node<T> *);

    Node<T> *dfs(Node<T> *node);

    void markHeightAndMSL(Node<T> *node)
    {
        if (node->left_ == nullptr)
        {
            if (node->right_ == nullptr)
            {
                node->height_ = 0;
                node->msl_ = 0;
            }
            else
            {
                node->height_ = node->right_->height_ + 1;
                node->msl_ = node->right_->height_ + 1;
            }
        }
        else if (node->right_ == nullptr)
        {
            node->height_ = node->left_->height_ + 1;
            node->msl_ = node->left_->height_ + 1;
        }
        else
        {
            node->height_ = std::max(node->left_->height_, node->right_->height_) + 1;
            node->msl_ = node->left_->height_ + node->right_->height_ + 2;
        }
        if (msl_ < node->msl_)
        {
            msl_ = node->msl_;
        }
    }

    void postOrderTraversal(Node<T> *node);

    void preOrderTraversal(Node<T> *node, std::ofstream &file);

    void replaceChild(Node<T> *parent, Node<T> *old, Node<T> *new_child)
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

template <typename T>
void BST<T>::preOrderTraversal(std::ofstream &file)
{
    preOrderTraversal(root_, file);
}

template <typename T>
Node<T> *BST<T>::dfs(Node<T> *node)
{
    if (node->height_ == 1)
    {
        if (node->left_ == nullptr)
        {
            if (count_left == msl_ / 2)
            {
                return node;
            }
            return node->right_;
        }
        else
        {
            if (count_right == msl_ / 2)
            {
                return node;
            }
            return node->left_;
        }
    }

    if (node->left_ != nullptr)
    {
        if (node->left_->height_ + 1 == node->height_)
        {
            if (count_right == msl_ / 2)
            {
                return node;
            }
            count_right += 1;
            return dfs(node->left_);
        }
    }
    if (count_left == msl_ / 2)
    {
        return node;
    }
    count_left += 1;
    return dfs(node->right_);
}

template <typename T>
void BST<T>::dfs()
{
    if (msl_ % 2 == 1)
    {
        return;
    }
    Node<T> *v;
    if (msl_root_->left_ != nullptr)
    {
        if (msl_root_->right_ != nullptr)
        {
            if (msl_root_->height_ == msl_ / 2)
            {
                remove(msl_root_->key_);
                return;
            }
            else if (msl_root_->left_->height_ + 1 > msl_ / 2)
            {
                count_right = msl_root_->right_->height_ + 2;
                count_left = 1;
                v = dfs(msl_root_->left_);
            }
            else
            {
                count_left = msl_root_->left_->height_ + 2;
                count_right = 1;
                v = dfs(msl_root_->right_);
            }
        }
        else
        {
            count_right = 1;
            v = dfs(msl_root_->left_);
        }
    }
    else
    {
        count_left = 1;
        v = dfs(msl_root_->right_);
    }
    remove(v->key_);
}

template <typename T>
void BST<T>::findMinRoot()
{
    findMinRoot(root_);
}

template <class T>
void BST<T>::findMinRoot(Node<T> *node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->msl_ == msl_)
    {
        if (msl_root_ == nullptr)
        {
            msl_root_ = node;
        }
        else
        {
            if (node->key_ < msl_root_->key_)
            {
                msl_root_ = node;
            }
        }
    }
    findMinRoot(node->left_);
    findMinRoot(node->right_);
}

template <class T>
int BST<T>::msl()
{
    return msl_;
}

template <class T>
void BST<T>::postOrderTraversal(Node<T> *node)
{
    if (node == nullptr)
    {
        return;
    }
    postOrderTraversal(node->left_);
    postOrderTraversal(node->right_);
    markHeightAndMSL(node);
}

template <class T>
void BST<T>::preOrderTraversal(Node<T> *node, std::ofstream &file)
{
    if (node == nullptr)
    {
        return;
    }
    file << node->key_ << "\n";
    preOrderTraversal(node->left_, file);
    preOrderTraversal(node->right_, file);
}

template <class T>
void BST<T>::postOrderTraversal()
{
    postOrderTraversal(root_);
}

template <class T>
void BST<T>::remove(T val)
{
    Node<T> *parent;
    auto v = root_;
    while (true)
    {
        if (v == nullptr)
        {
            return;
        }
        if (val < v->key_)
        {
            parent = v;
            v = v->left_;
        }
        else if (val > v->key_)
        {
            parent = v;
            v = v->right_;
        }
        else
        {
            break;
        }
    }
    Node<T> *result;
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
        result = v;
        v->key_ = min_node->key_;
        replaceChild(min_node_parent, min_node, min_node->right_);
    }
    replaceChild(parent, v, result);
}

template <typename T>
bool BST<T>::search(T val) const
{
    Node<T> *current = root_;
    while (current != nullptr)
    {
        if (val == current->key_)
        {
            return true;
        }
        else if (val < current->key_)
        {
            current = current->left_;
        }
        else
        {
            current = current->right_;
        }
    }
    return false;
}

template <class T>
bool BST<T>::insert(T val)
{
    auto w = new Node<T>(val);
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
    BST<long long> tree;
    std::ifstream fin("individual/bst/33/input.txt");
    std::ofstream ofStream("individual/bst/33/output.txt");
    std::string line;
    while (getline(fin, line))
    {
        tree.insert(stoi(line));
    }
    fin.close();
    tree.postOrderTraversal();
    tree.findMinRoot();
    tree.dfs();
    tree.preOrderTraversal(ofStream);
    return 0;
}