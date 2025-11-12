#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: 01 Matrix (Leetcode 542)
=========================================================
Given a binary grid mat, for each cell containing 1,
compute the distance to the nearest 0.

Example:
Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]

=========================================================
*/

/* ------------------------------------------------------
   Approach: Multi-source Level Order BFS (Optimal)
   ------------------------------------------------------ 
   💡 Idea:
   - Start BFS from all 0-cells at once, level by level, filling in nearest distance for each 1-cell from the closest 0-cell.

   🧩 Algorithm:
   1. For every cell (i,j) == 0, put in queue, visited, ans[i][j]=0.
   2. For each BFS round, update adjacent 1-cells with distance.
   3. Continue until all reachable 1-cells have assigned a value.

   ⏱ Time Complexity: O(M*N)
   📦 Space Complexity: O(M*N)
------------------------------------------------------ */
vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> ans(m, vector<int>(n, 0));
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            if(mat[i][j] == 0) {
                q.push({i, j});
                visited[i][j] = true;
            }

    vector<int> rowAdd = {-1, 0, 1, 0}, colAdd = {0, -1, 0, 1};
    int distance = 1;
    while(!q.empty()) {
        int l = q.size();
        for(int k=0; k<l; k++) {
            int x = q.front().first, y = q.front().second;
            for(int p=0; p<4; p++) {
                int i = x + rowAdd[p], j = y + colAdd[p];
                if(i>=0 && j>=0 && i<m && j<n && !visited[i][j] && mat[i][j] == 1) {
                    ans[i][j] = distance;
                    q.push({i, j});
                    visited[i][j] = true;
                }
            }
            q.pop();
        }
        distance++;
    }
    return ans;
}

/* ===================== Main Function ===================== */
int main() {
    vector<vector<int>> mat = {{0,0,0},{0,1,0},{1,1,1}};
    vector<vector<int>> result = updateMatrix(mat);
    cout << "Updated 01 Matrix:\n";
    for(auto& row : result) {
        for(int v : row) cout << v << " ";
        cout << "\n";
    }

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method      | Time Complexity | Space Complexity | Notes                        |
       |-------------|-----------------|------------------|------------------------------|
       | Level BFS   | O(M*N)          | O(M*N)           | Standard grid propagation    |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}

