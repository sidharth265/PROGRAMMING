#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: House Robber
Link: https://leetcode.com/problems/house-robber/

Problem Statement:
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, represented by the array nums. Adjacent houses have security systems connected, so robbing two adjacent houses will trigger an alarm. Find the maximum amount of money you can rob without alerting the police.

Example:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount = 1 + 3 = 4.

Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), house 3 (money = 9), and house 5 (money = 1).
Total amount = 2 + 9 + 1 = 12.
*/

/* Approach 1: Brute Force Recursion (Exponential)
💡 Idea:
Try robbing the current house and then skip the next, or skip the current house, and take the maximum.

🧩 Algorithm:
1. Start from index i=0 or 1 (to cover all options).
2. Recursively compute max amount by robbing i and moving to i+2 or i+3.
3. Track maximum amount robbed.

⏱ Time Complexity: O(2^n) (Exponential)
📦 Space Complexity: O(n) (recursion stack)
*/
void robRecUtil(vector<int>& nums, int i, int currentSum, int& maxSum) {
    if(i >= nums.size()) {
        maxSum = max(maxSum, currentSum);
        return;
    }
    currentSum += nums[i];
    robRecUtil(nums, i + 2, currentSum, maxSum);
    robRecUtil(nums, i + 3, currentSum, maxSum);
    currentSum -= nums[i]; // backtrack
}

int robRec(vector<int>& nums) {
    int maxSum = 0;
    robRecUtil(nums, 0, 0, maxSum);
    robRecUtil(nums, 1, 0, maxSum);
    return maxSum;
}

/* Approach 2: Top-Down Memoization
💡 Idea:
Use recursion with memoization to avoid recalculations.

🧩 Algorithm:
1. Define dp initialized with -1.
2. For each index i:
   a. If dp[i] != -1, return dp[i].
   b. Compute max by robbing i + max of dp[i+2] or dp[i+3].
3. Return dp[i].

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) + O(n) recursion stack
*/
int robMemoUtil(vector<int>& nums, int i, vector<int>& dp) {
    if(i >= nums.size()) return 0;
    if(dp[i] != -1) return dp[i];
    int cost1 = robMemoUtil(nums, i + 2, dp);
    int cost2 = robMemoUtil(nums, i + 3, dp);
    return dp[i] = nums[i] + max(cost1, cost2);
}

int robMemo(vector<int>& nums) {
    vector<int> dp(nums.size(), -1);
    return max(robMemoUtil(nums, 0, dp), robMemoUtil(nums, 1, dp));
}

/* Approach 3: Bottom-Up DP (Tabulation)
💡 Idea:
Build dp array where dp[i] is max amount robbed up to house i.

🧩 Algorithm:
1. Initialize dp[0] = nums[0].
2. dp[1] = max(nums[0], nums[1]).
3. For i in range 2 to n-1:
   dp[i] = max(nums[i] + dp[i-2], dp[i-1]).
4. Return dp[n-1].

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/
int robTab(vector<int>& nums) {
    int n = nums.size();
    if(n == 1) return nums[0];
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for(int i = 2; i < n; i++) {
        dp[i] = max(nums[i] + dp[i-2], dp[i-1]);
    }
    return dp[n-1];
}

/* Approach 4: Space-Optimized DP
💡 Idea:
Use two variables to store previous states instead of full dp array.

🧩 Algorithm:
1. Keep two variables: secondLast (dp[i-2]) and last (dp[i-1]).
2. For each house i, compute current max = max(nums[i] + secondLast, last).
3. Update secondLast and last accordingly.
4. Return last.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/
int robOptimized(vector<int>& nums) {
    int n = nums.size();
    if(n == 1) return nums[0];
    int secondLast = 0;
    int last = nums[0];
    for(int i = 1; i < n; i++) {
        int curr = max(nums[i] + secondLast, last);
        secondLast = last;
        last = curr;
    }
    return last;
}

int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3, 1},
        {2, 7, 9, 3, 1},
        {10, 1, 1, 10, 1, 10}
    };

    for(int idx = 0; idx < (int)testCases.size(); idx++) {
        cout << "Test case " << idx+1 << ":\n";

        cout << "Brute Force Recursion: " << robRec(testCases[idx]) << "\n";

        cout << "Top-Down Memoization: " << robMemo(testCases[idx]) << "\n";

        cout << "Bottom-Up Tabulation: " << robTab(testCases[idx]) << "\n";

        cout << "Space-Optimized DP: " << robOptimized(testCases[idx]) << "\n\n";
    }

    return 0;
}

/*
✅ Approach Overview:

| Approach             | Time Complexity | Space Complexity       | Notes                              |
|----------------------|-----------------|-----------------------|----------------------------------|
| Brute Force Recursion | O(2^n)          | O(n)                  | Exponential, only for small n    |
| Top-Down Memoization  | O(n)            | O(n) + O(n) recursion | Efficient, recursive              |
| Bottom-Up Tabulation  | O(n)            | O(n)                  | Iterative, uses dp array          |
| Space-Optimized DP    | O(n)            | O(1)                  | Uses constant space, most optimal |
*/
