#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;
    
    void print() const {
        cout << "[ ";
        for (int i = 0; i < data_.size(); ++i) {
            cout << data_[i] << " ";
        }
        cout << "] " << endl;
    }
    
    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }
    
    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }
    
    int LeftChild (int i) {
        return 2 * i;
    }
    int RightChild(int i) {
        return 2 * i + 1;
    }
    
    void SiftDown(int i) {
        int minIndex = i;
        int l = LeftChild(i);
        
        if (l <= data_.size() && data_[l - 1] < data_[minIndex - 1])
            minIndex = l;
        int r = RightChild(i);
        
        if (r <= data_.size() && data_[r - 1] < data_[minIndex - 1])
            minIndex = r;
        
        if (i != minIndex) {
            swaps_.push_back(make_pair(i - 1, minIndex - 1));
            swap(data_[i - 1], data_[minIndex - 1]);
            SiftDown(minIndex);
        }
    }
    
    void GenerateSwaps() {
        swaps_.clear();
        
        //print();
        
        int n = data_.size();
        
        for (int i = n / 2; i > 0; --i) {
            SiftDown(i);
            //print();
        }
        // The following naive implementation just sorts
        // the given sequence using selection sort algorithm
        // and saves the resulting sequence of swaps.
        // This turns the given array into a heap,
        // but in the worst case gives a quadratic number of swaps.
        //
    }
    
public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}


def SiftDown(self, i):
minIndex = i
left = self.LeftChild(i)
if left < self.n and self._data[left] < self._data[minIndex]:
minIndex = left

right = self.RightChild(i)
if right < self.n and self._data[right] < self._data[minIndex]:
minIndex = right
if i != minIndex:
self._swaps.append((i, minIndex))
self._data[i], self._data[minIndex] = self._data[minIndex], self._data[i]
self.SiftDown(minIndex)
