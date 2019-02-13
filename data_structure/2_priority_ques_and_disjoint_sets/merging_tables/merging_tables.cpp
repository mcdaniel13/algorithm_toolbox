#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement {
    int size, parent, rank;
    
    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;
    
    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
        //print();
    }
    
    void print() {
        cout << "======size======" << endl;
        cout << " [ ";
        for (int i = 0; i < sets.size(); ++i) {
            cout << sets[i].size << ' ';
        }
        cout << "] " << endl;
        cout << "=====parent=====" << endl;
        cout << " [ ";
        for (int i = 0; i < sets.size(); ++i) {
            cout << sets[i].parent << ' ';
        }
        cout << "] " << endl;
        cout << "======rank======" << endl;
        cout << " [ ";
        for (int i = 0; i < sets.size(); ++i) {
            cout << sets[i].rank << ' ';
        }
        cout << "] " << endl << endl;
        
    }
    
    int getParent(int table) {
        int i = table;
        if (i != sets[i].parent) {
            sets[i].parent = getParent(sets[i].parent);
        }
        return sets[i].parent;
        
        // find parent and compress path
    }
    
    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        //cout << "Destination parent = " << realDestination << endl;
        int realSource = getParent(source);
        //cout << "Source parent = " << realSource << endl;
        
        if (realDestination == realSource) {
            max_table_size = max(max_table_size, sets[realDestination].size);
            return;
        }
        
        else if (sets[realDestination].rank > sets[realSource].rank) {
            sets[realSource].parent = realDestination;
            sets[realDestination].size += sets[realSource].size;
            sets[realSource].size = 0;
            max_table_size = max(max_table_size, sets[realDestination].size);
            // merge two components
            // use union by rank heuristic
            // update max_table_size
        }
        
        else {
            sets[realDestination].parent = realSource;
            sets[realSource].size += sets[realDestination].size;
            sets[realDestination].size = 0;
            max_table_size = max(max_table_size, sets[realSource].size);
            if (sets[realDestination].rank == sets[realSource].rank) {
                sets[realSource].rank += 1;
            }
        }
        //print();
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }
    
    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;
        
        tables.merge(destination, source);
        cout << tables.max_table_size << endl;
    }
    
    return 0;
}
