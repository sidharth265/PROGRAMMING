#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Selection Sort
 Problem Link: (Common Sorting Algorithm)
====================================================

📝 Problem Statement:
Given an array of integers, sort the array in non-decreasing order using Selection Sort algorithm.
Selection Sort divides the list into sorted and unsorted parts, repeatedly selecting the smallest element 
from the unsorted section and swapping it with the first unsorted element.

📌 Input:
- Vector of integers `arr`
- Integer `n` size of array

📌 Output:
- Sorted vector in-place

----------------------------------------------------
🔹 Example:
Input: arr = [64, 25, 12, 22, 11]
Output: [11, 12, 22, 25, 64]

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Selection Sort
//////////////////////////////////////////////////////
/*
💡 Idea:
- For each position i, find the minimum element in the unsorted remainder of the array.
- Swap it with element at position i.
- Repeat until whole array sorted.

🧩 Algorithm:
1. For i from 0 to n-2:
   a. Initialize minIndex = i.
   b. For j from i+1 to n-1:
       - If arr[j] < arr[minIndex], update minIndex = j.
   c. Swap arr[i] and arr[minIndex].

⏱ Time Complexity: O(n^2) in all cases  
📦 Space Complexity: O(1) (in-place)  
Stable: No, because swapping can disrupt relative order of equal elements
*/

void selectionSort(vector<int> &arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i; // Track the index of minimum element
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    int n = (int)arr.size();

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    selectionSort(arr, n);

    cout << "Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Selection Sort is simple and in-place but inefficient for large data.
// Time complexity is always quadratic; it is not stable.
