#include <iostream>
#include <vector>

using namespace std;

void print (const vector<vector <int>> & str) {
    cout << "x size would be " << str.size() << endl;
    cout << "y size would be " << str[0].size() << endl;
    for(auto i = 0; i < str.size(); i++) {
        for (auto j = 0; j < str[0].size(); j++)
            cout << str[i][j];
        cout << "\n";
    }
}

int optimal_weight(int W, const vector<int> &w) {
    vector <vector <int>> ComWeight (W + 1, vector<int> (w.size() + 1));
    
    for (auto i = 0; i < w.size() + 1; i++)
        ComWeight[0][i] = 0;
    for (auto j = 0; j < W + 1; j++)
        ComWeight[j][0] = 0;
    
    //print(ComWeight);
    
    for (auto i = 1; i <= w.size(); i++) {
        for (auto j = 1; j <= W; j++) {
            ComWeight[j][i] = ComWeight[j][i-1];
            if (w[i-1] <= j) {
                int CurWeight = ComWeight[j-w[i-1]][i-1] + w[i-1];
                if (ComWeight[j][i] < CurWeight)
                    ComWeight[j][i] = CurWeight;
            }
            //print(ComWeight);
        }
    }
    return ComWeight[W][w.size()];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
    
}
