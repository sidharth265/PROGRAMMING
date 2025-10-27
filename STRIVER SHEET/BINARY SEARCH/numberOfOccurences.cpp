#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Count Occurrences in a Sorted Array
---------------------------------------------------------------
Given a sorted array of integers and a target value,
find the number of times the target occurs in the array.

---------------------------------------------------------------
Example:
Input: arr = [1,2,2,2,3,4,5], target = 2
Output: 3
Explanation: The target "2" appears 3 times.
===============================================================
*/


/*
===============================================================
Approach: Binary Search
---------------------------------------------------------------
💡 Idea:
- Use binary search to find:
  1. The index of the **first occurrence** of target.
  2. The index of the **last occurrence** of target.
- Count = (last - first + 1).

🧩 Algorithm:
1. Binary search (modified) to find the first occurrence.
2. Binary search (modified) to find the last occurrence.
3. If not found → return 0.
4. Else return (last - first + 1).

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(1)
===============================================================
*/
int countFreq(vector<int>& arr, int target) {
    int n = arr.size();
    int first = -1, last = -1;

    // Find first occurrence
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (arr[mid] == target) {
            first = mid;
            high = mid - 1; // keep searching left half
        }
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }

    // If not found at all
    if (first == -1) return 0;

    // Find last occurrence
    low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (arr[mid] == target) {
            last = mid;
            low = mid + 1; // keep searching right half
        }
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }

    return (last - first + 1);
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> arr = {1, 2, 2, 2, 3, 4, 5};
    int target = 2;
    cout << "Occurrences of " << target << ": " 
         << countFreq(arr, target) << endl; // Expected: 3

    target = 1;
    cout << "Occurrences of " << target << ": " 
         << countFreq(arr, target) << endl; // Expected: 1

    target = 5;
    cout << "Occurrences of " << target << ": " 
         << countFreq(arr, target) << endl; // Expected: 1

    target = 6;
    cout << "Occurrences of " << target << ": " 
         << countFreq(arr, target) << endl; // Expected: 0

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    - Linear scan: O(n), simple but slow.
    - Binary search:
       - Find first and last occurrence in O(log n).
       - Return (last-first+1).
       - Time: O(log n), Space: O(1)
    ===========================================================
    */
    return 0;
}
