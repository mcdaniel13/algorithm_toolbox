#include <iostream>
#include <vector>

using namespace std;

class graph {
public:
    vector<vector<int> > adj;
    vector<bool> isVisited;
    vector<bool> isStacked;
    
    bool isCycle;
    
public:
    void init() {
        size_t n, m;
        std::cin >> n >> m;
        adj.resize(n, vector<int>());
        for (size_t i = 0; i < m; i++) {
            int x, y;
            std::cin >> x >> y;
            adj[x - 1].push_back(y - 1);
        }
    }
    
    void acyclic_internal(int x, int start) {
        isVisited[x] = true;
        
        for (int i = 0; i < adj[x].size(); ++i) {
            if (isVisited[adj[x][i]] == false) {
                acyclic_internal(adj[x][i], start);
            }
            else if (isVisited[adj[x][i]] == true && adj[x][i] == start) {
                isCycle = true;
                break;
            }
        }
    }
    
    bool acyclic() {
        isVisited.resize(adj.size());
        isStacked.resize(adj.size());
        
        isCycle = false;
        
        for (int i = 0; i < isVisited.size(); ++i) {
            isVisited[i] = false;
            isStacked[i] = false;
        }
        
        for (int i = 0; i < adj.size(); ++i) {
            acyclic_internal(i, i);
        }
        //write your code here
        return isCycle;
    }
    
};

int main() {
    graph vertices;
    vertices.init();
    std::cout << vertices.acyclic();
}
