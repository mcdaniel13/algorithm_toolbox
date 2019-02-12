#include <iostream>
#include <vector>

using namespace std;

/*int gcd_naive(int a, int b) {
 int current_gcd = 1;
 for (int d = 2; d <= a && d <= b; d++) {
 if (a % d == 0 && b % d == 0) {
 if (d > current_gcd) {
 current_gcd = d;
 }
 }
 }
 return current_gcd;
 }*/

int gcd_fast(int a, int b) {
    int i = 0;
    vector<int> first;
    vector<int> second;
    vector<int> compare;
    
    first.push_back(a);
    second.push_back(b);
    
    while(second[i]) {
        //cout << "second[i] = " << second[i] << endl;
        //cout << "i = " << i << endl;
        compare.push_back(first[i] % second[i]);
        first.push_back(second[i]);
        second.push_back(compare[i]);
        i++;
        //cout << first[i] << ' ' << second[i] << ' ' << compare[i] << endl;
    }
    return first[i];
}

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << gcd_fast(a, b) << std::endl;
    return 0;
}
