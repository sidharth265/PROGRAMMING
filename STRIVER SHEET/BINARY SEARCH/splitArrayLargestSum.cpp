#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Split Array Largest Sum (LeetCode 410)
---------------------------------------------------------------
Link: https://leetcode.com/problems/split-array-largest-sum/

📌 Problem Statement:
You are given an array of integers nums and an integer k.  
Split nums into k non-empty contiguous subarrays such that:  
➡️ The largest sum among these subarrays is minimized.  

Return the minimized largest sum.

Constraints: 
- 1 <= nums.length <= 1000
- 0 <= nums[i] <= 10^6
- 1 <= k <= min(50, nums.length)

---------------------------------------------------------------
Example 1:
Input: nums = [7,2,5,10,8], k = 2
Output: 18

Explanation: There are 4 ways to split into 2 subarrays:
1. [7,2,5] + [10,8] = max(14,18)=18 ✅ optimal
2. [7,2] + [5,10,8] = max(9,23)=23
3. [7] + [2,5,10,8] = max(7,25)=25
4. [7,2,5,10] +  = max(24,8)=24
Hence the minimized largest sum is 18.

Example 2:
Input: nums = [1,4,4], k = 3
Output: 4
Explanation: Each subarray can be one element.
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Try every possible candidate for "maximum subarray sum" 
  in the range [max(nums), sum(nums)]. 
- Use a helper to check if we can split it into ≤k parts 
  given that maximum.

🧩 Algorithm:
1. Compute `low = max(nums)` (lowest possible max sum).
2. Compute `high = sum(nums)` (highest possible max sum).
3. For each capacity = low…high:
    - Traverse nums, greedily form subarrays without exceeding capacity.
    - If number of subarrays ≤ k → valid
    - Return this capacity as the answer.
4. If none works, return -1.

⏱ Time Complexity: O(n * (sum(nums) - max(nums)))
📦 Space Complexity: O(1)
===============================================================
*/
bool canSplitBrute(vector<int>& nums, int k, int maxAllowed) {
    int subarrays = 1, currSum = 0;
    for (int x : nums) {
        if (currSum + x > maxAllowed) {
            subarrays++;
            currSum = x;
        } else currSum += x;
    }
    return subarrays <= k;
}

int splitArray(vector<int>& nums, int k) {
    if (k > nums.size()) return -1;
    int low = *max_element(nums.begin(), nums.end());
    int high = accumulate(nums.begin(), nums.end(), 0);

    for (int cap = low; cap <= high; cap++) {
        if (canSplitBrute(nums, k, cap)) return cap;
    }
    return -1;
}


/*
===============================================================
Approach 2: Binary Search on Answer (Optimal)
---------------------------------------------------------------
💡 Idea:
- The "can split?" check is monotonic:
   • If possible with maxAllowed = X
   • Then possible for all > X
- So we binary search on [max(nums), sum(nums)].

🧩 Algorithm:
1. Compute `low = max(nums)` (smallest possible max sum).
2. Compute `high = sum(nums)` (largest possible max sum).
3. While low <= high:
   a) mid = (low+high)/2
   b) Greedily check if we can split using maxAllowed=mid
   c) If valid → store ans=mid, shrink (high=mid-1).
   d) If invalid → increase bound (low=mid+1).
4. Return ans.

⏱ Time Complexity: O(n log(sum(nums)))
📦 Space Complexity: O(1)
===============================================================
*/
bool canSplitBinary(vector<int>& nums, int k, int maxAllowed) {
    int subarrays = 1, currSum = 0;
    for (int x : nums) {
        if (currSum + x > maxAllowed) {
            subarrays++;
            currSum = x;
            if (subarrays > k) return false;
        } else currSum += x;
    }
    return true;
}

int splitArray2(vector<int>& nums, int k) {
    if (k > nums.size()) return -1;
    int low = *max_element(nums.begin(), nums.end());
    int high = accumulate(nums.begin(), nums.end(), 0);
    int ans = high;

    while (low <= high) {
        int mid = low+(high-low)/2;
        if (canSplitBinary(nums,k,mid)) {
            ans = mid;       // valid
            high = mid-1;    // try smaller maximum
        } else {
            low = mid+1;     // need larger maximum
        }
    }
    return ans;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> nums = {7,2,5,10,8};
    int k = 2;

    cout << "Brute Force Answer: " << splitArray(nums, k) << endl;    // Expected 18
    cout << "Binary Search Answer: " << splitArray2(nums, k) << endl; // Expected 18

    vector<int> nums2 = {1,4,4};
    k = 3;
    cout << "Binary Search Answer small test: " << splitArray2(nums2, k) << endl; // Expected 4

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Try every possible max sum from max(nums) to sum(nums).
       - Greedy check each possibility.
       - ❌ Very slow.
       - Time: O(n * (sum-max))

    2. Binary Search on Answer (Optimal):
       - Search in [max(nums), sum(nums)].
       - Greedy check with each mid.
       - ✅ Efficient and accepted.
       - Time: O(n log(sum)), Space: O(1)

    🔑 Conclusion:
    - Brute for clarity, Binary Search for actual solution.
    ===========================================================
    */
    return 0;
}
