// Solution for problem #6484 in ICPC Archive

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printBitString(vector<bool> bits) {
    for(bool b : bits) {
        if(b == false){
            cout << "0";
        } else if(b == true){
            cout << "1";
        }
    }
    cout << endl;
}

vector<bool> convertToBitArray(string input) {
    vector<bool> bits;
    
    for(auto c : input) {
        if(c == '0'){
            bits.push_back(false);
        }
        else if(c == '1') {
            bits.push_back(true);
        }
    }

    return bits;
}

void printSatellites(vector<bool> bits) {
    bool first = true;
    
    for(int i = 1; i < bits.size(); ++i) {
        if(bits[i] == true) { 
            if(first) { cout << i; first = false; } else { cout << " " << i; }

            for(int j = 2*i; j < bits.size(); j = j + i) {
                bits[j] = !bits[j];
            }
        } 
    }
    cout << endl;
}

int main() {
    string input;
    vector<bool> bits;

    while(cin >> input) {
        if(input == "0") { break; }

        bits = convertToBitArray(input);
        
        printSatellites(bits);
    }
}
