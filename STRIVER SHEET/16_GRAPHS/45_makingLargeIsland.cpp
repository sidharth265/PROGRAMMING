#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Making a Large Island (Leetcode 827)
Problem Link: https://leetcode.com/problems/making-a-large-island/

Problem Statement:
Given an n x n binary grid where 1 represents land and 0 represents water,
you may change at most one 0 to 1 (flip at most one cell).
Return the size of the largest island possible by this change.
An island is a group of connected 1s (connected vertically/horizontally).

Example:
Input: grid = [[1,0],[0,1]]
Output: 3

Input: grid = [[1,1],[1,0]]
Output: 4

Input: grid = [[1,1],[1,1]]
Output: 4
*/


// Disjoint Set Union (DSU) with Union by Size
class DSU {
public:
    vector<int> par, size;

    DSU(int n) {
        par.resize(n);
        size.resize(n, 1);
        for(int i=0; i<n; i++) par[i] = i;
    }

    int findP(int x) {
        if(par[x] == x) return x;
        return par[x] = findP(par[x]);
    }

    void unionSet(int u, int v) {
        int up = findP(u), vp = findP(v);
        if(up == vp) return;

        if(size[up] < size[vp]) {
            par[up] = vp;
            size[vp] += size[up];
        }
        else {
            par[vp] = up;
            size[up] += size[vp];
        }
    }
};


// Approach: DSU-based Component Merging for Large Island
// 💡 Idea:
// Treat each cell (i,j) as a DSU node (index i*n + j).
// Unite adjacent land cells to build connected components. For each water cell,
// check which unique islands (components) it can connect by flipping it, and compute the largest size possible.
//
// 🧩 Algorithm:
// 1. Use DSU to union all adjacent land cells.
// 2. Scan original grid for max component size.
// 3. For every water cell:
//   - Gather unique parent IDs of adjacent land (to avoid double-count).
//   - Summing up their sizes + 1 gives new island size if we flip this cell.
//   - Take the largest among all possibilities.
//
// ⏱ Time Complexity: O(N^2)
// 📦 Space Complexity: O(N^2)

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        DSU d(n*n);
        vector<int> rowAdd = {-1, 0, 1, 0}, colAdd = {0, -1, 0, 1};
        
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 0) continue;
                for(int p=0; p<4; p++) {
                    int x = i+rowAdd[p], y = j+colAdd[p];
                    if(x<0 || y<0 || x>=n || y>=n || grid[x][y] == 0) continue;
                    d.unionSet(i*n + j, x*n + y);
                }
            }
        }

        int ans = 0;
        for(int i = 0; i < n*n; ++i) {
            if(d.par[i] == i) ans = max(ans, d.size[i]);
        }

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1) continue;
                unordered_set<int> uniquePar;
                for(int p=0; p<4; p++) {
                    int x = i+rowAdd[p], y = j+colAdd[p];
                    if(x<0 || y<0 || x>=n || y>=n || grid[x][y] == 0) continue;
                    uniquePar.insert(d.findP(x*n + y));
                }
                int islandSize = 1;
                for(int x : uniquePar) islandSize += d.size[x];
                ans = max(ans, islandSize);
            }
        }

        return ans;
    }
};


int main() {
    Solution sol;
    vector<vector<vector<int>>> tests = {
        {{1,0},{0,1}},
        {{1,1},{1,0}},
        {{1,1},{1,1}},
        {{0,0},{0,0}},
        {{1,0,1},{0,1,0},{1,0,1}}
    };
    for(auto& grid : tests) {
        cout << "Largest Island size: " << sol.largestIsland(grid) << "\n";
    }
    return 0;
}

/*
✅ Approach Overview:
| Step              | Description                                 |
|-------------------|---------------------------------------------|
| DSU Merge         | Unite adjacent land cells to build islands   |
| Scan Size         | Track max island size in original grid       |
| Try Flips         | For each water cell, try to join neighbor islands |

| Approach | Time Complexity | Space Complexity | Notes                      |
|----------|----------------|------------------|----------------------------|
| DSU      | O(N^2)         | O(N^2)           | Efficient for dense/sparse grids |

This code is optimized, interview-ready, and strictly formatted per your template.
*/
