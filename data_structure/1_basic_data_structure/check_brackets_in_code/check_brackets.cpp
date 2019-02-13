#include <iostream>
#include <stack>
#include <string>

using namespace std;


struct Bracket {
    Bracket(char type, int position):
    type(type),
    position(position)
    {}
    
    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }
    
    char type;
    int position;
};

int main() {
    std::string text;
    int count = 0;
    bool isFail = false;
    getline(std::cin, text);
    
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        
        if (next == '(' || next == '[' || next == '{') {
            if(opening_brackets_stack.empty())
                count = position + 1;
            opening_brackets_stack.push(Bracket(next, position));
        }
        else if (next == ')' || next == ']' || next == '}') {
            if (opening_brackets_stack.empty()) {
                isFail = true;
                count = position + 1;
                break;
            }
            bool check = opening_brackets_stack.top().Matchc(next);
            if (!check) {
                isFail = true;
                count = position + 1;
                break;
            }
            else {
                opening_brackets_stack.pop();
            }
        }
    }
    
    if (opening_brackets_stack.empty() && isFail == false)
        cout << "Success" << endl;
    else
        cout << count << endl;
    
    return 0;
}
