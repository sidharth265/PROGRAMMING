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
  2
Explanation:
- The longest subarrays with sum 5 are [2, 3] and [5], so the maximum length is 2.

Approach Overview:
- Brute Force: Check all subarrays by expanding from each start index.
- Optimized (Prefix Sum + Hash Map): Track first index of each prefix sum; if current prefix is S and we saw S-k at index p, then (p+1..i) sums to k.
- Two Pointers (only for non-negative arrays): Maintain a sliding window; expand right, and shrink left while sum > k.

Complexity Overview:
- Brute Force: Time O(n^2), Space O(1).
- Prefix Sum + Hash Map: Time O(n), Space O(n).
- Two Pointers: Time O(n), Space O(1). Note: Works correctly for arrays with all non-negative numbers; with negatives, the window technique is not reliable.
*/

/*
Approach 1: Brute Force

Idea:
- For every start index i, accumulate sum to j and update answer when sum == k.

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
- Let prefix sum at i be S. If we have seen S-k before at index p, the subarray (p+1..i) sums to k.
- Store only the first index of each prefix sum to maximize length.

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

/*
Approach 3: Two Pointers / Sliding Window (Works for non-negative arrays)

Idea:
- Maintain a window [i..j] with running sum.
- Expand j; while sum > k, shrink i. Update answer when sum == k.
- Warning: This approach assumes all numbers are non-negative; with negatives, the window may miss valid subarrays.

Algorithm:
1) i=0, sum=0, ans=0
2) For j in [0..n-1]:
     sum += nums[j]
     while sum > k and i <= j:
         sum -= nums[i], i++
     if sum == k: ans = max(ans, j - i + 1)
3) Return ans

Time Complexity: O(n)
Space Complexity: O(1)
*/
int getLongestSubarray3(vector<int>& nums, int k) {
    int n = nums.size();
    int i=0;
    int j=0;
    int sum = 0;
    int ans = 0;
    while (j<n) {
        sum += nums[j];
        if (sum == k) {
            ans = max(ans, j-i+1);
        }
        while (sum > k && i <= j) {
            sum -= nums[i];
            i++;
        }
        if (sum == k) {
            ans = max(ans, j-i+1);
        }
        j++;
    }
    return ans;
}

int main() {
    vector<int> nums = {1, 2, 3, -2, 5};
    int k = 5;
    cout << "Length (Brute Force):  " << getLongestSubarray(nums, k) << "\n";
    cout << "Length (Optimized):    " << getLongestSubarray2(nums, k) << "\n";
    // Note: Sliding window (Approach 3) is suitable for non-negative arrays.
    cout << "Length (Sliding Window):" << getLongestSubarray3(nums, k) << "\n";
    return 0;
}
