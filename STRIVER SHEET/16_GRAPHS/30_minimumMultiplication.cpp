#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Minimum Multiplications to Reach End
Problem Link: https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1

Problem Statement:
Given an integer start, an integer end, and an array arr[] of positive integers.
At each step, you can multiply the current number by **any** element of arr and then take modulo 100000.
Your task is to find the **minimum number of multiplications** needed to reach `end` starting from `start`.
If it is impossible to reach end, return -1.

Example 1:
Input: arr = [2, 5, 7], start = 3, end = 30
Output: 2
Explanation:
Step 1: 3 * 2 = 6 % 100000 = 6
Step 2: 6 * 5 = 30 % 100000 = 30
=> Reached end in 2 multiplications.

Example 2:
Input: arr = [3, 4, 65], start = 7, end = 66175
Output: 4
Explanation:
7 * 3 = 21
21 * 3 = 63
63 * 65 = 4095
4095 * 65 = 266175 % 100000 = 66175
*/


// Approach: BFS on Modular Graph
// 💡 Idea:
// Treat each number (0–99999) as a graph node where an edge from `a -> (a * x) % 100000` exists for every x in arr.
// Use BFS to find the shortest path (fewest multiplications) from start to end.
//
// 🧩 Algorithm:
// 1. Initialize queue and visited[] array (size = 100000).
// 2. Start BFS from `start`, with distance counter `d`.
// 3. For each current value v, compute `(v * x) % 100000` for each x in arr.
// 4. If we reach `end`, return d (number of steps).
// 5. If BFS completes without reaching end, return -1.
//
// ⏱ Time Complexity: O(100000 * |arr|) in worst case.
// 📦 Space Complexity: O(100000)

int minimumMultiplications(vector<int>& arr, int start, int end) {
    int mod = 100000;
    vector<bool> visited(mod, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    int d = 0;
    while (!q.empty()) {
        int l = q.size();
        for (int i = 0; i < l; i++) {
            int v = q.front();
            q.pop();

            if (v == end) return d;
            for (int x : arr) {
                int u = (v * x) % mod;
                if (!visited[u]) {
                    q.push(u);
                    visited[u] = true;
                }
            }
        }
        d++;
    }
    return -1;
}


int main() {
    // Example 1
    vector<int> arr1 = {2, 5, 7};
    int start1 = 3, end1 = 30;
    cout << "Example 1 Output: " << minimumMultiplications(arr1, start1, end1) << "\n"; // Expected: 2

    // Example 2
    vector<int> arr2 = {3, 4, 65};
    int start2 = 7, end2 = 66175;
    cout << "Example 2 Output: " << minimumMultiplications(arr2, start2, end2) << "\n"; // Expected: 4

    // Example 3 - unreachable case
    vector<int> arr3 = {37, 45, 59};
    int start3 = 10, end3 = 99999;
    cout << "Example 3 Output: " << minimumMultiplications(arr3, start3, end3) << "\n"; // Expected: -1

    return 0;
}

/*
✅ Approach Overview:
| Approach      | Time Complexity | Space Complexity | Notes                                     |
|----------------|----------------|------------------|-------------------------------------------|
| BFS (Graph)    | O(100000 * k)  | O(100000)        | Efficient & optimal for minimal steps     |

This BFS approach ensures that each number (mod 100000) is visited at most once, guaranteeing the shortest path to 'end'.
*/
