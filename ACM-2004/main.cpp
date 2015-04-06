// TODO: This solution is unfinished

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum class Color {white, gray, black};

vector< list<int> > edges;
vector<string> routes;
int goal;

void print_stack(vector<int> s){
    for(auto i : s){
        cout << i << " ";
    }
    cout << endl;
}

string toString(vector<int> s){
    string result = "";
    for(int i = 0; i < s.size() - 1; ++i){
        result += std::to_string(s[i]) + " ";
    }
    result += std::to_string(s.back());

    return result;
}

bool lastNodeIsDuplicate(vector<int> s) {
    int back = s.back();
    for(int i = 0; i < s.size() - 1; ++i){
        if(s[i] == back) { return true; }
    }

    return false;
}

void search(vector<int> s) {
    if(lastNodeIsDuplicate(s)) { return; }   
    if(s.back() == goal) { 
        routes.push_back(toString(s));
    }
    else {
        for(int node : edges[s.back()]) {
            s.push_back(node);
            search(s);
            s.pop_back();
        }
    }
}

int main() {
    vector<int> stack;
    int u, v;
    bool firstDataSet = true;

    while(cin >> goal){
        if(!firstDataSet) { 
            cout << endl; 
        } else {
            firstDataSet = false;
        }


        stack.clear();
        routes.clear();
        edges.clear();
        edges.resize(21);

        while(cin >> u >> v) {
            if(u == 0 && v == 0) { break; }

            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        // Exhaustive search

        stack.push_back(1);
        search(stack);

        sort(routes.begin(), routes.end());

        for(auto r : routes) {
            cout << r << endl;
        }
    }

    return 0;
}
