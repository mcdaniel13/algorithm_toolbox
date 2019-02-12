#include <iostream>
#include <vector>

using namespace std;

int fibonacci_sum_fast(long long n) {
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
        LastDigitFrom = fibonacci_sum_fast(from-1);
    if (LastDigitTo < LastDigitFrom)
        result = LastDigitTo + 10 - LastDigitFrom;
    else
        result = LastDigitTo - LastDigitFrom;
    return result;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
