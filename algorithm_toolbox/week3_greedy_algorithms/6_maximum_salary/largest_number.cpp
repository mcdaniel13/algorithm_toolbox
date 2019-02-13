#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using namespace std;

bool compare(string a, string b) {
    return atoi((a+b).c_str()) > atoi((b+a).c_str());
}

string largest_number(vector<string> a) {
    //cout << "=====largest=====number======" << endl;
    
    sort(a.begin(),a.end(), compare);
    //for(size_t i = 0; i <a.size(); i++) {
    //    cout<< "final sort: a[" << i << "] = " << a[i] << endl;
    //}
    std::stringstream ret;
    for (size_t i = 0; i < a.size(); i++) {
        ret << a[i];
    }
    string result;
    ret >> result;
    return result;
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);
}
