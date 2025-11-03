#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Path With Minimum Effort
Problem Link: https://leetcode.com/problems/path-with-minimum-effort/

Problem Statement:
Given a 2D grid 'heights' where heights[i][j] represents the height of cell (i, j), find a path from (0, 0) to (m-1, n-1) that minimizes the maximum absolute difference in heights between two consecutive cells along the path. Return the minimum effort required, i.e., the smallest possible value of the maximum difference for any valid path.

Examples:
Input:
heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation:
- Path: (0,0)→(0,1)→(0,2)→(1,2)→(2,2)
- Along the path, the highest absolute difference between consecutive cells is 2.

Input:
heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation:
- Path: (0,0)→(1,0)→(2,0)→(2,1)→(2,2)
- All steps have changes ≤ 1; this is optimal.
*/


// Approach 1: Brute Force DFS (Backtracking with Maximum Jump Tracking)
// 💡 Idea:
// Try all paths recursively, keeping track of maximum 'jump' (difference) along current path. Return minimum effort among all valid paths.
//
// 🧩 Algorithm:
// 1. Use DFS from (0,0) to (m-1,n-1).
// 2. At each move, accumulate the largest encountered difference.
// 3. Prune paths where current maxDiff already exceeds the current global minimum found so far.
// 4. Return minimum overall maximum difference.
//
// ⏱ Time Complexity: O(4^(mn)), exponential
// 📦 Space Complexity: O(mn) for stack

int minEffortDFS;
void dfsBrute(const vector<vector<int>>& heights, int x, int y, int effort, vector<vector<bool>> &visited) {
    int m = heights.size(), n = heights[0].size();
    if (x == m-1 && y == n-1) {
        minEffortDFS = min(minEffortDFS, effort);
        return;
    }
    visited[x][y] = true;
    vector<int> dx = {-1, 0, 1, 0}, dy = {0, -1, 0, 1};
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && ny >= 0 && nx < m && ny < n && !visited[nx][ny]) {
            int jump = abs(heights[nx][ny] - heights[x][y]);
            dfsBrute(heights, nx, ny, max(effort, jump), visited);
        }
    }
    visited[x][y] = false;
}

int minimumEffortPathDFS(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();
    minEffortDFS = INT_MAX;
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    dfsBrute(heights, 0, 0, 0, visited);
    return minEffortDFS;
}


// Approach 2: Binary Search + DFS/BFS (Better, Practical for Large Inputs)
// 💡 Idea:
// The minimum effort answer must be in [0, 1e6]. Binary search on the effort 'limit', and for each 'mid', check using BFS/DFS if path exists where every step ≤ 'mid'.
//
// 🧩 Algorithm:
// 1. Define low=0 and high=max diff in grid (or 1e6).
// 2. For each mid, use DFS/BFS to check reachability from (0,0) to (m-1, n-1) within jumps ≤ mid.
// 3. If path exists, update answer and search lower.
// 4. Otherwise, search higher.
//
// ⏱ Time Complexity: O(mn log(MaxDiff))
// 📦 Space Complexity: O(mn)

bool canReachWithEffort(const vector<vector<int>>& heights, int maxEffort) {
    int m = heights.size(), n = heights[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    queue<pair<int,int>> q;
    q.push({0,0});
    visited[0][0] = true;
    vector<int> dx = {-1, 0, 1, 0}, dy = {0, -1, 0, 1};
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        if (x == m-1 && y == n-1) return true;
        for (int d=0;d<4;d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx>=0&&ny>=0&&nx<m&&ny<n && !visited[nx][ny] && abs(heights[nx][ny]-heights[x][y]) <= maxEffort) {
                visited[nx][ny] = true;
                q.push({nx,ny});
            }
        }
    }
    return false;
}

int minimumEffortPathBinarySearch(vector<vector<int>>& heights) {
    int lo = 0, hi = 1e6, ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        if (canReachWithEffort(heights, mid)) {
            ans = mid;
            hi = mid-1;
        } else {
            lo = mid+1;
        }
    }
    return ans;
}


// Approach 3: Dijkstra's Algorithm (Optimal, Greedy BFS)
// 💡 Idea:
// Treat each cell as a node; cost between two adjacent cells as abs(height diff).
// Use a priority_queue, always move to cell with currently lowest max-effort so far (greedy BFS).
//
// 🧩 Algorithm:
// 1. Use min-heap (dist, x, y). Each pop gives current least max-effort path to (x,y).
// 2. For each neighbor, relax the edge: nextEffort = max(curEffort, jump)
// 3. If found smaller effort for cell, push to heap.
// 4. Stop when destination is reached.
//
// ⏱ Time Complexity: O(mn * log(mn)) due to PQ usage
// 📦 Space Complexity: O(mn)

int minimumEffortPathDijkstra(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;

    vector<int> dx = {-1, 0, 1, 0}, dy = {0, -1, 0, 1};
    while (!pq.empty()) {
        int d = pq.top()[0], x = pq.top()[1], y = pq.top()[2];
        pq.pop();
        if (x == m-1 && y == n-1) return d;
        for (int p=0; p<4; p++) {
            int nx = x+dx[p], ny = y+dy[p];
            if(nx>=0 && ny>=0 && nx<m && ny<n) {
                int diff = max(abs(heights[nx][ny] - heights[x][y]), d);
                if(diff < dist[nx][ny]) {
                    dist[nx][ny] = diff;
                    pq.push({diff, nx, ny});
                }
            }
        }
    }
    return -1;
}


int main() {
    vector<vector<vector<int>>> examples = {
        {{1,2,2},{3,8,2},{5,3,5}},
        {{1,2,3},{3,8,4},{5,3,5}},
        {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}}
    };

    cout << "Dijkstra's Algorithm Solutions:\n";
    for(auto& grid : examples)
        cout << minimumEffortPathDijkstra(grid) << "\n";

    cout << "\nBinary Search + BFS Solutions:\n";
    for(auto& grid : examples)
        cout << minimumEffortPathBinarySearch(grid) << "\n";

    cout << "\nBrute Force DFS (small grid only):\n";
    for(int i=0; i<examples.size() && i<1; i++) // only first example; brute force is slow
        cout << minimumEffortPathDFS(examples[i]) << "\n";

    return 0;
}

/*
✅ Approach Overview:
| Approach              | Time Complexity         | Space Complexity    | Notes                                             |
|-----------------------|------------------------|---------------------|---------------------------------------------------|
| Brute Force DFS       | O(4^(mn))              | O(mn)               | Too slow for large m,n; only tiny grids           |
| Binary Search + BFS   | O(mn log(MaxDiff))     | O(mn)               | Efficient, great for interviews                   |
| Dijkstra (optimal)    | O(mn log(mn))          | O(mn)               | Fastest in practice for large grids, clean logic  |

Use Dijkstra's for clarity and speed. Binary search is great for explaining path-existence by threshold. DFS is only for illustrating recursion.
*/
