#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Detect Cycle in Directed Graph
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
Approach 1: DFS with Path Visited Tracking
-------------------------------------------
💡 Idea:
Detect cycle by performing DFS on each vertex keeping track of nodes in the current recursion stack.
If during DFS we reach a node already in recursion stack, a cycle is detected.

🧩 Algorithm:
1. Create adjacency list from edges.
2. Maintain two boolean vectors: visited and pathVisited.
3. For each unvisited vertex, run DFS:
   - Mark current node as visited and pathVisited
   - For each neighbor:
     - If neighbor is visited and also in pathVisited => cycle detected
     - Else if neighbor not visited, recurse DFS on neighbor
4. After DFS from node, remove it from pathVisited.
5. If no cycles detected, return false.

⏱ Time Complexity: O(V + E)
📦 Space Complexity: O(V + E)
*/
bool dfs(vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& pathVisited, int v) {
    visited[v] = true;
    pathVisited[v] = true;
    for (int u : adj[v]) {
        if (visited[u] && pathVisited[u]) return true;
        if (!visited[u]) {
            if (dfs(adj, visited, pathVisited, u)) return true;
        }
    }
    pathVisited[v] = false;
    return false;
}

bool isCyclic(int V, vector<vector<int>>& edges) {
    vector<vector<int>> adj(V);
    for (auto& it : edges) {
        adj[it[0]].push_back(it[1]);
    }

    vector<bool> visited(V, false);
    vector<bool> pathVisited(V, false);

    for (int v = 0; v < V; v++) {
        if (!visited[v]) {
            if (dfs(adj, visited, pathVisited, v)) return true;
        }
    }
    return false;
}

/* 
======== MAIN FUNCTION =========
Run example test cases
*/
int main() {
    int V1 = 4;
    vector<vector<int>> edges1 = {{0,1},{1,2},{2,3},{3,1}};
    cout << std::boolalpha;
    cout << "Graph 1 has cycle? " << isCyclic(V1, edges1) << " (Expected: true)\n";

    int V2 = 4;
    vector<vector<int>> edges2 = {{0,1},{1,2},{2,3}};
    cout << "Graph 2 has cycle? " << isCyclic(V2, edges2) << " (Expected: false)\n";

    // Summary
    cout << "\n✅ Approach Overview:\n";
    cout << "DFS with pathVisited set tracks recursion stack to detect cycles in directed graph efficiently.\n";
    cout << "Time Complexity: O(V + E), Space Complexity: O(V + E).\n";

    return 0;
}
