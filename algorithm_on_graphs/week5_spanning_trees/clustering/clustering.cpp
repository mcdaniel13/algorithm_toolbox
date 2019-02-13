#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    int x, y, rank, parent;
    
    Point() {
        rank = 0;
        parent = -1;
    }
};

struct Edge {
    int src, dest;
    double dist;
    
    Edge(int s, int d, double w) {
        src = s;
        dest = d;
        dist = w;
    }
};

class Graph {
private:
    vector<Point> points;
    vector<Edge> edges;
    
    int V, K;
    
public:
    void print (vector<Edge> val) {
        cout << "vector_Edge_src" << endl << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i].src << ' ';
        }
        cout << "] " << endl;
        cout << "vector_Edge_dest" << endl << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i].dest << ' ';
        }
        cout << "] " << endl;
        cout << "vector_Edge_dist" << endl << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i].dist << ' ';
        }
        cout << "] " << endl;
    }
    
    void print (vector<Point> val) {
        cout << "vector_point_x" << endl << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i].x << ' ';
        }
        cout << "] " << endl;
        cout << "vector_point_y" << endl << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i].y << ' ';
        }
        cout << "] " << endl;
        cout << "vector_point_rank" << endl << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i].rank << ' ';
        }
        cout << "] " << endl;
        cout << "vector_point_parent" << endl << "[ ";
        for (int i = 0; i < val.size(); ++i) {
            cout << val[i].parent << ' ';
        }
        cout << "] " << endl;
        
    }
    
    void init() {
        std::cin >> V;
        points.resize(V);
        for (size_t i = 0; i < V; i++) {
            int x_val, y_val;
            std::cin >> points[i].x >> points[i].y;
            points[i].parent = i;
        }
        std::cin >> K;
        //print(points);
    }
    
    double calculate_length(int first, int second) {
        double x1 = points[first].x;
        double y1 = points[first].y;
        double x2 = points[second].x;
        double y2 = points[second].y;
        
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    
    void set_points() {
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                int source = i;
                int destination = j;
                double weight = calculate_length(source, destination);
                
                edges.push_back(Edge(source, destination, weight));
            }
        }
        //print(edges);
        //print(points);
    }
    
    static bool sort_by_weight(const Edge &left, const Edge &right) {
        return left.dist < right.dist;
    }
    
    int find_parent(int x) {
        if (x != points[x].parent)
            points[x].parent = find_parent(points[x].parent);
        return points[x].parent;
    }
    
    void union_set(int x_parent, int y_parent) {
        if (points[x_parent].rank > points[y_parent].rank) {
            points[y_parent].parent = x_parent;
        } else {
            points[x_parent].parent = y_parent;
        }
        if (points[x_parent].rank == points[y_parent].rank)
            points[x_parent].rank++;
    }
    
    double clustering() {
        sort(edges.begin(), edges.end(), sort_by_weight);
        
        //        print(edges);
        
        int count_union_num = 0;
        int stopped_edge_num;
        
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i].src;
            int v = edges[i].dest;
            int u_parent = find_parent(u);
            int v_parent = find_parent(v);
            if (u_parent != v_parent) {
                union_set(u_parent, v_parent);
                count_union_num++;
            }
            if (count_union_num > V - K) {
                print(points);
                cout << count_union_num << endl;
                //                return edges[i].dist;
            }
        }
        print(points);
        cout << count_union_num << endl;
        return -1.;
    }
    
    
};

int main() {
    Graph gr;
    gr.init();
    gr.set_points();
    std::cout << std::setprecision(10) << gr.clustering() << std::endl;
}
