#include <iostream>
#include <vector>

using namespace std;

/* long long lcm_naive(int a, int b) {
 for (long l = 1; l <= (long long) a * b; ++l)
 if (l % a == 0 && l % b == 0)
 return l;
 
 return (long long) a * b;
 } */

long long gcd_fast(int a, int b) {
    int i = 0;
    vector<long long> first;
    vector<long long> second;
    vector<long long> compare;
    
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

long long lcm_fast(int a, int b) {
    vector<long long> first;
    vector<long long> second;
    
    first.push_back(a);
    second.push_back(b);
    
    return (long long) first[0] * second[0] / gcd_fast(a, b);
}

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << lcm_fast(a, b) << std::endl;
    return 0;
}
