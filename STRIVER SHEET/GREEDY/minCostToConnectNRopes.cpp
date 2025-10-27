#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Minimum Cost to Connect Ropes
Problem Link: https://practice.geeksforgeeks.org/problems/minimum-cost-of-ropes1456/1

Problem Statement:
Given N ropes of different lengths, your task is to connect these ropes into one rope. 
The cost of joining two ropes is equal to the sum of their lengths. 
Find the minimum cost to connect all ropes.

Example 1:
Input: [4, 3, 2, 6]
Output: 29
Explanation:
1. Connect ropes 2 and 3: cost = 5
2. Connect ropes 4 and 5: cost = 9
3. Connect ropes 6 and 9: cost = 15
Total cost = 5 + 9 + 15 = 29

Example 2:
Input: [1, 2, 3, 4, 5]
Output: 33
Explanation:
Combine 1 & 2 = 3 (cost 3)
Combine 3 & 3 = 6 (cost 6)
Combine 4 & 5 = 9 (cost 9)
Combine 6 & 9 = 15 (cost 15)
Total cost = 3+6+9+15 = 33

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Greedy using Min-Heap (Priority Queue)
   ------------------------------------------------------
   💡 Idea:
   Always connect the two smallest ropes first to minimize cost.
   Use a min-heap to efficiently get the smallest two ropes.

   🧩 Algorithm:
   1. Insert all rope lengths into a min-heap.
   2. Initialize total cost = 0.
   3. While there is more than one rope in the heap:
       a. Extract two smallest ropes.
       b. Add their lengths (cost) to total cost.
       c. Insert the combined rope back into heap.
   4. Return the total cost.

   ⏱ Time Complexity: O(N log N)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
int minCost(vector<int>& arr) {
    int ans = 0;
    priority_queue<int, vector<int>, greater<int>> q;
    for (int x : arr) q.push(x);
    while (q.size() > 1) {
        int a = q.top(); q.pop();
        int b = q.top(); q.pop();
        int add = a + b;
        ans += add;
        q.push(add);
    }
    return ans;
}

/* ===================== Main Function ===================== */
int main() {
    vector<vector<int>> testCases = {
        {4, 3, 2, 6},
        {1, 2, 3, 4, 5},
        {5, 17, 100, 11},
        {1, 1, 1, 1}
    };

    for (int i = 0; i < (int)testCases.size(); i++) {
        cout << "Test Case " << i + 1 << ": ";
        for (int x : testCases[i]) cout << x << " ";
        cout << "\nMinimum Cost: " << minCost(testCases[i]) << "\n\n";
    }

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method             | Time Complexity | Space Complexity | Notes                     |
       |--------------------|----------------|------------------|---------------------------|
       | Min-Heap Greedy    | O(N log N)      | O(N)             | Efficient, preferred approach |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
