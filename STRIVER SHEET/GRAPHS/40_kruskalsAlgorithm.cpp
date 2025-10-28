#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Minimum Spanning Tree using Kruskal’s Algorithm
Problem Link: https://www.geeksforgeeks.org/dsa/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/

Problem Statement:
Given an undirected, connected, and weighted graph with V vertices and a list of edges,
find the sum of weights of the edges included in the Minimum Spanning Tree (MST) using Kruskal’s algorithm.

Example:
Input:
V = 5
Edges = [[0,1,2],[0,3,6],[1,2,3],[1,3,8],[1,4,5],[2,4,7]]

Output: 16
Explanation:
MST includes edges (0-1, 1-2, 1-4, 0-3) with total weight = 2 + 3 + 5 + 6 = 16.
*/


// Disjoint Set (Union-Find with Union by Size)
class DisjointSet {
    vector<int> par, size;
public:
    DisjointSet(int n) {
        par.resize(n);
        size.resize(n, 0);
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int findUP(int x) {
        if (x == par[x]) return x;
        return par[x] = findUP(par[x]);
    }

    void unionSet(int u, int v) {
        int uP = findUP(u);
        int vP = findUP(v);
        if (uP == vP) return;

        if (size[vP] > size[uP]) {
            par[uP] = vP;
            size[vP] += size[uP];
        } else {
            par[vP] = uP;
            size[uP] += size[vP];
        }
    }
};


// Approach: Kruskal's Algorithm (Greedy + Disjoint Set)
// 💡 Idea:
// Sort all edges by weight (smallest first). Then iterate through the edges,
// adding each one to the MST **only if** it doesn’t form a cycle (checked using DSU).
// Stop when MST contains (V - 1) edges.
//
// 🧩 Algorithm:
// 1. Sort all edges in ascending order of weight.
// 2. Initialize DisjointSet for V nodes.
// 3. Traverse sorted edges:
//     - If endpoints belong to different sets, unite them and add weight to MST.
// 4. Return the total MST weight.
//
// ⏱ Time Complexity: O(E log E + E α(V)) ≈ O(E log E)
// 📦 Space Complexity: O(V)

class Solution {
public:
    int kruskalsMST(int V, vector<vector<int>>& edges) {
        DisjointSet d(V);
        sort(edges.begin(), edges.end(),
             [](const vector<int> &a, const vector<int> &b) { return a[2] < b[2]; });

        int ans = 0;
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (d.findUP(u) != d.findUP(v)) {
                d.unionSet(u, v);
                ans += w;
            }
        }
        return ans;
    }
};


int main() {
    int V = 5;
    vector<vector<int>> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7}
    };

    Solution s;
    cout << "Total weight of MST: " << s.kruskalsMST(V, edges) << "\n"; // Expected Output: 16
    return 0;
}

/*
✅ Approach Overview:
| Step              | Description                                         |
|-------------------|-----------------------------------------------------|
| Sort edges         | Sort by weight to consider lightest edges first    |
| Use DSU            | Efficiently detect and avoid cycles                |
| Greedy selection   | Always choose smallest available non-cyclic edge   |

| Approach           | Time Complexity | Space Complexity | Notes                             |
|--------------------|----------------|------------------|-----------------------------------|
| Kruskal’s Algorithm| O(E log E)     | O(V)             | Best for edge list representation |

This is the clean, interview-ready implementation of Kruskal’s MST algorithm using Union-Find (with path compression + union by size).
*/
