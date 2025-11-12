#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Topic: Graph Implementation
Description:
This code demonstrates standard graph representations using adjacency lists and adjacency matrices.
It includes code for:
- Creating a graph with weighted/unweighted edges
- Directed and undirected graphs
- Basic graph traversal (DFS and BFS)

=========================================================
*/

/* ------------------------------------------------------
   Graph Using Adjacency List
   ------------------------------------------------------
   Data Structure:
   - vector<vector<int>> or vector<vector<pair<int,int>>> for weighted edges
   - For directed/undirected graphs, insert accordingly.

   Features:
   - Efficient for sparse graphs.
   - Space: O(V+E)
------------------------------------------------------ */
class GraphAdjList {
    int V;
    vector<vector<pair<int, int>>> adj; // For weighted graph (node, weight)
public:
    GraphAdjList(int vertices) : V(vertices), adj(vertices) {}

    // Add undirected edge
    void addEdgeUndirected(int u, int v, int w = 1) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Add directed edge
    void addEdgeDirected(int u, int v, int w = 1) {
        adj[u].push_back({v, w});
    }

    void printGraph() {
        for (int u = 0; u < V; u++) {
            cout << u << " -> ";
            for (auto& edge : adj[u]) {
                cout << "(" << edge.first << ", w=" << edge.second << ") ";
            }
            cout << "\n";
        }
    }

    // Depth First Search
    void dfsHelper(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";
        for (auto& edge : adj[u]) {
            int v = edge.first;
            if (!visited[v])
                dfsHelper(v, visited);
        }
    }

    void dfs(int start) {
        vector<bool> visited(V, false);
        dfsHelper(start, visited);
        cout << "\n";
    }

    // Breadth First Search
    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (auto& edge : adj[u]) {
                int v = edge.first;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << "\n";
    }
};

/* ------------------------------------------------------
   Graph Using Adjacency Matrix
   ------------------------------------------------------
   Data Structure:
   - 2D vector or array of size V x V
   - adj[u][v] = weight or 0 if no edge

   Features:
   - Efficient for dense graphs.
   - Space: O(V^2)
------------------------------------------------------ */
class GraphAdjMatrix {
    int V;
    vector<vector<int>> adjMatrix;
public:
    GraphAdjMatrix(int vertices) : V(vertices) {
        adjMatrix.assign(V, vector<int>(V, 0));
    }

    // Add undirected edge
    void addEdgeUndirected(int u, int v, int w = 1) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
    }

    // Add directed edge
    void addEdgeDirected(int u, int v, int w = 1) {
        adjMatrix[u][v] = w;
    }

    void printGraph() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

/* ===================== Main Function ===================== */
int main() {
    // Adjacency List Example
    int V = 5;
    GraphAdjList gList(V);
    gList.addEdgeUndirected(0, 1);
    gList.addEdgeUndirected(0, 4);
    gList.addEdgeUndirected(1, 2);
    gList.addEdgeUndirected(1, 3);
    gList.addEdgeDirected(3, 4);
    cout << "Graph using adjacency list:\n";
    gList.printGraph();

    cout << "DFS starting from node 0:\n";
    gList.dfs(0);

    cout << "BFS starting from node 0:\n";
    gList.bfs(0);

    // Adjacency Matrix Example
    GraphAdjMatrix gMatrix(V);
    gMatrix.addEdgeUndirected(0, 1);
    gMatrix.addEdgeUndirected(0, 4);
    gMatrix.addEdgeUndirected(1, 2);
    gMatrix.addEdgeUndirected(1, 3);
    gMatrix.addEdgeDirected(3, 4);
    cout << "\nGraph using adjacency matrix:\n";
    gMatrix.printGraph();

    /* ------------------------------------------------------
       ✅ Summary
       ------------------------------------------------------
       | Representation   | Space Complexity  | Use Case             |
       |------------------|-------------------|----------------------|
       | Adjacency List   | O(V + E)          | Sparse graphs        |
       | Adjacency Matrix | O(V^2)            | Dense graphs         |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
