#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>

using namespace std;

struct point {
    explicit point() : x(-1), isStartPoint(-1) {}
    explicit point(int x, int isStartPoint, int PointNum) : x(x), isStartPoint(isStartPoint) {}
    
    int x;
    int isStartPoint;
    /* 0: start, 1: point, 2:end */
};

/* void print(const std::vector<point> &projectedLine){
 std::cerr<<"[";
 for (size_t i = 0; i < projectedLine.size(); i++) {
 std::cerr << projectedLine[i].x << " ";
 }
 std::cerr<<"]"<<std::endl;
 std::cerr<<"[";
 for (size_t i = 0; i < projectedLine.size(); i++) {
 std::cerr << projectedLine[i].isStartPoint << " ";
 }
 std::cerr<<"]"<<std::endl;
 }
 
 void print(const std::vector<int> &results) {
 std::cerr << "results = [";
 for (size_t i = 0; i < results.size(); i++) {
 std::cerr << results[i] << " ";
 }
 std::cerr << "]" << std::endl;
 } */

std::vector<int> howManyIncluded(const std::vector<point> &projectedLine, size_t result_size){
    int howManyInclusion = 0;
    vector<int> results(result_size);
    for(size_t i = 0; i < projectedLine.size(); i++) {
        if(projectedLine[i].isStartPoint >= 0 && projectedLine[i].isStartPoint != 50001) {
            results[projectedLine[i].isStartPoint] = howManyInclusion;
            if(projectedLine[i].isStartPoint == result_size - 1) {
                break;
            }
        }
        else if(projectedLine[i].isStartPoint == -50001)
            howManyInclusion++;
        else if(projectedLine[i].isStartPoint == 50001)
            howManyInclusion--;
    }
    
    return results;
}

std::vector<point> makeProjectedLine(const std::vector<std::pair<int, int>> &ranges, const std::vector<int> &points){
    /* make projected line */
    std::vector<point> projectedLine(ranges.size() * 2 + points.size()); /* should be sorted */
    
    int i = 0;
    for(auto &eachRange : ranges){
        projectedLine[i].x = eachRange.first;
        projectedLine[i].isStartPoint = -50001;
        i++;
        
        projectedLine[i].x = eachRange.second;
        projectedLine[i].isStartPoint = 50001;
        i++;
    }
    
    for(auto j = 0; j < points.size(); j++){
        projectedLine[i].x = points[j];
        projectedLine[i].isStartPoint = j;
        i++;
        
    }
    //std::sort(projectedLine.begin(), projectedLine.end(),
    //          [](point const &lhs, point const &rhs){ return lhs.isStartPoint < rhs.isStartPoint; });
    std::sort(projectedLine.begin(), projectedLine.end(),
              [](point const &lhs, point const &rhs){ return lhs.x < rhs.x; });
    
    return projectedLine;
}



int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> segments (n);
    std::vector<int> points(m);
    std::vector<int> results(points.size());
    
    for(size_t i = 0; i < segments.size(); i++)
        std::cin >> segments[i].first >> segments[i].second;
    
    for (size_t i = 0; i < points.size(); i++)
        std::cin >> points[i];
    
    std::vector<point> projectedLine(makeProjectedLine(segments, points));
    
    results = howManyIncluded(projectedLine, results.size());
    
    for (size_t i = 0; i < points.size(); i++)
        std::cout << results[i] << ' ';
    
    
    //std::mutex resultLock;
    //std::vector<int> results;
    
    //for (size_t i = 0; i < results.size(); i++) {
    //    std::cout << results[i] << ' ';
    //}
    
    //print(projectedLine);
    
    //std::vector<std::thread> threads;
    //results.resize(points.size());
    
    //for (int i = 0; i < points.size(); ++i) {
    //    threads.push_back(std::thread([&, i](){
    //        int result = howManyIncluded(points[i], projectedLine);
    //
    //            resultLock.lock();
    //            results[i] = result;
    //            resultLock.unlock();
    //        }));
    //    }
    
    //    for (auto& th : threads) th.join();
    
    //    for (int i = 0; i < points.size(); ++i){
    //    }
    
    //return 0;
}

