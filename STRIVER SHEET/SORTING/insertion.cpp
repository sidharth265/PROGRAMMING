#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Insertion Sort
 Problem Link: (Common Sorting Algorithm)
====================================================

📝 Problem Statement:
Given an array of integers, sort the array in non-decreasing order using Insertion Sort algorithm.
Insertion sort builds the sorted array one element at a time by inserting each element into its correct position.

📌 Input:
- An array of integers `arr` of size n

📌 Output:
- The array sorted in-place

----------------------------------------------------
🔹 Example:
Input: arr = [12, 11, 13, 5, 6]
Output: [5, 6, 11, 12, 13]

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Classic Insertion Sort
//////////////////////////////////////////////////////
/*
💡 Idea:
- Iterate from the second element to the end.
- For each element, insert it in the correct position among the previously sorted elements.
- Shift elements to the right if they are greater than the key.

🧩 Algorithm:
1. For i from 1 to n-1:
   a. key = arr[i]
   b. j = i - 1
   c. While j >= 0 and arr[j] > key:
       - Shift arr[j] to arr[j+1]
       - Decrement j
   d. Insert key at arr[j+1]

⏱ Time Complexity:
- Best case: O(n) when array is already sorted
- Average and Worst case: O(n^2)

📦 Space Complexity: O(1) in-place sorting
Stable: Yes (preserves relative order of equal elements)
*/

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    insertionSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Insertion sort is simple and stable.
// Efficient for small or nearly sorted arrays.
// Time complexity is quadratic in the average or worst case.
