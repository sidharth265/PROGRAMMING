#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Shortest Path in Directed Acyclic Graph (DAG)
Problem Link: [Assumed generic DAG shortest path problem on coding platforms]

Problem Statement:
Given a directed acyclic graph (DAG) with weighted edges, find the shortest path from the source vertex (0) to all other vertices. If a vertex is not reachable, return -1 for that vertex.

Example:
Input:
V = 6, E = 7
Edges = [[0,1,2], [0,4,1], [1,2,3], [4,2,2], [4,5,4], [2,3,6], [5,3,1]]

Output:
[0, 2, 3, 6, 1, 5]

Explanation:
- Distance from 0 to 0 is 0
- Shortest path from 0 to 1 has weight 2
- Shortest path from 0 to 2 is via 4 with weight 3
- Shortest path from 0 to 3 is via 4->5 with weight 6
- Shortest path from 0 to 4 is 1
- Shortest path from 0 to 5 is 5
*/


// Approach 1: Topological Sort + Relaxation
// 💡 Idea:
// Use DFS to perform a topological sort of the DAG and then relax edges in topological order to find shortest paths.
//
// 🧩 Algorithm:
// 1. Build adjacency list from input edges.
// 2. Perform DFS-based topological sort to order vertices.
// 3. Initialize distance array with INT_MAX; distance to source is 0.
// 4. Process vertices in topological order and update minimum distances.
// 5. Replace INT_MAX with -1 for unreachable vertices.
//
// ⏱ Time Complexity: O(V + E) for topo sort and relaxation combined.
// 📦 Space Complexity: O(V + E) for adjacency list, O(V) for stack and distance array.

void topoSortDFS(int v, const vector<vector<pair<int, int>>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[v] = true;
    for (const auto& edge : adj[v]) {
        int u = edge.first;
        if (!visited[u]) topoSortDFS(u, adj, visited, st);
    }
    st.push(v);
}

vector<int> shortestPathTopo(int V, int E, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj(V);
    for (const auto& it : edges) {
        adj[it[0]].push_back({it[1], it[2]});
    }

    stack<int> st;
    vector<bool> visited(V, false);
    for (int v = 0; v < V; v++) {
        if (!visited[v]) topoSortDFS(v, adj, visited, st);
    }

    vector<int> dist(V, INT_MAX);
    dist[0] = 0;

    while (!st.empty()) {
        int v = st.top();
        st.pop();
        if (dist[v] != INT_MAX) {
            for (const auto& edge : adj[v]) {
                int u = edge.first;
                int w = edge.second;
                if (dist[v] + w < dist[u]) {
                    dist[u] = dist[v] + w;
                }
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) dist[i] = -1;
    }

    return dist;
}


// Approach 2: Modified BFS using Queue (Works for DAG with non-negative edge weights)
// 💡 Idea:
// Use a BFS-like approach with a queue to propagate shortest distances, similar to shortest path in unweighted graphs but relaxing edges with weights.
// This approach works because the graph is a DAG and edges have non-negative weights.
//
// 🧩 Algorithm:
// 1. Build adjacency list from edges.
// 2. Initialize dist array with INT_MAX; dist to source is 0.
// 3. Push source node with distance 0 into queue.
// 4. While queue is not empty, dequeue node and relax its edges if shorter path found, enqueue updated nodes.
// 5. Replace INT_MAX with -1 for unreachable nodes.
//
// ⏱ Time Complexity: O(V + E), similar to Topological relaxation but BFS-based.
// 📦 Space Complexity: O(V + E) for adjacency, O(V) for dist and queue.

vector<int> shortestPathBFS(int V, int E, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj(V);
    vector<int> dist(V, INT_MAX);

    for (auto& it : edges) {
        adj[it[0]].push_back({it[1], it[2]});
    }

    queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0] = 0;

    while (!q.empty()) {
        int v = q.front().first;
        int d = q.front().second;
        q.pop();

        for (auto& it : adj[v]) {
            int u = it.first;
            int w = it.second;
            if (dist[u] > d + w) {
                dist[u] = d + w;
                q.push({u, dist[u]});
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) dist[i] = -1;
    }

    return dist;
}


int main() {
    vector<vector<int>> edges = {
        {0,1,2}, {0,4,1}, {1,2,3}, {4,2,2}, {4,5,4}, {2,3,6}, {5,3,1}
    };
    int V = 6, E = edges.size();

    cout << "Shortest distances using Topological Sort approach:\n";
    vector<int> distTopo = shortestPathTopo(V, E, edges);
    for (int d : distTopo) cout << d << " ";
    cout << "\n";

    cout << "Shortest distances using BFS-based approach:\n";
    vector<int> distBFS = shortestPathBFS(V, E, edges);
    for (int d : distBFS) cout << d << " ";
    cout << "\n";

    return 0;
}

/*
✅ Approach Overview:
| Approach           | Time Complexity | Space Complexity | Notes                                     |
|--------------------|-----------------|------------------|-------------------------------------------|
| Topological Sort    | O(V + E)        | O(V + E)         | Classic shortest path solution in DAG     |
| BFS-based Relaxation| O(V + E)        | O(V + E)         | Alternate approach relying on DAG property|

Both approaches find shortest paths from source in DAG efficiently. The topological approach is more canonical; the BFS-based approach exploits DAG and non-negative weights for relaxation.
*/
