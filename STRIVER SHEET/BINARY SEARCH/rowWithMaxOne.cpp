#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Row with Maximum 1s
---------------------------------------------------------------
Link: https://www.geeksforgeeks.org/problems/row-with-max-1s0023/1

Given a boolean 2D array (n × m), where each row is **sorted** (i.e., 
all 0s come before 1s), find the row index with the maximum number of 1s.
If no 1s exist, return -1.

---------------------------------------------------------------
Example:
Input:
n = 5, m = 4
arr =
0 0 1 1
0 1 1 1
1 1 1 1
0 0 0 0
0 0 0 0

Output: 2
Explanation: Row 2 has 4 ones, the maximum.
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Traverse each row, count 1s, and track the row with maximum 1s.

🧩 Algorithm:
1. Loop over all rows.
2. For each row, count 1s.
3. Update maxRow if this row has more 1s.
4. Return maxRow.

⏱ Time Complexity: O(n * m)
📦 Space Complexity: O(1)
===============================================================
*/
int rowWithMax1s(vector<vector<int>>& arr) {
    int n = arr.size();
    int maxRow = -1, maxCount = 0;
    for (int i=0; i<n; i++) {
        int count = 0;
        for (int x : arr[i]) if (x == 1) count++;
        if (count > maxCount) {
            maxCount = count;
            maxRow = i;
        }
    }
    return maxRow;
}


/*
===============================================================
Approach 2: Binary Search per row
---------------------------------------------------------------
💡 Idea:
- Rows are sorted, so we can find the **first 1** using binary search.
- Number of 1s = m - indexOfFirst1.

🧩 Algorithm:
1. For each row:
   - Binary search first index where arr[i][mid] = 1.
   - Count = m - index.
2. Track row with maximum count.

⏱ Time Complexity: O(n * log m)
📦 Space Complexity: O(1)
===============================================================
*/
int numberOfOnes(vector<int>& row, int m) {
    int low = 0, high = m-1, mid;
    while (low <= high) {
        mid = low + (high-low)/2;
        if (row[mid] == 0) low = mid+1;
        else high = mid-1;
    }
    return m - low; // index of first 1 is "low"
}
int rowWithMax1s2(vector<vector<int>>& arr) {
    int n = arr.size(), m = arr[0].size();
    int max1 = -1, ans = -1;
    for (int i=0; i<n; i++) {
        int count = numberOfOnes(arr[i], m);
        if (count > max1) {
            max1 = count;
            ans = i;
        }
    }
    return ans;
}


/*
===============================================================
Approach 3: Optimized (Top-Right Traversal)
---------------------------------------------------------------
💡 Idea:
- Start from top-right corner (i=0, j=m-1).
- If arr[i][j]==1 → move left (this row has more 1s).
- If arr[i][j]==0 → move down.
- Track the row where we moved left.

🧩 Algorithm:
1. Initialize i=0, j=m-1, maxRow=-1.
2. While (i<n && j>=0):
   - If arr[i][j]==1 → update maxRow=i; j--.
   - Else → i++.
3. Return maxRow.

⏱ Time Complexity: O(n + m)
📦 Space Complexity: O(1)
===============================================================
*/
int rowWithMax1s3(vector<vector<int>>& arr) {
    int n = arr.size(), m = arr[0].size();
    int maxRow = -1;
    int i = 0, j = m-1;
    while (i < n && j >= 0) {
        if (arr[i][j] == 1) {
            maxRow = i;
            j--; // move left
        } else {
            i++; // move down
        }
    }
    return maxRow;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<vector<int>> arr = {
        {0, 0, 1, 1},
        {0, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    cout << "Row with max 1s (Brute Force): " << rowWithMax1s(arr) << endl;    // 2
    cout << "Row with max 1s (Binary Search): " << rowWithMax1s2(arr) << endl; // 2
    cout << "Row with max 1s (Optimized): " << rowWithMax1s3(arr) << endl;     // 2

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Count 1s row-wise.
       - Time: O(n*m), Space: O(1).

    2. Binary Search per row:
       - Find first 1 in each row using binary search.
       - Time: O(n log m), Space: O(1).

    3. Optimized (Staircase Search):
       - Start from top-right corner.
       - Each move eliminates a row or column.
       - Time: O(n+m), Space: O(1).
    
    🔑 Conclusion:
    - Use Brute Force for clarity.
    - Use Optimized approach in practice (fastest).
    ===========================================================
    */

    return 0;
}
