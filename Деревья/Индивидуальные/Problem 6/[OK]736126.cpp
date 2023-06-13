#include <iostream>
#include <fstream>
#include <map>

std::ofstream out("out.txt");

class Tree
{
public:
    class Node
    {
    public:
        Node(int value)
        {
            this->value = value;
            this->parent = nullptr;
            this->left = nullptr;
            this->right = nullptr;
            this->mark = -1;
        }

        int value;
        Node *parent;
        Node *left;
        Node *right;
        int mark;
    };

    Node *root;

    Tree()
    {
        root = nullptr;
    };

    void add(int value, Node *current_root)
    {
        if (current_root == nullptr)
        {
            this->root = new Node(value);
            return;
        }
        if (value == current_root->value)
        {
            return;
        }
        else if (value < current_root->value)
        {
            if (current_root->left == nullptr)
            {
                current_root->left = new Node(value);
                current_root->left->parent = current_root;
            }
            else
            {
                current_root = current_root->left;
                add(value, current_root);
            }
        }
        else
        {
            if (current_root->right == nullptr)
            {
                current_root->right = new Node(value);
                current_root->right->parent = current_root;
            }
            else
            {
                current_root = current_root->right;
                add(value, current_root);
            }
        }
    }

    void straight_left_traversal(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        out << node->value << "\n";
        straight_left_traversal(node->left);
        straight_left_traversal(node->right);
    }

    void delete_node(int value, Node *current_root)
    {
        if (current_root == nullptr)
        {
            return;
        }

        if (value < current_root->value)
        {
            delete_node(value, current_root->left);
        }
        else if (value > current_root->value)
        {
            delete_node(value, current_root->right);
        }
        else
        {
            if (current_root == this->root)
            {
                if (current_root->left != nullptr && current_root->right == nullptr)
                {
                    this->root = current_root->left;
                }
                else if (current_root->left == nullptr && current_root->right != nullptr)
                {
                    this->root = current_root->right;
                }
                else
                {
                    Node *dead_end = current_root->right;
                    while (dead_end->left != nullptr)
                    {
                        dead_end = dead_end->left;
                    }

                    int tmp = dead_end->value;
                    dead_end->value = current_root->value;
                    current_root->value = tmp;
                    delete_node(value, dead_end);
                }
                return;
            }
            if (current_root->left == nullptr && current_root->right == nullptr)
            {
                if (current_root == current_root->parent->left)
                {
                    current_root->parent->left = nullptr;
                }
                else
                {
                    current_root->parent->right = nullptr;
                }
            }
            else if (current_root->left != nullptr && current_root->right == nullptr)
            {
                if (current_root == current_root->parent->left)
                {
                    current_root->parent->left = current_root->left;
                }
                else
                {
                    current_root->parent->right = current_root->left;
                }
            }
            else if (current_root->left == nullptr && current_root->right != nullptr)
            {
                if (current_root == current_root->parent->left)
                {
                    current_root->parent->left = current_root->right;
                }
                else
                {
                    current_root->parent->right = current_root->right;
                }
            }
            else
            {
                Node *dead_end = current_root->right;
                while (dead_end->left != nullptr)
                {
                    dead_end = dead_end->left;
                }

                int tmp = dead_end->value;
                dead_end->value = current_root->value;
                current_root->value = tmp;
                delete_node(value, dead_end);
            }
        }
    }

    struct Prev_data
    {
        int mark;
        int sum;
    };

    Node *max_root = new Node(-1);
    int max_length = -1;
    int max_sum = 0;

    Prev_data find_half_way(Node *node)
    {
        Node *current = node;
        if (current == nullptr)
        {
            return {-1, 0};
        }

        Prev_data right_data = find_half_way(current->right);
        Prev_data left_data = find_half_way(current->left);

        int right_mark = right_data.mark + 1;
        int left_mark = left_data.mark + 1;
        int current_half_way = left_mark + right_mark;

        int right_sum = right_data.sum;
        int left_sum = left_data.sum;
        int current_sum = right_sum + left_sum + current->value;

        if (current_half_way > max_length)
        {
            max_root = current;
            max_length = current_half_way;
            max_sum = current_sum;
        }
        else if (current_half_way == max_length && current_sum > max_sum)
        {
            max_root = current;
            max_length = current_half_way;
            max_sum = current_sum;
        }

        int current_mark = std::max(right_mark, left_mark);

        if (right_mark > left_mark)
        {
            current_sum -= left_sum;
        }
        else if (right_mark < left_mark)
        {
            current_sum -= right_sum;
        }
        else
        {
            current_sum = std::max(left_sum, right_sum) + current->value;
        }

        current->mark = current_mark;
        return {current_mark, current_sum};
    }

    Node *find_central()
    {
        Node *current = max_root;
        while (current->mark != max_length / 2)
        {
            if (current->right == nullptr)
            {
                current = current->left;
            }
            else if (current->left == nullptr)
            {
                current = current->right;
            }
            else
            {
                if (current->right->mark >= current->left->mark)
                {
                    current = current->right;
                }
                else
                {
                    current = current->left;
                }
            }
        }
        return current;
    }

    void processing()
    {
        find_half_way(this->root);
        Node *center = nullptr;
        if (max_length % 2 == 0)
        {
            center = find_central();
        }

        if (center != nullptr)
        {
            if (max_root != center)
            {
                delete_node(center->value, center);
                delete_node(max_root->value, max_root);
            }
            else
            {
                delete_node(center->value, center);
            }
        }
        else
        {
            delete_node(max_root->value, max_root);
        }
    }
};

int main()
{
    Tree tree = Tree();
    std::ifstream fin("in.txt");

    int x;
    while (fin >> x)
    {
        tree.add(x, tree.root);
    }
    fin.close();

    tree.processing();

    tree.straight_left_traversal(tree.root);
    return 0;
}