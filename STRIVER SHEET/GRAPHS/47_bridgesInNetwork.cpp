#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Critical Connections in a Network
Problem Link: https://leetcode.com/problems/critical-connections-in-a-network/

Problem Statement:
You are given a network of n nodes labeled from 0 to n - 1 and a list of connections where connections[i] = [u, v]
represents a connection between nodes u and v.
An edge is critical if removing it will make some nodes unable to reach each other.
Return all critical connections in the network in any order.

Example:
Input:
n = 4,
connections = [[0,1],[1,2],[2,0],[1,3]]
Output:
[[1,3]]
Explanation:
Removing the edge [1,3] will disconnect node 3 from the rest of the network.
*/


// Approach: Tarjan's Algorithm for Bridges (Critical edges)
// 💡 Idea:
// Use DFS to compute discovery time (tin) and low-link values for each node.
// A bridge is found if low[neighbor] > tin[current].
//
// 🧩 Algorithm:
// 1. Initialize tin and low arrays, visited array, timer counter.
// 2. DFS from node 0 (or unvisited nodes if disconnected):
//    - Set tin[node] = low[node] = timer++, mark visited.
//    - For each neighbor:
//       - If not visited, DFS on neighbor.
//       - Update low[node] with min(low[node], low[neighbor]).
//       - If low[neighbor] > tin[node], edge (node, neighbor) is a bridge.
//    - If neighbor visited and not parent, update low[node] with tin[neighbor].
//
// ⏱ Time Complexity: O(V + E)
// 📦 Space Complexity: O(V + E)

class Solution {
private:
    int timer = 0;
    void dfs(vector<vector<int>>& adj, vector<bool>& visited, vector<vector<int>>& bridges,
             vector<int>& tin, vector<int>& low, int node, int parent) {
        visited[node] = true;
        tin[node] = low[node] = timer++;
        for (int next : adj[node]) {
            if (next == parent) continue;
            if (!visited[next]) {
                dfs(adj, visited, bridges, tin, low, next, node);
                low[node] = min(low[node], low[next]);
                if (low[next] > tin[node]) {
                    bridges.push_back({node, next});
                }
            } else {
                low[node] = min(low[node], tin[next]);
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for (auto& connection : connections) {
            adj[connection[0]].push_back(connection[1]);
            adj[connection[1]].push_back(connection[0]);
        }
        vector<bool> visited(n, false);
        vector<vector<int>> bridges;
        vector<int> tin(n, -1), low(n, -1);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(adj, visited, bridges, tin, low, i, -1);
            }
        }
        return bridges;
    }
};


int main() {
    Solution s;
    int n = 4;
    vector<vector<int>> connections = {{0,1},{1,2},{2,0},{1,3}};
    vector<vector<int>> res = s.criticalConnections(n, connections);

    cout << "Critical connections:\n";
    for (auto& edge : res) {
        cout << "[" << edge[0] << ", " << edge[1] << "]\n";
    }
    return 0;
}

/*
✅ Approach Overview:
| Step          | Description                                |
|---------------|--------------------------------------------|
| DFS with Timer | Compute tin (discovery time) and low links |
| Identify Bridge| Edge where low[neighbor] > tin[node]      |
| Output Bridges | Collect and return all critical edges     |

| Approach         | Time Complexity | Space Complexity | Notes                 |
|------------------|-----------------|------------------|-----------------------|
| Tarjan’s Algorithm| O(V + E)        | O(V + E)         | Efficient and canonical solution |

This implementation handles disconnected graphs by running DFS from all unvisited nodes.
*/
