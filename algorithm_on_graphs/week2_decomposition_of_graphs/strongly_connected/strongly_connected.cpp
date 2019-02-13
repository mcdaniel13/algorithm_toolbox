#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class graph {
public:
    vector<vector<int>> adj;
    vector<vector<int>> reverse_adj;
    
    vector<bool> isVisited;
    
    stack<int> order;
    
public:
    void init() {
        size_t n, m;
        std::cin >> n >> m;
        adj.resize(n, vector<int>());
        reverse_adj.resize(n, vector<int>());
        for (size_t i = 0; i < m; i++) {
            int x, y;
            std::cin >> x >> y;
            adj[x - 1].push_back(y - 1);
            reverse_adj[y - 1].push_back(x - 1);
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
    
    void reverse_dfs(int x) {
        isVisited[x] = true;
        
        for (int i = 0; i < reverse_adj[x].size(); ++i) {
            int child_index = reverse_adj[x][i];
            if (isVisited[child_index] == false)
                reverse_dfs(child_index);
        }
    }
    
    int number_of_strongly_connected_components() {
        int result = 0;
        
        isVisited.resize(adj.size());
        
        for (int i = 0; i < isVisited.size(); ++i)
            isVisited[i] = false;
        
        for (int j = 0; j < adj.size(); ++j) {
            if (isVisited[j] == false)
                dfs(j);
        }
        
        for (int i = 0; i < isVisited.size(); ++i)
            isVisited[i] = false;
        
        while (order.empty() == false){
            int v = order.top();
            order.pop();
            
            if (isVisited[v] == false) {
                reverse_dfs(v);
                result++;
            }
            
        }
        //write your code here
        return result;
    }
    
};


int main() {
    graph vertices;
    
    vertices.init();
    
    int result = vertices.number_of_strongly_connected_components();
    std::cout << result;
}
