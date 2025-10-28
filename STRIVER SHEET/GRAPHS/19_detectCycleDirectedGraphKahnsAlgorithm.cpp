#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Detect Cycle in Directed Graph (Kahn's/BFS)
GeeksforGeeks Link: https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1/

Problem Statement:
------------------
Given a directed graph with V vertices and edges, check whether the graph contains a cycle or not.

Example:
Input: V = 4, edges = [[0,1],[1,2],[2,3],[3,1]]
Output: true
Explanation: The graph contains a cycle 1 -> 2 -> 3 -> 1

Constraints:
- 1 <= V <= 10^4
- 1 <= edges.length <= 10^5
====================================================
*/

/*
==========================================
Approach 1: Kahn's Algorithm (In-degree Based BFS)
------------------------------------------
💡 Idea:
If a DAG has a topological order, it is acyclic. If any cycle exists, we will not be able to process all nodes (nonzero in-degree remains).

🧩 Algorithm:
1. Build adjacency list and in-degree array from edge list.
2. Enqueue all nodes with zero in-degree.
3. Pop from queue, decrement in-degree of neighbors. Enqueue newly zero in-degree neighbors.
4. If all nodes are processed (visited count equals V), then acyclic.
   - Otherwise, a cycle is present.

⏱ Time Complexity: O(V+E)
📦 Space Complexity: O(V+E)
*/
bool isCyclic(int V, vector<vector<int>>& edges) {
    vector<vector<int>> adj(V);
    vector<int> inDeg(V, 0);
    for (auto& it : edges) {
        adj[it[0]].push_back(it[1]);
        inDeg[it[1]]++;
    }

    queue<int> q;
    vector<int> ans; // stores topological order (optional for cycle detection)

    for (int v = 0; v < V; v++) {
        if (inDeg[v] == 0) q.push(v);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (--inDeg[u] == 0) q.push(u);
        }
        ans.push_back(v);
    }

    return (ans.size() == V) ? false : true;
}

/*
================= MAIN FUNCTION ==================
Runs sample cases for cycle detection in directed graph using Kahn's algorithm
*/
int main() {
    int V1 = 4;
    vector<vector<int>> edges1 = {{0,1},{1,2},{2,3},{3,1}};
    cout << std::boolalpha;
    cout << "Graph 1 has cycle? " << isCyclic(V1, edges1) << " (Expected: true)\n";

    int V2 = 4;
    vector<vector<int>> edges2 = {{0,1},{1,2},{2,3}};
    cout << "Graph 2 has cycle? " << isCyclic(V2, edges2) << " (Expected: false)\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "Kahn's Algorithm (BFS with in-degree) can detect cycles efficiently in O(V+E).\n";
    cout << "If all vertices are not processed, there must be a cycle.\n";
    cout << "Suitable for large graphs and used widely in practice.\n";

    return 0;
}
