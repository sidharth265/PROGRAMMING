#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Disjoint Set (Union-Find) Data Structure with Union by Size
Problem Link: General data structure used in graph and set problems

Problem Statement:
Implement a Disjoint Set Union (DSU) or Union-Find data structure supporting efficient union and find operations.
This version uses Union by Size heuristic to balance the tree height, along with path compression in the find operation.

Details:
- Each element starts as its own set parent.
- The union of two sets attaches the smaller set under the larger set's root.
- The find function compresses paths for fast repeated queries.

Usage:
Common in Minimum Spanning Trees (Kruskal), connected components, and cycle detection problems.
*/


class DisjointSet {
    vector<int> par, size;
public:

    // Constructor: initializes parent and size arrays
    DisjointSet(int n) {
        par.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            par[i] = i;
    }

    // Find with path compression
    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    // Union by size
    void unionSet(int x, int z) {
        int upx = find(x);
        int upz = find(z);
        if (upx == upz) return;

        if (size[upz] > size[upx]) {
            par[upx] = upz;
            size[upz] += size[upx];
        } else {
            par[upz] = upx;
            size[upx] += size[upz];
        }
    }
};

int main() {
    DisjointSet ds(5);

    ds.unionSet(0, 1);
    ds.unionSet(1, 2);
    ds.unionSet(3, 4);

    cout << "Are 0 and 2 connected? " << (ds.find(0) == ds.find(2) ? "Yes" : "No") << "\n"; // Yes
    cout << "Are 0 and 4 connected? " << (ds.find(0) == ds.find(4) ? "Yes" : "No") << "\n"; // No

    ds.unionSet(2, 4);

    cout << "Are 0 and 4 connected after union? " << (ds.find(0) == ds.find(4) ? "Yes" : "No") << "\n"; // Yes

    return 0;
}

/*
✅ Approach Overview:
| Operation  | Time Complexity (Amortized) | Notes                       |
|------------|-----------------------------|-----------------------------|
| find       | O(α(n)) (Inverse Ackermann) | Path compression optimizes  |
| unionSet   | O(α(n))                     | Union by size keeps trees balanced |

This DSU efficiently supports sets union and connectedness queries with near constant time per operation.
*/
