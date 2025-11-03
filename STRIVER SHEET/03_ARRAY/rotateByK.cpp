#include<bits/stdc++.h>
using namespace std;

/*
Problem: Rotate Array by k Positions

Problem Statement:
Given an array arr and an integer k, rotate the array to the right by k steps. Rotation means each element is shifted to the right by one position, and the last element moves to the first position.

Example:
Input:
  arr = [1, 2, 3, 4, 5, 6, 7], k = 3
Output:
  [5, 6, 7, 1, 2, 3, 4]
Explanation:
- After 1 step: [7, 1, 2, 3, 4, 5, 6]
- After 2 steps: [6, 7, 1, 2, 3, 4, 5]
- After 3 steps: [5, 6, 7, 1, 2, 3, 4]

Approach Overview:
- Temp Array (O(n) space): Place each element at its rotated index using a temporary buffer, then copy back.
- Reverse Method (In-place O(1) space, recommended):
  1) Reverse the first n-k elements.
  2) Reverse the last k elements.
  3) Reverse the whole array.
This yields the array rotated right by k.
*/

/*
Approach 1: Temporary Array (Stable and Simple)

Idea:
- Compute new index for each element: newIndex = (i + k) % n, store in temp, then copy back.

Algorithm:
1) n = arr.size(), k = k % n
2) temp of size n
3) For i in [0..n-1]: temp[(i + k) % n] = arr[i]
4) Copy temp back into arr

Time Complexity: O(n)
Space Complexity: O(n)
*/
void rotate(vector<int>& arr, int k) {
    int n = arr.size();
    k = k % n; // Handle cases where k >= n
    vector<int> temp(n);
    for (int i = 0; i < n; i++) {
        temp[(i + k) % n] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

/*
Approach 2: In-place Reversal (Recommended)

Idea:
- Right rotation by k can be achieved by:
  - Reverse the prefix [0, n-k-1]
  - Reverse the suffix [n-k, n-1]
  - Reverse the entire array
- This places elements in their rotated positions in-place.

Algorithm:
1) k = k % n
2) reverse(nums.begin(), nums.end() - k)
3) reverse(nums.end() - k, nums.end())
4) reverse(nums.begin(), nums.end())

Time Complexity: O(n)
Space Complexity: O(1)
*/
void rotate2(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    reverse(nums.begin(), nums.end() - k);
    reverse(nums.end() - k, nums.end());
    reverse(nums.begin(), nums.end());
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;

    // Choose approach:
    // rotate(arr, k);   // Temp array
    rotate2(arr, k);     // In-place reversal

    cout << "Rotated array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}
