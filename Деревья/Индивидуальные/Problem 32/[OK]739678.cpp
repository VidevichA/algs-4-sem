#include <iostream>
#include <fstream>
#include <vector>

class BinarySearchTree
{

private:
    class Node
    {
        ;

    public:
        Node(int value) : value(value) {}

        int value, height = 0, leaves_count = 1, largest_half_way = 0, way_count = 0;
        Node *left = nullptr, *right = nullptr;
        bool on_way = false;
    };

    Node *root;

    int tree_largest_half_way = 0;

    std::ofstream out;

    Node *doInsert(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }
        if (value < node->value)
        {
            node->left = doInsert(node->left, value);
        }
        else if (value > node->value)
        {
            node->right = doInsert(node->right, value);
        }
        return node;
    }

    void PostOrderTraversal(Node *node)
    {
        if (node != nullptr)
        {
            PostOrderTraversal(node->left);
            PostOrderTraversal(node->right);
            if (node->right != nullptr && node->left != nullptr)
            {
                node->largest_half_way = node->left->height + node->right->height + 2;
                if (node->left->height > node->right->height)
                {
                    node->height = node->left->height + 1;
                    node->leaves_count = node->left->leaves_count;
                }
                else if (node->left->height < node->right->height)
                {
                    node->height = node->right->height + 1;
                    node->leaves_count = node->right->leaves_count;
                }
                else
                {
                    node->height = node->right->height + 1;
                    node->leaves_count = node->left->leaves_count + node->right->leaves_count;
                }
            }
            else if (node->left != nullptr)
            {
                node->largest_half_way = node->left->height + 1;
                node->height = node->left->height + 1;
                node->leaves_count = node->left->leaves_count;
            }
            else if (node->right != nullptr)
            {
                node->largest_half_way = node->right->height + 1;
                node->height = node->right->height + 1;
                node->leaves_count = node->right->leaves_count;
            }
            if (node->largest_half_way > tree_largest_half_way)
                tree_largest_half_way = node->largest_half_way;
        }
    }

    void PreOrderTraversalForFind(Node *node)
    {
        if (node != nullptr)
        {
            if (node->largest_half_way == tree_largest_half_way)
            {
                if (node == root)
                {
                    if ((node->right != nullptr && node->left == nullptr) || (node->right == nullptr && node->left != nullptr))
                    {
                        PreOrderTraversalForFlags(node, node->largest_half_way, 1);
                    }
                    else
                        PreOrderTraversalForFlags(node, node->largest_half_way, 0);
                }
                else
                    PreOrderTraversalForFlags(node, node->largest_half_way, 0);
            }
            else
            {
                PreOrderTraversalForFind(node->left);
                PreOrderTraversalForFind(node->right);
            }
        }
    }

    void PreOrderTraversalForFlags(Node *node, int power, int up_leaves)
    {
        if (node != nullptr)
        {
            node->on_way = true;
            if (node->largest_half_way == tree_largest_half_way)
                power = tree_largest_half_way;
            if (node->right != nullptr && node->left != nullptr)
            {
                if (power == 1)
                {
                    node->left->on_way = true;
                    node->left->way_count = up_leaves;
                    node->right->on_way = true;
                    node->right->way_count = up_leaves;
                    node->way_count = node->leaves_count * up_leaves;
                }
                else
                {
                    if (node->left->height + node->right->height + 2 == power || node->left->height == node->right->height)
                    {
                        if (node->largest_half_way == tree_largest_half_way)
                        {
                            if (node->left->height > node->right->height)
                            {
                                node->way_count = node->left->leaves_count * up_leaves + node->left->leaves_count * node->right->leaves_count;
                                PreOrderTraversalForFlags(node->left, node->left->height, up_leaves + node->right->leaves_count);
                                if (node->left->height + 1 > tree_largest_half_way - (node->left->height + 1))
                                    PreOrderTraversalForFlags(node->right, node->right->height, node->left->leaves_count);
                                else
                                    PreOrderTraversalForFlags(node->right, node->right->height, up_leaves);
                            }
                            else if (node->left->height < node->right->height)
                            {
                                node->way_count = node->right->leaves_count * up_leaves + node->left->leaves_count * node->right->leaves_count;
                                if (node->right->height + 1 > tree_largest_half_way - (node->right->height + 1))
                                    PreOrderTraversalForFlags(node->left, node->left->height, node->right->leaves_count);
                                else
                                    PreOrderTraversalForFlags(node->left, node->left->height, up_leaves);
                                PreOrderTraversalForFlags(node->right, node->right->height, up_leaves + node->left->leaves_count);
                            }
                            else
                            {
                                node->way_count = up_leaves * (node->right->leaves_count + node->right->leaves_count) + node->left->leaves_count * node->right->leaves_count;
                                PreOrderTraversalForFlags(node->left, node->largest_half_way - node->right->height - 2, up_leaves + node->right->leaves_count);
                                PreOrderTraversalForFlags(node->right, node->largest_half_way - node->left->height - 2, up_leaves + node->left->leaves_count);
                            }
                        }
                        else
                        {
                            node->way_count = node->left->leaves_count * up_leaves + node->right->leaves_count * up_leaves;
                            PreOrderTraversalForFlags(node->left, node->largest_half_way - node->right->height - 2, up_leaves);
                            PreOrderTraversalForFlags(node->right, node->largest_half_way - node->left->height - 2, up_leaves);
                        }
                    }
                    else
                    {
                        if (node->left->height > node->right->height)
                        {
                            node->way_count = node->leaves_count * up_leaves;
                            PreOrderTraversalForFlags(node->left, node->left->height, up_leaves);
                        }
                        else if (node->left->height < node->right->height)
                        {
                            node->way_count = node->leaves_count * up_leaves;
                            PreOrderTraversalForFlags(node->right, node->right->height, up_leaves);
                        }
                    }
                }
            }
            else if (node->left != nullptr)
            {
                node->way_count = node->leaves_count * up_leaves;
                PreOrderTraversalForFlags(node->left, node->left->height, up_leaves);
            }
            else if (node->right != nullptr)
            {
                node->way_count = node->leaves_count * up_leaves;
                PreOrderTraversalForFlags(node->right, node->right->height, up_leaves);
            }
            else
            {
                node->way_count = up_leaves;
            }
        }
    }

    void InOrderTraversalForVector(Node *node)
    {
        if (node != nullptr)
        {
            InOrderTraversalForVector(node->left);
            if (node->on_way && node->way_count != 0 && node->way_count % 2 == 0)
                correct_nodes.push_back(node->value);
            InOrderTraversalForVector(node->right);
        }
    }

    void PreOrderTraversalForOutput(Node *node)
    {
        if (node != nullptr)
        {
            out << node->value << std::endl;
            PreOrderTraversalForOutput(node->left);
            PreOrderTraversalForOutput(node->right);
        }
    }

    Node *findMinimum(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    void Delete(Node *&current, int deleted)
    {
        if (current == nullptr)
            return;
        if (current->value == deleted)
        {
            if (current->right == nullptr && current->left == nullptr)
            {
                if (current != root)
                {
                    delete current;
                    current = nullptr;
                }
                else
                {
                    root = nullptr;
                }
                delete current;
            }
            else if (current->right != nullptr && current->left == nullptr)
            {
                Node *memory = current->right;
                delete current;
                current = memory;
            }
            else if (current->right == nullptr && current->left != nullptr)
            {
                Node *memory = current->left;
                delete current;
                current = memory;
            }
            else if (current->right != nullptr && current->left != nullptr)
            {
                Node *memory = findMinimum(current->right);
                current->value = memory->value;
                Delete(current->right, current->value);
            }
        }
        else if (deleted > current->value)
        {
            Delete(current->right, deleted);
        }
        else
        {
            Delete(current->left, deleted);
        }
    }

public:
    BinarySearchTree() : root(nullptr), out("tst.out") {}

    std::vector<int> correct_nodes;

    void Insert(int value)
    {
        root = doInsert(root, value);
    }

    void PostOrderTraversal()
    {
        PostOrderTraversal(root);
    }

    void PreOrderTraversalForFind()
    {
        PreOrderTraversalForFind(root);
    }

    void InOrderTraversalForVector()
    {
        InOrderTraversalForVector(root);
    }

    void PreOrderTraversalForOutput()
    {
        PreOrderTraversalForOutput(root);
    }

    void Delete(int value)
    {
        Delete(root, value);
    }
};

int main()
{
    std::ifstream fin("tst.in");
    int value;
    BinarySearchTree tree;
    while (!fin.eof())
    {
        fin >> value;
        tree.Insert(value);
    }
    fin.close();

    tree.PostOrderTraversal();

    tree.PreOrderTraversalForFind();

    tree.InOrderTraversalForVector();

    if (tree.correct_nodes.size() % 2 == 1)
        tree.Delete(tree.correct_nodes[tree.correct_nodes.size() / 2]);

    tree.PreOrderTraversalForOutput();
    return 0;
}