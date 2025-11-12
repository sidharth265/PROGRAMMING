#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Flood Fill (Leetcode 733)
=========================================================
Given an image represented as a 2D grid, starting from cell (sr, sc),
change the color of all connected cells (up/down/left/right) with the same color to the new color.

Example:
Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
Output: [[2,2,2],[2,2,0],[1,0,1]]

=========================================================
*/

/* ------------------------------------------------------
   Brute Force: BFS Flood Fill (Using Queue)
   ------------------------------------------------------
   💡 Idea:
   Breadth First Search from the start cell, iteratively coloring all adjacent cells
   that match the original color.

   🧩 Algorithm:
   1. If color and original color are the same, return image.
   2. Start BFS from (sr, sc), enqueue initial cell.
   3. For each queue cell, for all 4 directions, color matching cells.
   4. Repeat until no cells are left.

   ⏱ Time Complexity: O(M*N)
   📦 Space Complexity: O(M*N) queue in worst case
------------------------------------------------------ */
vector<vector<int>> floodFill_BFS(vector<vector<int>>& image, int sr, int sc, int color) {
    int orgColor = image[sr][sc];
    int m = image.size(), n = image[0].size();
    if(color == orgColor) return image;
    queue<pair<int, int>> q;
    q.push({sr, sc});
    image[sr][sc] = color;

    vector<int> rowAdd = {-1, 0, 1, 0}, colAdd = {0, -1, 0, 1};
    while(!q.empty()) {
        int l = q.size();
        for(int k=0; k<l; k++) {
            int x = q.front().first, y = q.front().second;
            for(int p=0; p<4; p++) {
                int i = x + rowAdd[p], j = y + colAdd[p];
                if(i>=0 && j>=0 && i<m && j<n && image[i][j] == orgColor) {
                    q.push({i, j});
                    image[i][j] = color;
                }
            }
            q.pop();
        }
    }
    return image;
}

/* ------------------------------------------------------
   Better: DFS Flood Fill (Recursive)
   ------------------------------------------------------
   💡 Idea:
   Recursively visit and color all 4-direction connected cells matching original color.

   🧩 Algorithm:
   1. If color and original color are the same, return image.
   2. Call dfs from (sr, sc).
   3. In dfs, for each direction, recursively call if within bounds and color matches.
   4. Mark colored cells immediately.

   ⏱ Time Complexity: O(M*N)
   📦 Space Complexity: O(M*N) recursion stack
------------------------------------------------------ */
void dfs(vector<vector<int>>& image, int i, int j, int color, int orgColor, vector<int>& rowAdd, vector<int>& colAdd) {
    int m = image.size(), n = image[0].size();
    if(i<0 || j<0 || i>=m || j>=n || image[i][j] != orgColor) return;
    image[i][j] = color;
    for(int k=0; k<4; k++)
        dfs(image, i+rowAdd[k], j+colAdd[k], color, orgColor, rowAdd, colAdd);
}

vector<vector<int>> floodFill_DFS(vector<vector<int>>& image, int sr, int sc, int color) {
    int orgColor = image[sr][sc];
    if(orgColor == color) return image;
    vector<int> rowAdd = {-1, 0, 1, 0}, colAdd = {0, -1, 0, 1};
    dfs(image, sr, sc, color, orgColor, rowAdd, colAdd);
    return image;
}

/* ===================== Main Function ===================== */
int main() {
    vector<vector<int>> image1 = {{1,1,1},{1,1,0},{1,0,1}};
    int sr = 1, sc = 1, color = 2;

    vector<vector<int>> result_bfs = floodFill_BFS(image1, sr, sc, color);
    cout << "BFS Flood Fill Result:\n";
    for(auto& row : result_bfs) {
        for(int v : row) cout << v << " ";
        cout << "\n";
    }

    vector<vector<int>> image2 = {{1,1,1},{1,1,0},{1,0,1}};
    vector<vector<int>> result_dfs = floodFill_DFS(image2, sr, sc, color);
    cout << "DFS Flood Fill Result:\n";
    for(auto& row : result_dfs) {
        for(int v : row) cout << v << " ";
        cout << "\n";
    }

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method | Time Complexity | Space Complexity | Notes                  |
       |--------|-----------------|------------------|------------------------|
       | BFS    | O(M*N)          | O(M*N)           | Iterative, queue based |
       | DFS    | O(M*N)          | O(M*N)           | Recursive, stack based |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
