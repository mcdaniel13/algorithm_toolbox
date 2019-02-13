#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class graph {
private:
    vector<vector<int> > adj;
    
public:
    void init() {
        int n, m;
        std::cin >> n >> m;
        adj.resize(n, vector<int>());
        for (int i = 0; i < m; i++) {
            int x, y;
            std::cin >> x >> y;
            adj[x - 1].push_back(y - 1);
            adj[y - 1].push_back(x - 1);
        }
    }
    
    int bipartite() {
        vector<int> colored(adj.size(), -1);
        queue<int> Queue;
        int start = 0;
        
        colored[start] = 1;
        
        Queue.push(start);
        
        while (Queue.empty() == false) {
            int current = Queue.front();
            
            Queue.pop();
            
            for (int i = 0; i < adj[current].size(); ++i) {
                int next = adj[current][i];
                if (colored[next] == -1) {
                    Queue.push(next);
                    if (colored[current] == 1)
                        colored[next] = 0;
                    else
                        colored[next] = 1;
                }
                else if (colored[next] == colored[current])
                    return false;
            }
        }
        return true;
    }
};

int main() {
    graph gr;
    gr.init();
    
    int result = gr.bipartite();
    std::cout << result;
}
