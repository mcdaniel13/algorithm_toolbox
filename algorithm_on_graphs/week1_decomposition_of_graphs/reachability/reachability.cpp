#include <iostream>
#include <vector>

using namespace std;

class graph {
private:
    vector<vector<int> > adj;
    vector<bool> visited;
    int x, y;
    
public:
    void print() {
        for (int i = 0; i < adj.size(); ++i) {
            for (int j = 0; j < adj[i].size(); ++j) {
                cout << adj[i][j] + 1 << ' ';
            }
            cout << endl;
        }
    }
    
    void print(vector<bool> &adj) {
        cout << "[ ";
        for (int i = 0; i < adj.size(); i++) {
            cout << adj[i] << ' ';
        }
        cout << "] " << endl;
    }
    
    void insert() {
        size_t n, m;
        std::cin >> n >> m;
        adj.resize(n, vector<int>());
        for (size_t i = 0; i < m; i++) {
            int x, y;
            std::cin >> x >> y;
            adj[x - 1].push_back(y - 1);
            adj[y - 1].push_back(x - 1);
        }
        int x_temp, y_temp;
        std::cin >> x_temp >> y_temp;
        x = x_temp - 1;
        y = y_temp - 1;
    }
    
    void explore(int x, int y) {
        visited[x] = true;
        
        //print(visited);
        
        for (int i = 0; i < adj[x].size(); ++i) {
            if (visited[adj[x][i]] == false)
                explore(adj[x][i], y);
        }
    }
    
    int reach() {
        visited.resize(adj.size());
        
        for (int i = 0; i < visited.size(); ++i) {
            visited[i] = false;
        }
        //print(visited);
        explore(x, y);
        
        return visited[y] == false ? 0 : 1;
    }
};
int main() {
    graph vertices;
    vertices.insert();
    //vertices.print();
    std::cout << vertices.reach();
}
