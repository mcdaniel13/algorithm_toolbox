#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

typedef pair<double, int> dPair;

struct Point {
    int x, y;
};

class Graph {
public:
    vector< vector<int> > adj;
    vector< vector<double>> cost;
    vector<Point> points;
    int V;
    
public:
    void print (vector<vector<int>> val) {
        cout << "vector_2d_int" << endl;
        for (int i = 0; i < val.size(); ++i) {
            cout << "[ ";
            for (int j = 0; j < val[i].size(); ++j) {
                cout << val[i][j] << ' ';
            }
            cout << "] " << endl;
        }
    }
    
    void print (vector<vector<double>> val) {
        cout << "vector_2d_double" << endl;
        for (int i = 0; i < val.size(); ++i) {
            cout << "[ ";
            for (int j = 0; j < val[i].size(); ++j) {
                cout << val[i][j] << ' ';
            }
            cout << "] " << endl;
        }
    }
    
    void print (vector<double> val) {
        cout << "val_double" << endl;
        cout << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i] << ' ';
        }
        cout << "] " << endl;
    }
    
    void print (vector<int> val) {
        cout << "val_int" << endl;
        cout << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i] << ' ';
        }
        cout << "] " << endl;
    }
    
    void init() {
        std::cin >> V;
        points.resize(V);
        adj.resize(V, vector<int>());
        cost.resize(V, vector<double>());
        for (size_t i = 0; i < V; i++) {
            std::cin >> points[i].x >> points[i].y;
        }
    }
    
    
    
    double calculate_length(int first, int second) {
        double x = (points[first].x - points[second].x) * (points[first].x - points[second].x);
        double y = (points[first].y - points[second].y) * (points[first].y - points[second].y);
        return sqrt(x + y);
    }
    
    void set_points() {
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                int s = i;
                int d = j;
                double w = calculate_length(i, j);
                
                adj[s].push_back(d);
                adj[d].push_back(s);
                cost[s].push_back(w);
                cost[d].push_back(w);
            }
        }
        //        print(adj);
        //        print(cost);
        
    }
    
    double minimum_distance() {
        double result = 0.;
        
        vector<double> dist(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> isMST(V, false);
        
        priority_queue<dPair, vector<dPair>, greater<dPair>> in_queue;
        
        int start = 0;
        dist[start] = 0;
        
        in_queue.push(make_pair(dist[start], start));
        
        while (!in_queue.empty()) {
            int cur = in_queue.top().second;
            
            in_queue.pop();
            
            isMST[cur] = true;
            
            for (int i = 0; i < adj[cur].size(); ++i) {
                int next = adj[cur][i];
                double weight = cost[cur][i];
                
                if(isMST[next] == false && dist[next] > weight) {
                    dist[next] = weight;
                    in_queue.push(make_pair(dist[next], next));
                    parent[next] = cur;
                }
            }
        }
        
        //        print(parent);
        //        print(dist);
        
        for (int i = 0; i < V; ++i)
            result += dist[i];
        
        return result;
    }
    
};


int main() {
    Graph gr;
    
    gr.init();
    gr.set_points();
    
    std::cout << std::setprecision(10) << gr.minimum_distance() << std::endl;
}
