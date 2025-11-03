#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Number of Islands (With Diagonal Connections)
LeetCode Link: https://leetcode.com/problems/number-of-islands/ (modified for diagonal connectivity)

Problem Statement:
------------------
Given a 2D grid of characters consisting of 'L' (land) and 'W' (water),
an island is a group of adjacent 'L' cells connected **horizontally, vertically, or diagonally**.
Count the number of islands.

Example:
Input:
L L W W
L W W L
W L L L
W W W W

Output: 2

Explanation:
There are two islands. The first formed by the top-left L's connected by diagonals and sides.
The second island formed by the bottom-right cluster of L's.

Constraints:
- 1 <= grid.length, grid[0].length <= 300
- grid[i][j] is 'L' or 'W'.
====================================================
*/

/*
==========================================
Approach 1: DFS with 8-directional Connectivity
-------------------------------------------
💡 Idea:
Traverse the entire grid, and for each unvisited 'L', run DFS marking all connected 'L's including diagonals as visited.
Count each such DFS as one island.

🧩 Algorithm:
1. For each cell in grid:
   - If it is 'L', increment island count.
   - Run DFS from that cell marking connected lands with '#'.
2. DFS explores all 8 neighbors (including diagonals).
3. Return island count.

⏱ Time Complexity: O(m*n)
📦 Space Complexity: O(m*n) recursion stack in worst case
*/
class Solution {
public:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 'L') return;

        grid[i][j] = '#';  // mark visited

        for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
                if (k != 0 || l != 0) {
                    dfs(grid, i + k, j + l);
                }
            }
        }
    }

    int countIslands(vector<vector<char>>& grid) {
        int ans = 0;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'L') {
                    ans++;
                    dfs(grid, i, j);
                }
            }
        }
        return ans;
    }
};

/* ========= MAIN FUNCTION ========= */
int main() {
    Solution sol;

    vector<vector<char>> grid1 = {
        {'L', 'L', 'W', 'W'},
        {'L', 'W', 'W', 'L'},
        {'W', 'L', 'L', 'L'},
        {'W', 'W', 'W', 'W'}
    };

    vector<vector<char>> grid2 = {
        {'L', 'W', 'L', 'W'},
        {'W', 'L', 'W', 'L'},
        {'L', 'W', 'L', 'W'},
        {'W', 'L', 'W', 'L'}
    };

    cout << "Test Case 1: Number of Islands = " << sol.countIslands(grid1) << " (Expected: 2)\n";
    cout << "Test Case 2: Number of Islands = " << sol.countIslands(grid2) << " (Expected: 8)\n";

    return 0;
}
