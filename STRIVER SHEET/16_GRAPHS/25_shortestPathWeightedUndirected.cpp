#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Shortest Path in Undirected Weighted Graph (Node 1 to n)
Problem Link: [Assumed generic shortest path with path reconstruction problem]

Problem Statement:
Given an undirected weighted graph with n nodes and m edges, find the shortest path distance from node 1 to node n, and report the nodes on the path in reverse order (from n back to 1). If node n is unreachable, output -1.

Examples:
Input:
n = 5, m = 6
edges = [
    {1, 2, 2},
    {1, 3, 4},
    {2, 3, 1},
    {2, 4, 7},
    {3, 5, 3},
    {4, 5, 1}
]

Output:
[6, 5, 3, 2, 1]
Explanation:
- Shortest distance from 1 to 5 is 6.
- Path is 1 → 2 → 3 → 5. Output lists [distance, node n, ..., node 1].

Input:
n = 3, m = 1
edges = [
    {1, 2, 1}
]

Output:
[-1]
Explanation: Node 3 is unreachable.
*/


// Approach 1: Dijkstra with Path Reconstruction
// 💡 Idea:
// Use Dijkstra's algorithm to find the shortest path from node 1 to node n, maintaining a parent array for path reconstruction.
// After finishing, backtrack from n to 1 using the parent array to construct the path.
//
// 🧩 Algorithm:
// 1. Build adjacency list for undirected graph from edge list.
// 2. Set all distances to INT_MAX, distance to source (1) as 0. Initialize parent array.
// 3. Use min-heap (priority_queue) to greedily select next node.
// 4. For each neighbor, relax edge and update parent if shorter path found.
// 5. After Dijkstra, check if dist[n] is INT_MAX (unreachable). If so, output [-1].
// 6. Otherwise, backtrack parent from n to 1, collecting nodes and reverse to get correct order.
// 7. Output [distance, path from n to 1].
//
// ⏱ Time Complexity: O((n + m) * log n)
// 📦 Space Complexity: O(n + m) for adjacency list, O(n) for dist and parent arrays.

vector<int> shortestPathDijkstra(int n, int m, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);

    for (auto& it : edges) {
        adj[it[0]].push_back({it[1], it[2]});
        adj[it[1]].push_back({it[0], it[2]});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[1] = 0;
    parent[1] = 1;
    pq.push({0, 1});

    while (!pq.empty()) {
        int d = pq.top().first;
        int v = pq.top().second;
        pq.pop();

        for (auto& it : adj[v]) {
            int u = it.first, w = it.second;
            if (dist[u] > d + w) {
                dist[u] = d + w;
                parent[u] = v;
                pq.push({dist[u], u});
            }
        }
    }

    if (dist[n] == INT_MAX) return {-1};

    vector<int> ans;
    int cur = n;
    while (cur != parent[cur]) {
        ans.push_back(cur);
        cur = parent[cur];
    }
    ans.push_back(1); // Since parent[1]==1
    reverse(ans.begin(), ans.end());

    // Output format: [distance, path in order 1 → ... → n]
    vector<int> result;
    result.push_back(dist[n]);
    for (int node : ans) result.push_back(node);
    return result;
}



int main() {
    // Example 1
    int n1 = 5, m1 = 6;
    vector<vector<int>> edges1 = {
        {1, 2, 2},
        {1, 3, 4},
        {2, 3, 1},
        {2, 4, 7},
        {3, 5, 3},
        {4, 5, 1}
    };



    // Dijkstra
    auto result1 = shortestPathDijkstra(n1, m1, edges1);
    cout << "Dijkstra: ";
    for (int x : result1) cout << x << " "; cout << "\n";

    return 0;
}

/*
✅ Approach Overview:
| Approach                  | Time Complexity        | Space Complexity     | Notes                                          |
|---------------------------|------------------------|----------------------|------------------------------------------------|
| Dijkstra + Path backtrack | O((n + m) log n)       | O(n + m)             | Handles positive weights, efficient, interview |

Use Dijkstra's algorithm for weighted graphs. BFS can be used for unweighted graphs as an alternative.
*/
