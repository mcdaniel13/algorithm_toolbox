#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

//struct Segment {
//    int start, end;
//};

//bool compare(vector<pair<int, int>> &left, vector<pair <int, int>> &right) {
//    return left.first < right.first;
//}

vector<int> optimal_points(vector<pair<int, int>> segments, int n) {
    vector<int> points;
    vector<int> save;
    sort(segments.begin(), segments.end());
    //cout<<"=====func=====optimal_points====="<<endl;
    //cout<<"n = "<<n<<endl;
    //for (size_t j = 0; j < n; ++j) {
    //    cout<<"segments["<<j<<"] = "<<segments[j].first<<' '<<segments[j].second<<endl;
    //}
    
    int i = 0;
    int j = 0;
    
    save.push_back(segments[i].second);
    //cout<<"save["<<i<<"] = "<<save[i]<<endl;
    while(i < n-1) {
        //cout<<"=====while=====loop====="<<endl;
        //cout<<"i = "<<i<<endl;
        if (save[j] >= segments[i+1].first) {
            //cout<<"if_satisfies: save["<<j<<"] ="<<save[j] << " segments["<<i+1<<"].first = "<<segments[i+1].first<<endl;
            if (save[j] <= segments[i+1].second) {
                //cout<<"if_if satisfies: save["<<j<<"] ="<<save[j] << " segments["<<i+1<<"].second = "<<segments[i+1].second<<endl;
                i++;
            }
            else {
                save.pop_back();
                save.push_back(segments[i+1].second);
                //cout<<"if_else_satisfies: save["<<j-1<<"] = "<<save[j]<<endl;
                i++;
            }
        }
        else {
            save.push_back(segments[i+1].second);
            //cout<<"else_satisfies: save["<<j<<"] = "<<save[j]<<endl;
            i++;
            j++;
        }
    }
    return save;
}

int main() {
    int n;
    int a, b;
    std::cin >> n;
    vector<pair <int, int>> segments;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a >> b;
        segments.push_back(make_pair(a,b));
    }
    //for (size_t j = 0; j < n; ++j) {
    //    cout<<"segments["<<j<<"] = "<<segments[j].first<<' '<<segments[j].second<<endl;
    //}
    vector<int> points = optimal_points(segments, n);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}
