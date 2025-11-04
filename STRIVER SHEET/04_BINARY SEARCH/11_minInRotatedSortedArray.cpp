#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Find Minimum in Rotated Sorted Array
---------------------------------------------------------------
Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

A sorted array of distinct integers is rotated at some pivot index.
(e.g. [0,1,2,4,5,6,7] rotated at pivot 3 → [4,5,6,7,0,1,2])

Task:
- Find the minimum element in this rotated array.

Constraints:
- Array contains no duplicates.
- Must run in O(log n) time.

---------------------------------------------------------------
Example 1:
Input: nums = [3,4,5,1,2]
Output: 1

Example 2:
Input: nums = [4,5,6,7,0,1,2]
Output: 0

Example 3:
Input: nums = [11,13,15,17]
Output: 11
===============================================================
*/


/*
===============================================================
Approach: Binary Search
---------------------------------------------------------------
💡 Idea:
- Even after rotation, the array has two sorted halves.
- Compare mid element with rightmost element:
  • If nums[mid] > nums[high] → minimum lies in right half.
  • Else → minimum lies in left half (including mid).

🧩 Algorithm:
1. Initialize low = 0, high = n-1.
2. While low < high:
   - mid = (low+high)/2
   - If nums[mid] > nums[high] → low = mid+1
   - Else → high = mid
3. When loop ends, nums[low] = min element.

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(1)
===============================================================
*/
int findMin(vector<int>& nums) {
    int low = 0, high = nums.size()-1, mid;
    while (low < high) {
        mid = low + (high - low)/2;
        if (nums[mid] > nums[high]) low = mid+1; // Min is in right half
        else high = mid; // Min is in left half or at mid
    }
    return nums[low]; // The minimum element is at index low
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> arr1 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Minimum: " << findMin(arr1) << endl; // Output: 0

    vector<int> arr2 = {3, 4, 5, 1, 2};
    cout << "Minimum: " << findMin(arr2) << endl; // Output: 1

    vector<int> arr3 = {11,13,15,17};
    cout << "Minimum: " << findMin(arr3) << endl; // Output: 11

    vector<int> arr4 = {2,3,4,5,6,7,1};
    cout << "Minimum: " << findMin(arr4) << endl; // Output: 1

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    - Brute Force (linear scan): O(n), Space O(1)
       → Just find min directly (too slow for large arrays).

    - Optimal Binary Search:
       - Time: O(log n), Space: O(1)
       - Works because halves remain sorted after rotation.
       - Uses nums[mid] vs nums[high] to decide direction.
    ===========================================================
    */
    return 0;
}
