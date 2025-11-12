#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Lower Bound in a Sorted Array

Problem Statement:
Given a sorted array arr (non-decreasing) and an integer target, return the index of the first element
that is greater than or equal to target (the “lower bound”). If all elements are smaller than target,
return n (the array size).

Example:
Input:  arr = [1, 2, 4, 5, 6], target = 3
Output: 2
Explanation: The first element >= 3 is 4 at index 2.

Approach Overview:
- Brute Force: Scan from left to right, return the first index i with arr[i] >= target.
- Optimized (Binary Search): Find the smallest index i such that arr[i] >= target by shrinking search space accordingly.
*/

/*
Approach: Brute Force
Approach Idea:
- Linearly traverse and return the first position where arr[i] >= target.
- If not found, return n.

Algorithm:
1) For i in [0..n-1]:
   - If arr[i] >= target: return i
2) Return n

Time Complexity: O(n)
Space Complexity: O(1)
*/
int lowerBound_linear(const vector<int>& arr, int target) {
    int n = (int)arr.size();
    for (int i = 0; i < n; i++) {
        if (arr[i] >= target) return i;
    }
    return n;
}

/*
Approach: Binary Search (Lower Bound)
Approach Idea:
- Maintain an invariant: the answer is in [low..high].
- If arr[mid] >= target, mid could be the answer; move high = mid - 1.
- Else, move low = mid + 1.
- After the loop, low is the first index with arr[low] >= target (or n if none).

Algorithm:
1) low = 0, high = n-1
2) While low <= high:
   - mid = low + (high - low)/2
   - If arr[mid] >= target: high = mid - 1
   - Else: low = mid + 1
3) Return low

Time Complexity: O(log n)
Space Complexity: O(1)
*/
int lowerBound_bs(const vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low)/2; // prevent overflow
        if (arr[mid] >= target) {
            high = mid - 1; // mid could be the answer; search left
        } else {
            low = mid + 1;  // need a larger value; search right
        }
    }
    return low; // first index with arr[index] >= target (or n if none)
}

int main() {
    vector<int> arr = {1, 2, 4, 5, 6};
    int target = 3;

    cout << "Brute force lower bound index:  " << lowerBound_linear(arr, target) << "\n";
    cout << "Binary search lower bound index: " << lowerBound_bs(arr, target) << "\n";
    return 0;
}
