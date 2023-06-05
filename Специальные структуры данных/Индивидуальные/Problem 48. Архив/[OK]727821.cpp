#include <fstream>
#include <random>
#include <chrono>

std::random_device device;
auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);

struct Node
{
    int key_;
    long long priority_;
    int size_;
    Node *left_;
    Node *right_;

    explicit Node(int key) : key_(key), left_(nullptr), right_(nullptr), size_(1)
    {
        mt.seed(device());
        std::uniform_int_distribution<int> range(0, INT32_MAX);
        priority_ = range(mt);
    }
};

int size(Node *n)
{
    return (n != nullptr) ? n->size_ : 0;
}

void update_size(Node *n)
{
    if (n != nullptr)
    {
        n->size_ = size(n->left_) + size(n->right_) + 1;
    }
}

Node *merge(Node *left, Node *right)
{
    if (left == nullptr || right == nullptr)
    {
        return (left != nullptr) ? left : right;
    }

    if (left->priority_ > right->priority_)
    {
        left->right_ = merge(left->right_, right);
        update_size(left);
        return left;
    }
    else
    {
        right->left_ = merge(left, right->left_);
        update_size(right);
        return right;
    }
}

std::pair<Node *, Node *> split(Node *current, int k)
{
    if (current == nullptr)
    {
        return {nullptr, nullptr};
    }

    int current_pos = size(current->left_) + 1;

    if (current_pos <= k)
    {
        auto p = split(current->right_, k - current_pos);
        current->right_ = p.first;
        update_size(current);
        return {current, p.second};
    }
    else
    {
        auto p = split(current->left_, k);
        current->left_ = p.second;
        update_size(current);
        return {p.first, current};
    }
}

Node *build_tree(int n)
{
    Node *root = nullptr;
    for (int i = 1; i <= n; i++)
    {
        root = merge(root, new Node(i));
    }
    return root;
}

void print_inorder(Node *current, std::ofstream &ofStream)
{
    if (current == nullptr)
    {
        return;
    }
    print_inorder(current->left_, ofStream);
    ofStream << current->key_ << " ";
    print_inorder(current->right_, ofStream);
}

int main()
{
    std::ifstream fin("individual/data_structure/48_archive/archive.in");
    std::ofstream ofStream("individual/data_structure/48_archive/archive.out");
    int n, q;
    fin >> n >> q;

    Node *root = build_tree(n);

    int a, b;
    for (int i = 0; i < q; i++)
    {
        fin >> a >> b;
        auto p1 = split(root, b);
        auto p2 = split(p1.first, a - 1);
        root = merge(p2.second, merge(p2.first, p1.second));
    }
    print_inorder(root, ofStream);

    return 0;
}