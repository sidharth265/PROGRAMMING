#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Painter's Partition Problem-II
---------------------------------------------------------------
Link: https://www.geeksforgeeks.org/problems/the-painters-partition-problem1535/1

You have `n` boards each of length arr[i].
You have `k` painters. Each painter paints **contiguous boards** only.  
Find the **minimum time** required to paint all boards if each unit length
takes 1 time unit.

---------------------------------------------------------------
Example:
Input: arr = [10,20,30,40], k = 2  
Output: 60  

Explanation:
- Painter 1: boards {10,20} → total = 30  
- Painter 2: boards {30,40} → total = 70 → max = 70  
But if we do {10,20,30} and {40}:  
  - Painter 1: 60, Painter 2: 40 → max = 60 ✅ minimum possible.
===============================================================
*/


/*
===============================================================
Helper Function: possible
---------------------------------------------------------------
Checks if we can allocate boards such that no painter
exceeds `maxAllowed` time.

- Traverse boards sequentially, keep painting until exceeding `maxAllowed`.
- If exceeded, allocate to new painter.
- Reduce k count.
- If painters left < 0 → allocation not possible.

⏱ Time Complexity: O(n)
===============================================================
*/
bool canPaint(vector<int> &arr, int k, int maxAllowed) {
    int painters = 1; 
    int curr = 0;
    for (int len : arr) {
        if (len > maxAllowed) return false; // one board > max → impossible
        if (curr + len > maxAllowed) {
            painters++;
            curr = len;
        } else {
            curr += len;
        }
    }
    return painters <= k;
}


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Try every possible max value `x = [max(arr), sum(arr)]`.
- For each candidate x, check if we can allocate with `canPaint()`.
- First valid x is our answer.

⏱ Time Complexity: O((sum-max) * n) → exponential-ish for large input
📦 Space Complexity: O(1)
===============================================================
*/
int minTimeBrute(vector<int>& arr, int k) {
    int low = *max_element(arr.begin(), arr.end()); // at least 1 board
    int high = accumulate(arr.begin(), arr.end(), 0); // all boards by one painter

    for (int x = low; x <= high; x++) {
        if (canPaint(arr, k, x)) return x;
    }
    return -1;
}


/*
===============================================================
Approach 2: Optimized (Binary Search)
---------------------------------------------------------------
💡 Idea:
- The answer lies between [max(arr), sum(arr)].
- Use binary search on this range.
- For mid = (low+high)/2:
   - If possible with mid → try smaller (high=mid-1).
   - Else → increase (low=mid+1).
- Return low.

⏱ Time Complexity: O(n log(sum(arr)))
📦 Space Complexity: O(1)
===============================================================
*/
int minTimeBinarySearch(vector<int>& arr, int k) {
    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);
    int ans = high;

    while (low <= high) {
        int mid = low + (high-low)/2;
        if (canPaint(arr, k, mid)) {
            ans = mid;
            high = mid-1;
        } else {
            low = mid+1;
        }
    }
    return ans;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> arr = {10, 20, 30, 40};
    int k = 2;

    cout << "Brute Force Answer: " << minTimeBrute(arr, k) << endl;         // 60
    cout << "Binary Search Answer: " << minTimeBinarySearch(arr, k) << endl; // 60

    // Additional Test
    vector<int> arr2 = {5, 10, 30, 20, 15};
    k = 3;
    cout << "Brute: " << minTimeBrute(arr2, k) << endl;          
    cout << "Binary Search: " << minTimeBinarySearch(arr2, k) << endl;   // expected 35

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Try all possible max values.
       - Time: O(n*(sum-max)), impractical for large inputs.

    2. Optimized Binary Search:
       - Binary search the optimal max value.
       - Time: O(n log(sum)), Space: O(1)
       - Works efficiently even for large arrays.

    🔑 Conclusion:
    - Use binary search approach in practice.
    - Brute is just for conceptual clarity.
    ===========================================================
    */
    return 0;
}
