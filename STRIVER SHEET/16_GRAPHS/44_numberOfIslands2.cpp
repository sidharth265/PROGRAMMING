#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Number of Islands II (Dynamic Addition)
Problem Link: https://practice.geeksforgeeks.org/problems/number-of-islands/1

Problem Statement:
Given a grid of size n x m initially with all water (0s), process a sequence of operator queries.
Each operator [i, j] turns cell (i, j) from water to land. After each operation, return the current number of islands.
Islands are groups of connected land cells (4 directions).
Use Union-Find (DSU) to efficiently keep track of merging islands as new land is added.

Example:
Input: n = 4, m = 5, operators = [[1,1],[0,1],[3,3],[3,4]]
Output: [1, 1, 2, 2]
Explanation:
After each addition, islands may form and merge in the grid.
*/


// DSU with Union by Size
class DSU {
public :
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
        int up = findP(u);
        int vp = findP(v);
        if(up == vp) return;
        if(size[up] < size[vp]) {
            par[up] = vp;
            size[vp] += size[up];
        } else {
            par[vp] = up;
            size[up] += size[vp];
        }
    }
};


// Approach: DSU on Grid (Online Island Formation)
// 💡 Idea:
// Treat each cell (i, j) as a DSU node (index i*m + j). For each new land addition,
// check neighbors: connect DSU roots and decrement island count if a merge happens.
//
// 🧩 Algorithm:
// 1. Initialize DSU for all nm grid cells; mark all as water (false).
// 2. For each operator, if cell is not land:
//    a. Mark cell as land, increment island count.
//    b. For each 4-direction neighbor, if it's land and disjoint, unite sets and decrement count.
// 3. After each addition, record current count.
//
// ⏱ Time Complexity: O(4 * K α(N * M)) where K = number of operators
// 📦 Space Complexity: O(N * M)

class Solution {
public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        DSU d(n*m);
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int count = 0;
        vector<int> ans;

        vector<int> rowAdd = {-1, 0, 1, 0}, colAdd = {0, -1, 0, 1};
        for(auto& it : operators) {
            int i = it[0], j = it[1];
            if(!visited[i][j]) {
                visited[i][j] = true;
                count++;
                for(int p=0; p<4; p++) {
                    int x = i + rowAdd[p], y = j + colAdd[p];
                    if(x < 0 || y < 0 || x >= n || y >= m || !visited[x][y]) continue;
                    int up = d.findP(x*m + y), vp = d.findP(i*m + j);
                    if(up != vp) {
                        count--;
                        d.unionSet(up, vp);
                    }
                }
            }
            ans.push_back(count);
        }
        return ans;
    }
};


int main() {
    Solution s;
    int n = 4, m = 5;
    vector<vector<int>> ops = {{1,1},{0,1},{3,3},{3,4},{0,0},{1,0}};
    vector<int> result = s.numOfIslands(n, m, ops);
    cout << "Island counts after each step: ";
    for(int v : result) cout << v << " ";
    cout << "\n"; // Expected: [1 1 2 2 3 2]
    return 0;
}

/*
✅ Approach Overview:
| Step | Description |
|------|-------------|
| Add land | Mark new cell, possibly form new island |
| Merge | Connect adjacent land using DSU            |
| Count | Islands merge: decrease count if connected |

| Approach           | Time Complexity   | Space Complexity | Notes           |
|--------------------|------------------|------------------|-----------------|
| DSU for Online Grid| O(K α(NM))       | O(N*M)           | Real-time merge |

This is the optimal and standard DSU approach for **dynamic islands problems**.
*/
