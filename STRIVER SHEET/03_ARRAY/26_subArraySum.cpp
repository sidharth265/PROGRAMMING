#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Count Subarrays With Sum Equal to k

Problem Statement:
Given an integer array nums and an integer k, return the total number of continuous subarrays whose sum equals k.
The array may contain negative numbers, so sliding window is not reliable; use prefix sums for the optimized solution.

Example:
Input:  nums = [1, 1, 1], k = 2
Output: 2
Explanation: Subarrays [1,1] at indices (0,1) and (1,2).

Approach Overview:
- Approach 1 (Brute Force): Try all subarrays, maintain a running sum, increment count when sum == k.
- Approach 2 (Prefix Sum + HashMap): Track frequency of seen prefix sums; for each prefix sum S, add freq[S - k] to answer.
*/

/*
Approach: Brute Force
Approach Idea:
- Fix a start index i and extend the end index j while maintaining a running sum.
- Every time the running sum equals k, increment the count.
- Enumerates all O(n^2) subarrays by construction.

Algorithm:
1) ans = 0
2) For i = 0..n-1:
   - sum = 0
   - For j = i..n-1:
     - sum += nums[j]
     - If sum == k: ans++
3) Return ans

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
int subarraySum_bruteforce(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum == k) ans++;
        }
    }
    return ans;
}

/*
Approach: Optimized (Prefix Sum + HashMap)
Approach Idea:
- Maintain a running prefix sum S.
- Any subarray ending at current index with sum k corresponds to a prior prefix sum equal to S - k.
- Use a hashmap to store frequencies of prefix sums; add freq[S - k] to the answer before incrementing freq[S].

Algorithm:
1) freq[0] = 1, S = 0, ans = 0
2) For each x in nums:
   - S += x
   - If (S - k) exists in freq: ans += freq[S - k]
   - freq[S]++
3) Return ans

Time Complexity: O(n)
Space Complexity: O(n)
*/
int subarraySum_optimized(vector<int>& nums, int k) {
    unordered_map<long long,int> freq;
    freq[0] = 1;
    long long S = 0;
    int ans = 0;
    for (int x : nums) {
        S += x;
        auto it = freq.find(S - k);
        if (it != freq.end()) ans += it->second;
        freq[S]++;
    }
    return ans;
}

int main() {
    vector<int> nums = {1, 1, 1};
    int k = 2;

    cout << "Brute force:   " << subarraySum_bruteforce(nums, k) << "\n";
    cout << "Optimized:     " << subarraySum_optimized(nums, k) << "\n";
    return 0;
}
