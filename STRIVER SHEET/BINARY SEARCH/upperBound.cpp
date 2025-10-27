#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Upper Bound in a Sorted Array
---------------------------------------------------------------
Link: https://www.geeksforgeeks.org/problems/upper-bound-in-a-sorted-array/1

📌 Problem Statement:
Given a **sorted array** `arr` of size `n` and a `target` value,  
find the index of the **first element strictly greater than target**.

If no such element exists (i.e., all elements <= target), return `n`.

---------------------------------------------------------------
Example 1:
Input:
    arr = [1, 2, 4, 5, 6], target = 3
Output:
    2
Explanation:
    First element greater than 3 is `4` at index 2 (0-based).

Example 2:
Input:
    arr = [1, 2, 4, 5, 6], target = 6
Output:
    5
Explanation:
    No element is greater than 6, so return `n = 5`.

Constraints:
- 1 <= n <= 10^5
- arr is sorted in non-decreasing order
- -10^9 <= arr[i], target <= 10^9
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Traverse the array linearly from the beginning.
- Return the first index where arr[i] > target.

🧩 Algorithm:
1. Loop through each element i:
   - If arr[i] > target → return i
2. If loop ends, return n (no element greater).

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
===============================================================
*/
int upperBoundBrute(vector<int>& arr, int target) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        if (arr[i] > target) return i;
    }
    return n;
}


/*
===============================================================
Approach 2: Binary Search (Optimal)
---------------------------------------------------------------
💡 Idea:
- Use binary search since `arr` is sorted.
- Maintain low & high bounds.
- If arr[mid] <= target → search in right half.
- Else → potential answer, continue left half.

🧩 Algorithm:
1. Initialize low = 0, high = n - 1.
2. While low <= high:
   a) mid = (low + high)/2
   b) If arr[mid] <= target → move low = mid + 1
   c) Else → move high = mid - 1
3. At loop end, low = index of first element > target.
4. If none is greater, low = n.

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(1)
===============================================================
*/
int upperBoundBinary(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= target) low = mid + 1;
        else high = mid - 1;
    }
    return low; 
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    // Test Case 1
    vector<int> arr1 = {1, 2, 4, 5, 6};
    int target1 = 3;
    cout << "Input array: [1,2,4,5,6], target=3\n";
    cout << "➡ Brute Force UB index: " << upperBoundBrute(arr1, target1) << endl; // Expected 2
    cout << "➡ Binary Search UB index: " << upperBoundBinary(arr1, target1) << endl; // Expected 2
    cout << "-------------------------------\n";

    // Test Case 2
    vector<int> arr2 = {1, 2, 4, 5, 6};
    int target2 = 6;
    cout << "Input array: [1,2,4,5,6], target=6\n";
    cout << "➡ Brute Force UB index: " << upperBoundBrute(arr2, target2) << endl; // Expected 5
    cout << "➡ Binary Search UB index: " << upperBoundBinary(arr2, target2) << endl; // Expected 5
    cout << "-------------------------------\n";

    // Test Case 3
    vector<int> arr3 = {2, 2, 2, 2, 2};
    int target3 = 2;
    cout << "Input array: [2,2,2,2,2], target=2\n";
    cout << "➡ Brute Force UB index: " << upperBoundBrute(arr3, target3) << endl; // Expected 5
    cout << "➡ Binary Search UB index: " << upperBoundBinary(arr3, target3) << endl; // Expected 5
    cout << "-------------------------------\n";

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Simple linear traversal.
       - ❌ O(n), inefficient for large arrays.
    
    2. Binary Search (Optimal):
       - Uses sorted property.
       - ✅ O(log n), great even for large n.
    
    🔑 Conclusion:
    - Brute Force for clarity, Binary Search for efficiency.
    ===========================================================
    */
    return 0;
}
