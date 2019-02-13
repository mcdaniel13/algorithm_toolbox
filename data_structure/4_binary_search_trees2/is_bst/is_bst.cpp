#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Node {
public:
    int key;
    Node *leftChild;
    Node *rightChild;
    Node *parent;
    
    Node() {
        this->parent = nullptr;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    }
    
    void setKey(int keyVal) {
        key = keyVal;
    }
    
    void setLeft(Node *left) {
        leftChild = left;
        if (left != 0)
            leftChild->parent = this;
    }
    
    void setRight(Node *right) {
        rightChild = right;
        if (right != 0)
            rightChild->parent = this;
    }
    
    bool IsBinarySearchTreeUtil(int min, int max) {
        Node *node = this;
        
        if (node == nullptr) {
            return true;
        }
        
        if (node->key < min || node->key > max)
            return false;
        
        return node->leftChild->IsBinarySearchTreeUtil(min, node->key-1) &&
        node->rightChild->IsBinarySearchTreeUtil(node->key+1, max);
        
    }
};

class Tree {
private:
    
    int nodes;
    vector <Node> tree;
    Node root;
    
public:
    void read() {
        cin >> nodes;
        tree.resize(nodes);
        for (int i = 0; i < nodes; ++i) {
            int key, left, right;
            cin >> key >> left >> right;
            tree[i].setKey(key);
            tree[i].setLeft(left == -1 ? nullptr : &tree[left]);
            tree[i].setRight(right == -1 ? nullptr : &tree[right]);
        }
    }
    
    Node &findRoot(Node *theParent) {
        if (theParent->parent == nullptr)
            return *theParent;
        return findRoot(theParent->parent);
    }
    
    bool IsBinarySearchTree() {
        if (nodes == 0)
            return true;
        root = findRoot(&tree[0]);
        return root.IsBinarySearchTreeUtil(INT_MIN, INT_MAX);
    }
};

int main() {
    Tree t;
    t.read();
    if (t.IsBinarySearchTree()) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
