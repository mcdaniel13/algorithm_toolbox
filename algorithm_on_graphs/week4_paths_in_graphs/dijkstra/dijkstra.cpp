#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class graph {
private:
    vector<vector<int> > adj;
    vector<vector<int> > cost;
    int start, end;
    
public:
    void init() {
        int n, m;
        std::cin >> n >> m;
        adj.resize(n, vector<int>());
        cost.resize(n, vector<int>());
        for (int i = 0; i < m; i++) {
            int x, y, w;
            std::cin >> x >> y >> w;
            adj[x - 1].push_back(y - 1);
            cost[x - 1].push_back(w);
        }
    }
    
    void set_point() {
        int s, t;
        std::cin >> s >> t;
        s--, t--;
        start = s;
        end = t;
    }
    
    int distance(){
        vector<int> dist(adj.size(), INT_MAX);
        priority_queue<pair<int, int> , vector<pair<int, int>>, greater<pair<int, int>>> MakeQueue;
        
        dist[start] = 0;
        MakeQueue.push(make_pair(dist[start], start));
        
        while (MakeQueue.empty() == false) {
            int currV = MakeQueue.top().second;
            
            MakeQueue.pop();
            
            for (int i = 0; i < adj[currV].size(); ++i) {
                int nextV = adj[currV][i];
                int nextWeight = cost[currV][i];

                    MakeQueue.push(make_pair(dist[nextV], nextV));
                }
            }
        }
        
        return dist[end] != INT_MAX ? dist[end] : -1;
    }
};


int main() {
    graph gr;
    gr.init();
    gr.set_point();
    
    int result = gr.distance();
    
    std::cout << result;
}
