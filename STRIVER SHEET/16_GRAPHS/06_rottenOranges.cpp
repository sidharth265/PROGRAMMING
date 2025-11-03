#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Rotting Oranges (Leetcode 994)
=========================================================
Given a grid, each cell can be empty (0), a fresh orange (1), or a rotten orange (2).
Every minute, rotten oranges rot adjacent fresh oranges (up, down, left, right).
Return the minimum number of minutes until all oranges are rotten. If impossible, return -1.
*/

/* ------------------------------------------------------
   Multi-Source BFS (Optimal/Standard Solution)
   ------------------------------------------------------
   💡 Idea:
   Start BFS from all initially rotten oranges simultaneously, each level/minute spreads the rot.

   🧩 Algorithm:
   1. Add all rotten oranges to the queue and mark visited.
   2. Each round (minute), spread rot to adjacent fresh oranges, push them to the queue, and mark as visited.
   3. Increment minute counter after each round if queue is non-empty.
   4. At the end, if any fresh orange is left unvisited, return -1.
   5. Otherwise, return the total minutes (ans).

   ⏱ Time Complexity: O(M*N)
   📦 Space Complexity: O(M*N)
------------------------------------------------------ */
int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    int ans = 0;
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(m, vector<bool> (n, false));
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            if(grid[i][j] == 2) {
                q.push({i, j});
                visited[i][j] = true;
            }

    vector<int> rowAdd = {-1, 0, 1, 0}, colAdd = {0, -1, 0, 1};
    while(!q.empty()) {
        int l = q.size();
        for(int k=0; k<l; k++) {
            int x = q.front().first, y = q.front().second;
            for(int p=0; p<4; p++) {
                int i = x + rowAdd[p];
                int j = y + colAdd[p];
                if(i>=0 && i<m && j>=0 && j<n && !visited[i][j] && grid[i][j] == 1) {
                    visited[i][j] = true;
                    q.push({i, j});
                }
            }
            q.pop();
        }
        if(!q.empty()) ans++;
    }
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            if(grid[i][j] == 1 && !visited[i][j]) return -1;
    return ans;
}

/* ===================== Main Function ===================== */
int main() {
    vector<vector<int>> grid = {
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };
    cout << "Minutes until all oranges rot: " << orangesRotting(grid) << "\n";

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method         | Time Complexity | Space Complexity | Notes                      |
       |----------------|----------------|------------------|----------------------------|
       | Multi-Source BFS| O(M*N)         | O(M*N)           | Standard, level order spread|
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
