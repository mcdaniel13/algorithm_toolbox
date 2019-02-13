#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

class graph {
private:
    vector<vector<int> > adj;
    vector<bool> isVisited;
    stack<int> order;
    
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
    
    void print_order() {
        while (order.empty() == false) {
            cout << order.top() + 1 << " ";
            order.pop();
        }
    }
    
    void dfs(int x) {
        isVisited[x] = true;
        
        for (int i = 0; i < adj[x].size(); ++i) {
            int child_index = adj[x][i];
            if (isVisited[child_index] == false)
                dfs(child_index);
        }
        order.push(x);
    }
    
    void toposort() {
        isVisited.resize(adj.size());
        
        for (int i = 0; i < isVisited.size(); ++i)
            isVisited[i] = false;
        
        
        for (int j = 0; j < isVisited.size(); ++j)
            if(isVisited[j] == false)
                dfs(j);
    }
};

int main() {
    graph vertices;
    vertices.init();
    vertices.toposort();
    vertices.print_order();
}
