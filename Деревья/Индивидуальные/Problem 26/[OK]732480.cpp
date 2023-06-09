#include <fstream>
#include <vector>

using namespace std;

class Node {
public:
    Node *left;
    Node *right;
    int value;
    int childs = 0;
    int dif = 0;

    Node(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

ofstream writer;
vector<int> heights;
Node *root = nullptr;
int length = 1;

void addValue(int value) {
    Node *previous = root;
    Node *current;
    if (value == root->value) return;
    if (value > root->value) {
        current = root->right;
    } else {
        current = root->left;
    }
    while (current != nullptr) {
        if (value == current->value) return;
        if (value > current->value){
            previous = current;
            current = current->right;
        }
        else {
            previous = current;
            current = current->left;
        }
    }
    current = new Node(value);
    if (value > previous->value) {
        previous->right = current;
    } else {
        previous->left = current;
    }
}

void read() {
    ifstream read("tst.in");
    int rootValue;
    read >> rootValue;
    root = new Node(rootValue);
    int value;
    while (read >> value) {
        length++;
        addValue(value);
    }
}

void remove(Node* node, Node* previous){
    if (node->left == nullptr && node->right == nullptr){
        if (node == previous->left)  previous->left = nullptr;
        if (node == previous->right)  previous->right = nullptr;
        delete node;
        return;
    }
    if (node->left == nullptr){
        if (node == previous->left)  previous->left = node->right;
        if (node == previous->right)  previous->right = node->right;
        delete node;
        return;
    }
    if (node->right == nullptr){
        if (node == previous->left)  previous->left = node->left;
        if (node == previous->right)  previous->right = node->left;
        delete node;
        return;
    }
}

void remove(int value){
    if (root->value == value){
        if (root->right == nullptr){
            auto toDelete = root;
            root = root->left;
            delete toDelete;
            return;
        }
        if (root->left == nullptr){
            auto toDelete = root;
            root = root->right;
            delete toDelete;
            return;
        }
    }
    Node *previous = root;
    Node *current;
    if (value > root->value) {
        current = root->right;
    } else {
        current = root->left;
    }
    if (current == nullptr) return;
    if (value == root->value) current = root;
    while (current->value != value) {
        if (value > current->value){
            previous = current;
            current = current->right;
        }
        else {
            previous = current;
            current = current->left;
        }
        if (current == nullptr) return;
    }

    if (current->left == nullptr && current->right == nullptr){
        if (previous->left == current){
            previous->left = nullptr;
            delete current;
            return;
        }
        if (previous->right == current){
            previous->right = nullptr;
            delete current;
            return;
        }
    }
    if (current->left == nullptr){
        if (previous->left == current){
            previous->left = current->right;
            delete current;
            return;
        }
        if (previous->right == current){
            previous->right = current->right;
            delete current;
            return;
        }
    }
    if (current->right == nullptr){
        if (previous->left == current){
            previous->left = current->left;
            delete current;
            return;
        }
        if (previous->right == current){
            previous->right = current->left;
            delete current;
            return;
        }
    }

    previous = current;
    current = current->right;
    Node* prevForCurrent = previous;
    while (current->left != nullptr){
        prevForCurrent = current;
        current = current->left;
    }
    previous->value = current->value;
    remove(current, prevForCurrent);
}

void forwardLeft(Node* node){
    writer << node->value << endl;
    if (node->left != nullptr){
        forwardLeft(node->left);
    }
    if (node->right != nullptr){
        forwardLeft(node->right);
    }
}

void freeMem(Node* node){
    if (node->left != nullptr){
        freeMem(node->left);
    }
    if (node->right != nullptr){
        freeMem(node->right);
    }
    delete node;
}

int biggest = 0;
Node* biggestNode = nullptr;

void postOrderTraversal(Node* current = root){
    if (current->left != nullptr) {
        postOrderTraversal(current->left);
    }
    if (current->right != nullptr) {
        postOrderTraversal(current->right);
    }
    if (biggestNode == nullptr){
        biggestNode = current;
    }
    if (current->left == nullptr && current->right == nullptr){
        if (biggestNode->dif == 0 && current->value > biggestNode->value){
            biggestNode = current;
        }
        return;
    }
    if (current->left == nullptr){
        current->childs = current->right->childs + 1;
        current->dif = current->right->childs + 1;
        if (biggestNode->dif < current->dif){
            biggestNode = current;
        }
        if (biggestNode->dif == current->dif && biggestNode->value < current->value){
            biggestNode = current;
        }
        return;
    }
    if (current->right == nullptr){
        current->childs = current->left->childs + 1;
        current->dif = current->left->childs + 1;
        if (biggestNode->dif < current->dif){
            biggestNode = current;
        }
        if (biggestNode->dif == current->dif && biggestNode->value < current->value){
            biggestNode = current;
        }
        return;
    }
    current->childs = current->left->childs + current->right->childs + 2;
    current->dif = abs((current->left->childs + 1) - (current->right->childs + 1));
    if (biggestNode->dif < current->dif){
        biggestNode = current;
    }
    if (biggestNode->dif == current->dif && biggestNode->value < current->value){
        biggestNode = current;
    }
}

int main() {
    read();
    writer = ofstream("tst.out");
    heights = vector<int>(length);
    postOrderTraversal();
    remove(biggestNode->value);
    forwardLeft(root);
    freeMem(root);
}