// Solution to problem 6567 in ICPC Archive

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

enum class Move {LEFT, RIGHT, UP, DOWN};
enum class Square {EMPTY, OBSTACLE, USED};

struct Grid {
    std::vector< std::vector<Square> > sqrs;
    int row;
    int col;
    int moves = 0;
};

using namespace std;

int MOVES_EXAMINED = 0;

void printGrid(Grid g);

void printMoveList(vector<Move> v) {
    for(auto m : v){
        switch(m){
            case Move::UP:
                cout << "UP ";
                break;
            case Move::DOWN:
                cout << "DOWN ";
                break;
            case Move::LEFT:
                cout << "LEFT ";
                break;
            case Move::RIGHT:
                cout << "RIGHT ";
                break;
        }
    }
    cout << endl;
}

void findEmptySquare(Grid& g, int& row, int& col) {
    row = -1;
    col = -1;
    for(int i = 0; i < g.sqrs.size(); ++i) {
        for(int j = 0; j < g.sqrs[i].size(); ++j){
            if(g.sqrs[i][j] == Square::EMPTY) {
                row = i;
                col = j;
            }
        }
    }
}

void gridFill(Grid& g, int row, int col) {
    struct Pos {
        int r;
        int c;
    };

    Pos start;
    start.r = row;
    start.c = col;

    queue<Pos> q;
    q.push(start);

    while(!q.empty()){
        Pos curr = q.front();
        q.pop();

        g.sqrs[curr.r][curr.c] = Square::USED;

        Pos next;
        if(curr.r < g.sqrs.size() - 1) { // Move Down
            next.r = curr.r + 1;
            next.c = curr.c;
            if(g.sqrs[next.r][next.c] == Square::EMPTY) {
                q.push(next);
            }
        }
        if(curr.r > 0) { // Move Up
            next.r = curr.r - 1;
            next.c = curr.c;
            if(g.sqrs[next.r][next.c] == Square::EMPTY) {
                q.push(next);
            }
        }
        if(curr.c < g.sqrs[0].size() - 1) { // Move Right
            next.r = curr.r;
            next.c = curr.c + 1;
            if(g.sqrs[next.r][next.c] == Square::EMPTY) {
                q.push(next);
            }
        }
        if(curr.c > 0) { // Move Left
            next.r = curr.r;
            next.c = curr.c - 1;
            if(g.sqrs[next.r][next.c] == Square::EMPTY) {
                q.push(next);
            }
        }
    }
}

bool isDisconnected(Grid g){
    int row, col;
    findEmptySquare(g, row, col);
    gridFill(g, row, col);

    // If no empty square was found, the graph was connected
    findEmptySquare(g, row, col);
    if(row == -1 && col == -1) { return false; }
    else { return true; }
}

bool validMove(Grid g, Move m) {
    int new_row = g.row;
    int new_col = g.col;

    switch(m) {
        case Move::UP:
            --new_row;
            break;
        case Move::DOWN:
            ++new_row;
            break;
        case Move::LEFT:
            --new_col;
            break;
        case Move::RIGHT:
            ++new_col;
            break;
    }

    if(new_row < g.sqrs.size() && new_row >= 0 && new_col < g.sqrs[0].size() && new_col >= 0) {
        if(g.sqrs[new_row][new_col] == Square::EMPTY) {
            return true;
        }
    }
    return false;
}

bool addMoveIfValid(Grid g, vector<Move> &list, Move m){
    if(validMove(g, m)) {
        list.push_back(m);
        return true;
    }
    return false;
}

void updateGridFromMove(Grid &g, Move m) {
    switch(m) {
        case Move::UP:
            while(validMove(g, m)) {
                g.row--;
                g.sqrs[g.row][g.col] = Square::USED;
            }
            break;
        case Move::DOWN:
            while(validMove(g, m)) {
                g.row++;
                g.sqrs[g.row][g.col] = Square::USED;
            }
            break;
        case Move::LEFT:
            while(validMove(g, m)) {
                g.col--;
                g.sqrs[g.row][g.col] = Square::USED;
            }
            break;
        case Move::RIGHT:
            while(validMove(g, m)) {
                g.col++;
                g.sqrs[g.row][g.col] = Square::USED;
            }
            break;
    }
    ++g.moves;
}

