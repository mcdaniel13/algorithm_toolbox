#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/*
 void print(const vector<int>& print) {
 cout << "[ ";
 for(auto &value: print)
 cout << value << ' ';
 cout << "] " << endl;
 }
 */

int get_change(int m) {
    vector<int> coins(3);
    vector<int> MinNumberCoins(m + 1);
    int NumCoins;
    
    // Define the kinds of coin values
    coins[0] = 1;
    coins[1] = 3;
    coins[2] = 4;
    
    //print(coins);
    
    //Initialize all MinNumberCoins to infinite
    for (auto i = 1; i < MinNumberCoins.size(); i++) {
        MinNumberCoins[i] = INT_MAX;
    }
    
    //print(MinNumberCoins);
    
    //Find the minimum number of coins
    for (auto i = 1; i <= m; i++) {
        for (auto j = 0; j < coins.size(); j++) {
            if (i >= coins[j]) {
                NumCoins = MinNumberCoins[i-coins[j]] + 1;
                if (NumCoins < MinNumberCoins[i])
                    MinNumberCoins[i] = NumCoins;
            }
        }
    }
    
    //print(MinNumberCoins);
    
    return MinNumberCoins[m];
    
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
