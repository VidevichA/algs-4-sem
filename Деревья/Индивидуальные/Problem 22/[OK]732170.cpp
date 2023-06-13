#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin("in.txt");
std::ofstream out("out.txt");

std::vector<int> vertices;

struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    int height;
    int nv;

    TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

class Tree
{
private:
    TreeNode *root;

public:
    Tree() : root(nullptr) {}

    void add(int value)
    {
        root = add(root, value);
    }

    void delete_node(int value)
    {
        root = delete_node(root, value);
    }

    void preOrder()
    {
        PreOrderLeft(root);
    }

    void Process()
    {
        FindVertices(root);
    }

    ~Tree()
    {
        DestroyNode(root);
    }

    void PreProcess()
    {
        FindHeightAndNumOfVertices(root);
    }

private:
    TreeNode *add(TreeNode *node, int value)
    {
        if (node == nullptr)
        {
            node = new TreeNode(value);
            return node;
        }
        if (value < node->value)
        {
            node->left = add(node->left, value);
        }
        else if (value > node->value)
        {
            node->right = add(node->right, value);
        }
        else
        {
            return node;
        }
        return node;
    }

    TreeNode *delete_node(TreeNode *node, int value)
    {
        if (node == nullptr)
        {
            return node;
        }
        else if (value < node->value)
        {
            node->left = delete_node(node->left, value);
        }
        else if (value > node->value)
        {
            node->right = delete_node(node->right, value);
        }
        else
        {
            if (node->right == nullptr && node->left == nullptr)
            {
                node = nullptr;
            }
            else if (node->right == nullptr)
            {
                TreeNode *temp = node;
                node = node->left;
                temp = nullptr;
            }
            else if (node->left == nullptr)
            {
                TreeNode *temp = node;
                node = node->right;
                temp = nullptr;
            }
            else
            {
                int min = FindMin(node->right)->value;
                node->value = min;
                node->right = delete_node(node->right, min);
            }
        }
        return node;
    }

    TreeNode *FindMin(TreeNode *node)
    {
        if (node->left == nullptr)
        {
            return node;
        }
        else
        {
            return FindMin(node->left);
        }
    }

    void PreOrderLeft(TreeNode *node)
    {
        if (node != nullptr)
        {
            out << node->value << "\n";
            PreOrderLeft(node->left);
            PreOrderLeft(node->right);
        }
    }

    void FindVertices(TreeNode *node)
    {
        if (node != nullptr)
        {
            FindVertices(node->left);
            Process(node);
            FindVertices(node->right);
        }
    }

    void FindHeightAndNumOfVertices(TreeNode *node)
    {
        if (node != nullptr)
        {
            FindHeightAndNumOfVertices(node->left);
            FindHeightAndNumOfVertices(node->right);
            node->nv = CountNV(node);
            node->height = CountHeight(node);
            // std::cout << "val: " << node->value <<" height: " << node->height << " nv: " << node->nv << "\n";
        }
    }

    int CountNV(TreeNode *node)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            return 1;
        }
        else if (node->left == nullptr)
        {
            return node->right->nv + 1;
        }
        else if (node->right == nullptr)
        {
            return node->left->nv + 1;
        }
        else
        {
            return node->left->nv + node->right->nv + 1;
        }
    }

    int CountHeight(TreeNode *node)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            return 0;
        }
        else if (node->left == nullptr)
        {
            return node->right->height + 1;
        }
        else if (node->right == nullptr)
        {
            return node->left->height + 1;
        }
        else
        {
            return std::max(node->left->height, node->right->height) + 1;
        }
    }

    void Process(TreeNode *node)
    {
        if (node->left != nullptr && node->right != nullptr)
        {
            if (node->left->height != node->right->height && node->left->nv == node->right->nv)
            {
                vertices.push_back(node->value);
            }
        }
    }

    void DestroyNode(TreeNode *node)
    {
        if (node)
        {
            DestroyNode(node->left);
            DestroyNode(node->right);
            delete node;
        }
    }
};

int main()
{

    int num;
    Tree tree;
    while (!fin.eof())
    {
        fin >> num;
        tree.add(num);
    }
    tree.PreProcess();
    tree.Process();

    if (vertices.size() % 2 == 1)
    {
        tree.delete_node(vertices[(vertices.size() - 1) / 2]);
    }
    tree.preOrder();

    return 0;
}