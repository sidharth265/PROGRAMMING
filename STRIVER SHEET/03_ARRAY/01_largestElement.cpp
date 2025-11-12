#include <bits/stdc++.h>
using namespace std;

/*
Problem: Largest Element in an Array

Problem Statement:
Given an array of integers, find and return the largest element present in the array.

Example:
Input:
  arr = [1, 2, 3, 4, 5]
Output:
  5
Explanation:
- The maximum value among all elements is 5.

Approach:
- Initialize the answer with the first element of the array.
- Iterate through the array from index 1 to n-1.
- For each element, update the answer as the maximum of the current answer and the element.

Algorithm:
1) Set ans = arr[0].
2) For i from 1 to n-1:
     ans = max(ans, arr[i]).
3) Return ans.

Time Complexity:
- O(n), where n is the size of the array (single linear scan).

Space Complexity:
- O(1), using constant extra space.
*/

int largestElement(vector<int> &arr, int n) {
    int ans = arr[0];
    for (int i = 1; i < n; i++) {
        ans = max(ans, arr[i]);
    }
    return ans;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int n = arr.size();
    int result = largestElement(arr, n);
    cout << "Largest element: " << result << endl;
    return 0;
}
