#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Bubble Sort
 Problem Link: (Common Sorting Algorithm)
====================================================

📝 Problem Statement:
Given an array of integers, sort the array in non-decreasing order using Bubble Sort algorithm.
Bubble Sort repeatedly swaps adjacent elements if they are in wrong order,
bubbling the largest elements to the end with each pass.

📌 Input:
- Vector of integers `arr`

📌 Output:
- Sorted vector in-place

----------------------------------------------------
🔹 Example:
Input: arr = [64, 34, 25, 12, 22, 11, 90]
Output: [11, 12, 22, 25, 34, 64, 90]

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Classic Bubble Sort
//////////////////////////////////////////////////////
/*
💡 Idea:
- Repeatedly pass through the array.
- Swap adjacent elements if out of order.
- Stop early if no swaps done for a pass (array is sorted).

🧩 Algorithm:
1. For i from n-1 down to 0:
   a. Initialize swapped = false.
   b. For j from 0 to i-1:
      - If arr[j] > arr[j+1], swap and mark swapped true.
   c. If swapped is false after inner loop, break early.
2. Array is sorted in-place.

⏱ Time Complexity:
- Best case: O(n) (already sorted array, no swaps)
- Average/Worst case: O(n^2)

📦 Space Complexity: O(1) (in-place sorting)
Stable: Yes (preserves relative order of equal elements)
*/

void bubbleSort(vector<int> &arr) {
    int n = (int)arr.size();
    for (int i = n - 1; i >= 0; i--) {
        bool swapped = false; // Flag to check if any swap occurred in this pass
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no swaps occurred, array is sorted
        if (!swapped) break;
    }
}

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    bubbleSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Bubble sort is a simple, stable, in-place sorting algorithm.
// Best for small arrays or nearly sorted data due to early exit optimization.
// Time complexity is quadratic in worst case.
