#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <climits>
#include <stdlib.h>

using namespace std;

void print (const vector<vector <long long>> & str) {
    cout << "x size would be " << str.size() << endl;
    cout << "y size would be " << str[0].size() << endl;
    for(auto i = 0; i < str.size(); i++) {
        for (auto j = 0; j < str[0].size(); j++)
            cout << str[i][j] << ' ';
        cout << "\n";
    }
}
void print (const vector<char> & str) {
    cout << "char vector size wouㅍd be " << str.size() << endl;
    //cout << "y size would be " << str[0].size() << endl;
    for(auto i = 0; i < str.size(); i++) {
        cout << str[i] << ' ';
    }
    cout << "\n";
}

long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}
long long MinAndMax(int i, int j, vector<vector<long long>> MaxNums,
                    vector<vector<long long>> MinNums, vector<char> Operators, int isMax) {
    long long minimum = LONG_LONG_MAX;
    long long maximum = LONG_LONG_MIN;
    
    for (auto k = i; k <= j - 1; k++) {
        long long a = eval(MaxNums[i][k], MaxNums[k+1][j], Operators[k]);
        long long b = eval(MaxNums[i][k], MinNums[k+1][j], Operators[k]);
        long long c = eval(MinNums[i][k], MaxNums[k+1][j], Operators[k]);
        long long d = eval(MinNums[i][k], MinNums[k+1][j], Operators[k]);
        minimum = min(min(minimum, min(a, b)), min(c, d));
        maximum = max(max(maximum, max(a, b)), max(c, d));
    }
    if (isMax)
        return maximum;
    else
        return minimum;
}

long long get_maximum_value(const string &exp) {
    size_t size = exp.length()/2 + 1;
    vector<vector <long long>> MaxNums(size + 1, vector<long long> (size + 1));
    vector<vector <long long>> MinNums(size + 1, vector<long long> (size + 1));
    vector<char> Operators(size);
    //print(MaxNums);
    //print(MinNums);
    
    int j = 1;
    int k = 1;
    for(auto i = 1; i <= exp.length(); i++) {
        if(i % 2 == 1) {
            char temp = exp[i-1];
            MaxNums[j][j] = temp - '0';
            MinNums[j][j] = temp - '0';
            j++;
        }
        else {
            char temp = exp[i-1];
            Operators[k] = temp;
            k++;
        }
    }
    
    //print(MaxNums);
    //print(MinNums);
    //print(Operators);
    
    for(auto s = 1; s <= size - 1; s++) {
        for(auto i = 1; i <= size - s; i++) {
            int temp = i + s;
            MaxNums[i][temp] = MinAndMax(i, temp, MaxNums, MinNums, Operators, 1);
            MinNums[i][temp] = MinAndMax(i, temp, MaxNums, MinNums, Operators, 0);
            //print(MaxNums);
            //print(MinNums);
        }
    }
    return MaxNums[1][size];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
