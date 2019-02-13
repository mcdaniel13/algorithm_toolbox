#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

struct Request {
    Request(int arrival_time, int process_time):
    arrival_time(arrival_time),
    process_time(process_time)
    {}
    
    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
    dropped(dropped),
    start_time(start_time)
    {}
    
    bool dropped;
    int start_time;
};

struct SelfTime {
    SelfTime(int FinishTime, int PrevProcessingTime):
    FinishTime(FinishTime),
    PrevProcessingTime(PrevProcessingTime)
    
    {}
    
    int FinishTime;
    int PrevProcessingTime;
    
    
};

class Buffer {
public:
    Buffer(int size):
    size_(size),
    finish_time_()
    {}
    
    Response Process(const Request &request) {
        int prevProcessingTime = 0;
        
        if (finish_time_.empty()) {
            prevProcessingTime = request.arrival_time;
            finish_time_.push(SelfTime(request.arrival_time + request.process_time, request.process_time));
            return Response(false, request.arrival_time);
        }
        
        if (request.arrival_time >= finish_time_.front().FinishTime) {
            finish_time_.pop();
        }
        
        if (size_ > finish_time_.size()) {
            if (finish_time_.back().PrevProcessingTime < request.arrival_time)
                prevProcessingTime = request.arrival_time;
            else
                prevProcessingTime = finish_time_.back().PrevProcessingTime;
            finish_time_.push(SelfTime(finish_time_.back().FinishTime + request.process_time,
                                       prevProcessingTime + request.process_time));
            return Response(false, prevProcessingTime);
        } else
            return Response(true, request.arrival_time);
    }
    
private:
    int size_;
    std::queue <SelfTime> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();
    
    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);
    
    PrintResponses(responses);
    return 0;
}
