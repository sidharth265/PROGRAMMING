#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Number of Distinct Islands
GeeksforGeeks Link: https://practice.geeksforgeeks.org/problems/number-of-distinct-islands/1/

Problem Statement:
------------------
Given a 2D grid of 0's and 1's, count the number of distinct islands.
Two islands are considered distinct if one cannot be obtained from the other by 
translation (shifting) only. Rotation/reflection are not considered.

An island is a group of 1's connected 4-directionally (up, down, left, right).

Example:
Input:
grid = [
 [1,1,0,0,0],
 [1,1,0,0,0],
 [0,0,0,1,1],
 [0,0,0,1,1]
]
Output: 1

Explanation:
There is one distinct island shape.

Constraints:
- 1 <= grid.length, grid[0].length <= 50
- grid[i][j] is either 0 or 1
====================================================
*/

/*
==========================================
Approach 1: DFS with relative coordinate recording
------------------------------------------
💡 Idea:
 Encode each island shape by recording relative positions of land cells 
 from the first cell encountered in the island. Use a set to store all unique shapes.

🧩 Algorithm:
1. Iterate over grid cells.
2. For each unvisited land cell:
   - Perform DFS to find all connected land cells.
   - Record relative coordinates (x - x0, y - y0), where (x0, y0) is starting cell.
3. Insert the vector of relative positions into a set to ensure uniqueness.
4. Return the size of the set.

⏱ Time Complexity: O(m*n) since each cell visited once.
📦 Space Complexity: O(m*n) for visited tracking and storing shapes.
*/
class Solution {
    vector<int> rowAdd = {-1, 0, 1, 0};
    vector<int> colAdd = {0, -1, 0, 1};

    void dfs(vector<vector<int>>& grid, int x0, int y0, int x, int y, vector<pair<int, int>>& shape) {
        int m = grid.size(), n = grid[0].size();
        if (x < 0 || y < 0 || x >= m || y >= n || grid[x][y] != 1) 
            return;
        grid[x][y] = -1;  // mark visited
        shape.push_back({x - x0, y - y0});
        for (int k = 0; k < 4; k++) {
            dfs(grid, x0, y0, x + rowAdd[k], y + colAdd[k], shape);
        }
    }

public:
    int countDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<vector<pair<int, int>>> shapes;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    vector<pair<int, int>> shape;
                    dfs(grid, i, j, i, j, shape);
                    shapes.insert(shape);
                }
            }
        }
        return (int)shapes.size();
    }
};

/* ========= MAIN FUNCTION ========= */
int main() {
    Solution sol;

    vector<vector<int>> grid1 = {
        {1,1,0,0,0},
        {1,1,0,0,0},
        {0,0,0,1,1},
        {0,0,0,1,1}
    };

    vector<vector<int>> grid2 = {
        {1,1,0,1,1},
        {1,0,0,0,0},
        {0,0,0,0,1},
        {1,1,0,1,1}
    };

    cout << "Test Case 1: Distinct Islands = " << sol.countDistinctIslands(grid1) << " (Expected: 1)\n";
    cout << "Test Case 2: Distinct Islands = " << sol.countDistinctIslands(grid2) << " (Expected: 3)\n";

    return 0;
}