void updateGridFromMovelist(Grid &g, vector<Move> list) {
    for(auto m : list) {
        updateGridFromMove(g, m);  
    }
}

bool reachedGoal(Grid g) {
    for(auto i : g.sqrs){
        for(auto j : i){
            if(j == Square::EMPTY) {
                return false;
            }
        }
    }
    return true;
}

int numMoves(Grid g, int currentSmallest){
    queue<Grid> q;
    vector<Move> u, d, l, r;

    // So we don't need to check the ball position to check for win
    g.sqrs[g.row][g.col] = Square::USED; 
    
    Grid g_copy;
    if(validMove(g, Move::UP)){ 
        g_copy = g;
        updateGridFromMove(g_copy, Move::UP); 
        if(!isDisconnected(g_copy)){
            q.push(g_copy);
        }
    }
    if(validMove(g, Move::DOWN)){ 
        g_copy = g;
        updateGridFromMove(g_copy, Move::DOWN); 
        if(!isDisconnected(g_copy)){
            q.push(g_copy);
        }
    }
    if(validMove(g, Move::LEFT)){ 
        g_copy = g;
        updateGridFromMove(g_copy, Move::LEFT); 
        if(!isDisconnected(g_copy)){
            q.push(g_copy);
        }
    }
    if(validMove(g, Move::RIGHT)){ 
        g_copy = g;
        updateGridFromMove(g_copy, Move::RIGHT); 
        if(!isDisconnected(g_copy)){
            q.push(g_copy);
        }
    }
    
    int length;
    bool valid;
    Grid current,next;

    while(!q.empty()){
        current = q.front();
        q.pop();
        ++MOVES_EXAMINED;
        
        if(current.moves >= currentSmallest) { return currentSmallest; }

        if(reachedGoal(current)) { 
            return current.moves; 
        }
        else {
            if(validMove(current, Move::UP)){ 
                next = current;
                updateGridFromMove(next, Move::UP); 
                q.push(next);
            }
            if(validMove(current, Move::DOWN)){ 
                next = current;
                updateGridFromMove(next, Move::DOWN); 
                q.push(next);
            }
            if(validMove(current, Move::LEFT)){ 
                next = current;
                updateGridFromMove(next, Move::LEFT); 
                q.push(next);
            }
            if(validMove(current, Move::RIGHT)){ 
                next = current;
                updateGridFromMove(next, Move::RIGHT); 
                q.push(next);
            }
        }
    }
    return -1;
}

void printGrid(Grid g){
    for(auto i : g.sqrs){
        for(auto j : i){
            switch(j) {
                case Square::OBSTACLE:
                    cout << '*';
                    break;
                case Square::EMPTY:
                    cout << '.';
                    break;
                case Square::USED:
                    cout << 'X';
                    break;
            }
        }
        cout << endl;
    }
}

int solveForAllStartingPos(Grid g, int M, int N) {
    int smallestLength = INT_MAX;
    int length;

    MOVES_EXAMINED = 0;

    for(auto i = 0; i < M; ++i){
        for(auto j = 0; j < N; ++j){
            if(g.sqrs[i][j] != Square::OBSTACLE) {
                g.row = i;
                g.col = j;
                length = numMoves(g, smallestLength);

                if(length != -1 && length < smallestLength) {
                    smallestLength = length;
                }
            }
        }
    }

    if(smallestLength == INT_MAX) { return -1; }
    return smallestLength;
}

Grid readGrid(int M, int N) {
    Grid g;
    char square;

    for(auto i = 0; i < M; ++i){
            vector<Square> row;
            for(auto j = 0; j < N; ++j){
                cin >> square;
                switch(square) {
                    case '*':
                        row.push_back(Square::OBSTACLE);
                        break;
                    case '.':
                        row.push_back(Square::EMPTY);
                        break;
                }
            }
            g.sqrs.push_back(row);
    }

    return g;
}

void parsefile() {
    int m, n;
    char square;
    Grid g;
    int smallestMoves, i;

    i = 1;
    while(cin >> m >> n){
        g = readGrid(m, n);
        smallestMoves = solveForAllStartingPos(g, m, n);
        cout << "Case " << i << ": " << smallestMoves << endl;
        ++i;
    }
}

int main() {
    parsefile();
    return 0;
}
