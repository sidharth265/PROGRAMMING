#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Number of Enclaves
LeetCode Link: https://leetcode.com/problems/number-of-enclaves/

Problem Statement:
------------------
Given a 2D grid consists of 0s (water) and 1s (land), 
an enclave is a land cell that cannot walk off the boundary by moving only up, down, left, or right.
Return the number of enclaves (land cells not connected to any boundary).

Example 1:
Input: grid = [
  [0,0,0,0],
  [1,0,1,0],
  [0,1,1,0],
  [0,0,0,0]
]
Output: 3

Explanation: 3 land cells are enclosed and not connected to the boundary.

Example 2:
Input: grid = [
  [0,1,1,0],
  [0,0,1,0],
  [0,0,1,0],
  [0,0,0,0]
]
Output: 0

Explanation: All lands are connected to the boundary.

Constraints:
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 500
- grid[i][j] is either 0 or 1
====================================================
*/

/*
==========================================
Approach 1: BFS from Boundary Land Cells
------------------------------------------
💡 Idea:
Count all land cells, then exclude land cells reachable from boundary via BFS.
Remaining land cells are enclaves.

🧩 Algorithm:
1. Initialize totalLand (count of all land cells).
2. Initialize borderLand = 0, and a visited matrix.
3. Enqueue all land cells on the boundary, mark visited, count borderLand.
4. Run BFS from boundary land cells, mark all reachable land as visited and increment borderLand.
5. Enclaves = totalLand - borderLand.

⏱ Time Complexity: O(m*n)
📦 Space Complexity: O(m*n)
*/
int numEnclavesBFS(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<pair<int, int>> q;

    int totalLand = 0, borderLand = 0;
    
    // Count total land cells and enqueue boundary land cells
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                totalLand++;
                if (i == 0 || j == 0 || i == m - 1 || j == n - 1) {
                    visited[i][j] = true;
                    borderLand++;
                    q.push({i, j});
                }
            }
        }
    }

    vector<int> rowAdd = {-1, 0, 1, 0};
    vector<int> colAdd = {0, -1, 0, 1};

    while (!q.empty()) {
        int r = q.front().first, c = q.front().second;
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + rowAdd[k], nc = c + colAdd[k];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && grid[nr][nc] == 1) {
                visited[nr][nc] = true;
                borderLand++;
                q.push({nr, nc});
            }
        }
    }
    return totalLand - borderLand;
}

/*
==========================================
Approach 2: DFS from Boundary Land Cells
------------------------------------------
💡 Idea:
Run DFS from boundary land cells to mark all reachable land cells.
Remaining unmarked land cells are enclaves.

🧩 Algorithm:
1. For all boundaries, if land, run DFS marking visited cells (-1).
2. Finally, count all remaining land cells (1).
3. Restore temporarily marked cells back to 1.

⏱ Time Complexity: O(m*n)
📦 Space Complexity: O(m*n) recursion stack worst case
*/
void dfsMark(vector<vector<int>>& grid, int i, int j, vector<int>& rowAdd, vector<int>& colAdd) {
    int m = grid.size(), n = grid[0].size();
    grid[i][j] = -1; // mark as visited
    for (int k = 0; k < 4; k++) {
        int nr = i + rowAdd[k], nc = j + colAdd[k];
        if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
            dfsMark(grid, nr, nc, rowAdd, colAdd);
        }
    }
}

int numEnclavesDFS(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<int> rowAdd = {-1, 0, 1, 0}, colAdd = {0, -1, 0, 1};

    // Mark lands connected to boundary
    for (int i = 0; i < m; i++) {
        if (grid[i][0] == 1) dfsMark(grid, i, 0, rowAdd, colAdd);
        if (grid[i][n - 1] == 1) dfsMark(grid, i, n - 1, rowAdd, colAdd);
    }
    for (int j = 1; j < n - 1; j++) {
        if (grid[0][j] == 1) dfsMark(grid, 0, j, rowAdd, colAdd);
        if (grid[m - 1][j] == 1) dfsMark(grid, m - 1, j, rowAdd, colAdd);
    }

    // Count enclaves and restore marked cells
    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) ans++;
            else if (grid[i][j] == -1) grid[i][j] = 1; // restore
        }
    }

    return ans;
}

/*
==========================================
Approach 3: Optimal (Choose BFS or DFS based on stack depth constraints)
-------------------------------------------
Both BFS and DFS are O(m*n) time and space, the difference is BFS is iterative,
which can be preferable for large grids to avoid stack overflow.

Recommendation: Use BFS if grid is very large or stack depth is a concern.
*/

/* Main testing function */
int main() {
    vector<vector<int>> grid1 = {
        {0,0,0,0},
        {1,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    vector<vector<int>> grid2 = {
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,0,0}
    };

    cout << "Test Case 1 (BFS): Enclaves = " << numEnclavesBFS(grid1) << "\n";
    cout << "Test Case 1 (DFS): Enclaves = " << numEnclavesDFS(grid1) << "\n";

    cout << "Test Case 2 (BFS): Enclaves = " << numEnclavesBFS(grid2) << "\n";
    cout << "Test Case 2 (DFS): Enclaves = " << numEnclavesDFS(grid2) << "\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. BFS: Iterative marking of boundary connected land cells.\n";
    cout << "2. DFS: Recursive marking of boundary connected land cells.\n";
    cout << "Both approach run in O(m*n) with similar space.\n";
    cout << "BFS preferred to avoid deep recursion in large grids.\n";

    return 0;
}
