#include <iostream>
#include <vector>

using namespace std;

/*long long fibonacci_sum_fast(long long n) {
 vector<long long> FibArr;
 vector<long long> FibArrLast;
 long long result = 1;
 
 FibArr.push_back(0);
 FibArr.push_back(1);
 //FibArrLast.push_back(0);
 //FibArrLast.push_back(1);
 
 for (int i = 2; i <= n; ++i) {
 FibArr.push_back((long long)(FibArr[i-1] + FibArr[i-2])%10);
 result = result + FibArr[i];
 //FibArrLast.push_back(FibArr[i] % 10);
 }
 
 return result % 10;
 
 }*/

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

int main() {
    long long n = 0;
    std::cin >> n;
    if (n < 1)
        cout << "0" << endl;
    else
        std::cout << fibonacci_sum_fast(n) << endl;
}
