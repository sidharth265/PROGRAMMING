#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Number of Ways to Reach a Target Sum in a Weighted Graph
Problem Link: [Custom problem based on counting shortest paths]

Problem Statement:
Given an undirected weighted graph with n nodes and roads, calculate the number of distinct shortest paths from node 0 to node n-1.
The answer should be modulo 10^9+7.

Examples:
Input:
n = 3, roads = [[0,1,1],[1,2,1],[0,2,2]]
Output: 2
Explanation:
Paths:
0 -> 1 -> 2: total weight 2
0 -> 2: total weight 2
Both paths are shortest; total ways = 2.

Input:
n = 2, roads = [[0,1,1]]
Output: 1
Explanation:
Only one path: 0 -> 1.
*/


// Approach 1: Dijkstra with Path Counting
// 💡 Idea:
// Use a min-heap to find shortest paths from node 0 to n-1, while maintaining count of number of such shortest paths.
//
// 🧩 Algorithm:
// 1. Build undirected adjacency list with weights.
// 2. Initialize dist array with LONG_MAX, ways array with 0, and set dist[0]=0, ways[0]=1.
// 3. Use a min heap to process nodes in increasing order of dist.
// 4. For each neighbor, relax edges; if a shorter path is found, update ways and dist.
// 5. If an equally short path is found, update ways accordingly.
// 6. Return ways[n-1] as the number of shortest paths.
//
// ⏱ Time Complexity: O(E log V)
// 📦 Space Complexity: O(V + E)

int countPaths(int n, vector<vector<int>>& roads) {
    vector<vector<pair<int, long>>> adj(n);
    for(auto& it : roads) {
        adj[it[0]].push_back({it[1], it[2]});
        adj[it[1]].push_back({it[0], it[2]});
    }
    vector<long> dist(n, LONG_MAX), ways(n,0);
    priority_queue<pair<long,int>, vector<pair<long,int>>, greater<pair<long,int>>> pq;

    dist[0] = 0;
    ways[0] = 1;
    pq.push({0, 0});
    int mod = 1e9 + 7;

    while(!pq.empty()) {
        int v = pq.top().second;
        long d = pq.top().first;
        pq.pop();
        if(d > dist[v]) continue;
        for(auto& it : adj[v]) {
            int u = it.first;
            long w = it.second;
            long nd = d + w;
            if (dist[u] > nd) {
                dist[u] = nd;
                ways[u] = ways[v];
                pq.push({nd, u});
            } else if (dist[u] == nd) {
                ways[u] = (ways[u] + ways[v]) % mod;
            }
        }
    }
    return ways[n-1];
}


int main() {
    // Example 1
    int n1 = 3;
    vector<vector<int>> roads1 = {{0,1,1},{1,2,1},{0,2,2}};
    cout << "Number of shortest paths (Example 1): " << countPaths(n1, roads1) << "\n";
    // Expected Output: 2

    // Example 2
    int n2 = 2; 
    vector<vector<int>> roads2 = {{0,1,1}};
    cout << "Number of shortest paths (Example 2): " << countPaths(n2, roads2) << "\n";
    // Expected Output: 1

    // Example 3 - no alternative path
    int n3 = 4;
    vector<vector<int>> roads3 = {{0,1,1},{1,3,3},{0,3,4}};
    cout << "Number of shortest paths (Example 3): " << countPaths(n3, roads3) << "\n";
    // Expected Output: 1

    return 0;
}

/*
✅ Approach Overview:
| Approach              | Time Complexity       | Space Complexity      | Notes                                   |
|-----------------------|----------------------|----------------------|-----------------------------------------|
| Dijkstra + Path Count | O(E log V)           | O(V + E)             | Efficient solution for shortest path count in weighted graphs |
*/
