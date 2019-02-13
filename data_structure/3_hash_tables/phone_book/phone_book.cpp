#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

void print(const vector<Query>& contacts) {
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].name != "") {
            cout << "==========================" << endl;
            cout << "contact location = " << i << endl;
            cout << "contact number = " << contacts[i].number << endl;
            cout << "contact name = " << contacts[i].name << endl << endl;
        }
    }
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    vector<string> contacts;
    contacts.resize(10000000);
    for (size_t i = 0; i < queries.size(); ++i) {
        int key = queries[i].number;
        
        if (queries[i].type == "add") {
            contacts[key] = queries[i].name;
            //print(contacts);
        } else if (queries[i].type == "del") {
            contacts[key] = "";
        } else {
            string response;
            if (contacts[key] != "")
                response = contacts[key];
            else
                response = "not found";
            result.push_back(response);
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
