#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Search in Rotated Sorted Array II (Duplicates Allowed)
---------------------------------------------------------------
Link: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

You are given an integer array `nums` sorted in ascending order,
rotated at an unknown pivot, and may contain **duplicates**.

Return true if target exists, else false.

---------------------------------------------------------------
Example 1:
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

Example 3:
Input: nums = [1,0,1,1,1], target = 0
Output: true
===============================================================
*/


/*
===============================================================
Approach: Modified Binary Search with Duplicate Handling
---------------------------------------------------------------
💡 Key Observations:
- Same as rotated sorted array search (LeetCode 33).
- But duplicates make it ambiguous, e.g. [2,2,2,3,4,2]:
   • nums[low] == nums[mid] == nums[high] ⇒ can't tell which half sorted.
   • Solution: skip duplicates by doing low++ or high--.

🧩 Algorithm:
1. Initialize low=0, high=n-1
2. While low <= high:
   - mid = (low+high)/2
   - If nums[mid]==target → return mid
   - If nums[low] < nums[mid] → Left half sorted
       * If target in [nums[low], nums[mid]) → search left
       * Else → search right
   - Else if nums[low] > nums[mid] → Right half sorted
       * If target in (nums[mid], nums[high]] → search right
       * Else → search left
   - Else (nums[low]==nums[mid]) → low++ (skip duplicate)
3. If not found → return -1

⏱ Time Complexity:
- Best/Average: O(log n)
- Worst case (all duplicates): O(n)
📦 Space Complexity: O(1)
===============================================================
*/
int search(vector<int>& nums, int target) {
    int low = 0, high = nums.size()-1;
    while (low <= high) {
        int mid = low + (high - low)/2;

        if (nums[mid] == target) return mid;  // target found

        // Left half sorted
        if (nums[low] < nums[mid]) {
            if (target >= nums[low] && target < nums[mid])
                high = mid-1;
            else
                low = mid+1;
        }
        // Right half sorted
        else if (nums[low] > nums[mid]) {
            if (target > nums[mid] && target <= nums[high])
                low = mid+1;
            else
                high = mid-1;
        }
        // Duplicates case: nums[low] == nums[mid]
        else {
            low++;  // skip duplicate
        }
    }
    return -1; // not found
}


/*
===============================================================
Example Usage / Test Cases
===============================================================
*/
int main() {
    vector<int> nums1 = {2, 5, 6, 0, 0, 1, 2};
    cout << "Search 0: " << search(nums1, 0) << endl; // Expected index of 0 (e.g., 3 or 4)

    cout << "Search 3: " << search(nums1, 3) << endl; // Expected -1 (not present)

    vector<int> nums2 = {1, 0, 1, 1, 1};
    cout << "Search 0: " << search(nums2, 0) << endl; // Expected 1

    vector<int> nums3 = {1,1,1,1,1,1};
    cout << "Search 1: " << search(nums3, 1) << endl; // Expected valid index (0 to n-1)
    cout << "Search 2: " << search(nums3, 2) << endl; // Expected -1 (not present)

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    - Without Duplicates (LeetCode 33):
       • Strictly O(log n) using binary search.

    - With Duplicates (LeetCode 81):
       • Need to handle ambiguous "all equal" case.
       • Worst case degrades to O(n), but usually O(log n).

    🔑 Conclusion:
    - For duplicates, average runtime is still efficient.
    - Worst case (all same elements) requires scan.
    ===========================================================
    */

    return 0;
}
