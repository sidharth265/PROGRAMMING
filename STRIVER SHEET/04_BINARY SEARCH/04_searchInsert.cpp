#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Search Insert Position
---------------------------------------------------------------
Link: https://leetcode.com/problems/search-insert-position/

Given a sorted array of distinct integers and a target value,
return the index if the target is found.  
If not, return the index where it would be **inserted in order**.

---------------------------------------------------------------
Example 1:
Input: nums = [1,3,5,6], target = 5
Output: 2

Example 2:
Input: nums = [1,3,5,6], target = 2
Output: 1

Example 3:
Input: nums = [1,3,5,6], target = 7
Output: 4

Example 4:
Input: nums = [1,3,5,6], target = 0
Output: 0
===============================================================
*/


/*
===============================================================
Approach: Binary Search
---------------------------------------------------------------
💡 Idea:
- Since nums is sorted (and distinct), binary search works.
- If nums[mid] == target ⇒ return mid.
- If target < nums[mid] ⇒ move left (high = mid-1).
- If target > nums[mid] ⇒ move right (low = mid+1).
- If target not found, "low" will be positioned at the correct 
  insertion index.

🧩 Algorithm:
1. Initialize low=0, high=n-1
2. While low <= high:
   - mid = (low+high)/2
   - If nums[mid]==target → return mid
   - If target < nums[mid] → high=mid-1
   - Else → low=mid+1
3. Return low (insertion point)

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(1)
===============================================================
*/
int searchInsert(vector<int>& nums, int target) {
    int low = 0, high = nums.size()-1;
    while (low <= high) {
        int mid = low + (high-low)/2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target) high = mid-1;
        else low = mid+1;
    }
    return low; // insertion index
}


/*
===============================================================
Example Usage / Testing
===============================================================
*/
int main() {
    vector<int> nums = {1, 3, 5, 6};

    cout << "Target=5 → " << searchInsert(nums, 5) << endl; // Expected 2
    cout << "Target=2 → " << searchInsert(nums, 2) << endl; // Expected 1
    cout << "Target=7 → " << searchInsert(nums, 7) << endl; // Expected 4
    cout << "Target=0 → " << searchInsert(nums, 0) << endl; // Expected 0

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    - Brute Force (linear scan):
       Iterate and return first index ≥ target.
       • Time: O(n), Space: O(1)

    - Binary Search (Optimal):
       Perform binary search and return correct index.
       • Time: O(log n), Space: O(1)

    🔑 Conclusion:
    - Interviewers expect **binary search** solution.
    - Robust and handles "not found" by returning insertion point.
    ===========================================================
    */

    return 0;
}
