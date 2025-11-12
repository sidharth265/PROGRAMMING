#include<bits/stdc++.h>
using namespace std;

/*
Problem: Move Zeroes to the End (Stable order of non-zero elements)

Problem Statement:
Given an integer array nums, move all 0’s to the end of the array while maintaining the relative order of the non-zero elements. Do this in-place without making a copy of the array.

Example:
Input:
  nums = [0, 1, 0, 3, 12]
Output:
  [1, 3, 12, 0, 0]
Explanation:
- All non-zero elements keep their relative order; zeroes are shifted to the end.

Approach Overview:
- Compact-and-Fill (Stable): Write non-zero elements forward, then fill the remainder with 0.
- Two-Pointer Swap: Find the first 0 position and swap in non-zero elements encountered afterward.

Complexity Overview:
- Both approaches run in O(n) time and O(1) extra space.
*/

/*
Approach 1: Compact-and-Fill (Stable)

Idea:
- Use an index j to write the next non-zero.
- First pass: copy each non-zero nums[i] to nums[j++].
- Second pass: fill the remaining positions from j..n-1 with 0.

Algorithm:
1) j = 0
2) For i in [0..n-1]:
     if nums[i] != 0: nums[j++] = nums[i]
3) For i in [j..n-1]: nums[i] = 0

Time Complexity: O(n)
Space Complexity: O(1)
*/
void moveZerosToEnd(vector<int>& nums) {
    int n = nums.size();
    int j = 0; // next write position for non-zero
    for (int i = 0; i < n; i++) {
        if (nums[i] != 0) {
            nums[j] = nums[i];
            j++;
        }
    }
    for (int i = j; i < n; i++) {
        nums[i] = 0;
    }
}

/*
Approach 2: Two-Pointer Swap

Idea:
- Locate the first zero at index j.
- Scan forward with i; when a non-zero is found at i, swap it with position j and advance j.
- Maintains relative order among non-zero elements because each non-zero is moved to the earliest available zero slot in sequence.

Algorithm:
1) j = first index where nums[j] == 0 (or n if none)
2) For i from j+1 to n-1:
     if nums[i] != 0: swap(nums[j], nums[i]); j++
3) End

Time Complexity: O(n)
Space Complexity: O(1)
*/
void moveZeroesToEnd2(vector<int>& nums) {
    int n = nums.size();
    int j=0;
    while (j<n && nums[j] != 0) {
        j++;
    }
    int i = j+1;
    while (i<n) {
        if (nums[i] != 0) {
            swap(nums[j++], nums[i]);
        }
        i++;
    }
}

int main() {
    vector<int> nums = {0, 1, 0, 3, 12};
    moveZerosToEnd(nums);
    for (int num : nums) cout << num << " ";
    cout << "\n";

    vector<int> nums2 = {0, 1, 0, 3, 12};
    moveZeroesToEnd2(nums2);
    for (int num : nums2) cout << num << " ";
    cout << "\n";
    
    return 0;
}
