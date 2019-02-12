#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
 void print(const vector<int> &value) {
 //cerr << "[" ;
 for(auto &val: value) {
 cout << val << ' ';
 }
 //cerr << "] " << endl;
 //cerr << "size = " << value.size() << endl;
 }
 */

std::vector<int> optimal_sequence (int n) {
    std::vector<int> sequence;
    std::vector<int> MinSteps(n + 1);
    std::vector<int> ValueAtSteps(n + 1);
    
    
    for (auto i = 2; i <= n; i++) {
        MinSteps[i] = MinSteps[i-1] + 1;
        ValueAtSteps[i] = i - 1;
        if (i % 2 == 0)
            if (MinSteps[i/2] < MinSteps[i]) {
                MinSteps[i] = MinSteps[i/2] + 1;
                ValueAtSteps[i] = i / 2;
            }
        if (i % 3 ==0)
            if (MinSteps[i/3] < MinSteps[i]) {
                MinSteps[i] = MinSteps[i / 3] + 1;
                ValueAtSteps[i] = i / 3;
            }
    }
    
    //print(MinSteps);
    //print(ValueAtSteps);
    
    for(auto i = n; i != 0; i = ValueAtSteps[i]) {
        sequence.push_back(i);
    }
    
    sort(sequence.begin(), sequence.end());
    
    return(sequence);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence(optimal_sequence(n));
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i)
        std::cout << sequence[i] << " ";
}
