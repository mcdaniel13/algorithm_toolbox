#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class Bucket {
private:
    list<string> items;
public:
    void CHECK () {
        for (list<string>::iterator it = items.begin(); it != items.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
    
    bool FIND(string info) {
        return items.end() != find(items.begin(), items.end(), info);
    }
    
    void ADD (string info) {
        list<string>::iterator it = find(items.begin(), items.end(), info);
        if(it == items.end())
            items.push_front(info);
    }
    
    void DELETE (string info) {
        items.remove(info);
    }
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<Bucket> buckets;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i) {
            size_t hash_temp = hash * multiplier + s[i];
            hash = ((hash_temp % prime) + prime) % prime;
        }
        return ((hash % bucket_count) + bucket_count) % bucket_count;
    }
    
public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        buckets.resize(bucket_count);
    }
    
    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }
    
    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }
    
    void processQuery(const Query& query) {
        int key = (query.type == "check") ? query.ind : hash_func(query.s);
        Bucket &thisBucket = buckets[key];
        
        if (query.type == "check")
            thisBucket.CHECK();
        else if (query.type == "find")
            writeSearchResult(thisBucket.FIND(query.s));
        else if (query.type == "add")
            thisBucket.ADD(query.s);
        else if (query.type == "del")
            thisBucket.DELETE(query.s);
    }
    
    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
