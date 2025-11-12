#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Articulation Points (Cut Vertices) in Graph
Problem Link: https://practice.geeksforgeeks.org/problems/articulation-point-1/

Problem Statement:
Given an undirected connected graph with V vertices,
find all articulation points (cut vertices) in the graph.
An articulation point is a vertex whose removal increases the number of connected components.

Example:
Input:
V = 5
Edges = [[0,1],[1,2],[2,0],[1,3],[3,4]]
Output:
1 3

Explanation:
Removing either vertex 1 or 3 increases the number of disconnected components in the graph.
*/


// Approach: Tarjan's DFS based Algorithm for Articulation Points
// 💡 Idea:
// Use DFS to track discovery time (tin), and low-link values (low).
// A node u is an articulation point if:
// - u is root of DFS tree and has two or more children
// - or u has a child v such that low[v] >= tin[u]
//
// 🧩 Algorithm:
// 1. Initialize tin, low arrays and visited/mark vectors.
// 2. For each unvisited node, run DFS:
//    - Set tin[u], low[u] to timer++
//    - Track children count
//    - Update low[u] via recursive children exploration
//    - Mark articulation points based on conditions above.
//
// ⏱ Time Complexity: O(V + E)
// 📦 Space Complexity: O(V + E)

class Solution {
private:
    int timer = 0;

    void dfs(vector<int> adj[], vector<bool>& visited, vector<bool>& mark,
             vector<int>& tin, vector<int>& low, int node, int parent) {
        visited[node] = true;
        tin[node] = low[node] = timer++;
        int child = 0;
        for (int next : adj[node]) {
            if (next == parent) continue;
            if (!visited[next]) {
                dfs(adj, visited, mark, tin, low, next, node);
                low[node] = min(low[node], low[next]);
                if (low[next] >= tin[node] && parent != -1) {
                    mark[node] = true;
                }
                child++;
            } else {
                low[node] = min(low[node], tin[next]);
            }
        }
        if (child > 1 && parent == -1) mark[node] = true;
    }

public:
    vector<int> articulationPoints(int V, vector<int> adj[]) {
        vector<bool> visited(V, false), mark(V, false);
        vector<int> tin(V, -1), low(V, -1);

        for (int v = 0; v < V; v++) {
            if (!visited[v]) {
                dfs(adj, visited, mark, tin, low, v, -1);
            }
        }

        vector<int> ans;
        for (int v = 0; v < V; v++) {
            if (mark[v]) ans.push_back(v);
        }
        if (ans.empty()) return {-1};
        return ans;
    }
};


int main() {
    int V = 5;
    vector<int> adj[V];
    vector<vector<int>> edges = {{0,1},{1,2},{2,0},{1,3},{3,4}};
    for (auto &edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    Solution sol;
    vector<int> articulationPoints = sol.articulationPoints(V, adj);
    cout << "Articulation points: ";
    for (int v : articulationPoints) cout << v << " ";
    cout << "\n";

    return 0;
}

/*
✅ Approach Overview:
| Step                 | Description                                    |
|----------------------|------------------------------------------------|
| DFS discovery times   | Track when a vertex was first visited           |
| Low-link values       | Track earliest reachable vertex in subtree      |
| Articulation Criteria | Root with multiple children, or low[child]>=tin |

| Approach          | Time Complexity | Space Complexity | Notes                     |
|-------------------|-----------------|------------------|---------------------------|
| Tarjan's Algorithm| O(V+E)          | O(V+E)           | Efficient articulation point detection |

This implementation covers disconnected graphs by DFS from all unvisited nodes.
*/
