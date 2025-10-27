#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Find Peak Element
Link: https://leetcode.com/problems/find-peak-element/

A peak element is one that is strictly greater than its neighbors.
Return the index of any peak.

Constraints:
- nums[i] != nums[i+1]
- At least one peak always exists.

---------------------------------------------------------------
Example 1:
Input: nums = [1,2,3,1]
Output: 2   (nums[2] = 3)

Example 2:
Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5 (nums[1]=2 or nums=6 are valid peaks)
===============================================================
*/


/*
===============================================================
Approach: Binary Search
---------------------------------------------------------------
💡 Key Idea:
- If nums[mid] < nums[mid+1] 👉 there must be a peak on the right.
- Else 👉 there must be a peak on the left or at mid.

🧩 Algorithm:
1. Initialize left=0, right=n-1.
2. While left < right:
   - mid = (left+right)/2
   - If nums[mid] < nums[mid+1] → left = mid+1
   - Else → right = mid
3. At the end, left == right = index of a peak.

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(1)
===============================================================
*/
int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    int left = 0, right = n-1;

    while (left < right) {
        int mid = left + (right - left)/2;
        if (nums[mid] < nums[mid+1]) {
            // Peak must be in right half
            left = mid+1;
        } else {
            // Peak is in left half or at mid
            right = mid;
        }
    }
    return left; // or right, both same
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> arr1 = {1, 2, 3, 1};
    cout << "Peak index: " << findPeakElement(arr1) << endl; // Expected 2

    vector<int> arr2 = {1, 2, 1, 3, 5, 6, 4};
    cout << "Peak index: " << findPeakElement(arr2) << endl; // Expected 1 or 5

    vector<int> arr3 = {10}; // Single element
    cout << "Peak index: " << findPeakElement(arr3) << endl; // Expected 0

    vector<int> arr4 = {1, 2}; // Two elements
    cout << "Peak index: " << findPeakElement(arr4) << endl; // Expected 1 (larger is peak)

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Linear Scan:
       - Check neighbors, find peak directly.
       - Time: O(n)

    2. Binary Search (Optimal):
       - Use slope property (if rising, peak on right; if falling, peak on left).
       - Time: O(log n)
       - Space: O(1)
    ===========================================================
    */
    return 0;
}
