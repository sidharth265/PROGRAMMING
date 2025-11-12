#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Most Stones Removed with Same Row or Column
Problem Link: https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/

Problem Statement:
On a 2D plane, we place n stones at some integer coordinate points.
Each coordinate point may have at most one stone.
A stone can be removed if it shares either the same row or the same column
as another stone that remains on the plane.

Return the maximum number of stones that can be removed.

Example 1:
Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation:
One possible way is:
Remove stones at (2,2), (2,1), (1,2), (1,0), (0,1) leaving (0,0).

Example 2:
Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Explanation:
One possible way is:
Remove stones at (2,2), (2,0), (0,2) leaving (0,0), (1,1).
*/


// Disjoint Set Union (Dynamic DSU with HashMap)
class DSU {
public:
    unordered_map<int, int> parent;

    // Find with path compression
    int find(int x) {
        if (parent.find(x) == parent.end())
            parent[x] = x;
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union two nodes
    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};


// Approach: DSU on Rows + Columns (LeetCode 947)
// 💡 Idea:
// Consider each row and each column as separate graph nodes.
// Each stone at (x, y) connects the row node (x) and column node (y + 10001).
// All stones connected via shared row/column form one connected component.
// Answer = total stones - number of connected components.
//
// 🧩 Algorithm Steps:
// 1. Iterate over each stone at (x, y) and "union" x with (y + OFFSET).
// 2. Track unique parent nodes (connected components).
// 3. Return n - number_of_components.
//
// ⏱ Time Complexity: O(N α(N)) (near-linear)
// 📦 Space Complexity: O(N)

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        DSU dsu;
        for (auto& stone : stones)
            dsu.unite(stone[0], stone[1] + 10001); // Offset to separate row/col space

        unordered_set<int> components;
        for (auto& stone : stones)
            components.insert(dsu.find(stone[0]));

        return stones.size() - components.size();
    }
};


int main() {
    Solution s;

    vector<vector<int>> stones1 = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    vector<vector<int>> stones2 = {{0,0},{0,2},{1,1},{2,0},{2,2}};
    vector<vector<int>> stones3 = {{0,0}};

    cout << "Example 1 Output: " << s.removeStones(stones1) << "\n"; // Expected 5
    cout << "Example 2 Output: " << s.removeStones(stones2) << "\n"; // Expected 3
    cout << "Example 3 Output: " << s.removeStones(stones3) << "\n"; // Expected 0

    return 0;
}


/*
✅ Approach Overview:
| Concept                   | Description |
|----------------------------|-------------|
| Graph-based Components     | Stones sharing row/column are in same component |
| Disjoint Set Union (DSU)   | Efficiently merges row/column relationships |
| Removal Rule               | From each component, keep just one stone |

| Approach | Time Complexity | Space Complexity | Notes |
|-----------|----------------|------------------|------------------------------|
| DSU (HashMap) | O(N α(N)) | O(N) | Efficient and handles large coordinates easily |

This DSU approach is clean, scalable, and commonly accepted for LeetCode 947.
*/
