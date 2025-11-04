#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Find Ceil of an Element in a Sorted Array

Problem Statement:
Given a sorted array arr (non-decreasing) and an integer x, find the index of the smallest element
that is greater than or equal to x (the ceil). If such an element does not exist, return -1.

Example:
Input:
  arr = [1, 2, 8, 10, 10, 12], x = 5
Output:
  Ceil index = 2 (value = 8)

Approach Overview:
- Use binary search to locate the first index i such that arr[i] >= x.
- Maintain the invariant that the answer lies in [low..high], and shrink the range accordingly.
- When the loop ends, low is the first index with arr[low] >= x (if low is within bounds).
*/

/*
Approach: Lower Bound via Binary Search
Approach Idea:
- If arr[mid] >= x, the ceil could be at mid or to the left, so move high = mid - 1.
- Otherwise, move low = mid + 1.
- After the loop, low is the first index with arr[low] >= x, if low < n.

Algorithm:
1) low=0, high=n-1
2) While low <= high:
   - mid = low + (high-low)/2
   - If arr[mid] >= x: high = mid - 1
   - Else: low = mid + 1
3) If low == n: return -1
   Else return low

Time Complexity: O(log n)
Space Complexity: O(1)
*/
int findCeil(vector<int>& arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (arr[mid] >= x) high = mid - 1;
        else low = mid + 1;
    }
    return (low == n) ? -1 : low;
}

int main() {
    vector<int> arr = {1, 2, 8, 10, 10, 12};
    int x = 5;
    int idx = findCeil(arr, x);
    if (idx != -1) {
        cout << "Ceil of " << x << " is: " << arr[idx] << " at index " << idx << "\n";
    } else {
        cout << "No ceil found for " << x << "\n";
    }
    return 0;
}
