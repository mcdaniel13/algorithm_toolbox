#include <iostream>

using namespace std;

long long get_pisano_period2(long long m) {
    long long a = 0;
    long long b = 1;
    long long compare;
    long long result = (a+b) % m;
    for(int i = 1; i <= m*m; ++i) {
        compare = (a+b) % m;
        a = b;
        b = compare;
        if (a == 0 && b == 1) {
            result = i;
            break;
        }
    }
    //cout<<"pisano period = "<<result<<endl;
    return result;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
    long long a = 0;
    long long b = 1;
    long long remainder = n % get_pisano_period2(m);
    //cout<<"remainder = "<<remainder<<endl;
    long long result = remainder;
    
    for(int i = 1; i < remainder; ++i) {
        result = (a+b) % m;
        //cout<<"i="<<i<<' '<<a<<' '<<b<<' '<<result<<endl;
        a = b;
        b = result;
        
    }
    //cout<<"result="<<result<<endl;
    return result % m;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
