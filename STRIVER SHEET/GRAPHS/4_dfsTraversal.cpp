#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Topic: Depth First Search (DFS) on Graph
Description:
Performs DFS traversal on graph represented by adjacency list.
This example uses vector<bool> for visited nodes and starts traversal from node 0.

=========================================================
*/

/* ------------------------------------------------------
   Implementation Details
   ------------------------------------------------------
   - DFS is recursive.
   - `visited` tracks visited nodes.
   - `ans` stores the traversal order.
   - Starts at node 0, assumes graph is connected or accessible from 0.

   Time Complexity: O(V + E)
   Space Complexity: O(V + E) for adjacency + O(V) for recursion stack and visited map
------------------------------------------------------ */

void DFS(int i, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& ans) {
    visited[i] = true;
    ans.push_back(i);
    for (int j : adj[i]) {
        if (!visited[j]) DFS(j, adj, visited, ans);
    }
}

vector<int> dfs(vector<vector<int>>& adj) {
    vector<int> ans;
    vector<bool> visited(adj.size(), false);
    DFS(0, adj, visited, ans);
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

    vector<int> result = dfs(adj);
    cout << "DFS traversal starting from node 0:\n";
    for (int v : result) cout << v << " ";
    cout << "\n";

    /* ------------------------------------------------------
       ✅ Summary
       ------------------------------------------------------
       | Method | Time Complexity | Space Complexity | Notes                   |
       |--------|-----------------|------------------|-------------------------|
       | DFS    | O(V + E)        | O(V + E)         | Uses unordered_map for visited |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
