#include <bits/stdc++.h>
using namespace std;
int Hash[9] = {0};

inline bool isValidRow(int Row, int Val) {
    return Hash[Row] & (1<<Val);
}

inline bool isValidCol(int Col, int Val) {
    return Hash[Col] & (1<<(Val+9));
}

inline bool isValid3x3(int i, int j, int Val) {
    return Hash[3*(i/3)+(j/3)] & (1<<(Val+18));
}

void display(vector<vector<char> > &board) {
    for(auto x: board) {
        for(auto y: x)
            cout << y << " ";
        cout << endl;
    }
    cout << endl;
}

void Solve(vector<vector<char> > &board, int i, int j) {
    if(i == board.size() && j == board.size()) 
        display(board);
    
    else if(board[i][j] != '.') {
        if(j == board.size()-1 && i == board.size()-1) 
            display(board);
        else if(j == board.size()-1)
            Solve(board, i+1, 0);
        else 
            Solve(board, i, j+1);
    }
    else {
        bool val = false;
        for(int Val = 0; Val < 9; ++Val) {
            if(!isValidRow(i, Val) && !isValidCol(j, Val) && !isValid3x3(i, j, Val)) {
                Hash[i] |= (1<<Val);
                Hash[j] |= (1<<(Val+9));
                Hash[3*(i/3)+(j/3)] |= (1<<(Val+18));
                
                board[i][j] = Val+'1';
                //////////////////////////////////////////////
                if(j == board.size()-1 && i == board.size()-1) 
                    display(board);
                else if(j == board.size()-1)
                    Solve(board, i+1, 0);
                else 
                    Solve(board, i, j+1);
                //////////////////////////////////////////////
                
                // else {
                Hash[i] ^= (1<<Val);
                Hash[j] ^= (1<<(Val+9));
                Hash[3*(i/3)+(j/3)] ^= (1<<(Val+18));
                board[i][j] = '.';
            }
        }
    }
}

void mark_first(vector<vector<char> > &board) {
    for(int i = 0; i < board.size(); ++i)
        for(int j = 0; j < board.size(); ++j)
            if(board[i][j] != '.') {
                Hash[i] |= (1<<(board[i][j]-'1'));
                Hash[j] |= (1<<((board[i][j]-'1')+9));
                Hash[3*(i/3)+(j/3)] |= (1<<((board[i][j]-'1')+18));
            }
        
}

int main() {
    vector<vector<char> > board = { {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                    {'6', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                    {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                    {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                    {'.', '.', '.', '.', '8', '.', '.', '7', '.'}};

    mark_first(board);
    Solve(board, 0, 0);

    // display(board);

    return 0;
}
