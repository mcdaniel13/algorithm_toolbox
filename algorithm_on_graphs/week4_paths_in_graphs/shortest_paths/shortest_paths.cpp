#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Edge {
    int src, dest, weight;
};

class graph {
private:
    /* For Bellman-Ford */
    vector <Edge> edges;
    vector<long long> dist;
    vector<bool> shortest;
    
    /* For BFS */
    vector<vector<int> > adj;
    vector<int> reachable;
    
    /* For All */
    queue <int> in_queue;
    int V, E;
    int src;
    
public:
    void init() {
        std::cin >> V >> E;
        
        edges.resize(E);
        adj.resize(V, vector<int>());
        dist.resize(V, INT_MAX);
        shortest.resize(V, true);
        reachable.resize(V, false);
        
        for (int i = 0; i < E; i++) {
            int x, y, w;
            std::cin >> x >> y >> w;
            edges[i].src = x - 1;
            edges[i].dest = y - 1;
            edges[i].weight = w;
            adj[x - 1].push_back(y - 1);
        }
        int s;
        cin >> s;
        src = s - 1;
    }
    
    void bellman_ford_algo_for_finding_shortest() {
        dist[src] = 0;
        
        for (int i = 0; i < V - 1; ++i) {
            for (int j = 0; j < E; ++j) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;
                if (dist[u] != INT_MAX && dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        
        for (int j = 0; j < V - 1; ++j) {
            for (int i = 0; i < E; ++i) {
                int u = edges[i].src;
                int v = edges[i].dest;
                int weight = edges[i].weight;
                if (dist[u] != INT_MAX && dist[v] > dist[u] + weight) {
                    in_queue.push(u);
                    in_queue.push(v);
                }
            }
        }
    }
    void bfs_for_finding_shortest() {
        vector<bool> isVisited(V, false);
        
        while (!in_queue.empty()) {
            int current = in_queue.front();
            
            in_queue.pop();
            
            if (isVisited[current])
                continue;
            
            isVisited[current] = true;
            
            for (int i = 0; i < adj[current].size(); ++i) {
                int next = adj[current][i];
                if (!isVisited[next]) {
                    in_queue.push(next);
                }
            }
        }
        
        for (int i = 0; i < V; ++i)
            if (isVisited[i])
                shortest[i] = false;
    }
    
    void bfs_for_finding_reachable () {
        vector<int> distance(V, -1);
        queue<int> Queue;
        
        distance[src] = 0;
        
        Queue.push(src);
        
        while (Queue.empty() == false) {
            int current = Queue.front();
            
            Queue.pop();
            
            for (int i = 0; i < adj[current].size(); ++i) {
                int next = adj[current][i];
                if (distance[next] == -1) {
                    Queue.push(next);
                    distance[next] = distance[current] + 1;
                }
            }
        }
        
        for (int i = 0; i < V; ++i)
            if (distance[i] != -1)
                reachable[i] = true;
    }
    
    
    void print_results() {
        reachable[src] = true;
        for (int i = 0; i < V; i++) {
            if (!reachable[i]) {
                std::cout << "*\n";
            } else if (!shortest[i]) {
                std::cout << "-\n";
            } else {
                std::cout << dist[i] << "\n";
            }
        }
    }
};

int main() {
    graph gr;
    gr.init();
    gr.bellman_ford_algo_for_finding_shortest();
    gr.bfs_for_finding_shortest();
    gr.bfs_for_finding_reachable();
    gr.print_results();
}
