#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Network Delay Time
Problem Link: https://leetcode.com/problems/network-delay-time/

Problem Statement:
You are given a network of n nodes labeled 1 to n, and a list of travel times as directed edges times[i] = (u, v, w),
where u is the source node, v is the target node, and w is the time it takes for a signal to travel from u to v.

A signal is sent from a specific starting node k. Return the minimum time required for all n nodes to receive the signal.
If it is impossible for all nodes to receive the signal (some nodes are unreachable), return -1.

Example 1:
Input:
times = [[2,1,1],[2,3,1],[3,4,1]]
n = 4, k = 2
Output: 2
Explanation:
Signal travel path:
2 → 1 (1 unit)
2 → 3 (1 unit)
3 → 4 (1 additional unit)
=> Total time when last node (4) receives signal is 2.

Example 2:
Input:
times = [[1,2,1]]
n = 2, k = 1
Output: 1
Explanation: All nodes reachable within time 1.

Example 3:
Input:
times = [[1,2,1]]
n = 2, k = 2
Output: -1
Explanation: Node 1 cannot be reached.
*/


// Approach 1: Bellman-Ford Algorithm (Up to n-1 Relaxations)
// 💡 Idea:
// Treat the network as a directed weighted graph. Bellman-Ford ensures shortest paths even with negative edges (not needed here but conceptually valid).
// For each edge, relax distances up to n-1 times.
//
// 🧩 Algorithm:
// 1. Initialize distances: 0 for source k and ∞ for others.
// 2. Repeat n-1 times: for each edge (u,v,w), relax if dist[v] > dist[u] + w.
// 3. Return max distance among all nodes, or -1 if any node unreachable.
//
// ⏱ Time Complexity: O(n * E)
// 📦 Space Complexity: O(n)

int networkDelayTimeBellmanFord(vector<vector<int>>& times, int n, int k) {
    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (auto& e : times) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
                dist[v] = dist[u] + w;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;
        ans = max(ans, dist[i]);
    }
    return ans;
}


// Approach 2: Dijkstra’s Algorithm using Min-Heap (Optimal for Sparse Graphs)
// 💡 Idea:
// Treat the problem as a single-source shortest path with non-negative weights.
// Use a min-heap to always expand the least costly node first.
//
// 🧩 Algorithm:
// 1. Build adjacency list (directed edges with weights).
// 2. Initialize min-heap with (0, k) meaning distance 0 to source k.
// 3. While heap isn't empty, pop node with smallest known distance.
// 4. Relax all its neighbors (v, w): if dist[v] > dist[u] + w, update and push to heap.
// 5. After processing, return maximum dist (when last node receives signal) or -1 if any node unreachable.
//
// ⏱ Time Complexity: O((V + E) log V)
// 📦 Space Complexity: O(V + E)

int networkDelayTimeDijkstra(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto& it : times)
        adj[it[0]].push_back({it[1], it[2]});

    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});
    dist[k] = 0;

    while (!pq.empty()) {
        int v = pq.top().second;
        int d = pq.top().first;
        if (d > dist[v]) continue;
        for (auto& it : adj[v]) {
            int u = it.first;
            int w = it.second;
            if (dist[u] > d + w) {
                dist[u] = d + w;
                pq.push({dist[u], u});
            }
        }
    }

    int cost = *max_element(dist.begin() + 1, dist.end());
    return (cost == INT_MAX) ? -1 : cost;
}


// Approach 3: BFS on Weighted Graph (Using Queue, Similar to Bellman-Ford BFS Variant)
// 💡 Idea:
// Apply a simple queue-driven relaxation instead of a heap. Each relaxation adds the next node to the queue when an update occurs.
//
// 🧩 Algorithm:
// 1. Build adjacency list.
// 2. Initialize queue with node k, distance[k] = 0.
// 3. For each popped node, try relaxing all neighbors. If a shorter path is found, push neighbor to queue.
// 4. Stop when queue empties. Determine maximum distance.
//
// ⏱ Time Complexity: O(V + E) average (depends on graph structure)
// 📦 Space Complexity: O(V + E)

int networkDelayTimeBFS(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto& it : times)
        adj[it[0]].push_back({it[1], it[2]});

    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;

    queue<int> q;
    q.push(k);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& it : adj[u]) {
            int v = it.first;
            int w = it.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                q.push(v);
            }
        }
    }

    int cost = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;
        cost = max(cost, dist[i]);
    }
    return cost;
}


int main() {
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    int n = 4, k = 2;

    cout << "Dijkstra's Algorithm: " << networkDelayTimeDijkstra(times, n, k) << "\n";
    cout << "Bellman-Ford Algorithm: " << networkDelayTimeBellmanFord(times, n, k) << "\n";
    cout << "BFS Approach: " << networkDelayTimeBFS(times, n, k) << "\n";

    return 0;
}

/*
✅ Approach Overview:
| Approach              | Time Complexity       | Space Complexity    | Notes                                            |
|-----------------------|----------------------|---------------------|--------------------------------------------------|
| Bellman-Ford          | O(V * E)             | O(V)                | Works even with negative edges; less efficient   |
| Dijkstra (Heap)       | O((V + E) log V)     | O(V + E)            | Fastest for positive weights; ideal solution     |
| Weighted BFS          | O(V + E)             | O(V + E)            | Simpler but may repeat work; still practical     |

The **Dijkstra approach** is most efficient for real graphs with positive weights, and should be preferred in interviews.
*/
