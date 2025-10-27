#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Find Eventual Safe States
LeetCode Link: https://leetcode.com/problems/find-eventual-safe-states/

Problem Statement:
------------------
In a directed graph, a node is a "safe" state if every possible path starting from that node leads to a terminal node (a node with no outgoing edges).
Return all safe nodes sorted in ascending order.

Example:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: Nodes 2, 4, 5, and 6 are eventual safe states.

Constraints:
- graph.length == n
- 1 <= n <= 10^4
- 0 <= graph[i].length <= n
====================================================
*/

/*
==========================================
Approach 1: Topological Sort on Reverse Graph (Kahn's Algorithm)
------------------------------------------
💡 Idea:
Nodes with out-degree 0 are safe. From these, propagate backward along incoming edges.
Nodes that reduce to out-degree 0 in the reversed graph are also safe.

🧩 Algorithm:
1. Build reverse graph from given graph and compute out-degree (in-degree in reversed graph).
2. Initialize queue with nodes that have out-degree 0 in original graph.
3. Pop from queue, add node to safe list.
4. Decrease out-degree of predecessors, enqueue again if out-degree reaches 0.
5. Sort and return safe nodes.

⏱ Time Complexity: O(V + E)
📦 Space Complexity: O(V + E)
*/
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> adj(V); // reversed graph
    vector<int> inDeg(V, 0);   // out-degree in original graph
    queue<int> q;
    vector<int> ans;

    for (int v = 0; v < V; v++) {
        inDeg[v] = (int)graph[v].size();
        if (inDeg[v] == 0) q.push(v);
        for (int u : graph[v]) adj[u].push_back(v); // reverse edges
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans.push_back(v);
        for (int u : adj[v]) {
            if (--inDeg[u] == 0) q.push(u);
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

/* 
================= MAIN FUNCTION ==================
Runs example test case for eventual safe nodes
*/
int main() {
    vector<vector<int>> graph = {
        {1,2},
        {2,3},
        {5},
        {0},
        {5},
        {},
        {}
    };

    vector<int> safeNodes = eventualSafeNodes(graph);

    cout << "Eventual safe nodes: ";
    for (int node : safeNodes) cout << node << " ";
    cout << "\n(Expected: 2 4 5 6)\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "Reverse the graph and perform BFS (Kahn's algorithm) over out-degrees.\n";
    cout << "Nodes that reduce to out-degree zero are safe.\n";
    cout << "Time complexity O(V + E), space O(V + E), efficient for large graphs.\n";

    return 0;
}
