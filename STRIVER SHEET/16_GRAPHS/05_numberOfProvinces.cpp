#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Number of Provinces (Connected Components in a Graph)
Problem Link: https://leetcode.com/problems/number-of-provinces/

Problem Statement:
Given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith and jth nodes are connected,
return the number of connected components (provinces).

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: DFS on Adjacency Matrix (Brute Force)
   ------------------------------------------------------
   💡 Idea:
   Use DFS directly on the adjacency matrix to find connected components.
   Mark all nodes reachable from a node as visited.

   🧩 Algorithm:
   1. For each node, if not visited, start DFS.
   2. DFS visits all neighbors where isConnected[i][j] == 1.
   3. Count number of DFS calls as number of provinces.

   ⏱ Time Complexity: O(N²)
   📦 Space Complexity: O(N) for visited array and recursion stack
------------------------------------------------------ */
void dfsMatrix(int i, vector<vector<int>>& isConnected, vector<bool>& visited) {
    visited[i] = true;
    int n = isConnected.size();
    for (int j = 0; j < n; j++) {
        if (j != i && isConnected[i][j] == 1 && !visited[j]) {
            dfsMatrix(j, isConnected, visited);
        }
    }
}

int findCircleNum_DFS_Matrix(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<bool> visited(n, false);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsMatrix(i, isConnected, visited);
            count++;
        }
    }
    return count;
}

/* ------------------------------------------------------
   Approach 2: DFS after building adjacency list (Better)
   ------------------------------------------------------
   💡 Idea:
   Convert adjacency matrix to adjacency list for efficient neighbor traversal.
   Then run DFS to find connected components.

   🧩 Algorithm:
   1. Build adjacency list from matrix.
   2. For each unvisited node, perform DFS.
   3. Count DFS calls as provinces.

   ⏱ Time Complexity: O(N²)
   📦 Space Complexity: O(N²) adjacency + O(N) visited
------------------------------------------------------ */
void dfsList(int i, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[i] = true;
    for (int v : adj[i]) {
        if (!visited[v]) dfsList(v, adj, visited);
    }
}

int findCircleNum_DFS_List(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (isConnected[i][j] && i != j)
                adj[i].push_back(j);

    vector<bool> visited(n, false);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsList(i, adj, visited);
            count++;
        }
    }
    return count;
}

/* ------------------------------------------------------
   Approach 3: BFS after building adjacency list (Optimal)
   ------------------------------------------------------
   💡 Idea:
   Use BFS for traversal instead of DFS, still starting from an adjacency list.

   🧩 Algorithm:
   Similar to 2, but use a queue to traverse the graph.

   ⏱ Time Complexity: O(N²)
   📦 Space Complexity: O(N²) adjacency + O(N) visited and queue
------------------------------------------------------ */
int findCircleNum_BFS_List(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (isConnected[i][j] && i != j)
                adj[i].push_back(j);

    vector<bool> visited(n, false);
    queue<int> q;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            q.push(i);
            visited[i] = true;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            count++;
        }
    }
    return count;
}

/* ===================== Main Function ===================== */
int main() {
    vector<vector<int>> isConnected = {
        {1,1,0},
        {1,1,0},
        {0,0,1}
    };

    cout << "Number of Provinces (DFS on Matrix): " << findCircleNum_DFS_Matrix(isConnected) << endl;
    cout << "Number of Provinces (DFS on List): " << findCircleNum_DFS_List(isConnected) << endl;
    cout << "Number of Provinces (BFS on List): " << findCircleNum_BFS_List(isConnected) << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method           | Time Complexity | Space Complexity | Notes                      |
       |------------------|-----------------|------------------|----------------------------|
       | DFS on Matrix    | O(N²)           | O(N)             | Direct use of adjacency matrix |
       | DFS on List      | O(N²)           | O(N²) + O(N)     | Converts matrix to list     |
       | BFS on List      | O(N²)           | O(N²) + O(N)     | BFS variant, similar to DFS |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
