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

int lcs2(vector<int> &a, vector<int> &b) {
    vector<vector <int>> CompareNum(a.size() + 1, vector<int> (b.size() + 1));
    
    for (auto i = 0; i <= a.size(); i++)
        CompareNum[i][0] = 0;
    for (auto j = 0; j <= b.size(); j++)
        CompareNum[0][j] = 0;
    
    //print(CompareNum);
    
    for (auto i = 1; i <= a.size(); i++) {
        for (auto j = 1; j <= b.size(); j++) {
            int insertion = CompareNum[i][j-1];
            int deletion = CompareNum[i-1][j];
            int match = CompareNum[i-1][j-1] + 1;
            int mismatch = CompareNum[i-1][j-1];
            
            if (a[i-1] == b[j-1])
                CompareNum[i][j] = max(insertion, max(deletion, match));
            else
                CompareNum[i][j] = max(insertion, max(deletion, mismatch));
            //print(CompareNum);
        }
    }
    
    return CompareNum[a.size()][b.size()];
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    
    std::cout << lcs2(a, b) << std::endl;
}
