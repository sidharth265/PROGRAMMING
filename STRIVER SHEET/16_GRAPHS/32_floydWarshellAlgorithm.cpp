#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Floyd–Warshall Algorithm (All-Pairs Shortest Path)
Problem Link: https://www.geeksforgeeks.org/dsa/floyd-warshall-algorithm-dp-16/

Problem Statement:
Given a weighted graph represented as an adjacency matrix `dist`, where dist[i][j] is the cost to go from node i to node j,
find the shortest distance between every pair of vertices using the Floyd-Warshall algorithm.

If vertex i and j are not directly connected, the distance between them is given as a large value (e.g., 1e8),
representing infinity.

Example:
Input graph:
[
 [0,  4,  1e8, 5],
 [1e8, 0,  1,   1e8],
 [2,  1e8, 0,   3],
 [1e8, 1e8, 1,   0]
]

Output distance matrix:
0 4 5 5
6 0 1 4
2 6 0 3
3 7 1 0
*/


// Approach: Floyd–Warshall Algorithm
// 💡 Idea:
// The algorithm considers every vertex as an intermediate node one by one
// and tries to improve the shortest path between every pair of vertices (i, j)
// using k as an intermediate vertex.
//
// 🧩 Algorithm:
// 1. Take adjacency matrix as input (dist[i][j] = weight or INF if not connected).
// 2. For each vertex k (intermediate):
//      For each vertex i (source):
//          For each vertex j (destination):
//              Update dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]).
// 3. At the end, dist[i][j] has the shortest path length.
//
// ⏱ Time Complexity: O(V³)
// 📦 Space Complexity: O(1) (in-place update)

void floydWarshall(vector<vector<int>> &dist) {
    int n = dist.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != 1e8 && dist[k][j] != 1e8)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}


// Helper function to print distance matrix
void printMatrix(vector<vector<int>> &dist) {
    int n = dist.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == 1e8)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
}


int main() {
    int INF = 1e8;
    vector<vector<int>> dist = {
        {0, 4, INF, 5},
        {INF, 0, 1, INF},
        {2, INF, 0, 3},
        {INF, INF, 1, 0}
    };

    cout << "Input adjacency matrix:\n";
    printMatrix(dist);

    floydWarshall(dist);

    cout << "\nShortest distance matrix:\n";
    printMatrix(dist);

    return 0;
}

/*
✅ Approach Overview:
| Step                | Description                                                   |
|---------------------|---------------------------------------------------------------|
| Initialization       | Use adjacency matrix with INF for absent edges               |
| Triple nested loops  | For each node k, improve shortest paths via k as intermediate|
| Output               | Matrix with shortest path distances                          |

| Approach          | Time Complexity | Space Complexity | Notes                                 |
|-------------------|----------------|------------------|---------------------------------------|
| Floyd-Warshall    | O(V³)          | O(1) (in-place)  | Works for all pairs, detects negatives|

Can also detect **negative weight cycles** if dist[i][i] < 0 for any i.
*/

