#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Single Element in a Sorted Array
---------------------------------------------------------------
Link: https://leetcode.com/problems/single-element-in-a-sorted-array/

You are given a sorted array `nums` consisting of pairs of elements, 
except for **one single element** that appears only once.  

Find that single element in O(log n) time and O(1) space.

---------------------------------------------------------------
Example 1:
Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Example 2:
Input: nums = [3,3,7,7,10,11,11]
Output: 10
===============================================================
*/


/*
===============================================================
Approach: Binary Search on Index Parity
---------------------------------------------------------------
💡 Observations:
- Sorted array with pairs ⇒ elements come in (a,a), (b,b),...
- Single element disrupts this pairing.
- Left side of single element:
   * first occurrence = **even index**
   * second occurrence = **odd index**
- Right side of single element:
   * first occurrence = **odd index**
   * second occurrence = **even index**

🧩 Algorithm:
1. Initialize low=0, high=n-1.
2. While low<high:
   - mid = (low+high)/2
   - Make mid even (so we always check pairs properly).
   - If nums[mid] == nums[mid+1], then single is to the right → low=mid+2
   - Else → single must be at mid or left → high=mid
3. Return nums[low].

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(1)
===============================================================
*/
int singleNonDuplicate(vector<int>& nums) {
    int low = 0, high = nums.size()-1;
    while (low < high) {
        int mid = low + (high-low)/2;
        // force mid to be even
        if (mid % 2 == 1) mid--;

        if (nums[mid] == nums[mid+1]) {
            // pair is perfect, move right
            low = mid + 2;
        } else {
            // mismatch, single must be at mid or left
            high = mid;
        }
    }
    return nums[low];  // low points to single element
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> nums1 = {1,1,2,2,3,3,4,4,5};
    cout << "Single element: " << singleNonDuplicate(nums1) << endl; // Expected 5

    vector<int> nums2 = {3,3,7,7,10,11,11};
    cout << "Single element: " << singleNonDuplicate(nums2) << endl; // Expected 10

    vector<int> nums3 = {0,1,1,2,2,3,3};
    cout << "Single element: " << singleNonDuplicate(nums3) << endl; // Expected 0

    vector<int> nums4 = {1};
    cout << "Single element: " << singleNonDuplicate(nums4) << endl; // Expected 1

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - XOR all elements → result is single.
       - Time: O(n), Space: O(1).
       - Works! But not O(log n).

    2. Binary Search on pairs (Optimal):
       - Use index parity + pair matching.
       - Time: O(log n), Space: O(1).
       - 🏆 Expected solution in interviews.
    ===========================================================
    */

    return 0;
}
