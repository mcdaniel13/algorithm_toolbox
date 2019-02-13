#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

class graph {
private:
    vector <Edge> edges;
    vector<int> dist;
    
    int V, E;
    
public:
    void init() {
        std::cin >> V >> E;
        dist.resize(V);
        edges.resize(E);
        for (int i = 0; i < E; i++) {
            int x, y, w;
            std::cin >> x >> y >> w;
            edges[i].src = x - 1;
            edges[i].dest = y - 1;
            edges[i].weight = w - 1;
        }
    }
    
    bool negative_cycle_internal(int src) {
        
        for (int i = 0; i < dist.size(); ++i)
            dist[i] = INT_MAX;
        
        dist[src] = 0;
        
        for (int i = 0; i < V - 1; ++i) {
            for (int j = 0; j < E; ++j) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                if (dist[u] != INT_MAX && dist[v] > dist[u] + weight)
                    dist[v] = dist[u] + weight;
            }
        }
        
        for (int i = 0; i < E; ++i) {
            int u = edges[i].src;
            int v = edges[i].dest;
            int weight = edges[i].weight;
            if (dist[u] != INT_MAX && dist[v] > dist[u] + weight)
                return true;
        }
        
        return false;
    }
    
    bool negative_cycle() {
        vector<bool> isVisited(V);
        
        for (int i = 0; i < V; ++i) {
            if (isVisited[i] == false) {
                if (negative_cycle_internal(i))
                    return true;
                
                for (int i = 0; i < V; ++i) {
                    if (dist[i] != INT_MAX)
                        isVisited[i] = true;
                }
            }
        }
        return false;
    }
};

int main() {
    graph gr;
    gr.init();
    std::cout << gr.negative_cycle();
    //std::cout << gr.negative_cycle_internal();
}
