#include <iostream>
#include <istream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node {
public:
    int key;
    Node *parent;
    Node *leftChild;
    Node *rightChild;
    
    Node() {
        this->parent = nullptr;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
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
    
    list<int> in_order() {
        list <int> result;
        stack<Node *> NodeStack;
        Node *node = this;
        
        while (node != nullptr || NodeStack.empty() == false) {
            while (node != nullptr) {
                NodeStack.push(node);
                node = node->leftChild;
            }
            
            node = NodeStack.top();
            result.push_back(node->key);
            NodeStack.pop();
            
            node = node->rightChild;
        }
        
        return result;
    }
    
    list<int> pre_order() {
        list<int> result;
        stack<Node *> NodeStack;
        
        NodeStack.push(this);
        
        while (NodeStack.empty() == false) {
            Node *node = NodeStack.top();
            result.push_back(NodeStack.top()->key);
            NodeStack.pop();
            
            if (node->rightChild != nullptr)
                NodeStack.push(node->rightChild);
            
            if (node->leftChild != nullptr)
                NodeStack.push(node->leftChild);
        }
        
        return result;
    }
    
    list<int> post_order() {
        list<int> result;
        stack<Node *> NodeStack;
        stack<int> out;
        
        NodeStack.push(this);
        
        while (NodeStack.empty() == false) {
            Node *node = NodeStack.top();
            NodeStack.pop();
            
            out.push(node->key);
            
            if (node->leftChild != nullptr)
                NodeStack.push(node->leftChild);
            
            if (node->rightChild != nullptr)
                NodeStack.push(node->rightChild);
        }
        
        while (out.empty() == false) {
            result.push_back(out.top());
            out.pop();
        }
        
        return result;
    }
};

class TreeOrders {
    int n;
    vector <Node> nodes;
    Node Root;
    
public:
    void read() {
        cin >> n;
        nodes.resize(n);
        for (int i = 0; i < n; i++) {
            int left, right;
            cin >> nodes[i].key;
            cin >> left;
            nodes[i].setLeft(left == -1 ? nullptr : &nodes[left]);
            cin >> right;
            nodes[i].setRight(right == -1 ? nullptr : &nodes[right]);
        }
    }
    
    Node &findRootInternal(Node *theParent) {
        if (theParent->parent == nullptr)
            return *theParent;
        return findRootInternal(theParent->parent);
    }
    
    void findRoot() {
        Root = findRootInternal(&nodes[0]);
    }
    
    list<int> in_order() {
        return Root.in_order();
    }
    
    list<int> pre_order() {
        return Root.pre_order();
    }
    
    list<int> post_order() {
        return Root.post_order();
    }
};

void print(list <int> a) {
    for (list<int>::iterator it = a.begin(); it != a.end(); it++) {
        if (it != a.begin())
            cout << ' ';
        cout << *it;
    }
    cout << '\n';
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    t.findRoot();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;
    
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
#endif
    
    return main_with_large_stack_space();
}

