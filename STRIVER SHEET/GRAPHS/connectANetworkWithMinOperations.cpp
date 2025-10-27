#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Number of Operations to Make Network Connected
Problem Link: https://leetcode.com/problems/number-of-operations-to-make-network-connected/

Problem Statement:
There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a network where connections[i] = [a, b] represents a connection between computers a and b.
Any computer can reach any other computer directly or indirectly through the network.

You can remove some cables between two directly connected computers and place them between any pair of disconnected computers.
Return the minimum number of times you need to do this in order to make all the computers connected.
If it is not possible, return -1.

Example 1:
Input: n = 4, connections = [[0,1],[0,2],[1,2]]
Output: 1
Explanation:
Remove the cable between computer 1 and 2 and connect between any one of (1,3) or (2,3).

Example 2:
Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
Output: -1
Explanation:
We have 4 cables but need at least 5 to connect 6 computers, so it's impossible.
*/


// Disjoint Set Union (Union-Find with Union by Size)
class DisjointSet {
public:
    vector<int> par, size;

    DisjointSet(int n) {
        par.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            par[i] = i;
    }

    int findP(int x) {
        if (x == par[x]) return x;
        return par[x] = findP(par[x]);
    }

    void unionSet(int u, int v) {
        int up = findP(u);
        int vp = findP(v);
        if (up == vp) return;

        if (size[up] < size[vp]) {
            par[up] = vp;
            size[vp] += size[up];
        } else {
            par[vp] = up;
            size[up] += size[vp];
        }
    }
};


// Approach: Disjoint Set Union
// 💡 Idea:
// The task is to connect all computers. To connect n computers, we need at least n−1 cables.
// If there aren’t enough cables, return -1.
// Otherwise, count how many connected components (disconnected groups) exist.
// We need (components - 1) operations to connect these groups into one component.
//
// 🧩 Algorithm:
// 1. If connections < n−1, return -1 (not enough cables).
// 2. Initialize DSU for n computers.
// 3. Perform union operations for all given connections.
// 4. Count unique parents (connected components).
// 5. The answer = (#components - 1)
//
// ⏱ Time Complexity: O(E α(V)) ≈ O(E)
// 📦 Space Complexity: O(V)

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) return -1; // Not enough cables

        DisjointSet dsu(n);
        for (auto& edge : connections)
            dsu.unionSet(edge[0], edge[1]);

        int components = 0;
        for (int i = 0; i < n; i++)
            if (dsu.findP(i) == i)
                components++;

        return components - 1;
    }
};


int main() {
    Solution s;

    vector<vector<int>> conn1 = {{0,1},{0,2},{1,2}};
    cout << "Example 1 Output: " << s.makeConnected(4, conn1) << "\n"; // Expected 1

    vector<vector<int>> conn2 = {{0,1},{0,2},{0,3},{1,2}};
    cout << "Example 2 Output: " << s.makeConnected(6, conn2) << "\n"; // Expected -1

    vector<vector<int>> conn3 = {{0,1},{0,2},{3,4},{2,3}};
    cout << "Example 3 Output: " << s.makeConnected(5, conn3) << "\n"; // Expected 0

    return 0;
}

/*
✅ Approach Overview:
| Step | Description |
|------|-------------|
| 1 | Check if we have at least (n−1) edges |
| 2 | Use DSU to merge connected nodes |
| 3 | Count total unique components |
| 4 | Answer = (#components − 1) |

| Approach | Time Complexity | Space Complexity | Notes |
|-----------|----------------|------------------|------------------------------------------------|
| DSU (Union-Find) | O(E α(V)) | O(V) | Efficient and optimal for connectivity problems |

This is the official LeetCode 1319 solution approach, implemented in an interview-ready, fully documented format.
*/
