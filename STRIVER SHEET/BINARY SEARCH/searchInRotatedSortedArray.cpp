#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Search in Rotated Sorted Array
---------------------------------------------------------------
Link: https://leetcode.com/problems/search-in-rotated-sorted-array/

You are given an integer array `nums` (sorted in ascending order)
that has been rotated at an unknown pivot index.

Return the index of `target` if found, else return -1.

Constraints:
- No duplicate elements.
- Must run in O(log n) time.

---------------------------------------------------------------
Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:
Input: nums = [1], target = 0
Output: -1
===============================================================
*/


/*
===============================================================
Approach: Modified Binary Search
---------------------------------------------------------------
💡 Key Observations:
- In a rotated array at least one half (left or right of mid)
  is always sorted.
- Compare `target` with sorted half’s range:
  • If it lies inside ⇒ shrink search to this half.
  • Otherwise ⇒ move search to the other half.
- Repeat until found or exhausted.

🧩 Algorithm:
1. Initialize low=0, high=n-1
2. While low <= high:
   - mid = (low+high)/2
   - If nums[mid]==target → return mid
   - If left half sorted (nums[low] <= nums[mid]):
       * If target in range [nums[low], nums[mid]) → high=mid-1
       * Else → low=mid+1
   - Else (right half sorted):
       * If target in range (nums[mid], nums[high]] → low=mid+1
       * Else → high=mid-1
3. If not found → return -1

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(1)
===============================================================
*/
int search(vector<int>& nums, int target) {
    int low = 0, high = nums.size()-1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (nums[mid] == target) return mid;  // Target found

        // If left half is sorted
        if (nums[low] <= nums[mid]) {
            if (target >= nums[low] && target < nums[mid])
                high = mid - 1;  // Search left half
            else
                low = mid + 1;   // Search right half
        }
        // Else right half is sorted
        else {
            if (target > nums[mid] && target <= nums[high])
                low = mid + 1;  // Search right half
            else
                high = mid - 1; // Search left half
        }
    }
    return -1; // Not found
}


/*
===============================================================
Example Usage / Testing
===============================================================
*/
int main() {
    vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Search 0: " << search(nums1, 0) << endl;  // Expected 4
    cout << "Search 3: " << search(nums1, 3) << endl;  // Expected -1

    vector<int> nums2 = {1};
    cout << "Search 1: " << search(nums2, 1) << endl;  // Expected 0
    cout << "Search 0: " << search(nums2, 0) << endl;  // Expected -1

    vector<int> nums3 = {6,7,1,2,3,4,5};
    cout << "Search 3: " << search(nums3, 3) << endl;  // Expected 4

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    - Linear Scan: O(n), trivial but too slow.
    - Modified Binary Search: O(log n), Space O(1).
      • At least one half always sorted.
      • Narrow search based on range check.
    🔑 Always the expected answer in interviews.
    ===========================================================
    */
    return 0;
}
