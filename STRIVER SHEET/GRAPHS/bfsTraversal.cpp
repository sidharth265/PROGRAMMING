#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Topic: Breadth First Search (BFS) on Graph with Vector<bool> Visited
Description:
Performs BFS traversal on a graph represented by an adjacency list.
Uses a vector<bool> for tracking visited nodes, starting traversal from node 0.

=========================================================
*/

/* ------------------------------------------------------
   Implementation Details
   ------------------------------------------------------
   - BFS explores graph layer-by-layer using a queue.
   - Vector<bool> visited tracks visited nodes, efficient in both time and memory.
   - ans collects nodes in BFS traversal order.
   - Starts BFS from node 0.

   Time Complexity: O(V + E)
   Space Complexity: O(V + E) for adjacency + O(V) for visited and queue
------------------------------------------------------ */
vector<int> bfs(const vector<vector<int>> &adj) {
    vector<int> ans;
    queue<int> q;
    vector<bool> visited(adj.size(), false);
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans.push_back(v);

        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
    return ans;
}

/* ===================== Main Function ===================== */
int main() {
    // Example graph as adjacency list
    vector<vector<int>> adj = {
        {1, 2},    // edges from node 0
        {0, 3},    // edges from node 1
        {0, 3, 4}, // edges from node 2
        {1, 2, 5}, // edges from node 3
        {2},       // edges from node 4
        {3}        // edges from node 5
    };

    vector<int> traversal = bfs(adj);
    cout << "BFS traversal starting from node 0:\n";
    for (int node : traversal) cout << node << " ";
    cout << "\n";

    /* ------------------------------------------------------
       ✅ Summary
       ------------------------------------------------------
       | Method | Time Complexity | Space Complexity | Notes                   |
       |--------|-----------------|------------------|-------------------------|
       | BFS    | O(V + E)        | O(V + E)         | Vector<bool> for visited|
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
