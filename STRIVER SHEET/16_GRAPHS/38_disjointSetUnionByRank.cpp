#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Disjoint Set (Union-Find) Data Structure
Problem Link: General concept used in many graph algorithms (no single problem link)

Problem Statement:
Disjoint Set Union (DSU) or Union-Find is a data structure that keeps track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets.
It supports two main operations efficiently:
- find(x): Returns the representative (or parent) of the set containing element x.
- unionSet(x, y): Unites the sets that contain x and y.

Features:
- Path Compression in find optimizes repeated searches by flattening the tree structure.
- Union by Rank ensures balanced union tree height to keep operations near constant time.

This structure is commonly used in Kruskal's MST, connected components detection, cycle detection, etc.

Example:
Initially: n = 5, sets = {{0}, {1}, {2}, {3}, {4}}
unionSet(0,2) -> sets = {{0,2}, {1}, {3}, {4}}
unionSet(4,2) -> sets = {{0,2,4}, {1}, {3}}
find(4) and find(0) both return the same representative indicating same set.
*/


class DisjointSet {
    vector<int> par, rank;
public:
    // Constructor: initializes parent and rank arrays
    DisjointSet(int n) {
        par.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            par[i] = i;
    }

    // Find with path compression
    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    // Union by rank
    void unionSet(int x, int z) {
        int upx = find(x);
        int upz = find(z);
        if (upx == upz) return;

        if (rank[upz] > rank[upx])
            par[upx] = upz;
        else if (rank[upx] > rank[upz])
            par[upz] = upx;
        else {
            par[upz] = upx;
            rank[upx]++;
        }
    }
};


int main() {
    // Create a DisjointSet for 5 elements (0 to 4)
    DisjointSet ds(5);

    ds.unionSet(0, 2); // Union sets containing 0 and 2
    ds.unionSet(4, 2); // Union sets containing 4 and 2
    ds.unionSet(3, 1); // Union sets containing 3 and 1

    // Check if 4 and 0 are in the same set
    cout << "4 and 0 " << (ds.find(4) == ds.find(0) ? "are in the same set.\n" : "are NOT in the same set.\n");

    // Check if 1 and 0 are in the same set
    cout << "1 and 0 " << (ds.find(1) == ds.find(0) ? "are in the same set.\n" : "are NOT in the same set.\n");

    return 0;
}

/*
✅ Approach Overview:
| Operation  | Complexity (Amortized) | Notes                                  |
|------------|------------------------|----------------------------------------|
| find       | O(α(n)) (inverse Ackermann function, very slow growing) | Path Compression            |
| unionSet   | O(α(n))                                          | Union by Rank/Size heuristic |

Disjoint Set supports almost constant time union/find operations after path compression and rank optimizations.
This makes it ideal for problems involving dynamic connectivity, MST, connected components, and cycle detection.
*/
