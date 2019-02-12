#include <iostream>
#include <vector>

using namespace std;

void print (const vector<vector <int>> & str) {
    cout << "x size would be " << str.size() << endl;
    cout << "y size would be " << str[0].size() << endl;
    for(auto i = 0; i < str.size(); i++) {
        for (auto j = 0; j < str[0].size(); j++)
            cout << str[i][j] << ' ';
        cout << "\n";
    }
}

int partition3 (const vector<int> &A) {
    int sum = 0;
    for(auto &valueA: A) {
        sum += valueA;
    }
    
    if (sum % 3 != 0 || A.size() < 3)
        return 0;
    
    auto x_size = sum/3;
    auto y_size = A.size();
    
    vector <vector <int>> ComparePartition (x_size + 1, vector<int> (y_size + 1));
    
    //print(ComparePartition);
    
    for (auto i = 1; i <= x_size; i++) {
        for (auto j = 1; j <= y_size; j++) {
            int temp = i - A[j-1];
            if ((A[j-1] == i)||(temp > 0 && ComparePartition[temp][j - 1])) {
                if(ComparePartition[i][j-1] == 0)
                    ComparePartition[i][j] = 1;
                else
                    ComparePartition[i][j] = 2;
            }
            else {
                ComparePartition[i][j] = ComparePartition[i][j-1];
            }
            //print(ComparePartition);
        }
    }
    
    if(ComparePartition[x_size][y_size] == 2)
        return 1;
    else
        return 0;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
    return 0;
}

//http://thisthread.blogspot.com/2018/02/partitioning-souvenirs.html
