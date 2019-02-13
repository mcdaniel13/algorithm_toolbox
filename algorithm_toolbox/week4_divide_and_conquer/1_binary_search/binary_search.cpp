#include <iostream>
#include <cassert>
#include <vector>
#include <math.h>

using std::vector;
using namespace std;

int binary_search(const vector<int> &a, int low, int high, int x) {
    //write your code here
    if(high < low) {
        //cout<<"high = "<<high<<" low = "<<low<<" x = "<<x<<endl;
        //cout<<"=====final====="<<endl;
        return -1;
    }
    
    int mid = round (low + (high - low)/2);
    //cout<<"high = "<<high<<" low = "<<low<<" mid = "<<mid<<" a[mid] = "<<a[mid]<<" x = "<<x<<endl;
    if (x == a[mid]) {
        //cout<<"=====equal====="<<endl;
        //cout<<"high = "<<high<<" low = "<<low<<" mid = "<<mid<<" a[mid] = "<<a[mid]<<" x = "<<x<<endl;
        return mid;
    }
    else if (x < a[mid]) {
        //cout<<"=====less====="<<endl;
        //cout<<"high = "<<high<<" low = "<<low<<" mid = "<<mid<<" a[mid] = "<<a[mid]<<" x = "<<x<<endl;
        return binary_search(a, low, mid - 1, x);
    }
    else {
        //cout<<"=====greater====="<<endl;
        //cout<<"high = "<<high<<" low = "<<low<<" mid = "<<mid<<" a[mid] = "<<a[mid]<<" x = "<<x<<endl;
        return binary_search(a, mid + 1, high, x);
    }
}

/*
 int linear_search(const vector<int> &a, int x) {
 for (size_t i = 0; i < a.size(); ++i) {
 if (a[i] == x) return i;
 }
 return -1;
 }
 */

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    int low = 0, high = (int)a.size() - 1;
    int m;
    std::cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    for (int i = 0; i < m; ++i) {
        //replace with the call to binary_search when implemented
        std::cout << binary_search(a, low, high, b[i]) << ' ';
    }
}
