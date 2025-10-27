#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Count Subsequences with Given Sum
 Problem Link: (Common Subsequence / Backtracking Problem)
====================================================

📝 Problem Statement:
Given an array of integers and a target sum k, count the number of unique subsequences 
(of any length) whose elements sum up exactly to k.

📌 Input:
- An array of integers `arr`
- An integer target sum `k`

📌 Output:
- Number of subsequences that sum to k

----------------------------------------------------
🔹 Example 1:
Input: arr = [1, 2, 3], k = 3  
Output: 2  
Explanation: Subsequences [1, 2] and [3] sum to 3.

🔹 Example 2:
Input: arr = [2, 3, 5, 6], k = 8  
Output: 2  
Explanation: Subsequences [3, 5] and [2, 6] sum to 8.

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Brute Force (Backtracking All Subsequences)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use recursion to either include or exclude each element.
- Keep track of the current sum.
- When we reach the end, if current sum equals target k, increment answer.

🧩 Algorithm:
1. Define recursive function generate(arr, sum, k, i, ans).
2. If index i reaches end:
   - If sum == k, increment ans.
   - Return.
3. Recursive call excluding arr[i].
4. Add arr[i] to sum.
5. Recursive call including arr[i].
6. Backtrack sum by subtracting arr[i].

⏱ Time Complexity: O(2^n) - All subsequences explored  
📦 Space Complexity: O(n) - Call stack for recursion
*/

void generate(vector<int> &arr, int &sum, int &k, int i, int &ans) {
    if (i == arr.size()) {
        if (sum == k) ans++;
        return;
    }
    // Exclude arr[i]
    generate(arr, sum, k, i + 1, ans);
    // Include arr[i]
    sum += arr[i];
    generate(arr, sum, k, i + 1, ans);
    // Backtrack
    sum -= arr[i];
}

int findWaysBrute(vector<int> &arr, int k) {
    int ans = 0;
    int sum = 0;
    generate(arr, sum, k, 0, ans);
    return ans;
}

//////////////////////////////////////////////////////
// Approach 2: Optimized (Using Dynamic Programming - Subset Sum Count)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use DP to count subsequences summing to each possible total.
- dp[i][j]: the number of subsequences from first i elements with sum j.

🧩 Algorithm:
1. Create 2D dp vector of size (n+1) x (k+1).
2. Initialize dp[0][0] = 1 (empty subsequence sum 0).
3. For i in [1..n]:
    For j in [0..k]:
       - dp[i][j] = dp[i-1][j]
       - If j >= arr[i-1], dp[i][j] += dp[i-1][j-arr[i-1]]
4. Result is dp[n][k].

⏱ Time Complexity: O(n*k)  
📦 Space Complexity: O(n*k)
*/

int findWaysDP(vector<int> &arr, int k) {
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= arr[i - 1])
                dp[i][j] += dp[i - 1][j - arr[i - 1]];
        }
    }
    return dp[n][k];
}

//////////////////////////////////////////////////////
// Main function with test cases
//////////////////////////////////////////////////////
int main() {
    vector<int> arr1 = {1, 2, 3};
    int k1 = 3;
    cout << "Brute Force: Number of subsequences with sum " << k1 << ": " << findWaysBrute(arr1, k1) << endl;
    cout << "DP: Number of subsequences with sum " << k1 << ": " << findWaysDP(arr1, k1) << endl;

    vector<int> arr2 = {2, 3, 5, 6};
    int k2 = 8;
    cout << "\nBrute Force: Number of subsequences with sum " << k2 << ": " << findWaysBrute(arr2, k2) << endl;
    cout << "DP: Number of subsequences with sum " << k2 << ": " << findWaysDP(arr2, k2) << endl;

    return 0;
}


//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// 1. Brute Force (Backtracking): Explores all subsequences, simple but exponential time.
// 2. Dynamic Programming: Efficiently counts subsequences with bottom-up table, polynomial time in n*k.
