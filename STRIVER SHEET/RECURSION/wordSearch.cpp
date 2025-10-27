#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Word Search in 2D Grid
 Problem Link: (LeetCode 79 or similar)
====================================================

📝 Problem Statement:
Given an m x n grid of characters `board` and a string `word`, 
return true if `word` exists in the grid.
The word can be constructed from letters of sequentially adjacent cells, 
where adjacent cells are horizontally or vertically neighboring.
The same letter cell may not be used more than once.

📌 Input:
- A 2D character grid `board`
- A target string `word`

📌 Output:
- Boolean true if word exists, false otherwise

----------------------------------------------------
🔹 Example:
Input:
board = [
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED"

Output: true

Explanation:
Word "ABCCED" can be constructed from adjacent cells in the grid.

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Backtracking with DFS on Grid
//////////////////////////////////////////////////////
/*
💡 Idea:
- For each cell matching the first letter of word, start DFS.
- Move to adjacent cells (up, down, left, right).
- Mark cells visited temporarily to avoid reuse.
- Backtrack on failure.

🧩 Algorithm:
1. Iterate all grid cells.
2. If cell matches word[0], call recursive dfs(i,j, index).
3. dfs returns true if word fully found (index == word.size()).
4. For dfs at position (i,j):
   - Check bounds and matching character.
   - Temporarily mark visited by changing cell to special char.
   - Recursively search all 4 neighbors for next char.
   - Restore cell after searching.
5. Return true if any dfs returns true, else false.

⏱ Time Complexity: O(m * n * 4^l), l = length of word  
📦 Space Complexity: O(l) recursion stack depth
*/

bool find(vector<vector<char>> &board, string &word, int i, int j, int index) {
    if (index == (int)word.size()) return true;
    if (i < 0 || i >= (int)board.size() || j < 0 || j >= (int)board[0].size()) return false;
    if (board[i][j] != word[index]) return false;

    char temp = board[i][j];
    board[i][j] = '#'; // mark visited
    bool found = find(board, word, i, j + 1, index + 1) ||
                 find(board, word, i + 1, j, index + 1) ||
                 find(board, word, i, j - 1, index + 1) ||
                 find(board, word, i - 1, j, index + 1);
    board[i][j] = temp; // restore
    return found;
}

bool exist(vector<vector<char>> &board, string word) {
    for (int i = 0; i < (int)board.size(); i++) {
        for (int j = 0; j < (int)board[0].size(); j++) {
            if (board[i][j] == word[0]) {
                if (find(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
    }
    return false;
}

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };

    string word = "ABCCED";

    if (exist(board, word)) {
        cout << "Word found!" << endl;
    } else {
        cout << "Word not found!" << endl;
    }
    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Backtracking + DFS explores all potential paths,
// marking visited cells to avoid reuse.
// Prunes ineffective paths quickly to find target word.
