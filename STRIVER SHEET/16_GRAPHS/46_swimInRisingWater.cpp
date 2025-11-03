#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Swim in Rising Water
Problem Link: https://leetcode.com/problems/swim-in-rising-water/

Problem Statement:
You are given an n x n grid of integers grid[i][j] representing the elevation at point (i, j).
You start at (0, 0) and want to reach (n-1, n-1).
You can only move in 4 directions and only to cells with an elevation ≤ current time t.
The water rises with time, so you need to minimize the earliest time you can reach the destination.

Return the least time t such that you can swim from (0, 0) to (n-1, n-1).

Example:
Input: grid = [[0,2],[1,3]]
Output: 3

Explanation:
You must wait until t=3 to reach the bottom right corner.

Input: grid = [[0,1,2,3,4],[24,23,22,21,5], [12,13,14,15,16], [11,17,18,19,20], [10,9,8,7,6]]
Output: 16

Explanation:
You can reach (4,4) at time t=16.
*/


// Approach: Dijkstra's/Priority Queue (Greedy BFS)
// 💡 Idea:
// The problem is to minimize the largest elevation encountered in the path.
// This is analogous to a graph shortest path, where cell (i,j) weight is max(previous, grid[i][j]).
// Use a min-heap to always expand the cell with the lowest possible elevation so far.
//
// 🧩 Algorithm:
// 1. Priority queue {current max elevation to reach (i,j), i, j}, push start cell.
// 2. While queue not empty, pop lowest max-elevation cell.
// 3. If at (n-1, n-1), return its elevation.
// 4. Otherwise, for all 4 neighbors, push {max(elev so far, neighbor elev)} if not visited.
// 5. If never reach destination, return -1.
//
// ⏱ Time Complexity: O(n^2 log n)
// 📦 Space Complexity: O(n^2)

int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;

    q.push({grid[0][0], 0, 0});
    visited[0][0] = true;

    vector<int> rowAdd = {-1, 0, 1, 0}, colAdd = {0, -1, 0, 1};
    while(!q.empty()) {
        int i = q.top()[1];
        int j = q.top()[2];
        int e = q.top()[0];
        q.pop();
        if(i == n-1 && j == n-1) return e;

        for(int p=0; p<4; p++) {
            int x = i + rowAdd[p];
            int y = j + colAdd[p];
            if(x>=0 && y>=0 && x<n && y<n && !visited[x][y]) {
                q.push({max(e, grid[x][y]), x, y});
                visited[x][y] = true;
            }
        }
    }
    return -1;
}


int main() {
    vector<vector<vector<int>>> tests = {
        {{0,2},{1,3}},
        {{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}},
        {{0}},
        {{0, 99}, {99, 0}}
    };
    for(auto& grid : tests)
        cout << "Least time to reach destination: " << swimInWater(grid) << "\n";
    return 0;
}

/*
✅ Approach Overview:
| Step | Description |
|------|-------------|
| Use min-heap | Expand path with smallest possible current max elevation |
| Mark visit   | Avoid cycles, expand only unvisited cells               |
| Greedy      | Reaches end with minimal elevation time                  |

| Approach       | Time Complexity   | Space Complexity | Notes     |
|----------------|------------------|------------------|-----------|
| Dijkstra/Heap  | O(n^2 log n)     | O(n^2)           | Clean, optimal for problem constraints |

This solution is interview-ready, clean, and matches your requested formatting.
*/
