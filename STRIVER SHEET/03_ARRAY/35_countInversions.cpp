#include <bits/stdc++.h>
using namespace std;

/*
Problem: Count Inversions in an Array

Problem Statement:
Given an array of integers arr, count the number of inversions in the array. An inversion is a pair of indices (i, j) such that i < j and arr[i] > arr[j].

Example:
Input:
  arr = [1, 20, 6, 4, 5]
Output:
  5
Explanation:
- The inversions are: (20,6), (20,4), (20,5), (6,4), (6,5).

Approach Overview:
- Brute Force: Check every pair (i, j) with i<j and count if arr[i] > arr[j].
- Optimal (Merge Sort Count): Use a modified merge sort; while merging, when an element from the right half is placed before an element from the left half, it contributes inversions equal to remaining elements in the left half.

Complexity Overview:
- Brute Force: Time O(n^2), Space O(1).
- Merge Sort Count: Time O(n log n), Space O(n) (auxiliary arrays).
*/

/*
Approach 1: Brute Force Enumeration

Idea:
- Compare all pairs (i, j) with i<j and increment count when arr[i] > arr[j].

Algorithm:
1) Initialize count = 0.
2) For i in [0..n-2]:
     For j in [i+1..n-1]:
       - If arr[i] > arr[j], count++.
3) Return count.

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
int inversionCount(vector<int> &arr) {
    int n = arr.size();
    int count = 0;
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (arr[i] > arr[j]) count ++;
        }
    }
    return count;
}

/*
Approach 2: Merge Sort Based Counting (Optimal)

Idea:
- During merge of two sorted halves [low..mid] and [mid+1..high], if arr1[i] > arr2[j], then all remaining elements in arr1 from i..n1-1 are inversions with arr2[j], because both halves are sorted.

Algorithm:
1) Recursively split the array (merge sort).
2) While merging:
   - Maintain two temporary arrays arr1 (left half) and arr2 (right half).
   - If arr1[i] <= arr2[j], place arr1[i] into original and i++.
   - Else (arr1[i] > arr2[j]): place arr2[j], increment count by (n1 - i), and j++.
3) Sum counts from all merges and return.

Time Complexity: O(n log n)
Space Complexity: O(n) for temporary arrays
- Stable: Yes
- In-place: No (uses auxiliary arrays)
*/
void merge(vector<int> &arr, int low, int mid, int high, int &count) {
    vector<int> arr1 (arr.begin()+low, arr.begin()+mid+1);
    vector<int> arr2 (arr.begin()+mid+1, arr.begin()+high+1);
    int i=0, j=0, k=low;
    int n1 = arr1.size(), n2 = arr2.size();
    while(i<n1 && j<n2) {
        if (arr1[i] > arr2[j]) {
            count += n1-i;
            arr[k++] = arr2[j++];
        }
        else {
            arr[k++] = arr1[i++];
        }
    }
    while (i<n1) arr[k++] = arr1[i++];
    while (j<n2) arr[k++] = arr2[j++];
}

void sort (vector<int> &arr, int low, int high, int &count) {
    if (low == high) return;
    int mid = low + (high - low)/2;
    sort(arr, low, mid, count);
    sort(arr, mid+1, high, count);
    merge(arr, low, mid, high, count);
}

int inversionCount2(vector<int> &arr) {
    int n = arr.size();
    int count = 0;
    sort(arr, 0, n-1, count);
    return count;
}

// Example usage
int main() {
    vector<int> arr = {1, 20, 6, 4, 5};
    cout << "Number of inversions (Brute Force): " << inversionCount(arr) << endl;
    cout << "Number of inversions (Merge Sort): " << inversionCount2(arr) << endl;
    return 0;
}
