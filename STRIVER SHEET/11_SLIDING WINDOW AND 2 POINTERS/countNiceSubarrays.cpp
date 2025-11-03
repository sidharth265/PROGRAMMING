#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Count Number of Nice Subarrays
 Problem Link: https://leetcode.com/problems/count-number-of-nice-subarrays/

 Problem Statement:
 Given an array of integers `nums` and an integer `k`, return the number of 
 non-empty subarrays with exactly `k` odd numbers.

-------------------------------------------------
 Example 1:
 Input: nums = [1,1,2,1,1], k = 3
 Output: 2
 Explanation: The subarrays with exactly 3 odd numbers are [1,1,2,1] and [1,2,1,1].

 Example 2:
 Input: nums = [2,4,6], k = 1
 Output: 0
 Explanation: There is no subarray with exactly one odd number.

 Example 3:
 Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
 Output: 16
-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force
// -------------------------------------------------
/*
💡 Idea:
   - Iterate over all subarrays.
   - Count the number of odd numbers in each subarray.
   - If odd count == k, increment answer.
   - Break early if odd count > k.

🧩 Algorithm:
   1. Initialize ans = 0.
   2. For i in [0..n-1]:
        - oddCount = 0
        - For j in [i..n-1]:
            - If nums[j] is odd, oddCount++
            - If oddCount == k, ans++
            - Else if oddCount > k, break
   3. Return ans.

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(1)
*/

int numberOfSubarraysBrute(vector<int>& nums, int k) {
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        int oddCount = 0;
        for (int j = i; j < n; j++) {
            if (nums[j] % 2 != 0) oddCount++;
            if (oddCount == k) ans++;
            else if (oddCount > k) break;
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 2: Sliding Window with AtMost Trick
// -------------------------------------------------
/*
💡 Idea:
   - The count of subarrays with exactly k odd numbers = 
     count of subarrays with at most k odd numbers - count of subarrays with at most (k-1) odd numbers.
   - Use sliding window to count subarrays with at most t odd numbers.

🧩 Algorithm:
   Helper: atMost(nums, t)
     - Use two pointers to maintain window with ≤ t odd numbers.
     - Move right pointer, update odd count.
     - If odd count > t, move left pointer until valid again.
     - Add window length to answer.
   Main:
     - Return atMost(nums, k) - atMost(nums, k-1)

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/

int atMost(vector<int>& nums, int t) {
    if (t < 0) return 0;
    int ans = 0, left = 0, oddCount = 0;
    int n = nums.size();
    for (int right = 0; right < n; right++) {
        if (nums[right] & 1) oddCount++;
        while (oddCount > t) {
            if (nums[left] & 1) oddCount--;
            left++;
        }
        ans += right - left + 1;
    }
    return ans;
}

int numberOfSubarraysOptimal(vector<int>& nums, int k) {
    return atMost(nums, k) - atMost(nums, k - 1);
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1, 1, 2, 1, 1}, 3},
        {{2, 4, 6}, 1},
        {{2, 2, 2, 1, 2, 2, 1, 2, 2, 2}, 2}
    };

    for (auto& t : tests) {
        const vector<int>& nums = t.first;
        int k = t.second;

        cout << "Input array: ";
        for (int num : nums) cout << num << " ";
        cout << "\nk = " << k << "\n";

        cout << "Brute Force: " << numberOfSubarraysBrute(const_cast<vector<int>&>(nums), k) << "\n";
        cout << "Optimal Sliding Window: " << numberOfSubarraysOptimal(const_cast<vector<int>&>(nums), k) << "\n";
        cout << "--------------------------\n";
    }

    // -------------------------------------------------
    // ✅ Approach Overview
    // -------------------------------------------------
    /*
    Approach 1 (Brute Force):
      - Checks all subarrays exhaustively.
      - TC = O(n^2), SC = O(1)

    Approach 2 (Sliding Window with AtMost Trick):
      - Uses two pointers to count subarrays at most k and at most k-1 odd counts.
      - TC = O(n), SC = O(1)
    */

    return 0;
}
