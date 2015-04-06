// Solution to problem #2007 in the ICPC Archive

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> stack;

void print_stack() {
    for(auto s : stack) {
        cout << s << " ";
    }
    cout << endl;
}

void error(string word) {
    cout << "Expected " << stack.back() << " found " << word << endl;
}

void stack_pop(string word) {
    char c;

    if(stack.back() == word) {
        stack.pop_back();
        if(stack.size() == 0){
            cout << "Correctly tagged paragraph" << endl;
            stack.clear();
            stack.push_back("#");
        }
    } else {
        error(word);
        if(word != "#") { 
            // Consume the rest of the paragraph
            do cin.get(c); while (c != '#');
        }
        stack.clear();
        stack.push_back("#");
    }
}

void stack_push(string word) {
    if(word != "#") { stack.push_back(word.substr(0,1) + "/" + word.substr(1)); }
    else { stack.push_back(word); }
}

int main() {
    char c;
    string word;

    stack_push("#");

    while(cin.get(c)){
        if(c == '\n'){ 
            if(cin.peek() == '#') { break; }
        }
        else if(c == '#') { 
            word = c;
            stack_pop(word);
        } else if(c == '<') {
            word = c;
            cin.get(c);
            if(c == '/') { 
                word += c; 

                cin.get(c);
                if(c >= 'A' && c <= 'Z') { word += c; } else { cin.putback(c); continue; }

                cin.get(c);
                if(c == '>') { word += c; } else { cin.putback(c); continue; }
            } else if (c >= 'A' && c <= 'Z') {
                word += c;

                cin.get(c);
                if(c == '>') { word += c; } else { cin.putback(c); continue; }
            } else {
                cin.putback(c);
                continue;
            }

            // We have the entire tag in 'word', push or pop
            if(word[1] == '/') {
                stack_pop(word);
            } else {
                stack_push(word);
            }
        }
    }
}
