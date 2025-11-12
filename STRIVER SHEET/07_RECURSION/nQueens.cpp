#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: N-Queens Problem
 Problem Link: https://leetcode.com/problems/n-queens/

 Problem Statement:
 The n-queens puzzle is the problem of placing `n` queens 
 on an `n x n` chessboard such that no two queens attack each other.

 Return all distinct solutions to the n-queens puzzle.
 Each solution contains a distinct board configuration of the 
 n-queens' placement, where:
   - 'Q' → queen
   - '.' → empty square.

-------------------------------------------------
 Example 1:
 Input: n = 4
 Output: 
 [
   [".Q..","...Q","Q...","..Q."],
   ["..Q.","Q...","...Q",".Q.."]
 ]

 Example 2:
 Input: n = 1
 Output: [["Q"]]
-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Backtracking (Standard)
// -------------------------------------------------
/*
💡 Idea:
   - Place queens row by row.
   - For each row, try every column.
   - Only place a queen if it is "safe" (no other queen in column or diagonals).
   - If we place queens in all rows, record the board as a valid solution.

🧩 Algorithm:
   1. Start with row 0.
   2. For each column col:
        - Check if board[row][col] is safe.
        - If safe, put 'Q', recurse for next row.
        - Backtrack by removing 'Q'.
   3. Collect valid configurations.

⏱ Time Complexity: O(n!)
📦 Space Complexity: O(n^2) for the board
*/

bool isSafe(vector<string>& board, int n, int row, int col) {
    // check vertical column
    for (int i = 0; i < row; i++)
        if (board[i][col] == 'Q') return false;

    // check upper-left diagonal
    for (int i = row-1, j = col-1; i>=0 && j>=0; i--, j--)
        if (board[i][j] == 'Q') return false;

    // check upper-right diagonal
    for (int i = row-1, j = col+1; i>=0 && j<n; i--, j++)
        if (board[i][j] == 'Q') return false;

    return true;
}

void backtrackGenerate(vector<vector<string>>& result, vector<string>& board, int n, int row) {
    if (row == n) {
        result.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (!isSafe(board, n, row, col)) continue;
        board[row][col] = 'Q';
        backtrackGenerate(result, board, n, row+1);
        board[row][col] = '.';
    }
}

vector<vector<string>> solveNQueens_Backtracking(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    backtrackGenerate(result, board, n, 0);
    return result;
}


// -------------------------------------------------
// Approach 2: Optimized Backtracking with HashSets
// -------------------------------------------------
/*
💡 Idea:
   - Instead of scanning diagonals & columns every time, 
     maintain 3 hashsets (or arrays) to track used columns and diagonals.
   - col[c] = true → column `c` already has a queen.
   - diag1[r+c] = true → "\" diagonal is occupied.
   - diag2[r-c+n-1] = true → "/" diagonal is occupied.

🧩 Algorithm:
   1. At each row, loop through columns.
   2. Only place queen if col[c], diag1[r+c], diag2[r-c+n-1] are unused.
   3. Mark them as used, recurse.
   4. Backtrack by unmarking them.

⏱ Time Complexity: O(n!)
📦 Space Complexity: O(n) (for tracking arrays)
*/

void optimizedGenerate(vector<vector<string>>& result, vector<string>& board,
                       int n, int row, vector<int>& col, vector<int>& diag1, vector<int>& diag2) {
    if (row == n) {
        result.push_back(board);
        return;
    }
    for (int c = 0; c < n; c++) {
        if (col[c] || diag1[row+c] || diag2[row-c+n-1]) continue;

        // Place queen
        board[row][c] = 'Q';
        col[c] = diag1[row+c] = diag2[row-c+n-1] = 1;

        optimizedGenerate(result, board, n, row+1, col, diag1, diag2);

        // Backtrack
        board[row][c] = '.';
        col[c] = diag1[row+c] = diag2[row-c+n-1] = 0;
    }
}

vector<vector<string>> solveNQueens_Optimized(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    vector<int> col(n, 0), diag1(2*n, 0), diag2(2*n, 0);

    optimizedGenerate(result, board, n, 0, col, diag1, diag2);
    return result;
}


// -------------------------------------------------
// Approach 3: Count-Only Version (totalNQueens)
// -------------------------------------------------
/*
💡 Idea:
   - Sometimes, the problem only asks for number of solutions.
   - Use same optimized backtracking, but instead of storing boards,
     just increase a counter.

🧩 Algorithm:
   Exactly same as optimized, but return a count instead of storing boards.

⏱ Time Complexity: O(n!)
📦 Space Complexity: O(n)
*/

void countNQueens(int n, int row, vector<int>& col, vector<int>& diag1, vector<int>& diag2, int& count) {
    if (row == n) {
        count++;
        return;
    }
    for (int c = 0; c < n; c++) {
        if (col[c] || diag1[row+c] || diag2[row-c+n-1]) continue;

        col[c] = diag1[row+c] = diag2[row-c+n-1] = 1;
        countNQueens(n, row+1, col, diag1, diag2, count);
        col[c] = diag1[row+c] = diag2[row-c+n-1] = 0;
    }
}

int totalNQueens(int n) {
    int count = 0;
    vector<int> col(n,0), diag1(2*n,0), diag2(2*n,0);
    countNQueens(n, 0, col, diag1, diag2, count);
    return count;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    int n = 4;
    cout << "N-Queens Problem (n = " << n << ")\n\n";

    cout << "Approach 1 (Backtracking - Standard):\n";
    auto res1 = solveNQueens_Backtracking(n);
    for (auto &sol : res1) {
        for (auto &row : sol) cout << row << "\n";
        cout << "------------------\n";
    }

    cout << "\nApproach 2 (Optimized Backtracking with HashSets):\n";
    auto res2 = solveNQueens_Optimized(n);
    for (auto &sol : res2) {
        for (auto &row : sol) cout << row << "\n";
        cout << "------------------\n";
    }

    cout << "\nApproach 3 (Count Solutions Only):\n";
    cout << "Total solutions for n = " << n << " → " << totalNQueens(n) << "\n";

    // -------------------------------------------------
    // ✅ Approach Overview
    // -------------------------------------------------
    /*
    Approach 1 (Plain Backtracking):     TC = O(n!), SC = O(n^2)
    Approach 2 (Optimized with HashSet): TC = O(n!), faster constants, SC = O(n)
    Approach 3 (Count Only):             TC = O(n!), SC = O(n), used when only count required
    */

    return 0;
}
