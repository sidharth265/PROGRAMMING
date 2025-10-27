#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Find the Smallest Divisor Given a Threshold
---------------------------------------------------------------
Link: https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/

Given an array `nums` and an integer `threshold`, find the
**smallest divisor d** such that:

   sum( ceil(nums[i] / d) ) <= threshold

---------------------------------------------------------------
Example:
Input: nums = [1,2,5,9], threshold = 6
Output: 5

Explanation:
If d=5 → [ceil(1/5), ceil(2/5), ceil(5/5), ceil(9/5)]
        = [1,1,1,2] = sum=5 <= 6 ✅
If d=4 → [1,1,2,3] = sum=7 (too large ❌)

So the smallest divisor is 5.
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Start from divisor = 1, increase until we satisfy threshold.

🧩 Algorithm:
1. divisor = 1
2. Compute sum( ceil(nums[i]/divisor) ).
3. If sum <= threshold → return divisor.
4. Else divisor++

⏱ Time Complexity: O(n * max(nums))
📦 Space Complexity: O(1)
===============================================================
*/
int smallestDivisor(vector<int>& nums, int threshold) {
    for (int divisor = 1; ; divisor++) {
        int sum = 0;
        for (int num : nums) {
            sum += (num + divisor - 1) / divisor; // integer ceil
        }
        if (sum <= threshold) return divisor;
    }
    return -1; // should never reach
}


/*
===============================================================
Approach 2: Optimized Binary Search
---------------------------------------------------------------
💡 Idea:
- Divisor range = [1, max(nums)].
- If divisor too small → sum is large (>threshold).
- As divisor increases → sum decreases monotonically.
- Monotonic property ⇒ binary search on divisor!

🧩 Algorithm:
1. low = 1, high = max(nums).
2. While low <= high:
   - mid = (low+high)/2
   - If sum(ceil(nums[i]/mid)) <= threshold → valid
     → try smaller divisor (move high=mid-1).
   - Else move low=mid+1.
3. Answer = low.

⏱ Time Complexity: O(n log(max(nums)))
📦 Space Complexity: O(1)
===============================================================
*/
bool exceedsThreshold(vector<int>& nums, int threshold, int d) {
    int sum = 0;
    for (int x : nums) {
        sum += (x + d - 1) / d; // integer division ceil
        if (sum > threshold) return true; // early exit
    }
    return false;
}

int smallestDivisor2(vector<int>& nums, int threshold) {
    int high = *max_element(nums.begin(), nums.end());
    int low = 1, ans = high;

    while (low <= high) {
        int mid = low + (high-low)/2;
        if (!exceedsThreshold(nums, threshold, mid)) {
            ans = mid;    // valid divisor
            high = mid-1; // try smaller
        } else {
            low = mid+1;  // need larger divisor
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
    vector<int> nums = {1, 2, 5, 9};
    int threshold = 6;

    cout << "Brute Force: " 
         << smallestDivisor(nums, threshold) << endl; // Expected 5

    cout << "Binary Search: " 
         << smallestDivisor2(nums, threshold) << endl; // Expected 5

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Check every divisor from 1 to max(nums).
       - Very slow if max(nums) is large.
       - Time: O(n * max(nums)).

    2. Binary Search (Optimal):
       - Exploits monotonic behavior of sum vs divisor.
       - Time: O(n log(max(nums))).
       - Space: O(1).
       - 🏆 Expected in interviews and contests.
    ===========================================================
    */
    return 0;
}
