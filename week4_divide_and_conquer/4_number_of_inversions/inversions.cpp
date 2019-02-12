#include <iostream>
#include <vector>

using std::vector;
using namespace std;

long long merge (vector<int> &a, vector<int> &b, size_t left, size_t mid, size_t right) {
    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;
    
    int count = 0;
    
    while ((i <= mid) && (j <= right)) {
        if (a[i] <= a[j]) {
            b[k] = a[i];
            k++;
            i++;
        }
        else {
            b[k] = a[j];
            k++;
            j++;
            count = count + (mid + 1 - i);
        }
    }
    
    while (i <= mid) {
        b[k] = a[i];
        k++;
        i++;
    }
    
    while (j <= right) {
        b[k] = a[j];
        k++;
        j++;
    }
    
    for(int x = left; x <= right; x++) {
        a[x] = b[x];
    }
    
    return count;
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    long long number_of_inversions = 0;
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        number_of_inversions = get_number_of_inversions(a, b, left, mid);
        number_of_inversions += get_number_of_inversions(a, b, mid + 1, right);
        
        number_of_inversions += merge(a, b, left, mid , right);
    }
    return number_of_inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int> b(a.size());
    cout << get_number_of_inversions(a, b, 0, a.size() - 1) << endl;
}

