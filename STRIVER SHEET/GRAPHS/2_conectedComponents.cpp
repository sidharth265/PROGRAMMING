#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Find Connected Components in an Undirected Graph
Description:
Given a graph with V vertices and a list of edges, find and return 
all connected components of the graph using Depth First Search (DFS).

Example:
Input: V = 5, edges = [[0,1],[1,2],[3,4]]
Output: [[0,1,2],[3,4]]

=========================================================
*/

/* ------------------------------------------------------
   Approach: Using DFS on Adjacency List
   ------------------------------------------------------
   💡 Idea:
   Construct adjacency list from edges and perform DFS to find connected components.

   🧩 Algorithm:
   1. Build adjacency list for undirected graph.
   2. Maintain a visited array.
   3. For each unvisited node, perform DFS collecting nodes of the component.
   4. Add the component to the result.
   5. Return all components.

   ⏱ Time Complexity: O(V + E)
   📦 Space Complexity: O(V + E)
------------------------------------------------------ */

void dfs(int i, vector<int>& comp, vector<vector<int>>& adjList, vector<bool>& visited) {
    visited[i] = true;
    comp.push_back(i);
    for (int j : adjList[i]) {
        if (!visited[j]) dfs(j, comp, adjList, visited);
    }
}

vector<vector<int>> getComponents(int V, vector<vector<int>>& edges) {
    vector<vector<int>> adjList(V);
    for (auto& x : edges) {
        adjList[x[0]].push_back(x[1]);
        adjList[x[1]].push_back(x[0]);
    }
    vector<bool> visited(V, false);
    vector<vector<int>> result;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            vector<int> comp;
            dfs(i, comp, adjList, visited);
            result.push_back(comp);
        }
    }
    return result;
}

/* ===================== Main Function ===================== */
int main() {
    int V = 7;
    vector<vector<int>> edges = {{0,1}, {1,2}, {3,4}, {5,6}};

    vector<vector<int>> components = getComponents(V, edges);
    cout << "Connected components:\n";
    for (auto& comp : components) {
        for (int node : comp) cout << node << " ";
        cout << "\n";
    }

    /* ------------------------------------------------------
       ✅ Summary
       ------------------------------------------------------
       | Method     | Time Complexity | Space Complexity | Notes               |
       |------------|-----------------|------------------|---------------------|
       | DFS        | O(V + E)        | O(V + E)         | Simple, efficient   |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
