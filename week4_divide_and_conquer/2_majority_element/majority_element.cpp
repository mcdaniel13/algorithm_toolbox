#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_majority_element(vector<int> &a, int left, int right) {
    sort(a.begin(),a.end());
    int compare = a[left];
    int count = 1;
    for(int i = 1; i < right; i++) {
        if (compare == a[i]) {
            //cout<<"====compare " << compare << " a["<< i<< "] "<< a[i] << " ====" << endl;
            count++;
            //cout<<"==== in compare = a[i], count = "<<count<<endl;
            if(count > (right-left) / 2) {
                //cout<<"==== count > (right-left) / 2 = " << (right-left)/2 << endl;
                return 1;
            }
        }
        else {
            //cout<<"====compare != a["<< i << "] "<< a[i] << " ====" << endl;
            compare = a[i];
            count = 1;
        }
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
