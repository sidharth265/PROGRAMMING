#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Shortest Path in Unweighted Graph (BFS)
GeeksforGeeks Link: https://practice.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1/

Problem Statement:
------------------
Given an unweighted (or directed) graph as an adjacency list and a source vertex src,
find the shortest distance from src to every other vertex. If a vertex is unreachable, distance is -1.

Example:
Input: adj = [[1,2],[0,3],[0,3],[1,2]], src = 0
Output: [0,1,1,2]

Explanation: 
- Node 0: dist = 0 (source)
- Node 1: dist = 1 (via 0->1)
- Node 2: dist = 1 (via 0->2)
- Node 3: dist = 2 (via 0->1->3 OR 0->2->3)

Constraints:
- 1 <= V <= 10^4
- All edges are unweighted, adj[i] contains neighbours of i.
====================================================
*/

/*
==========================================
Approach 1: BFS for Shortest Path in Unweighted Graph
------------------------------------------
💡 Idea:
Breadth-first search guarantees the shortest path to all nodes in an unweighted graph from a source.

🧩 Algorithm:
1. Initialize a dist array with INT_MAX; dist[src]=0.
2. Push {src,0} into queue.
3. While queue not empty:
   - Pop v,d. For all adjacents u, if d+1<dist[u], set dist[u]=d+1 and push u,d+1.
4. After processing, set any remaining INT_MAX distances to -1.
5. Return dist array.

⏱ Time Complexity: O(V+E)
📦 Space Complexity: O(V)
*/
vector<int> shortestPath(vector<vector<int>>& adj, int src) {
    int V = adj.size();
    vector<int> dist(V, INT_MAX);
    queue<pair<int, int>> q;
    q.push({src, 0});
    dist[src] = 0;

    while (!q.empty()) {
        int v = q.front().first;
        int d = q.front().second;
        q.pop();
        for (int u : adj[v]) {
            if (d + 1 < dist[u]) {
                dist[u] = d + 1;
                q.push({u, d + 1});
            }
        }
    }
    for (int v = 0; v < V; v++) {
        if (dist[v] == INT_MAX) dist[v] = -1;
    }
    return dist;
}

/*
================= MAIN FUNCTION ==================
Runs a sample test for BFS shortest path algorithm
*/
int main() {
    vector<vector<int>> adj = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2}
    };

    int src = 0;
    vector<int> dist = shortestPath(adj, src);
    cout << "Shortest distances from src " << src << ": ";
    for (int d : dist) cout << d << " ";
    cout << "\n(Expected: 0 1 1 2)\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "BFS is optimal for shortest path in unweighted graphs (O(V+E)).\n";
    cout << "Directly tracks distance; no edge weights needed. Efficient for large graphs.\n";

    return 0;
}
