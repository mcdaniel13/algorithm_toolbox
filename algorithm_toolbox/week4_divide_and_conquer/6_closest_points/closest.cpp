#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

bool compareX(pair <int, int> left, pair <int, int> right) {
    return left.first < right.first;
}

bool compareY(pair <int, int> left, pair <int, int> right) {
    return left.second < right.second;
}

double min(double x, double y) {
    if (x < y)
        return x;
    else
        return y;
}

double dist(int x1, int y1, int x2, int y2) {
    double result = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2) * (y1 - y2));
    return result;
}

double brute_force(vector<pair <int, int>> points, size_t left, size_t right) {
    double min = 99999999999999999;
    double compare = 0;
    for (size_t i = left; i < right; i++) {
        for (size_t j = i + 1; j < right; j++) {
            compare = dist(points[i].first, points[i].second, points[j].first, points[j].second);
            if (compare < min) {
                min = compare;
            }
        }
    }
    return min;
}
double closest_points(vector <pair <int, int>> points, size_t left, size_t right, double d_mid) {
    double min = d_mid;
    double compare = 0;
    sort(points.begin(), points.end(), compareY);
    
    for (size_t i = left; i < right; i++) {
        for (size_t j = i + 1; j < right && (points[j].second - points[i].second) < min; j++) {
            compare = dist(points[i].first, points[i].second, points[j].first, points[j].second);
            if (compare < min)
                min = compare;
        }
    }
    return min;
}
double min_dist(vector<pair <int, int>> points, size_t left, size_t right) {
    if(left < right) {
        if (right - left <= 3) {
            return brute_force(points, left, right);
        }
        
        size_t mid = left + (right - left) / 2;
        
        double dist_left = min_dist(points, left, mid);
        double dist_right = min_dist(points, mid, right);
        
        double dist_middle = min(dist_left, dist_right);
        
        vector<pair<int, int>> temp;
        size_t j = 0;
        for (size_t i = left; i < right; i++) {
            if (abs(points[i].first - points[mid].first) < dist_middle) {
                temp.push_back(make_pair(points[i].first, points[i].second));
            }
        }
        double temp_val = closest_points(temp, 0, temp.size(), dist_middle);
        double result = min(dist_middle, temp_val);
        return result;
    }
    else
        return 99999999999999999;
}

double minimal_distance(vector<pair <int, int>> points) {
    sort(points.begin(), points.end(), compareX);
    
    return min_dist(points, 0, points.size());
}

int main() {
    size_t n;
    int x, y;
    std::cin >> n;
    //vector<int> x(n);
    //vector<int> y(n);
    vector<pair <int, int>> points;
    for (size_t i = 0; i < n; i++) {
        std::cin >> x >> y;
        points.push_back(make_pair(x,y));
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << minimal_distance(points) << "\n";
}
