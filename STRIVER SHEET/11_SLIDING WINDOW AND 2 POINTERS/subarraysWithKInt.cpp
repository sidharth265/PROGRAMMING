#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Subarrays with K Different Integers
 Problem Link: https://leetcode.com/problems/subarrays-with-k-different-integers/

 Problem Statement:
 Given an array of integers nums and an integer k,
 return the number of subarrays with exactly k distinct integers.

-------------------------------------------------
 Example:
 Input: nums = [1,2,1,2,3], k = 2
 Output: 7
 Explanation:
 Subarrays: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,3]
-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force (O(n^2))
// -------------------------------------------------
/*
💡 Idea:
   - For each starting index, expand the subarray while counting distinct values.
   - Once we reach k distinct, increment answer.
   - If distinct exceeds k, break inner loop.

🧩 Algorithm:
   1. For i in [0..n-1]:
      - Create empty hashmap
      - For j in [i..n-1]:
         - Add nums[j] to map
         - If map.size() == k, increment ans
         - If map.size() > k, break

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(n)
*/

int subarraysWithKDistinctBrute(vector<int>& nums, int k) {
    int ans = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        unordered_map<int, int> intCount;
        for (int j = i; j < n; j++) {
            intCount[nums[j]]++;
            if ((int)intCount.size() == k) ans++;
            else if ((int)intCount.size() > k) break;
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 2: Sliding Window (atMost Trick, O(n))
// -------------------------------------------------
/*
💡 Idea:
   - The number of subarrays with **exactly** k distinct elements =
     (# with at most k) - (# with at most k-1)
   - Use a sliding window to efficiently count subarrays with at most t distinct numbers.

🧩 Algorithm:
   Helper:
     int atMost(nums, t):
       - Initialize count map, ans, left pointer.
       - For each right, add to map.
           - If map.size() > t, increment left and remove from map as needed.
           - Add (right - left + 1) to ans for each window.
   Main:
     subarraysWithKDistinct(nums, k) = atMost(nums, k) - atMost(nums, k-1)

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

int atMost(vector<int>& nums, int k) {
    if (k == 0) return 0;
    unordered_map<int, int> intCount;
    int ans = 0, left = 0;
    for (int right = 0; right < (int)nums.size(); right++) {
        if (++intCount[nums[right]] == 1) k--;
        while (k < 0) {
            if (--intCount[nums[left]] == 0) k++;
            left++;
        }
        ans += right - left + 1;
    }
    return ans;
}

int subarraysWithKDistinctOptimal(vector<int>& nums, int k) {
    return atMost(nums, k) - atMost(nums, k - 1);
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1,2,1,2,3}, 2},
        {{1,2,1,3,4}, 3},
        {{1,2,1,2,3,4}, 3},
        {{1,2,3,4,5}, 5},
        {{1,2,1,3,4,2,3}, 3}
    };

    for (int i = 0; i < (int)tests.size(); i++) {
        const vector<int>& nums = tests[i].first;
        int k = tests[i].second;
        cout << "Test case " << (i+1) << ": nums = ";
        for (int num : nums) cout << num << " ";
        cout << "k = " << k << endl;
        cout << "Brute Force: " << subarraysWithKDistinctBrute(const_cast<vector<int>&>(nums), k) << endl;
        cout << "Sliding Window Optimal: " << subarraysWithKDistinctOptimal(const_cast<vector<int>&>(nums), k) << endl;
        cout << "-----------------------------\n";
    }

    // ✅ Approach Overview
    /*
    Approach 1 (Brute Force):  TC = O(n^2), SC = O(n)
    Approach 2 (Sliding Window): TC = O(n), SC = O(n)
    */

    return 0;
}
