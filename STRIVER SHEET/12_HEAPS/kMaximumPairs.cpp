#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Top K Sum Combinations from Two Arrays
 Problem Context:
 -----------------
 Given two arrays a and b, find the k largest sums possible where each sum is formed by adding an element from a and an element from b.

 Example:
 Input: a = [1,4,2,3], b = [2,5,1,6], k = 4
 Output: [10, 9, 9, 8]
 Explanation: The top sums are 10 (4+6), 9 (4+5), 9 (3+6), 8 (3+5).

 Constraints:
 - 1 <= size of arrays <= 10^5 (for optimal)
 - k <= size(a) * size(b)
====================================================
*/

/* 
==========================================
 Approach 1: Brute Force - Generate all sums and use a min-heap
-----------------------------------------
💡 Idea:
Calculate all possible sums and maintain a min-heap of size k with largest sums.

⏱ Time Complexity: O(n*m * log k) where n and m are sizes of arrays
📦 Space Complexity: O(k)
*/
vector<int> topKSumPairsBrute(vector<int>& a, vector<int>& b, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;  // min-heap
    
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            int sum = a[i] + b[j];
            pq.push(sum);
            if ((int)pq.size() > k) pq.pop();
        }
    }

    vector<int> ans(pq.size());
    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        ans[i] = pq.top();
        pq.pop();
    }
    return ans;
}

/* 
==========================================
 Approach 2: Better - Using Max-Heap & Sorting (Optimized approach)
-----------------------------------------
💡 Idea:
Sort both arrays. Use a max-heap to efficiently explore largest sums by combination indexes with pruning to avoid duplicate pairs.

🧩 Algorithm:
1. Sort a and b in descending order.
2. Push initial pair (a[0] + b[0], (0,0)) into max-heap.
3. Use a set to track visited index pairs.
4. Pop from heap and add sum to answer.
5. Push next two potential pairs formed by moving one step in a or b if not visited.
6. Repeat k times.

⏱ Time Complexity: O(k log k)
📦 Space Complexity: O(k)
*/
vector<int> topKSumPairsBetter(vector<int> &a, vector<int> &b, int k) {
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    int n = (int)a.size(), m = (int)b.size();
    priority_queue<pair<int, pair<int, int>>> maxHeap;
    set<pair<int,int>> visited;

    maxHeap.push({a[0] + b[0], {0, 0}});
    visited.insert({0, 0});
    vector<int> ans;

    while (k-- && !maxHeap.empty()) {
        auto top = maxHeap.top(); maxHeap.pop();
        ans.push_back(top.first);
        int i = top.second.first, j = top.second.second;

        if (i + 1 < n && !visited.count({i + 1, j})) {
            maxHeap.push({a[i + 1] + b[j], {i + 1, j}});
            visited.insert({i + 1, j});
        }
        if (j + 1 < m && !visited.count({i, j + 1})) {
            maxHeap.push({a[i] + b[j + 1], {i, j + 1}});
            visited.insert({i, j + 1});
        }
    }
    return ans;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Top K Sum Pairs from Two Arrays ===\n\n";

    vector<int> a = {1,4,2,3};
    vector<int> b = {2,5,1,6};
    int k = 4;

    vector<int> resBrute = topKSumPairsBrute(a, b, k);
    cout << "Brute Force Result: ";
    for (int val : resBrute) cout << val << " ";
    cout << "\n";

    vector<int> resBetter = topKSumPairsBetter(a, b, k);
    cout << "Better Result: ";
    for (int val : resBetter) cout << val << " ";
    cout << "\n";

    return 0;
}

/*
✅ Approach Overview:
- Brute Force: Simple heap of all sums, inefficient for large arrays.
- Better: Uses sorting and max heap with visited pairs to prune, efficient with O(k log k) time.
- Use better approach for large inputs.
*/
