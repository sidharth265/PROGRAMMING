#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Quick Sort
 Problem Link: (Common Sorting Algorithm)
====================================================

📝 Problem Statement:
Given an array of integers, sort the array in non-decreasing order using Quick Sort algorithm.
Quick Sort uses a pivot to partition the array into two halves and recursively sorts them.

📌 Input:
- Vector of integers `arr`

📌 Output:
- Sorted vector in-place

----------------------------------------------------
🔹 Example:
Input: arr = [10, 7, 8, 9, 1, 5]  
Output: [1, 5, 7, 8, 9, 10]

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Quick Sort (In-place Partitioning)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Choose a pivot element (here, the first element).
- Partition the array such that elements less than pivot come before it, others after.
- Recursively apply quicksort on sub-arrays.

🧩 Algorithm:
1. If low >= high, return.
2. Partition: 
   - Initialize i = low, j = high.
   - Move i right while arr[i] < pivot.
   - Move j left while arr[j] >= pivot.
   - Swap arr[i] and arr[j] if i < j.
   - Swap pivot with arr[j].
3. Recursively quickSort low to j and j+1 to high.

⏱ Time Complexity:
- Best/Average: O(n log n)
- Worst: O(n^2) (bad pivot choices)

📦 Space Complexity: O(log n) recursion stack  
Stable: No (may reorder equal elements)
In-place: Yes
*/

int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[low];
    int i = low, j = high;
    while (i < j) {
        while (i < high && arr[i] < pivot) i++;
        while (j > low && arr[j] >= pivot) j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void quickSort(vector<int> &arr, int low, int high) {
    if (low >= high) return;
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi);
    quickSort(arr, pi + 1, high);
}

void printArray(const vector<int> &arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

//////////////////////////////////////////////////////
// Main function with example test
//////////////////////////////////////////////////////
int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    cout << "Original array: ";
    printArray(arr);

    quickSort(arr, 0, (int)arr.size() - 1);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Quick Sort is efficient and in-place but not stable.
// Performance depends on pivot selection; can degrade to O(n^2).
