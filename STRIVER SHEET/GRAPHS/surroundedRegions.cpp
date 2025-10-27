#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Surrounded Regions
LeetCode Link: https://leetcode.com/problems/surrounded-regions/

Problem Statement:
------------------
Given an m x n matrix board containing 'X' and 'O', capture all regions that are surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

A region is surrounded if it is completely surrounded by 'X' on all four sides.

Example 1:
Input:
X X X X
X O O X
X X O X
X O X X
Output:
X X X X
X X X X
X X X X
X O X X

Explanation:
The 'O's in positions that are not connected to an edge get flipped.

Constraints:
- m == board.length
- n == board[i].length
- 1 <= m, n <= 200
- board[i][j] is 'X' or 'O'.
====================================================
*/

/* 
==========================================
Approach 1: BFS from Border 'O's
-----------------------------------------
💡 Idea:
All 'O's that are connected to the border cannot be captured. 
Mark these safe 'O's first using BFS, then flip all other 'O's to 'X'.

🧩 Algorithm:
1. Traverse the board edges, enqueue all 'O's found and mark them as safe (change them to '#')
2. Perform BFS to mark all 'O's connected to these border 'O's as safe(by changing to '#')
3. After BFS, flip all unmarked 'O's to 'X' (captured regions)
4. Flip '#' back to 'O' to restore safe regions.

⏱ Time Complexity: O(m*n)
📦 Space Complexity: O(m*n) for the queue in worst case
*/
void solveBFS(vector<vector<char>>& board) {
    if(board.empty()) return;
    int m = board.size(), n = board[0].size();
    queue<pair<int, int>> q;

    // Add all border 'O's to queue & mark as '#'
    for (int i = 0; i < m; i++) {
        if (board[i][0] == 'O') {
            q.push({i, 0});
            board[i][0] = '#';
        }
        if (board[i][n - 1] == 'O') {
            q.push({i, n - 1});
            board[i][n - 1] = '#';
        }
    }
    for (int j = 1; j < n - 1; j++) {
        if (board[0][j] == 'O') {
            q.push({0, j});
            board[0][j] = '#';
        }
        if (board[m - 1][j] == 'O') {
            q.push({m - 1, j});
            board[m - 1][j] = '#';
        }
    }

    vector<int> rowAdd = {-1, 0, 1, 0};
    vector<int> colAdd = {0, -1, 0, 1};

    while (!q.empty()) {
        int r = q.front().first, c = q.front().second;
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + rowAdd[k];
            int nc = c + colAdd[k];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'O') {
                board[nr][nc] = '#';
                q.push({nr, nc});
            }
        }
    }

    // Flip captured regions and restore safe regions
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = (board[i][j] == '#') ? 'O' : 'X';
        }
    }
}

/* 
==========================================
Approach 2: DFS from Border 'O's
-----------------------------------------
💡 Idea:
Similar to BFS, but use DFS to mark safe 'O's starting from the border.

🧩 Algorithm:
1. Traverse board edges and for each 'O', run DFS marking connected 'O's as safe (#)
2. After DFS, flip all unmarked 'O's to 'X'
3. Flip safe '#' back to 'O'

⏱ Time Complexity: O(m*n)
📦 Space Complexity: O(m*n) recursion stack in worst case
*/
void dfsMarkSafe(vector<vector<char>>& board, int i, int j, vector<int>& rowAdd, vector<int>& colAdd) {
    int m = board.size(), n = board[0].size();
    board[i][j] = '#';
    for (int k = 0; k < 4; k++) {
        int r = i + rowAdd[k];
        int c = j + colAdd[k];
        if (r >= 0 && r < m && c >= 0 && c < n && board[r][c] == 'O') {
            dfsMarkSafe(board, r, c, rowAdd, colAdd);
        }
    }
}

void solveDFS(vector<vector<char>>& board) {
    int m = board.size(), n = board[0].size();
    if (m == 0 || n == 0) return;
    vector<int> rowAdd = {-1, 0, 1, 0};
    vector<int> colAdd = {0, -1, 0, 1};

    // Mark safe regions connected to borders
    for (int i = 0; i < m; i++) {
        if (board[i][0] == 'O') dfsMarkSafe(board, i, 0, rowAdd, colAdd);
        if (board[i][n - 1] == 'O') dfsMarkSafe(board, i, n - 1, rowAdd, colAdd);
    }
    for (int j = 1; j < n - 1; j++) {
        if (board[0][j] == 'O') dfsMarkSafe(board, 0, j, rowAdd, colAdd);
        if (board[m - 1][j] == 'O') dfsMarkSafe(board, m - 1, j, rowAdd, colAdd);
    }

    // Flip captured regions and restore safe regions
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = (board[i][j] == '#') ? 'O' : 'X';
        }
    }
}

/* Testing the algorithms */
int main() {
    vector<vector<char>> board1 = {
        {'X','X','X','X'},
        {'X','O','O','X'},
        {'X','X','O','X'},
        {'X','O','X','X'}
    };
    
    vector<vector<char>> board2 = board1;

    cout << "Original Board:\n";
    for (auto& row : board1) {
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    cout << "\n";

    solveBFS(board1);
    cout << "After solveBFS:\n";
    for (auto& row : board1) {
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    cout << "\n";

    solveDFS(board2);
    cout << "After solveDFS:\n";
    for (auto& row : board2) {
        for (char c : row) cout << c << " ";
        cout << "\n";
    }
    cout << "\n";

    /* ✅ Approach Overview */
    cout << "✅ Approach Overview:\n";
    cout << "Both BFS and DFS approaches are efficient and run in O(m*n) time.\n";
    cout << "BFS uses a queue for marking safe cells connected to border 'O's.\n";
    cout << "DFS uses recursion to mark safe cells similarly.\n";
    cout << "Both mark safe cells with '#' and flip captured 'O's to 'X's.\n";
    cout << "For most cases, BFS can be iterative and may avoid deep recursion.\n";
    cout << "DFS can be simpler to implement recursively.\n";

    return 0;
}
