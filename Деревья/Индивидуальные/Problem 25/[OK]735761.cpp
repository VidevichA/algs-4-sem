#include <iostream>
#include <vector>
#include <fstream>

std::ifstream fin;
std::ofstream fout;
std::vector<long long> nodes;

class BinaryTree
{
private:
    class Node
    {
    public:
        long long value;
        long long amountL;
        long long amountR;
        long long difference;
        Node *right;
        Node *left;

        Node(long long value)
        {
            this->value = value;
            this->amountL = 0;
            this->amountR = 0;
            this->difference = 0;
            this->right = nullptr;
            this->left = nullptr;
        }
    };
    Node *root;
    size_t amountOfNodes;
    long long max_difference = LONG_LONG_MIN;

    void CountAmountOfNodes(Node *current, long long &amount)
    {
        if (current == nullptr)
        {
            return;
        }
        ++amount;
        CountAmountOfNodes(current->left, amount);
        CountAmountOfNodes(current->right, amount);
    }

    void PreOrderTraversal(Node *current)
    {
        if (current == nullptr)
        {
            return;
        }
        fout << current->value << '\n';
        PreOrderTraversal(current->left);
        PreOrderTraversal(current->right);
    }

    void PostOrderTraversal(Node *current)
    {
        if (current == nullptr)
        {
            return;
        }
        PostOrderTraversal(current->left);
        PostOrderTraversal(current->right);

        if (current->left == nullptr && current->right == nullptr)
        {
            current->amountL = 0;
            current->amountR = 0;
        }
        else if (current->left == nullptr && current->right != nullptr)
        {
            current->amountL = 0;
            current->amountR = current->right->amountR + current->right->amountL + 1;
        }
        else if (current->left != nullptr && current->right == nullptr)
        {
            current->amountR = 0;
            current->amountL = current->left->amountR + current->left->amountL + 1;
        }
        else
        {
            current->amountL = current->left->amountL + current->left->amountR + 1;
            current->amountR = current->right->amountR + current->right->amountL + 1;
        }
        current->difference = abs(current->amountR - current->amountL);
        if (max_difference < current->difference)
        {
            max_difference = current->difference;
        }
    }

    void InOrderTraversal(Node *current)
    {
        if (current == nullptr)
        {
            return;
        }
        InOrderTraversal(current->left);
        if (current->difference == max_difference)
        {
            nodes.push_back(current->value);
        }
        InOrderTraversal(current->right);
    }

    bool RemoveRight(Node *current, long long value)
    {
        Node *toDelete = Search(current, value);

        if (toDelete == nullptr)
        {
            return false;
        }

        if (toDelete == root && amountOfNodes == 1)
        {
            root = nullptr;
            delete toDelete;
            return true;
        }

        if (toDelete->left == nullptr && toDelete->right == nullptr)
        {
            Node *parent = current;
            while (parent->right != toDelete && parent->left != toDelete)
            {
                if (value < parent->value)
                {
                    parent = parent->left;
                    continue;
                }
                if (value > parent->value)
                {
                    parent = parent->right;
                    continue;
                }
            }

            if (parent->left == toDelete)
            {
                parent->left = nullptr;
            }
            if (parent->right == toDelete)
            {
                parent->right = nullptr;
            }
            delete toDelete;
            return true;
        }

        if (toDelete->left != nullptr && toDelete->right == nullptr)
        {
            Node *left = toDelete->left;
            toDelete->value = left->value;
            toDelete->left = left->left;
            toDelete->right = left->right;
            delete left;
            return true;
        }

        if (toDelete->left == nullptr && toDelete->right != nullptr)
        {
            Node *right = toDelete->right;
            toDelete->value = right->value;
            toDelete->left = right->left;
            toDelete->right = right->right;
            delete right;
            return true;
        }

        Node *toReplace = toDelete->right;

        if (toReplace->left == nullptr)
        {
            toDelete->value = toReplace->value;
            toDelete->right = toReplace->right;
            delete toReplace;
            return true;
        }

        Node *parentOfReplacement = toDelete->right;

        while (toReplace->left != nullptr)
        {
            toReplace = toReplace->left;
        }

        while (parentOfReplacement->left != toReplace)
        {
            parentOfReplacement = parentOfReplacement->left;
        }

        toDelete->value = toReplace->value;
        parentOfReplacement->left = nullptr;
        if (toReplace->right != nullptr)
        {
            parentOfReplacement->left = toReplace->right;
        }
        delete toReplace;

        return true;
    }

public:
    BinaryTree()
    {
        this->root = nullptr;
        this->amountOfNodes = 0;
    }

    size_t GetAmountOfNodes()
    {
        return this->amountOfNodes;
    }

    long long GetMaxDifference()
    {
        return this->max_difference;
    }

    bool Add(long long value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            amountOfNodes++;
            return true;
        }

        Node *current = root;
        while (current != nullptr)
        {
            if (current->value == value)
            {
                return false;
            }
            if (current->value > value)
            {
                if (current->left == nullptr)
                {
                    current->left = new Node(value);
                    amountOfNodes++;
                    return true;
                }
                current = current->left;
                continue;
            }
            if (current->value < value)
            {
                if (current->right == nullptr)
                {
                    current->right = new Node(value);
                    amountOfNodes++;
                    return true;
                }
                current = current->right;
                continue;
            }
        }
        return false;
    }

    Node *Search(Node *current, long long value)
    {
        while (current != nullptr)
        {
            if (current->value == value)
            {
                return current;
            }
            else if (value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return nullptr;
    }

    void PreOrderTraversal()
    {
        PreOrderTraversal(root);
    }

    void PostOrderTraversal()
    {
        PostOrderTraversal(root);
    }

    void InOrderTraversal()
    {
        InOrderTraversal(root);
    }

    bool Delete(long long value)
    {
        return RemoveRight(root, value);
    }
};

int main()
{
    BinaryTree tree;
    fin.open("tst.in");
    long long value;
    while (!fin.eof())
    {
        fin >> value;
        tree.Add(value);
    }
    fin.close();
    fout.open("tst.out");

    tree.PostOrderTraversal();
    tree.InOrderTraversal();
    if (nodes.size() % 2 == 1)
    {
        tree.Delete(nodes[nodes.size() / 2]);
    }
    tree.PreOrderTraversal();

    fout.close();
    return 0;
}