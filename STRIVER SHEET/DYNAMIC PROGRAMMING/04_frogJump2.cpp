#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Frog Jump with K Distance
Link: https://leetcode.com/problems/frog-jump/ or similar Frog Jump variants on GeeksforGeeks

Problem Statement:
A frog is initially at position 0 and wants to reach position n-1. Given an array height where height[i] represents the height of the ith stone, the frog can jump from stone i to any stone j where i < j ≤ i + k. The cost of a jump is the absolute difference in the heights of the stones: |height[i] - height[j]|. The goal is to find the minimum total cost to reach the last stone (index n-1).

Examples:

Input:
n = 5, height = [10, 30, 40, 50, 20], k = 3
Output:
30
Explanation:
The frog can jump from stone 0 to stone 4 directly with cost |10-20| = 10,
or from 0 to 1 to 4 with cost |10-30| + |30-20| = 20 + 10 = 30,
or using other jumps, minimal cost is 30.

Input:
n = 3, height = [10, 20, 10], k = 1
Output:
20
Explanation:
Frog can only jump one step at a time,
min cost is |10-20| + |20-10| = 10 + 10 = 20.
*/

/* Approach 1: Brute Force Recursion (Exponential)
💡 Idea:
Try all possible jumps from the current stone i to stones i+1 ... i+k recursively to find minimal cost.

🧩 Algorithm:
1. If at the first stone (index 0), cost = 0.
2. Otherwise, for each possible jump length j=1 to k, recursively compute cost from stone i-j plus jump cost.
3. Return the minimal cost over all jumps.

⏱ Time Complexity: O(k^n) (Exponential, very inefficient)
📦 Space Complexity: O(n) (recursion stack)
*/
int frogJumpRec(int ind, vector<int>& height, int k) {
    if (ind == 0) return 0;
    int minSteps = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if (ind - j >= 0) {
            int jump = frogJumpRec(ind - j, height, k) + abs(height[ind] - height[ind - j]);
            minSteps = min(minSteps, jump);
        }
    }
    return minSteps;
}

/* Approach 2: Top-Down DP with Memoization
💡 Idea:
Same as recursion but store computed results to avoid repeated computations.

🧩 Algorithm:
1. Use a dp vector initialized with -1.
2. If dp[ind] != -1, return dp[ind].
3. Compute min cost as in recursion and store in dp[ind].
4. Return dp[ind].

⏱ Time Complexity: O(n*k)
📦 Space Complexity: O(n) for dp + O(n) for recursion stack
*/
int frogJumpMemo(int ind, vector<int>& height, vector<int>& dp, int k) {
    if (ind == 0) return 0;
    if (dp[ind] != -1) return dp[ind];

    int minSteps = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if (ind - j >= 0) {
            int jump = frogJumpMemo(ind - j, height, dp, k) + abs(height[ind] - height[ind - j]);
            minSteps = min(minSteps, jump);
        }
    }
    return dp[ind] = minSteps;
}

/* Approach 3: Bottom-Up DP (Tabulation)
💡 Idea:
Build up dp array from the start using the relation dp[i] = min(dp[i-j] + cost).

🧩 Algorithm:
1. Initialize dp[0] = 0.
2. For each stone i from 1 to n-1:
   a. Initialize minSteps to max int.
   b. For each j in 1 to k:
      i. Check if stone i-j exists.
      ii. Update minSteps with min(minSteps, dp[i-j] + |height[i] - height[i-j]|).
   c. Set dp[i] = minSteps.
3. Return dp[n-1].

⏱ Time Complexity: O(n*k)
📦 Space Complexity: O(n)
*/
int frogJumpTab(int n, vector<int>& height, int k) {
    vector<int> dp(n, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + abs(height[i] - height[i - j]));
            }
        }
    }
    return dp[n - 1];
}

int main() {
    // Test case 1
    int n1 = 5;
    vector<int> height1 = {10, 30, 40, 50, 20};
    int k1 = 3;

    cout << "Test case 1 results:\n";
    cout << "Brute Force Recursion: " << frogJumpRec(n1 - 1, height1, k1) << "\n";

    vector<int> dp1(n1, -1);
    cout << "Top-Down Memoization: " << frogJumpMemo(n1 - 1, height1, dp1, k1) << "\n";

    cout << "Bottom-Up Tabulation: " << frogJumpTab(n1, height1, k1) << "\n\n";

    // Test case 2
    int n2 = 3;
    vector<int> height2 = {10, 20, 10};
    int k2 = 1;

    cout << "Test case 2 results:\n";
    cout << "Brute Force Recursion: " << frogJumpRec(n2 - 1, height2, k2) << "\n";

    vector<int> dp2(n2, -1);
    cout << "Top-Down Memoization: " << frogJumpMemo(n2 - 1, height2, dp2, k2) << "\n";

    cout << "Bottom-Up Tabulation: " << frogJumpTab(n2, height2, k2) << "\n";

    return 0;
}

/*
✅ Approach Overview:

| Approach           | Time Complexity | Space Complexity | Notes                    |
|--------------------|-----------------|------------------|--------------------------|
| Brute Force        | O(k^n)          | O(n)             | Exponential, impractical |
| Top-Down Memoization| O(n*k)          | O(n) + O(n) stack| Efficient, easy to write |
| Bottom-Up Tabulation| O(n*k)          | O(n)             | Most efficient, iterative|
*/
