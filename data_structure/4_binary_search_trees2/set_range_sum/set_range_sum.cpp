#include <cstdio>
//#include <iostream>
//#include <sstream>
//#include <fstream>

// Splay tree implementation

// Vertex of a splay tree
using namespace std;

struct Vertex {
    int key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    long long sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;
    
    Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
    : key(key), sum(sum), left(left), right(right), parent(parent) {}
    
    //    void print(std::ostream &where){
    //        where <<"\t"<< key << "    [shape=circle]" << std::endl;
    //
    //        if(right != NULL) {
    //            where <<"\t" << key << " -> " << right->key  << std::endl;
    //            right->print(where);
    //        }
    //
    //        if(left != NULL) {
    //            where <<"\t" << key << " -> " << left->key  << std::endl;
    //            left->print(where);
    //        }
    //    }
};

void update(Vertex* v) {
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;
    if (parent == NULL) {
        return;
    }
    Vertex* grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Vertex* find(Vertex*& root, int key) {
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
    right = find(root, key);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) {
        left->parent = NULL;
    }
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Vertex* min_right = right;
    while (min_right->left != NULL) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(int x) {
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_vertex = NULL;
    split(root, x, left, right);
    if (right == NULL || right->key != x) {
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_vertex), right);
}

void setParent(Vertex* v, Vertex* root) {
    if (v != NULL)
        v->parent = root;
}

void erase(int x) {
    Vertex* N = find(root, x);
    if (N != NULL && N->key == x) {
        Vertex *N_next = find(root, x + 1);
        if (N_next != NULL) {
            splay(root, N_next);
            splay(root, N);
            Vertex *N_left = N->left;
            N_next->left = N_left;
            setParent(N_next, NULL);
            setParent(N_left, N_next);
            root = N_next;
            update(root);
        } else {
            splay(root, N);
            Vertex *N_left = N->left;
            root = N_left;
            setParent(N_left, NULL);
            splay(root, root);
        }
    }
}

bool find(int x) {
    Vertex* N = find(root, x);
    return N != NULL && N->key == x ? true : false;
}

long long sum(int from, int to) {
    Vertex* left = NULL;
    Vertex* middle = NULL;
    Vertex* right = NULL;
    split(root, from, left, middle);
    split(middle, to + 1, middle, right);
    long long ans = 0;
    
    if (to < from)
        return 0;
    
    if (middle != NULL)
        ans += middle->sum;
    
    Vertex *N_middle = merge(left, middle);
    root = merge(N_middle, right);
    
    return ans;
}

const int MODULO = 1000000001;

int main(){
    int n;
    scanf("%d", &n);
    int last_sum_result = 0;
    for (int i = 0; i < n; i++) {
        char buffer[10];
        scanf("%s", buffer);
        char type = buffer[0];
        switch (type) {
            case '+' : {
                int x;
                scanf("%d", &x);
                insert((x + last_sum_result) % MODULO);
            } break;
            case '-' : {
                int x;
                scanf("%d", &x);
                erase((x + last_sum_result) % MODULO);
            } break;
            case '?' : {
                int x;
                scanf("%d", &x);
                printf(find((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
            } break;
            case 's' : {
                int l, r;
                scanf("%d %d", &l, &r);
                long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
                printf("%lld\n", res);
                last_sum_result = int(res % MODULO);
            } break;
                //            case 'p' : {
                //                std::stringstream result;
                //                result <<"digraph D {"<<std::endl;
                //                if(root != NULL)
                //                    root->print(result);
                //                result <<"}"<<std::endl;
                //                std::cerr << result.str();
                //
                //                ofstream dotFile;
                //                dotFile.open ("/Users/Cho/Documents/test.dot");
                //                dotFile << result.str();
                //                dotFile.close();
                //                std::system ("dot -Tpdf /Users/Cho/Documents/test.dot -o /Users/Cho/Documents/test.pdf");
                //            } break;
        }
    }
    return 0;
}
