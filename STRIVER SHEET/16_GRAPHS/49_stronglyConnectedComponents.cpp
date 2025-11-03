#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Number of Strongly Connected Components (Kosaraju's Algorithm)
Problem Link: https://practice.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1

Problem Statement:
Given a Directed Graph with V vertices and adjacency list adj,
find the number of Strongly Connected Components (SCCs) in the graph.

A Strongly Connected Component is a maximal group of vertices such that each vertex is reachable from every other vertex in the same group.

Example:
Input:
V = 5
adj = [[2], [0], [1, 3], [4], []]

Output: 3

Explanation:
There are three SCCs: {0,1,2}, {3}, and {4}.
*/


// Approach: Kosaraju's Algorithm
// 💡 Idea:
// 1. Perform DFS on original graph to fill stack with vertices in finishing order.
// 2. Reverse the graph (transpose).
// 3. Process vertices in order from stack on reversed graph and count how many DFS calls are needed.
//
// 🧩 Algorithm:
// 1. DFS on original graph, push nodes onto stack on finishing DFS.
// 2. Reverse edges of graph creating a transpose.
// 3. Pop from stack and run DFS on transpose graph for unvisited nodes,
//    increment count of SCCs.
//
// ⏱ Time Complexity: O(V + E)
// 📦 Space Complexity: O(V + E)

class Solution {
private:
    void dfs1(const vector<vector<int>>& adj, stack<int>& sorted, vector<bool>& visited, int v) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u])
                dfs1(adj, sorted, visited, u);
        }
        sorted.push(v);
    }

    void dfs2(const vector<vector<int>>& reversed, vector<bool>& visited, int v) {
        visited[v] = true;
        for (int u : reversed[v]) {
            if (!visited[u])
                dfs2(reversed, visited, u);
        }
    }

public:
    int kosaraju(vector<vector<int>>& adj) {
        int V = adj.size();
        stack<int> sorted;
        vector<bool> visited(V, false);

        // Step 1: DFS to fill order stack on original graph
        for (int v = 0; v < V; v++) {
            if (!visited[v])
                dfs1(adj, sorted, visited, v);
        }

        // Step 2: Reverse graph edges (transpose)
        vector<vector<int>> reversed(V);
        for (int v = 0; v < V; v++) {
            visited[v] = false;  // Reset visited for next DFS
            for (int u : adj[v]) {
                reversed[u].push_back(v);
            }
        }

        // Step 3: DFS on reversed graph in stack order to find SCCs
        int countSCC = 0;
        while (!sorted.empty()) {
            int v = sorted.top();
            sorted.pop();
            if (!visited[v]) {
                ++countSCC;
                dfs2(reversed, visited, v);
            }
        }
        return countSCC;
    }
};



int main() {
    Solution s;
    int V = 5;
    vector<vector<int>> adj = {
        {2},   // 0 -> 2
        {0},   // 1 -> 0
        {1,3}, // 2 -> 1,3
        {4},   // 3 -> 4
        {}     // 4 -> no outgoing edges
    };

    cout << "Number of Strongly Connected Components: " << s.kosaraju(adj) << "\n"; // Expected 3

    return 0;
}

/*
✅ Approach Overview:
| Step                   | Description                                                     |
|------------------------|-----------------------------------------------------------------|
| DFS to order vertices   | Perform DFS and push to stack nodes in finishing order          |
| Reverse graph edges     | Create transpose graph for reverse edges                        |
| DFS from stack on trans | Count SCCs as number of DFS runs on transpose graph in order    |

| Approach       | Time Complexity | Space Complexity | Notes                         |
|----------------|-----------------|------------------|-------------------------------|
| Kosaraju's Alg | O(V + E)        | O(V + E)         | Straightforward, efficient SCC detection |

This solution is structured for interviews with detailed comments and clear function separation.
*/
