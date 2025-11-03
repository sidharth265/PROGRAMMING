#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Find the City With the Smallest Number of Neighbors at a Threshold Distance
Problem Link: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/

Problem Statement:
Given n cities numbered from 0 to n-1, and a list of edges where edges[i] = [u, v, w] where u and v are cities connected by a two-way road of weight w,
find the city with the smallest number of cities that are reachable within a given distanceThreshold.
If there are multiple such cities, return the one with the greatest number.

Example:
Input:
n = 4,
edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]],
distanceThreshold = 4

Output: 3
Explanation:
- City 0 can reach 1 and 2.
- City 1 can reach 0, 2, and 3.
- City 2 can reach 1 and 3.
- City 3 can reach 1 and 2.
City 3 and 0 both have 2 reachable cities, but city 3 has the higher index, so return 3.
*/


// Approach 1: Floyd-Warshall Algorithm (All-Pairs Shortest Path)
// 💡 Idea:
// Use Floyd-Warshall to compute shortest paths between all pairs of cities.
// Count the number of reachable cities (distance <= distanceThreshold) for each city,
// then choose the city with the smallest count and highest number if tie.
//
// ⏱ Time Complexity: O(n³)
// 📦 Space Complexity: O(n²)

int findTheCityFloydWarshall(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, 1e9));
    for (auto& edge : edges) {
        dist[edge[0]][edge[1]] = edge[2];
        dist[edge[1]][edge[0]] = edge[2];
    }
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != 1e9 && dist[k][j] != 1e9) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    int city = -1, minCount = n+1;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (dist[i][j] <= distanceThreshold) count++;
        }
        if (count <= minCount) {
            minCount = count;
            city = i;
        }
    }
    return city;
}


// Approach 2: Dijkstra's Algorithm from Each City
// 💡 Idea:
// For each city, run Dijkstra's algorithm to find single-source shortest paths,
// count reachable cities within distanceThreshold, and track the city with minimal count.
//
// ⏱ Time Complexity: O(n * (E log V))
// 📦 Space Complexity: O(n + E)

int findTheCityDijkstra(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<pair<int,int>>> adj(n);
    for (auto& edge : edges) {
        adj[edge[0]].push_back({edge[1], edge[2]});
        adj[edge[1]].push_back({edge[0], edge[2]});
    }

    int city = -1, minCount = n+1;
    for (int src = 0; src < n; src++) {
        vector<int> dist(n, 1e9);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int v = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            if (d > dist[v]) continue;
            for (auto& it : adj[v]) {
                int u = it.first, w = it.second;
                if (dist[u] > d + w) {
                    dist[u] = d + w;
                    pq.push({dist[u], u});
                }
            }
        }

        int count = 0;
        for (int d : dist) {
            if (d <= distanceThreshold) count++;
        }
        if (count <= minCount) {
            minCount = count;
            city = src;
        }
    }
    return city;
}


int main() {
    int n = 4;
    vector<vector<int>> edges = {{0,1,3}, {1,2,1}, {1,3,4}, {2,3,1}};
    int distanceThreshold = 4;

    cout << "City found by Floyd-Warshall: " << findTheCityFloydWarshall(n, edges, distanceThreshold) << "\n";    // Output: 3
    cout << "City found by Dijkstra: " << findTheCityDijkstra(n, edges, distanceThreshold) << "\n";              // Output: 3

    return 0;
}

/*
✅ Approach Overview:
| Approach           | Time Complexity     | Space Complexity  | Notes                                    |
|--------------------|--------------------|-------------------|------------------------------------------|
| Floyd-Warshall     | O(n³)              | O(n²)             | Computes all-pairs shortest paths, slower|
| Dijkstra (per node)| O(n * (E log n))   | O(n + E)          | Efficient for sparse graphs               |

The choice depends on graph density and n. Floyd-Warshall easier to implement for dense/small graphs.
*/
