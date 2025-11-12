#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Frog Jump Minimum Cost (Frog Jump)
Problem Link: https://leetcode.com/problems/frog-jump-with-minimum-cost/ (Conceptual)

Problem Statement:
A frog is at the 0th step of a staircase with heights[], and it can jump to the next step or skip one step.
Each jump costs the absolute difference in height between the landing step and the starting step.
Determine the minimum total cost to reach the last step.

Example:
Input: height = [10, 20, 30, 10]
Output: 20
Explanation:
Jump from step 0 → 1 cost = |20 - 10| = 10
Jump from step 1 → 3 cost = |10 - 20| = 10
Total cost = 20
*/


// Approach 1: Top-Down Memoization
// 💡 Idea:
// Recursively compute minimum cost to reach step i,
// using results from smaller subproblems stored in dp.
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(n) for dp + recursion stack

int generate(vector<int>& height, int i, vector<int>& dp) {
    if (i <= 0) return 0;
    if (dp[i] != -1) return dp[i];

    int jump1 = abs(height[i] - height[i - 1]) + generate(height, i - 1, dp);
    int jump2 = (i > 1) ? abs(height[i] - height[i - 2]) + generate(height, i - 2, dp) : INT_MAX;

    return dp[i] = min(jump1, jump2);
}

int minCostTopDown(vector<int>& height) {
    int n = height.size();
    vector<int> dp(n, -1);
    return generate(height, n - 1, dp);
}


// Approach 2: Bottom-Up Tabulation
// 💡 Idea:
// Compute dp[] iteratively from base cases dp[0] = 0.
// For each step i, dp[i] = min(jump1 cost, jump2 cost).
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(n)

int minCostBottomUp(vector<int>& height) {
    int n = height.size();
    vector<int> dp(n);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        int jump1 = abs(height[i] - height[i - 1]) + dp[i - 1];
        int jump2 = (i > 1) ? abs(height[i] - height[i - 2]) + dp[i - 2] : INT_MAX;
        dp[i] = min(jump1, jump2);
    }
    return dp[n - 1];
}


// Approach 3: Space Optimized Iterative
// 💡 Idea:
// Keep only last two dp values to save space.
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(1)

int minCostSpaceOptimized(vector<int>& height) {
    int n = height.size();
    if (n == 1) return 0;

    int last = 0;        // dp[i-1]
    int secondLast = 0;  // dp[i-2]
    int curr = 0;

    for (int i = 1; i < n; i++) {
        int jump1 = abs(height[i] - height[i - 1]) + last;
        int jump2 = (i > 1) ? abs(height[i] - height[i - 2]) + secondLast : INT_MAX;
        curr = min(jump1, jump2);
        secondLast = last;
        last = curr;
    }

    return curr;
}


int main() {
    vector<int> height = {10, 20, 30, 10};

    cout << "Top-Down Memoization: " << minCostTopDown(height) << "\n";
    cout << "Bottom-Up Tabulation: " << minCostBottomUp(height) << "\n";
    cout << "Space Optimized Iterative: " << minCostSpaceOptimized(height) << "\n";

    return 0;
}

/*
✅ Approach Overview:
| Approach               | Time Complexity | Space Complexity | Notes                        |
|------------------------|-----------------|------------------|------------------------------|
| Top-Down Memoization   | O(n)            | O(n)             | Recursion + caching          |
| Bottom-Up Tabulation   | O(n)            | O(n)             | Iterative DP                 |
| Space Optimized Iterative | O(n)          | O(1)             | Only stores necessary states |

Dynamic Programming transforms exponential recursive calls to linear time using either memoization or tabulation techniques.
*/
