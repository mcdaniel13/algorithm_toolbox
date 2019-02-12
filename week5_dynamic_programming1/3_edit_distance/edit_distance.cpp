#include <iostream>
#include <string>
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

int edit_distance(const string &str1, const string &str2) {
    vector<vector <int>> CompareStr(str1.size() + 1, vector<int> (str2.size() + 1));
    
    //cout << "str1 size would be " << str1.size() << endl;
    //cout << "str2 size would be " << str2.size() << endl;
    
    for (auto i = 0; i <= str1.size(); i++)
        CompareStr[i][0] = i;
    for (auto j = 0; j <= str2.size(); j++)
        CompareStr[0][j] = j;
    
    //print(CompareStr);
    
    for (auto i = 1; i <= str1.size(); i++) {
        for (auto j = 1; j <= str2.size(); j++) {
            int insertion = CompareStr[i][j - 1] + 1;
            int deletion = CompareStr[i - 1][j] + 1;
            int match = CompareStr[i - 1][j - 1];
            int mismatch = CompareStr[i - 1][j - 1] + 1;
            
            if (str1[i-1] == str2[j-1])
                CompareStr[i][j] = min(insertion, min(deletion, match));
            else
                CompareStr[i][j] = min(insertion, min(deletion, mismatch));
            //print(CompareStr);
        }
        //print(CompareStr);
    }
    
    return CompareStr[str1.size()][str2.size()];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
