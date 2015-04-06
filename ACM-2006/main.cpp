// Solution to problem #2006 ICPC Archive

#include <map>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    string word;
    char c;
    map<string,int> wordcount;
    string most_frequent;
    int frequency_count = 0;

    while(cin.get(c)) {
        if(c == '#') {
            // End-of-Paragraph
            if(frequency_count != 0){
                cout << setw(4) << frequency_count << ' ' << most_frequent << endl;
            }
            word = "";
            wordcount.clear();
            most_frequent = "";
            frequency_count = 0;
        }
        else if(c >= 'a' && c <= 'z'){
            word += c; // Add to current word
        }
        else if(c >= 'A' && c <= 'Z') {
            c = 'a' + (c - 'A'); // Convert to lower-case
            word += c;
        }
        else {
            if(word.length() != 0){
                // Non-alphabetic character
                if(wordcount.find(word) == wordcount.end()) {
                    wordcount[word] = 1;
                }
                else {
                    ++wordcount[word];
                }
                if(wordcount[word] > frequency_count) {
                    frequency_count = wordcount[word];
                    most_frequent = word;
                }
                word = "";
            }
        }
    }

    return 0;
}
