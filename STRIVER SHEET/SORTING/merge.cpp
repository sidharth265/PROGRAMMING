#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Merge Sort
 Problem Link: (Common Sorting Algorithm)
====================================================

📝 Problem Statement:
Given an array of integers, sort the array in non-decreasing order using the Merge Sort algorithm.
Merge Sort is a divide-and-conquer algorithm that divides the array into halves, sorts them recursively,
and then merges the sorted halves.

📌 Input:
- A vector of integers `arr`

📌 Output:
- The vector sorted in-place (though using auxiliary space)

----------------------------------------------------
🔹 Example:
Input: arr = [38, 27, 43, 3, 9, 82, 10]  
Output: [3, 9, 10, 27, 38, 43, 82]

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Merge Sort (Divide and Conquer)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Recursively split array into halves until single elements.
- Merge sorted halves back in sorted order.
- Merging requires temporary arrays.

🧩 Algorithm:
1. If left < right:
   a. Calculate mid = left + (right - left) / 2
   b. Recursively mergeSort left half (left, mid)
   c. Recursively mergeSort right half (mid+1, right)
   d. Merge left and right sorted halves

2. Merge(left, mid, right):
   a. Copy left and right halves to temporary arrays.
   b. Merge elements in sorted order to original array.

⏱ Time Complexity: O(n log n)  
📦 Space Complexity: O(n) due to auxiliary arrays
Stable: Yes (preserves order of equal elements)
Not in-place due to extra space usage
*/

void merge(vector<int> &arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    int ll = mid - left + 1, rl = right - mid;

    while (i < ll && j < rl) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < ll) arr[k++] = leftArr[i++];
    while (j < rl) arr[k++] = rightArr[j++];
}

void mergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void printArray(const vector<int> &arr) {
    for (int num : arr) cout << num << " ";
    cout << endl;
}

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    cout << "Original array: ";
    printArray(arr);

    mergeSort(arr, 0, (int)arr.size() - 1);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Merge sort efficiently sorts arrays in O(n log n) time,
// is stable, but requires O(n) extra space due to merging step.
