#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
private:
    int NumOfWorker;
    vector<pair <int, long long>> data_;
    
    
    
    int Parent (int i) {
        return i / 2;
    }
    
    int LeftChild (int i) {
        return 2 * i;
    }
    
    int RightChild(int i) {
        return 2 * i + 1;
    }
    
    bool CompareWorker(pair <int, long long> worker1, pair <int, long long> worker2) {
        if (worker1.second != worker2.second)
            return worker1.second < worker2.second;
        else
            return worker1.first < worker2.first;
        
    }
    void SiftUp (int i) {
        while (i > 1 && CompareWorker(data_[i - 1], data_[Parent(i) - 1])) {
            swap(data_[Parent(i) - 1], data_[i - 1]);
            i = Parent(i);
        }
    }
    
    void SiftDown(int i) {
        int minIndex = i;
        
        int l = LeftChild(i);
        if (l <= data_.size() && CompareWorker(data_[l - 1], data_[minIndex - 1]))
            minIndex = l;
        
        int r = RightChild(i);
        if (r <= data_.size() && CompareWorker(data_[r - 1], data_[minIndex - 1]))
            minIndex = r;
        
        if (i != minIndex) {
            swap(data_[i - 1], data_[minIndex - 1]);
            SiftDown(minIndex);
        }
    }
    
public:
    HeapBuilder(int n): NumOfWorker(n) {
        for (int i = 0; i < NumOfWorker; ++i)
            data_.push_back(make_pair(i, 0));
    }
    
    pair <int, long long> get_data_() {
        return data_[0];
    }
    
    void ChangePriority(int i, long long p) {
        long long old_p = data_[i - 1].second;
        data_[i - 1].second = p;
        if (p < old_p)
            SiftUp(i);
        else
            SiftDown(i);
    }
    
};

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;
    
    vector<int> assigned_workers_;
    vector<long long> start_times_;
    
    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }
    
    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }
    
    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        HeapBuilder MinHeap(num_workers_);
        for (int i = 0; i < jobs_.size(); ++i) {
            assigned_workers_[i] = MinHeap.get_data_().first;
            start_times_[i] = MinHeap.get_data_().second;
            MinHeap.ChangePriority(1, MinHeap.get_data_().second + jobs_[i]);
        }
    }
    
public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
