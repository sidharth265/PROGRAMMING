#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Shortest Path in Binary Matrix
Problem Link: https://leetcode.com/problems/shortest-path-in-binary-matrix/

Problem Statement:
Given an n x n binary matrix grid, find the length of the shortest clear path from the top-left cell (0,0) to the bottom-right cell (n-1, n-1). Cells with value 0 are open, and 1 are blocked. You may move in 8 directions (vertically, horizontally, or diagonally). The path length is the number of cells visited. If no path exists, return -1.

Examples:
Input:
grid = [
    [0,1],
    [1,0]
]
Output: 2
Explanation:
- Path: (0,0) -> (1,1), length = 2

Input:
grid = [
    [0,0,0],
    [1,1,0],
    [1,1,0]
]
Output: 4
Explanation:
- Path: (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2), length = 4
*/


// Approach 1: Brute Force DFS (Backtracking)
// 💡 Idea:
// Try all possible paths using DFS and backtracking, checking all 8 directions at each cell, marking visited cells, and unmarking them after backtracking.
//
// 🧩 Algorithm:
// 1. If start or end cells are blocked, return -1.
// 2. Use DFS from (0,0), passing current path length and visited matrix.
// 3. At each step, try all 8 directions. If a cell is within bounds and open/visitable, recurse.
// 4. Track minimum path length reaching (n-1, n-1).
//
// ⏱ Time Complexity: O(8^(n*n))
// 📦 Space Complexity: O(n*n) stack depth for backtracking.

int minPath;
void dfsBrute(int x, int y, int n, int d, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
    if (x < 0 || y < 0 || x >= n || y >= n || grid[x][y] != 0 || visited[x][y]) return;
    if (x == n-1 && y == n-1) {
        minPath = min(minPath, d+1);
        return;
    }
    visited[x][y] = true;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0)
                dfsBrute(x+dx, y+dy, n, d+1, grid, visited);
        }
    }
    visited[x][y] = false;
}

int shortestPathBinaryMatrixBrute(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] || grid[n-1][n-1]) return -1;
    minPath = INT_MAX;
    vector<vector<bool>> visited(n, vector<bool>(n,false));
    dfsBrute(0,0,n,0,grid,visited);
    return minPath==INT_MAX?-1:minPath;
}


// Approach 2: BFS (Optimal for Unweighted Graph)
// 💡 Idea:
// Use BFS (level-order traversal) starting from (0,0), propagating outwards in all 8 directions, stopping when the end cell is reached. BFS guarantees shortest path in unweighted graphs.
//
// 🧩 Algorithm:
// 1. If start or end cell blocked, return -1.
// 2. Initialize distance matrix with INT_MAX.
// 3. Use queue for BFS, each state as (distance, x, y).
// 4. At each step, visit all 8 neighbors, update their distance if not yet reached via a shorter path, and push to queue.
// 5. When (n-1, n-1) dequeued, return distance + 1.
//
// ⏱ Time Complexity: O(n^2)
// 📦 Space Complexity: O(n^2) for distances, queue.

int shortestPathBinaryMatrixBFS(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] || grid[n-1][n-1]) return -1;
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    queue<vector<int>> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;

    while (!pq.empty()) {
        int d = pq.front()[0], x0 = pq.front()[1], y0 = pq.front()[2];
        pq.pop();

        if (x0 == n-1 && y0 == n-1) return dist[x0][y0] + 1;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int x = x0 + i, y = y0 + j;
                if (x >= 0 && y >= 0 && x < n && y < n && grid[x][y] == 0 && dist[x][y] > d + 1) {
                    pq.push({d + 1, x, y});
                    dist[x][y] = d + 1;
                    // Optionally mark visited to avoid repeated work:
                    grid[x][y] = -1;
                }
            }
        }
    }
    return -1;
}



int main() {
    vector<vector<vector<int>>> grids = {
        {{0,1},{1,0}},
        {{0,0,0},{1,1,0},{1,1,0}},
        {{1,0},{0,0}}
    };

    // Test Brute Force DFS (small grid only due to time)
    cout << "Brute Force (small grid): " << shortestPathBinaryMatrixBrute(grids[0]) << "\n";

    // BFS (Optimal for all grids)
    for (int i=0;i<grids.size();i++) {
        vector<vector<int>> grid = grids[i];
        cout << "BFS Approach Grid " << i << ": " << shortestPathBinaryMatrixBFS(grid) << "\n";
    }


    return 0;
}

/*
✅ Approach Overview:
| Approach     | Time Complexity      | Space Complexity  | Notes                                           |
|--------------|----------------------|-------------------|-------------------------------------------------|
| Brute Force  | O(8^(n^2))           | O(n^2)            | Very slow, backtracking; only practical for n≤5 |
| BFS          | O(n^2)               | O(n^2)            | Fast, reliable; guaranteed shortest path        |

Use BFS for performance and simplicity on interview; Brute Force for exhaustive checks; A* for advanced/competitive scenarios.
*/
