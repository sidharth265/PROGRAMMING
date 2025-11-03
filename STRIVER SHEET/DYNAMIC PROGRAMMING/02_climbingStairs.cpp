#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Climbing Stairs
Problem Link: https://leetcode.com/problems/climbing-stairs/

Problem Statement:
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps.
In how many distinct ways can you climb to the top?

Example:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top:
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
*/


// Approach 1: Top-Down Memoization (Recursion + DP)
// 💡 Idea:
// Use recursion to break the problem down to smaller subproblems,
// cache results in dp array to avoid recomputation.
//
// 🧩 Algorithm:
// 1. If i == n, one valid way is reached (return 1).
// 2. If i > n, invalid path (return 0).
// 3. If dp[i] already computed, reuse it.
// 4. Otherwise, dp[i] = ways from i+1 + ways from i+2.
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(n)

int generate(int i, int& n, vector<int>& dp) {
    if (i > n) return 0;
    if (i == n) return 1;
    if (dp[i] != -1) return dp[i];
    return dp[i] = generate(i + 1, n, dp) + generate(i + 2, n, dp);
}

int climbStairsTopDown(int n) {
    vector<int> dp(n + 1, -1);
    return generate(0, n, dp);
}


// Approach 2: Bottom-Up Tabulation (Iterative DP)
// 💡 Idea:
// Build up the dp table from the base cases to the target by summation.
//
// 🧩 Algorithm:
// 1. dp[n] = 1 (one way to stay at top).
// 2. dp[n-1] = 1 (one step to top).
// 3. For i = n-2 down to 0, dp[i] = dp[i+1] + dp[i+2].
// 4. Return dp[0] as ways to reach top from bottom.
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(n)

int climbStairsBottomUp(int n) {
    vector<int> dp(n + 1);
    dp[n] = 1;
    dp[n-1] = 1;
    for (int i = n - 2; i >= 0; i--) {
        dp[i] = dp[i + 1] + dp[i + 2];
    }
    return dp[0];
}


// Approach 3: Space Optimized DP
// 💡 Idea:
// Store only last two computed values to save space.
//
// 🧩 Algorithm:
// 1. prev2 = ways to reach top from n (1).
// 2. prev1 = ways to reach top from n-1 (1).
// 3. For i from n-2 down to 0, curr = prev1 + prev2, update prev2 and prev1.
// 4. Return curr.
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(1)

int climbStairsSpaceOpt(int n) {
    if (n == 1) return 1;
    int prev2 = 1, prev1 = 1, curr;
    for (int i = n - 2; i >= 0; i--) {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}


int main() {
    int n = 10;
    cout << "Top-Down Memoization: " << climbStairsTopDown(n) << "\n";
    cout << "Bottom-Up Tabulation: " << climbStairsBottomUp(n) << "\n";
    cout << "Space Optimized DP: " << climbStairsSpaceOpt(n) << "\n";
    return 0;
}

/*
✅ Approach Overview:
| Approach               | Time Complexity | Space Complexity | Notes                         |
|------------------------|-----------------|------------------|-------------------------------|
| Top-Down Memoization   | O(n)            | O(n)             | Recursion + caching            |
| Bottom-Up Tabulation   | O(n)            | O(n)             | Iterative filling              |
| Space Optimized DP     | O(n)            | O(1)             | Efficient space usage          |

Dynamic Programming transforms an exponential recursion into linear time via subproblem caching or bottom-up computation.
*/
