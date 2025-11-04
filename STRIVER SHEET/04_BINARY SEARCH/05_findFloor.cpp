#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Find Floor of an Element in a Sorted Array

Problem Statement:
Given a sorted array arr (non-decreasing) and an integer x, return the index of the largest element
that is less than or equal to x (the floor). If such an element does not exist, return -1.

Example:
Input:
  arr = [1, 2, 8, 10, 10, 12], x = 5
Output:
  Floor index = 1 (value = 2)

Approach Overview:
- Use binary search to locate the last index i such that arr[i] <= x.
- Maintain a candidate answer; when arr[mid] <= x, move right to find a larger valid value.
*/

/*
Approach: Binary Search for Floor
Approach Idea:
- If arr[mid] <= x, mid is a valid floor candidate; move low = mid + 1 to try to find a larger one.
- If arr[mid] > x, move high = mid - 1 to discard larger elements.
- Track the best index seen so far.

Algorithm:
1) low=0, high=n-1, ans=-1
2) While low <= high:
   - mid = low + (high-low)/2
   - If arr[mid] <= x: ans = mid; low = mid + 1
   - Else: high = mid - 1
3) Return ans

Time Complexity: O(log n)
Space Complexity: O(1)
*/
int findFloor(vector<int>& arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (arr[mid] <= x) {
            ans = mid;          // candidate floor
            low = mid + 1;      // try to find a larger <= x
        } else {
            high = mid - 1;     // discard right half
        }
    }
    return ans;
}

int main() {
    vector<int> arr = {1, 2, 8, 10, 10, 12};
    int x = 5;
    int idx = findFloor(arr, x);
    if (idx != -1) {
        cout << "Floor of " << x << " is: " << arr[idx] << " at index " << idx << "\n";
    } else {
        cout << "No floor found for " << x << "\n";
    }
    return 0;
}
