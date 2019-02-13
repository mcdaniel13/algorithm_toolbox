#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    vector<int> arr;
    //write your code here
    int i = 0;
    int j = 0;
    int temp = 0;
    int remain = n;
    
    arr.push_back(1);
    while(1) {
        if(remain >= arr[j]) {
            summands.push_back(arr[j]);
            arr.push_back(arr[j]+1);
            remain -= summands[i];
            j++;
            i++;
        }
        else {
            temp = summands[i-1];
            //cout<<temp<<endl;
            summands.pop_back();
            summands.push_back(remain + temp);
            break;
        }
    }
    return summands;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
