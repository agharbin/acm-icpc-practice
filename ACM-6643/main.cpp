// Solution for problem #6643 in ICPC Archive

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int letterValue(vector<int> values, char c) {
    if(c == '_'){
        return values[26];
    }
    else {
        return values[c - 'A'];
    }
}

int main() {
    vector<int> values;
    int read_val;
    for(int i = 0; i < 27; ++i){
        cin >> read_val;
        values.push_back(read_val);
    }

    string squares;
    string word;
    while(cin >> squares) {
        cin >> word;
        int result = 0;
        int word_multiplier = 1;
        for(int i = 0; i < squares.length(); ++i) {
            switch(squares[i]){
                case '.':
                    result += letterValue(values, word[i]);
                    break;
                case '2':
                    result += 2 * letterValue(values, word[i]);
                    break;
                case '3':
                    result += 3 * letterValue(values, word[i]);
                    break;
                case 'd':
                    result += letterValue(values, word[i]);
                    word_multiplier *= 2;
                    break;
                case 't':
                    result += letterValue(values, word[i]);
                    word_multiplier *= 3;
                    break;
            }
        }
        cout << result * word_multiplier << endl;
    }
    return 0;
}
