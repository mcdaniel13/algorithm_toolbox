#include <iostream>
using namespace std;

int get_change(int m) {
    int dime = 0;
    int nickel = 0;
    int penny = 0;
    int remain = 0;
    dime = m / 10;
    //cout<<"dime="<<dime<<endl;
    remain = m - dime*10;
    //cout<<"remain="<<remain<<endl;
    nickel = remain / 5;
    //cout<<"nickel="<<nickel<<endl;
    penny = remain - nickel*5;
    //cout<<"penny="<<penny<<endl;
    
    return dime+nickel+penny;
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}

