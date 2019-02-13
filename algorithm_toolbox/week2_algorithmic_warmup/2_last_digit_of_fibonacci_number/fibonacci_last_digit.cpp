#include <iostream>
#include <vector>

using namespace std;

/*int get_fibonacci_last_digit_naive(int n) {
 if (n <= 1)
 return n;
 
 int previous = 0;
 int current  = 1;
 
 for (int i = 0; i < n - 1; ++i) {
 int tmp_previous = previous;
 previous = current;
 current = tmp_previous + current;
 }
 
 return current % 10;
 }*/

int get_fibonacci_last_digit_fast(int n) {
    vector<int> FibArr(n+2);
    
    FibArr[0] = 0;
    FibArr[1] = 1;
    
    for (int i = 2; i <= n; ++i) {
        FibArr[i] = FibArr[i-1] + FibArr[i-2];
    }
    return FibArr[n] % 10;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << get_fibonacci_last_digit_fast(n) << '\n';
}
