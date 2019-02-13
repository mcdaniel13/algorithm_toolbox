#include <iostream>
#include <vector>

using namespace std;

class graph {
private:
    vector<vector<int> > adj;
    vector<bool> visited;
    
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
    }
    
    void explore(int x) {
        visited[x] = true;
        
        //print(visited);
        
        for (int i = 0; i < adj[x].size(); ++i) {
            if (visited[adj[x][i]] == false)
                explore(adj[x][i]);
        }
    }
    
    int number_of_components() {
        int res = 0;
        visited.resize(adj.size());
        
        for (int i = 0; i < visited.size(); ++i) {
            visited[i] = false;
        }
        
        for (int i = 0; i < adj.size(); ++i) {
            if (visited[i] == false) {
                explore(i);
                res += 1;
            }
        }
        return res;
    }
};

int main() {
    graph vertices;
    vertices.insert();
    //vertices.print();
    std::cout << vertices.number_of_components();
}
