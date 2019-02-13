#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void partition3(vector<int> &a, int l, int r, int & m1, int & m2) {
    int x = a[l];
    int i = l;
    int lt = l;
    int gt = r;
    while (gt >= i){
        if (a[i] < x) {
            swap(a[i], a[lt]);
            i++;
            lt++;
        }
        else if (a[i] == x) {
            i++;
        }
        else {
            swap(a[i], a[gt]);
            gt--;
        }
    }
    m1 = lt;
    m2 = gt;
    return;
}

/*int partition2(vector<int> &a, int l, int r) {
 int x = a[l];
 int j = l;
 for (int i = l + 1; i <= r; i++) {
 if (a[i] <= x) {
 j++;
 swap(a[i], a[j]);
 }
 }
 swap(a[l], a[j]);
 return j;
 }*/

void randomized_quick_sort(vector<int> &a, int l, int r) {
    int m1 = 0;
    int m2 = 0;
    /*if (l >= r) {
     return;
     }*/
    while (l < r) {
        int k = l + rand() % (r - l + 1);
        swap(a[l], a[k]);
        
        partition3(a, l, r, m1, m2);
        
        if ((m1 - l) < (r - m2)) {
            randomized_quick_sort(a, l, m1 - 1);
            l = m2 + 1;
        }
        else {
            randomized_quick_sort(a, m2 + 1, r);
            r = m1 - 1;
        }
        /*int m = partition2(a, l, r);
         
         if ((m - l) < (r - m)) {
         randomized_quick_sort(a, l, m - 1);
         l = m + 1;
         }
         else {
         randomized_quick_sort(a, m + 1, r);
         r = m - 1;
         }*/
    }
    return;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
