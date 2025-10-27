#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Topological Sort (DFS Based)
GeeksforGeeks Link: https://practice.geeksforgeeks.org/problems/topological-sort/1/

Problem Statement:
------------------
Given a Directed Acyclic Graph (DAG) with V vertices and edges,
return one possible topological ordering of its vertices.

A topological ordering of a DAG is a linear ordering of its vertices such that
for every directed edge u -> v, vertex u comes before v in the ordering.

Example:
Input: V = 6, edges = [[5, 2], [5, 0], [4, 0], [4, 1], [2, 3], [3, 1]]
Output: [5, 4, 2, 3, 1, 0] (or any valid topological order)

Constraints:
- 2 <= V <= 10000
- 1 <= edges.length <= 100000
- edges[i] = [u, v] means directed edge u->v
====================================================
*/

/*
==========================================
Approach 1: DFS with Stack (Post-order)
------------------------------------------
💡 Idea:
Process each node recursively, after visiting all its neighbors, push it onto a stack.
When finished, popping the stack produces a valid topological ordering.

🧩 Algorithm:
1. Build adjacency list from edge list.
2. For each unvisited node, do DFS:
    - Visit all unvisited neighbors recursively.
    - After all neighbors are processed, push node to stack.
3. Pop all nodes from the stack for topological order.

⏱ Time Complexity: O(V+E)
📦 Space Complexity: O(V+E) for adjacency list, O(V) for visited and stack.
*/
void dfs(vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st, int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) dfs(adj, visited, st, u);
    }
    st.push(v);
}

vector<int> topoSort(int V, vector<vector<int>>& edges) {
    stack<int> st;
    vector<bool> visited(V, false);
    vector<vector<int>> adj(V);
    for (auto& it : edges) adj[it[0]].push_back(it[1]);

    for (int v = 0; v < V; v++) {
        if (!visited[v]) dfs(adj, visited, st, v);
    }
    vector<int> ans;
    while (!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}

/*
================= MAIN FUNCTION ==================
Runs sample test cases for topological sorting using DFS
*/
int main() {
    int V = 6;
    vector<vector<int>> edges = {
        {5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}
    };

    vector<int> order = topoSort(V, edges);

    cout << "Topological order:";
    for (int v : order) cout << " " << v;
    cout << "\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "DFS-based approach for topological sort is efficient and provides one valid order.\n";
    cout << "It uses post-order DFS and a stack to capture the correct order.\n";
    cout << "Time: O(V+E), Space: O(V+E). Suitable for large DAGs.\n";

    return 0;
}
