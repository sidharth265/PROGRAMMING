#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Bellman-Ford Algorithm (Single Source Shortest Path)
Problem Link: https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1

Problem Statement:
Given a weighted directed graph and a source vertex src, find the shortest path distances from src to all vertices using the Bellman-Ford algorithm.
If a negative weight cycle is detected, return {-1}.

The graph is represented as an edge list: edges[i] = [u, v, w] meaning there is a directed edge from u to v with weight w.

Input:
V = 5, edges = [[0,1,-1],[0,2,4],[1,2,3],[1,3,2],[1,4,2],
                [3,2,5],[3,1,1],[4,3,-3]], src = 0

Output:
Shortest distances from src:
[0, -1, 2, -2, 1]
*/


// Approach: Bellman-Ford Algorithm
// 💡 Idea:
// Bellman-Ford relaxes all edges V-1 times to find the shortest distance to every vertex.
// It can handle negative edge weights and also detect negative weight cycles.
//
// 🧩 Algorithm:
// 1. Initialize dist[] to a large value. Set dist[src] = 0.
// 2. Repeat V-1 times:
//      - For each edge (u, v, w):
//          - If dist[u] + w < dist[v], update dist[v].
// 3. After V-1 iterations, run one more iteration:
//      - If any edge can still be relaxed => Negative cycle detected.
// 4. Return the dist[] array or {-1} if negative cycle exists.
//
// ⏱ Time Complexity: O(V * E)
// 📦 Space Complexity: O(V)

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, 1e8);
    dist[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] == 1e8) continue;
            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[u] == 1e8) continue;
        if (dist[u] + w < dist[v])
            return {-1}; // Negative weight cycle detected
    }

    return dist;
}


int main() {
    int V = 5, src = 0;
    vector<vector<int>> edges = {
        {0,1,-1}, {0,2,4}, {1,2,3}, {1,3,2}, {1,4,2},
        {3,2,5}, {3,1,1}, {4,3,-3}
    };

    vector<int> result = bellmanFord(V, edges, src);

    if (result.size() == 1 && result[0] == -1) {
        cout << "Negative weight cycle detected!\n";
    } else {
        cout << "Shortest distances from source " << src << ":\n";
        for (int d : result)
            cout << d << " ";
        cout << "\n";
    }

    return 0;
}

/*
✅ Approach Overview:
| Step               | Description                                                  |
|--------------------|--------------------------------------------------------------|
| Relax edges        | Update distances for all edges V-1 times                     |
| Detect cycles      | If any edge can still relax after V-1 rounds → negative cycle|
| Handles negatives  | Works with graphs having negative edge weights               |

| Approach        | Time Complexity | Space Complexity | Supports Negative Edges | Detects Negative Cycle |
|-----------------|----------------|------------------|--------------------------|------------------------|
| Bellman-Ford    | O(V * E)       | O(V)             | Yes                      | Yes                    |

Bellman-Ford is preferred over Dijkstra for graphs involving negative edge weights.
*/
