#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Topological Sort (BFS / Kahn's Algorithm)
GeeksforGeeks Link: https://practice.geeksforgeeks.org/problems/topological-sort/1/

Problem Statement:
------------------
Given a Directed Acyclic Graph (DAG) with V vertices and edges,
return one possible topological ordering of its vertices.

A topological ordering of a DAG is a linear ordering of its vertices such that
for every directed edge u -> v, vertex u comes before v in the ordering.

Example:
Input: V = 6, edges = [[5, 2], [5, 0], [4, 0], [4, 1], [2, 3], [3, 1]]
Output: [4, 5, 2, 3, 1, 0] (or any valid topological order)

Constraints:
- 2 <= V <= 10000
- 1 <= edges.length <= 100000
- edges[i] = [u, v] means directed edge u->v
====================================================
*/

/*
==========================================
Approach 1: Kahn's Algorithm (BFS using In-Degree)
------------------------------------------
💡 Idea:
Count in-degree for each node. Start from nodes with zero in-degree, iteratively remove them from the graph
and decrement in-degrees of their neighbors. When a neighbor reaches zero in-degree, enqueue it.

🧩 Algorithm:
1. Build adjacency list and in-degree array from edge list.
2. Enqueue all nodes with zero in-degree.
3. While queue not empty:
   a. Pop node, append to result.
   b. For each neighbor, decrement its in-degree.
   c. If any neighbor's in-degree becomes zero, enqueue it.
4. If result contains all nodes, a valid topological order exists.

⏱ Time Complexity: O(V+E)
📦 Space Complexity: O(V+E)
*/
vector<int> topoSort_Kahn(int V, vector<vector<int>>& edges) {
    vector<vector<int>> adj(V);
    vector<int> inDeg(V, 0);
    for (auto& it : edges) {
        adj[it[0]].push_back(it[1]);
        inDeg[it[1]]++;
    }

    queue<int> q;
    vector<int> ans;

    for (int v = 0; v < V; v++) {
        if (inDeg[v] == 0) q.push(v);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans.push_back(v);
        for (int u : adj[v]) {
            if (--inDeg[u] == 0) q.push(u);
        }
    }
    return ans;
}

/*
================= MAIN FUNCTION ==================
Runs sample test case for topological sorting using Kahn's BFS algorithm
*/
int main() {
    int V = 6;
    vector<vector<int>> edges = {
        {5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}
    };

    vector<int> order = topoSort_Kahn(V, edges);

    cout << "Topological order:";
    for (int v : order) cout << " " << v;
    cout << "\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "Kahn's Algorithm (BFS using In-Degree) is the standard method for topological sorting in DAGs.\n";
    cout << "Efficiently finds a valid order with O(V+E) time and avoids recursion stack.\n";
    cout << "Great choice for large graphs and practical use in build systems/dependency resolution!\n";

    return 0;
}
