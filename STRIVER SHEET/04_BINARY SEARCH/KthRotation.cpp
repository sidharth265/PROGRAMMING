#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Find Number of Rotations in a Sorted and Rotated Array

Problem Statement:
Given a sorted array that has been rotated an unknown number of times, return the index of the minimum element.
This index equals the number of rotations. The array is assumed to have distinct elements.

Example:
Input:  arr = [4, 5, 6, 7, 0, 1, 2]
Output: 4
Explanation: Minimum element 0 is at index 4, so the array was rotated 4 times.

Approach Overview:
- Use a modified binary search to locate the minimum (pivot).
- Compare middle element with the rightmost element to decide which half contains the pivot.

----------------------------------------
Approach: Modified Binary Search (Pivot at minimum)
Approach Idea:
- If arr[mid] > arr[high], the minimum lies to the right of mid → low = mid + 1.
- Else, the minimum lies at mid or to its left → high = mid.
- Loop until low == high; that index is the minimum (rotation count).

Algorithm:
1) low = 0, high = n - 1
2) While low < high:
   - mid = low + (high - low)/2
   - If arr[mid] > arr[high]: low = mid + 1
   - Else: high = mid
3) Return low

Time Complexity: O(log n)
Space Complexity: O(1)
*/
int findKRotation(vector<int> &arr) {
    int low = 0, high = (int)arr.size() - 1;
    while (low < high) {
        int mid = low + (high - low)/2;
        if (arr[mid] > arr[high]) low = mid + 1;
        else high = mid;
    }
    return low;
}

int main() {
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};
    int k = findKRotation(arr);
    cout << "The array is rotated " << k << " times.\n";
    return 0;
}
