#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Check if an array is sorted and rotated

Problem Statement:
Given an integer array nums, determine whether it is a rotation of a non-decreasing sorted array.
Formally, nums is "sorted and rotated" if there exists an index k such that rotating a sorted
(non-decreasing) array by k positions yields nums. Arrays of size 0 or 1 are considered true.

Examples:
- [3,4,5,1,2] -> true  (sorted [1,2,3,4,5] rotated by 3)
- [1,2,3,4,5] -> true  (0 rotations)
- [2,1,3,4]   -> false (order breaks more than once)

Approach Overview:
- Approach 1 (Explicit Pivot Check): Find first drop (nums[i] > nums[i+1]); treat next index as pivot.
  Verify non-decreasing order from pivot to end, then from start to pivot-1, ensuring wrap-around consistency.
- Approach 2 (Count Drops — Recommended): Count positions i where nums[i] > nums[(i+1)%n].
  For a sorted-and-rotated or already sorted array, this count is at most 1.

----------------------------------------
Approach: Explicit Pivot Check
Approach Idea:
- Locate the first index where order decreases; that position + 1 is the rotation pivot.
- Confirm non-decreasing order in the two parts: [pivot..n-1] and [0..pivot-1],
  ensuring the last element of the first part is >= the first element of the second part.

Algorithm:
1) If n <= 1: return true.
2) Find first i in [0..n-2] with nums[i] > nums[i+1]; if none, return true.
   - Let pivot = i+1.
3) Verify non-decreasing in [pivot..n-1]; if any nums[j] < nums[j-1], return false.
4) Verify non-decreasing in [0..pivot-1]; if any nums[j] < nums[j-1], return false.
5) Ensure wrap-around: nums[0] >= nums[n-1] (implicitly checked by steps above via sequence continuity).
6) Return true.

Time Complexity: O(n)
Space Complexity: O(1)
*/
bool isSortedAndRotated(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return true;

    int pivot = -1;
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] > nums[i + 1]) {
            pivot = i + 1;
            break;
        }
    }
    if (pivot == -1) return true; // already non-decreasing

    // Check non-decreasing from pivot to end
    for (int i = pivot + 1; i < n; i++) {
        if (nums[i] < nums[i - 1]) return false;
    }
    // Check non-decreasing from start to pivot-1
    for (int i = 1; i < pivot; i++) {
        if (nums[i] < nums[i - 1]) return false;
    }
    // Additionally ensure the wrap-around ordering: last of first segment <= first of second segment,
    // which in this construction means nums[n-1] <= nums[0] must hold.
    if (nums[n - 1] > nums[0]) return false;

    return true;
}

/*
----------------------------------------
Approach: Count Drops (Recommended Concise Method)
Approach Idea:
- Traverse circularly and count how many times the sequence decreases:
  positions i where nums[i] > nums[(i+1)%n].
- For a non-decreasing sorted array (possibly rotated), there can be at most one such decrease.

Algorithm:
1) If n <= 1: return true.
2) Set count = 0.
3) For i in [0..n-1]:
   - If nums[i] > nums[(i+1) % n], count++.
4) Return (count <= 1).

Time Complexity: O(n)
Space Complexity: O(1)
*/
bool isSortedAndRotated2(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return true;

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > nums[(i + 1) % n]) count++;
    }
    return count <= 1;
}

int main() {
    vector<int> nums = {3, 4, 5, 1, 2};

    cout << (isSortedAndRotated(nums)
                 ? "The array is sorted and rotated."
                 : "The array is not sorted and rotated.")
         << "\n";

    // Alternative concise check:
    // cout << (isSortedAndRotated2(nums)
    //              ? "The array is sorted and rotated."
    //              : "The array is not sorted and rotated.")
    //      << "\n";

    return 0;
}
