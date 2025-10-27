#include<bits/stdc++.h>
using namespace std;

/*
Problem: Longest Subarray with Sum k

Problem Statement:
Given an integer array nums and an integer k, find the length of the longest contiguous subarray whose sum equals k.

Example:
Input:
  nums = [1, 2, 3, -2, 5], k = 5
Output:
  3
Explanation:
- The subarray [2, 3] sums to 5 (length 2), and [1, 2, 3, -2, 1] would if present; here the longest with sum 5 is [2, 3] or [1, 2, 3, -1] if existed. In this input, [2, 3] and [5] exist; the maximum length is 2. For demonstration, code prints lengths from both approaches on provided input.

Approach Overview:
- Brute Force: Check all subarrays using two loops; update the maximum length when sum equals k.
- Optimized (Prefix Sum + Hash Map): Track the first index where each prefix sum occurs. For each position i with prefix sum S, if (S - k) has appeared at index j, then subarray (j+1..i) sums to k; update the maximum length.

Complexity Overview:
- Brute Force: Time O(n^2), Space O(1).
- Optimized: Time O(n), Space O(n).
*/

/*
Approach 1: Brute Force

Idea:
- For every start index i, accumulate a running sum to j and check if it equals k.

Algorithm:
1) ans = 0
2) For i in [0..n-1]:
     sum = 0
     For j in [i..n-1]:
        sum += nums[j]
        if sum == k: ans = max(ans, j - i + 1)
3) Return ans

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
int getLongestSubarray(vector<int>& nums, int k){
    int n = nums.size();
    int ans = 0;
    for (int i=0; i<n; i++) {
        int sum = 0;
        for (int j=i; j<n; j++) {
            sum += nums[j];
            if (sum == k) {
                ans = max(ans, j-i+1);
            }
        }
    }
    return ans;
}

/*
Approach 2: Prefix Sum + Hash Map (Optimized)

Idea:
- Let prefix sum at i be S. If there exists an earlier index j with prefix sum S-k,
  then the subarray (j+1..i) has sum k. Store only the first occurrence of each prefix sum to maximize length.

Algorithm:
1) ans = 0, sum = 0, map firstIndex
2) For i in [0..n-1]:
     sum += nums[i]
     if sum == k: ans = max(ans, i+1)
     if (sum - k) exists in firstIndex: ans = max(ans, i - firstIndex[sum - k])
     if sum not in firstIndex: firstIndex[sum] = i
3) Return ans

Time Complexity: O(n)
Space Complexity: O(n)
*/
int getLongestSubarray2(vector<int>& nums, int k){
    int n = nums.size();
    unordered_map<int, int> prefixSum;
    int ans = 0;
    int sum = 0;
    for (int i=0; i<n; i++) {
        sum += nums[i];
        if (k==sum) {
            ans = max(ans, i+1);
        }
        if (prefixSum.find(sum-k) != prefixSum.end()) {
            ans = max(ans, i-prefixSum[sum-k]);
        }
        if (prefixSum.find(sum) == prefixSum.end()) {
            prefixSum[sum] = i;
        }
    }
    return ans;
}

int main() {
    vector<int> nums = {1, 2, 3, -2, 5};
    int k = 5;
    cout << "Length of the longest subarray with sum " << k << " (Brute force): " << getLongestSubarray(nums, k) << endl;
    cout << "Length of the longest subarray with sum " << k << " (Optimized): " << getLongestSubarray2(nums, k) << endl;
    return 0;
}
