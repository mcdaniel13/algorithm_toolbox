#include <iostream>
#include <vector>

using namespace std;

/*long long fibonacci_sum_squares_naive(long long n) {
 if (n <= 1)
 return n;
 
 long long previous = 0;
 long long current  = 1;
 long long sum      = 1;
 
 for (long long i = 0; i < n - 1; ++i) {
 long long tmp_previous = previous;
 previous = current;
 current = tmp_previous + current;
 sum += current * current;
 }
 
 return sum % 10;
 }*/

long long fibonacci_sum_fast(long long n) {
    vector<int> last_digit = {
        0, 1, 2, 4, 7, 2, 0, 3, 4, 8,
        3, 2, 6, 9, 6, 6, 3, 0, 4, 5,
        0, 6, 7, 4, 2, 7, 0, 8, 9, 8,
        8, 7, 6, 4, 1, 6, 8, 5, 4, 0,
        5, 6, 2, 9, 2, 2, 5, 8, 4, 3,
        8, 2, 1, 4, 6, 1, 8, 0, 9, 0};
    long long result = n % 60;
    return last_digit[result];
}

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    long long result = 0;
    long long LastDigitTo = fibonacci_sum_fast(to);
    long long LastDigitFrom = 0;
    if (from == 0)
        LastDigitFrom = 0;
    else
        LastDigitFrom = fibonacci_sum_fast(from);
    if (LastDigitTo < LastDigitFrom)
        result = LastDigitTo + 10 - LastDigitFrom;
    else
        result = LastDigitTo - LastDigitFrom;
    return result;
}

long long fibonacci_sum_squares_fast(long long n) {
    long long vertical = get_fibonacci_partial_sum_fast(n, n-1);
    long long horizontal = get_fibonacci_partial_sum_fast(n+1, n);
    long long result = (vertical * horizontal) % 10;
    return result;
}
int main() {
    long long n = 0;
    std::cin >> n;
    //std::cout << fibonacci_sum_squares_naive(n)<<endl;
    std::cout << fibonacci_sum_squares_fast(n)<<endl;
}
