#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class graph {
private:
    vector<vector<int> > adj;
    
    int start;
    int end;
    
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
    
    void set_points() {
        int s, t;
        std::cin >> s >> t;
        s--, t--;
        start = s;
        end = t;
    }
    
    int distance() {
        vector<int> dist(adj.size(), -1);
        queue<int> Queue;
        
        dist[start] = 0;
        
        Queue.push(start);
        
        while (Queue.empty() == false) {
            int current = Queue.front();
            
            Queue.pop();
            
            for (int i = 0; i < adj[current].size(); ++i) {
                int next = adj[current][i];
                if (dist[next] == -1) {
                    Queue.push(next);
                    dist[next] = dist[current] + 1;
                }
            }
        }
        return dist[end];
    }
};

int main() {
    graph vertices;
    vertices.init();
    vertices.set_points();
    std::cout << vertices.distance();
}
