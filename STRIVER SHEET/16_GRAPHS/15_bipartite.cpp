#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Is Graph Bipartite?
LeetCode Link: https://leetcode.com/problems/is-graph-bipartite/

Problem Statement:
------------------
Given an undirected graph, determine if it is bipartite.
A graph is bipartite if you can split its vertices into two disjoint sets U and V such that 
every edge connects a vertex in U to one in V (no edge connects vertices within the same set).

Example 1:
Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: The graph can be colored using two colors.

Example 2:
Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
Output: false
Explanation: No valid 2-coloring exists.

Constraints:
- graph is represented as an adjacency list.
- 1 <= graph.length <= 100
- 0 <= graph[i][j] < graph.length
- graph[i][j] != i
- graph[i] does not contain duplicates
====================================================
*/

/*
==========================================
Approach 1: DFS Coloring
------------------------------------------
💡 Idea:
Try to color the graph nodes with two colors (0 and 1). If at any point adjacent nodes have the same color, graph is not bipartite.

🧩 Algorithm:
1. Initialize color vector with -1 for uncolored nodes.
2. For each uncolored node, start DFS with color 0.
3. In DFS, assign color to current node, and recursively assign alternate color to neighbors.
4. If a neighbor has same color as current, return false.
5. If successfully color all, return true.

⏱ Time Complexity: O(V+E)
📦 Space Complexity: O(V)
*/
bool dfs(vector<vector<int>>& graph, vector<int>& val, int v, int b) {
    val[v] = b;
    for (int u : graph[v]) {
        if (val[u] == b) return false; // same color on adjacent nodes
        else if (val[u] == -1) {
            if (!dfs(graph, val, u, !b)) return false;
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    vector<int> val(graph.size(), -1);
    for (int v = 0; v < graph.size(); v++) {
        if (val[v] == -1) {
            if (!dfs(graph, val, v, 0)) return false;
        }
    }
    return true;
}

/* 
======== MAIN FUNCTION ========= 
Demonstrates bipartite checks on example graphs
*/
int main() {
    vector<vector<int>> graph1 = {
        {1, 3},
        {0, 2},
        {1, 3},
        {0, 2}
    };

    vector<vector<int>> graph2 = {
        {1, 2, 3},
        {0, 2},
        {0, 1, 3},
        {0, 2}
    };

    cout << std::boolalpha; // print true/false instead of 1/0

    cout << "Graph1 is Bipartite? " << isBipartite(graph1) << " (Expected: true)\n";
    cout << "Graph2 is Bipartite? " << isBipartite(graph2) << " (Expected: false)\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "DFS Coloring is an efficient O(V+E) solution.\n";
    cout << "Color each node with alternating colors; conflict means graph is not bipartite.\n";
    cout << "Simple, intuitive, and widely used for bipartite checks in graphs.\n";

    return 0;
}
