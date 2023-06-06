#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

const int EMPTY = -1337;

struct Node
{
    int value;
    Node *left, *right;
    int height, num;

    explicit Node(int value_)
    {
        value = value_;
        left = nullptr;
        right = nullptr;
        height = 0;
        num = 0;
    }
};

class Tree
{
private:
    Node *root;
    set<int> nodes;

    void addNode(Node *currNode, Node *node)
    {
        if (currNode->value > node->value)
        {
            if (currNode->left == nullptr)
            {
                currNode->left = node;
                return;
            }
            else
            {
                addNode(currNode->left, node);
            }
        }
        else if (currNode->value < node->value)
        {
            if (currNode->right == nullptr)
            {
                currNode->right = node;
                return;
            }
            else
            {
                addNode(currNode->right, node);
            }
        }
        else
        {
            return;
        }
    }

    void straightLeftWayNode(Node *node, ofstream &out)
    {
        if (node != nullptr)
        {
            out << node->value << "\n";
            straightLeftWayNode(node->left, out);
            straightLeftWayNode(node->right, out);
        }
    }

    Node *getNewNode(Node *node)
    {
        Node *temp = node->right;
        if (temp->left == nullptr)
        {
            temp->left = node->left;
            return temp;
        }
        else
        {
            while (temp->left->left != nullptr)
            {
                temp = temp->left;
            }
            Node *forRet = temp->left;
            temp->left = temp->left->right;
            return forRet;
        }
    }

    Node *rightRemove(Node *node)
    {
        if (node->right == nullptr)
        {
            return node->left;
        }
        else if (node->left == nullptr)
        {
            return node->right;
        }
        else
        {
            if (node->right->left == nullptr)
            {
                Node *temp = node->right;
                temp->left = node->left;
                return temp;
            }
            else
            {
                Node *temp = getNewNode(node);
                temp->left = node->left;
                temp->right = node->right;
                return temp;
            }
        }
    }

    void removeNode(Node *node, const int &value)
    {
        if (node->value > value)
        {
            if (node->left == nullptr)
            {
                return;
            }
            if (node->left->value == value)
            {
                node->left = rightRemove(node->left);
            }
            else
            {
                removeNode(node->left, value);
            }
        }
        else if (node->value < value)
        {
            if (node->right == nullptr)
            {
                return;
            }
            if (node->right->value == value)
            {
                node->right = rightRemove(node->right);
            }
            else
            {
                removeNode(node->right, value);
            }
        }
        else
        {
            if (root == nullptr)
            {
                return;
            }
            root = rightRemove(root);
        }
    }

public:
    Tree(int value)
    {
        root = new Node(value);
    }

    void add(int value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            return;
        }
        Node *node = new Node(value);
        addNode(root, node);
    }

    void straightLeftWay()
    {
        ofstream out("out.txt");
        straightLeftWayNode(root, out);
        out.close();
    }

    void remove(int value)
    {
        removeNode(root, value);
    }

    void height(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        height(node->left);
        height(node->right);
        int height = 0, left = 0, right = 0;
        if (node->left != nullptr)
        {
            left = node->left->height;
        }
        if (node->right != nullptr)
        {
            right = node->right->height;
        }
        height = 1 + max(left, right);
        node->height = height;
    }

    void numOfNodes(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        numOfNodes(node->left);
        numOfNodes(node->right);
        int num = 0;
        if (node->left != nullptr)
        {
            num += node->left->num;
        }
        if (node->right != nullptr)
        {
            num += node->right->num;
        }
        num += 1;
        node->num = num;
    }

    void initHeightNum()
    {
        if (root == nullptr)
        {
            return;
        }
        numOfNodes(root);
        height(root);
    }

    void findAvg(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->left != nullptr && node->right != nullptr)
        {
            if (node->left->height == node->right->height &&
                node->left->num != node->right->num)
            {
                nodes.insert(node->value);
            }
        }
        findAvg(node->left);
        findAvg(node->right);
    }

    int centralNode()
    {
        if (nodes.size() % 2 == 0)
        {
            return -1;
        }
        else
        {
            int i = nodes.size() / 2;
            auto it = nodes.begin();
            while (i != 0)
            {
                i--;
                it++;
            }
            i = *it;
            return i;
        }
    }

    Tree(const vector<int> &list)
    {
        root = nullptr;
        for (int i : list)
        {
            add(i);
        }
        initHeightNum();
        findAvg(root);
    }
};

vector<int> readFile()
{
    vector<int> v;
    ifstream in("in.txt");
    while (!in.eof())
    {
        int a;
        in >> a;
        v.push_back(a);
    }
    in.close();
    return v;
}

int main()
{
    Tree tree(readFile());
    int avg = tree.centralNode();
    if (avg != -1)
    {
        tree.remove(avg);
    }
    tree.straightLeftWay();
    return 0;
}
