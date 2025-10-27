#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Binary Search in a Sorted Array

Problem Statement:
Given a sorted array nums (non-decreasing order) and an integer target, return the index of target if it exists;
otherwise, return -1. The search must run in O(log n) time.

Example:
Input:
  nums = [1, 2, 3, 4, 5], target = 3
Output:
  2

Approach Overview:
- Use binary search to repeatedly halve the search interval.
- Compare target with middle element:
  - If target < nums[mid], discard right half (move high).
  - If target > nums[mid], discard left half (move low).
  - Else, found at mid.

----------------------------------------
Approach: Iterative Binary Search
Approach Idea:
- Maintain two pointers low and high delimiting the current search range.
- Compute mid = low + (high - low)/2 to avoid overflow.
- Narrow the range based on comparisons until low > high.

Algorithm:
1) low = 0, high = n-1
2) While low <= high:
   - mid = low + (high - low)/2
   - If nums[mid] == target: return mid
   - Else if nums[mid] < target: low = mid + 1
   - Else: high = mid - 1
3) Return -1

Time Complexity: O(log n)
Space Complexity: O(0) extra
*/
int search(vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    int target = 3;
    int result = search(nums, target);
    if (result != -1) {
        cout << "Element found at index: " << result << "\n";
    } else {
        cout << "Element not found\n";
    }
    return 0;
}
