#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Sudoku Solver
 Problem Link: (LeetCode 37 or similar)
====================================================

📝 Problem Statement:
Given a 9x9 Sudoku board with some cells filled and others empty (denoted by '.'),
fill the empty cells such that the completed board satisfies all Sudoku rules:
1. Each row contains digits 1-9 without repetition.
2. Each column contains digits 1-9 without repetition.
3. Each of the nine 3x3 sub-grids contains digits 1-9 without repetition.

📌 Input:
- 9x9 board of characters (digits or '.' for empty cells)

📌 Output:
- The board filled with digits satisfying Sudoku rules.

----------------------------------------------------
🔹 Example:
Input:
[["5","3",".",".","7",".",".",".","."],
 ["6",".",".","1","9","5",".",".","."],
 [".","9","8",".",".",".",".","6","."],
 ["8",".",".",".","6",".",".",".","3"],
 ["4",".",".","8",".","3",".",".","1"],
 ["7",".",".",".","2",".",".",".","6"],
 [".","6",".",".",".",".","2","8","."],
 [".",".",".","4","1","9",".",".","5"],
 [".",".",".",".","8",".",".","7","9"]]

Output: (One valid solution with all cells filled satisfying Sudoku constraints)
====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Backtracking (DFS) Sudoku Solver
//////////////////////////////////////////////////////
/*
💡 Idea:
- Try each cell sequentially.
- For empty cells, try placing digits 1-9.
- Check if placing digit is valid (no conflicts in row, column, sub-grid).
- Recurse to next cells.
- Backtrack if dead-end encountered.

🧩 Algorithm:
1. Iterate over all cells.
2. If cell empty ('.'):
   a. For digit from '1' to '9':
      i. Check if valid placement.
      ii. Place digit, recurse.
      iii. If recursion returns true, solution found.
      iv. Else backtrack (reset cell to '.').
3. If no empty cells, return true (solved).
4. If no valid digit fits, return false to backtrack.

⏱ Time Complexity: O(9^(N*N)) where N=9 (worst case)  
📦 Space Complexity: O(N*N) for recursion stack
*/

bool isValid(vector<vector<char>> &board, char num, int row, int col) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) return false;
        if (board[i][col] == num) return false;
    }
    int gridRow = (row / 3) * 3, gridCol = (col / 3) * 3;
    for (int i = gridRow; i < gridRow + 3; i++) {
        for (int j = gridCol; j < gridCol + 3; j++) {
            if (board[i][j] == num) return false;
        }
    }
    return true;
}

bool solve(vector<vector<char>> &board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, c, i, j)) {
                        board[i][j] = c;
                        if (solve(board)) return true;
                        else board[i][j] = '.';
                    }
                }
                return false; // No valid digit found
            }
        }
    }
    return true; // Solved
}

void solveSudoku(vector<vector<char>> &board) {
    solve(board);
}

//////////////////////////////////////////////////////
// Main function with example Sudoku puzzle
//////////////////////////////////////////////////////
int main() {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    solveSudoku(board);

    cout << "Solved Sudoku Board:\n";
    for (const auto &row : board) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Backtracking tries all possibilities systematically,
// pruning invalid choices early with isValid checking,
// solving the Sudoku puzzle recursively with backtracking.
