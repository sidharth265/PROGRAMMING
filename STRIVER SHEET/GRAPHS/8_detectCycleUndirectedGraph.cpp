#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Cycle Detection in Undirected Graph (DFS and BFS)
=========================================================
Given an undirected graph (edges), check if it contains a cycle.
Provide both DFS (recursive) and BFS (queue-based) solutions.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: DFS for Cycle Detection (Recursive)
   ------------------------------------------------------
   💡 Idea:
   Explore each node recursively: for each edge, skip the parent node.
   If a visited node is found that's *not* the parent, a cycle exists.

   🧩 Algorithm:
   - For each component, run dfs(v, -1):
     - Mark v visited.
     - For each u in adj[v]:
         - If u != parent and visited[u], cycle.
         - If !visited[u], recursively dfs(u, v).
   - If no cycles in any component, return false.

   ⏱ Time Complexity: O(V + E)
   📦 Space Complexity: O(V + E) (adjacency + call stack)
------------------------------------------------------ */
bool dfs(vector<vector<int>>& adj, vector<bool>& visited, int v, int p) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (u != p && visited[u]) return true;
        if (!visited[u])
            if (dfs(adj, visited, u, v)) return true;
    }
    return false;
}

bool isCycleDFS(int V, vector<vector<int>>& edges) {
    vector<vector<int>> adj(V);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    vector<bool> visited(V, false);
    for (int v = 0; v < V; v++) {
        if (!visited[v]) {
            if (dfs(adj, visited, v, -1)) return true;
        }
    }
    return false;
}

/* ------------------------------------------------------
   Approach 2: BFS for Cycle Detection (Queue, Parent Tracking)
   ------------------------------------------------------
   💡 Idea:
   For every node v in the component:
   - For each neighbor u:
      - If u already visited and u != parent, cycle exists.
      - If not visited, enqueue and mark.

   ⏱ Time Complexity: O(V + E)
   📦 Space Complexity: O(V + E)
------------------------------------------------------ */
bool isCycleBFS(int V, vector<vector<int>>& edges) {
    vector<vector<int>> adj(V);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (visited[i]) continue;
        queue<pair<int, int>> q;
        q.push({i, -1});
        visited[i] = true;
        while (!q.empty()) {
            int v = q.front().first;
            int p = q.front().second; q.pop();
            for (int u : adj[v]) {
                if (u != p && visited[u]) return true;
                if (!visited[u]) {
                    q.push({u, v});
                    visited[u] = true;
                }
            }
        }
    }
    return false;
}

/* ===================== Main Function ===================== */
int main() {
    int V1 = 5;
    vector<vector<int>> edges1 = {{0,1},{1,2},{1,3},{3,4}};        // No cycle
    int V2 = 5;
    vector<vector<int>> edges2 = {{0,1},{1,2},{2,3},{3,0},{2,4}};  // Cycle

    cout << "DFS: ";
    cout << (isCycleDFS(V1, edges1) ? "Cycle" : "No Cycle") << "\n";
    cout << "DFS: ";
    cout << (isCycleDFS(V2, edges2) ? "Cycle" : "No Cycle") << "\n";
    cout << "BFS: ";
    cout << (isCycleBFS(V1, edges1) ? "Cycle" : "No Cycle") << "\n";
    cout << "BFS: ";
    cout << (isCycleBFS(V2, edges2) ? "Cycle" : "No Cycle") << "\n";

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method | Time Complexity | Space Complexity | Notes                      |
       |--------|-----------------|------------------|----------------------------|
       | DFS    | O(V + E)        | O(V + E)         | Recursive call stack       |
       | BFS    | O(V + E)        | O(V + E)         | Iterative, tracks parents  |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
