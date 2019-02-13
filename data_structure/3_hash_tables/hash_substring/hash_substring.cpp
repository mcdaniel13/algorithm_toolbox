#include <iostream>
#include <string>
#include <vector>
/*
 #include <fstream>
 #include <cassert>
 #include <sstream>
 #include <iomanip>
 */

using namespace std;

typedef unsigned long long ull;

/*string ReadTextFiletoString(fstream &file) {
 if(file.is_open()) {
 string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
 return str;
 } else assert(0);
 }
 
 string ReadTextFiletoString(string filename) {
 fstream infile(filename, fstream::in);
 return ReadTextFiletoString(infile);
 }*/

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

/*Data test_input() {
 Data data;
 string directory("/Users/Cho/Documents/coursera_data_structure/week4_hash_tables/hash_substring/tests/06");
 string text(ReadTextFiletoString(directory));
 
 stringstream input(text);
 
 input >> data.pattern >> data.text;
 return data;
 }*/

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

long long PolyHash(const string& s, size_t p, size_t x) {
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i) {
        size_t hash_temp = hash * x + s[i];
        hash = ((hash_temp % p) + p) % p;
    }
    return hash;
}

vector<long long> PrecomputeHashes(string T, size_t PatternSize, size_t p, size_t x) {
    vector<long long> H(T.size() - PatternSize + 1);
    
    string S = T.substr(T.size() - PatternSize, PatternSize);
    H[T.size() - PatternSize] = PolyHash(S, p, x);
    
    long long y = 1;
    for (size_t i = 1; i <= PatternSize; ++i) {
        size_t y_temp = y * x;
        y = ((y_temp % p) + p) % p;
    }
    for (int j = T.size() - PatternSize - 1; j >= 0; --j) {
        long long h_temp = (x * H[j + 1] + T[j] - y * T[j + PatternSize]);
        H[j] = ((h_temp % p) + p) % p;
    }
    return H;
}

bool AreEqual(const string &TextString, const string &PatternString) {
    if (PatternString.size() != TextString.size())
        return false;
    for (int i = 0; i < PatternString.size(); ++i) {
        if (PatternString[i] != TextString[i])
            return false;
    }
    return true;
}

std::vector<int> get_occurrences(const Data& input) {
    const string &P = input.pattern;
    const string &T = input.text;
    
    static const size_t multiplier = 1;
    static const size_t prime = 1000000007;
    
    long long pHash = PolyHash(P, prime, multiplier);
    //cout << "PatternHash = " << PatternHash << endl;
    vector<int> result;
    vector<long long> H = PrecomputeHashes(T, P.size(), prime, multiplier);
    //vector<int> TestHash(T.size() - P.size());
    
    /*for (size_t i = 0; i + P.size() <= T.size(); ++i) {
     string subText = T.substr(i, P.size());
     TestHash[i] = PolyHash(subText, prime, multiplier);
     }*/
    for (size_t i = 0; i + P.size() <= T.size(); ++i) {
        //cout << "TextHash = " << TextHash << endl;
        if (pHash != H[i])
            continue;
        if (AreEqual(T.substr(i, P.size()), P))
            result.push_back(i);
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
