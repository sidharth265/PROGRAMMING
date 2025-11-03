#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: House Robber II
Link: https://leetcode.com/problems/house-robber-ii/

Problem Statement:
You are a professional robber planning to rob houses arranged in a circle. Each house has a certain amount of money stashed, represented by the array nums. Adjacent houses have security connections, so robbing two adjacent houses will trigger an alarm. Because houses are in a circle, the first and last house are also adjacent. Find the maximum amount you can rob without alerting the police.

Example:

Input: nums = [2,3,2]
Output: 3
Explanation: Cannot rob house 1 and house 3 together because they are adjacent in a circle. Rob house 2 only for maximum amount 3.

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money=1) and house 3 (money=3), total 4.
*/

/* Approach 1: Convert Circular to Two Linear Robber Problems
💡 Idea:
The circular constraint means first and last houses cannot both be robbed. We solve two linear "House Robber I" problems:
1. Rob houses from index 0 to n-2
2. Rob houses from index 1 to n-1
Take the max of these two results.

🧩 Algorithm:
1. If only one house, return its amount.
2. Define helper function to solve linear robber problem.
3. Compute max robbed amount excluding last house.
4. Compute max robbed amount excluding first house.
5. Return max of these two.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) for DP array
*/

/* Helper function: solves House Robber I on a linear array */
int robLinear(vector<int>& nums, int start, int end) {
    int length = end - start + 1;
    vector<int> dp(length);
    dp[0] = nums[start];
    if (length == 1) return dp[0];
    dp[1] = max(nums[start], nums[start + 1]);
    for (int i = 2; i < length; i++) {
        dp[i] = max(nums[start + i] + dp[i - 2], dp[i - 1]);
    }
    return dp[length - 1];
}

/* Main function for House Robber II */
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];

    int robExcludingLast = robLinear(nums, 0, n - 2);
    int robExcludingFirst = robLinear(nums, 1, n - 1);

    return max(robExcludingLast, robExcludingFirst);
}

int main() {
    vector<vector<int>> testCases = {
        {2, 3, 2},
        {1, 2, 3, 1},
        {1, 2, 3},
        {4, 1, 2, 7, 5, 3, 1}
    };

    for (int i = 0; i < (int)testCases.size(); i++) {
        cout << "Test Case " << i + 1 << " result: " << rob(testCases[i]) << "\n";
    }

    return 0;
}

/*
✅ Approach Overview:

| Approach                      | Time Complexity | Space Complexity | Notes                             |
|-------------------------------|-----------------|------------------|----------------------------------|
| Linear House Robber (Helper)  | O(n)            | O(n)             | Standard House Robber I solution |
| Circular House Robber II       | O(n)            | O(n)             | Solve two linear problems and max|
*/
