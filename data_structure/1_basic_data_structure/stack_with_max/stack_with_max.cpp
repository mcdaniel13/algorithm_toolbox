#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

class StackWithMax {
    
    vector<int> stack;
    vector<int> stackMax;
    
public:
    
    void Push(int value) {
        if (stackMax.size() != 0)
            stackMax.push_back(max(value, stackMax.back()));
        else
            stackMax.push_back(value);
        stack.push_back(value);
    }
    
    void Pop() {
        assert(stack.size());
        stackMax.pop_back();
        stack.pop_back();
    }
    
    int Max() const {
        return stackMax.back();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;
    
    string query;
    string value;
    
    StackWithMax stack;
    vector<int> MaxPrint;
    
    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            MaxPrint.push_back(stack.Max());
        }
        else {
            assert(0);
        }
    }
    for (int i = 0; i < MaxPrint.size(); ++i) {
        cout << MaxPrint[i] << endl;
    }
    return 0;
}
