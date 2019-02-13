#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*void SwapValue(double a, double b) {
 int t = a;
 a = b;
 b = t;
 }
 
 int partition (vector<double> arr, int low, int high) {
 int pivot = arr[high];
 cout<<"arr[high] = "<<arr[high]<<" low = "<<low<<" high = "<<high<<endl;
 int i = low - 1;
 
 for(int k = low; k <= high; k++) {
 cout<<"Partition["<<k<<"] = "<<arr[k] << endl;
 }
 for (int j=low; j <= high - 1; j++) {
 if (arr[j] <= pivot) {
 i++;
 SwapValue(arr[i], arr[j]);
 }
 }
 SwapValue(arr[i+1], arr[high]);
 return (i+1);
 }
 
 void QuickSort(vector<double> arr, int low, int high) {
 if (low < high)
 {
 for(int i = low; i <= high; i++) {
 cout<<"QuickSortArr["<<i<<"] = "<<arr[i] << endl;
 }
 int pi = partition(arr, low, high);
 
 QuickSort(arr, low, pi-1);
 QuickSort(arr, pi+1, high);
 }
 }*/
bool compare(pair<double, int> first, pair<double, int> second) {
    return first.first > second.first;
}

vector<pair <double, int>> SortingValuePerWeight(vector<double> weight, vector<double> values, int n) {
    vector<pair <double, int>> values_per_weight;
    
    for(int i = 0; i < n; i++) {
        values_per_weight.push_back(make_pair(values[i]/weight[i], weight[i]));
        //cout<<"values_per_weight = "<<values_per_weight[i];
        //cout<<" where values = "<<values[i]<<"and weight = "<<weight[i]<<endl;
    }
    //QuickSort(values_per_weight, 0, n-1);
    sort(values_per_weight.begin(), values_per_weight.end(), compare);
    for(int j = 0; j < n; j++) {
        //cout<<"j = "<<j;
        //cout<<" values_per_weight = "<<values_per_weight[j].first << "," << values_per_weight[j].second << endl;
    }
    return values_per_weight;
    
}

double get_optimal_value(int capacity, vector<double> weights, vector<double> values, int n) {
    double value = 0.0;
    double weightleft = capacity;
    int i = 0;
    vector<pair <double, int>> eff = SortingValuePerWeight(weights, values, n);
    while(weightleft > 0) {
        if (weightleft < eff[i].second) {
            value += weightleft * eff[i].first;
            weightleft = 0;
        }
        else {
            weightleft -= eff[i].second;
            value += eff[i].first * eff[i].second;
            i++;
        }
    }
    return value;
}

int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<double> values(n);
    vector<double> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }
    
    double optimal_value = get_optimal_value(capacity, weights, values, n);
    
    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}
