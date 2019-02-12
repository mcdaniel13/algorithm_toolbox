#include <iostream>
#include <vector>

using namespace std;
void print (const vector < vector < vector <int> > > &value) {
    cout << "size of x = " << value.size() << endl;
    cout << "size of y = " << value[0].size() << endl;
    cout << "size of z = " << value[0][0].size() << endl;
    
    cout << "[ ";
    for (auto i = 0; i < value.size(); i++) {
        for (auto j = 0; j < value[0].size(); j++) {
            for (auto k = 0; k < value[0][0].size(); k++) {
                cout << value[i][j][k] << ' ';
            }
        }
    }
    
    cout<< "]" << endl;
}

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    cout<< "start" << endl;
    vector<vector<vector<int>>> CompareNum (a.size() + 1,
                                            vector<vector<int>> (b.size() + 1, vector<int> (c.size() + 1)));
    
    for (auto i = 0; i <= a.size(); i++)
        for (auto j = 0; j <= b.size(); j++)
            for (auto k = 0; k <= c.size(); k++)
                CompareNum[i][j][k] = 0;
    
    for (auto i = 1; i <= a.size(); i++) {
        for (auto j = 1; j <= b.size(); j++) {
            for (auto k = 1; k <= c.size(); k++) {
                int insertion1 = CompareNum[i][j][k - 1];
                int insertion2 = CompareNum[i][j - 1][k];
                int deletion = CompareNum[i - 1][j][k];
                int match = CompareNum[i - 1][j - 1][k - 1] + 1;
                int mismatch = CompareNum[i - 1][j - 1][k - 1];
                
                if (a[i - 1] == b[j - 1] && a[i - 1] == c[k - 1])
                    CompareNum[i][j][k] = max(max(insertion1, insertion2), max(deletion,match));
                else
                    CompareNum[i][j][k] = max(max(insertion1, insertion2), max(deletion, mismatch));
            }
        }
    }
    
    return CompareNum[a.size()][b.size()][c.size()];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}

