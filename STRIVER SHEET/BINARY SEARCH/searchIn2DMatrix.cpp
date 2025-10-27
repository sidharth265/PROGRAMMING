#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Search a 2D Matrix
---------------------------------------------------------------
Link: https://leetcode.com/problems/search-a-2d-matrix/

You are given an m x n integer matrix with the following properties:

1. Integers in each row are sorted in ascending order.
2. The first integer of each row is greater than the last integer of the previous row.

Write an efficient algorithm to determine if a given target exists in the matrix.

---------------------------------------------------------------
Example:
Input: 
matrix = [[1,3,5,7],
          [10,11,16,20],
          [23,30,34,60]], target = 3
Output: true

Explanation: 3 exists in row 0, column 1.
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Traverse every element, check if equal to target.

⏱ Time Complexity: O(m*n)
📦 Space Complexity: O(1)
===============================================================
*/
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (matrix[i][j] == target) return true;
        }
    }
    return false;
}


/*
===============================================================
Approach 2: Row Selection + Binary Search
---------------------------------------------------------------
💡 Idea:
- Use row’s last element to find the possible row.
- Once found, do binary search in that row.

🧩 Steps:
1. Linearly find row `i` with last element >= target.
2. Perform binary search on row i.

⏱ Time Complexity: O(m + log n)
📦 Space Complexity: O(1)
===============================================================
*/
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int row = -1;
    for (int i=0; i<m; i++) {
        if (target == matrix[i][n-1]) return true;
        if (target < matrix[i][n-1]) {
            row = i;
            break;
        }
    }
    if (row == -1) return false;

    int low = 0, high = n-1;
    while (low <= high) {
        int mid = low + (high-low)/2;
        if (matrix[row][mid] == target) return true;
        else if (matrix[row][mid] < target) low = mid+1;
        else high = mid-1;
    }
    return false;
}


/*
===============================================================
Approach 3: Optimal (Flatten Matrix & Binary Search)
---------------------------------------------------------------
💡 Idea:
- Matrix can be viewed as a sorted 1D array of size m*n.
- Index mapping:
   - Row = mid / n
   - Col = mid % n

🧩 Steps:
1. Do binary search on range [0 ... m*n-1].
2. Convert mid back into matrix indices.
3. Compare with target.

⏱ Time Complexity: O(log(m*n))
📦 Space Complexity: O(1)
===============================================================
*/
bool searchMatrix3(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int low = 0, high = m*n - 1;

    while (low <= high) {
        int mid = low + (high-low)/2;
        int element = matrix[mid/n][mid%n];
        if (element == target) return true;
        else if (element < target) low = mid+1;
        else high = mid-1;
    }
    return false;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int target = 3;

    cout << "Brute Force: " 
         << (searchMatrix(matrix, target) ? "Found" : "Not Found") << endl;

    cout << "Row + Binary Search: " 
         << (searchMatrix2(matrix, target) ? "Found" : "Not Found") << endl;

    cout << "Optimal Flattened Binary Search: " 
         << (searchMatrix3(matrix, target) ? "Found" : "Not Found") << endl;

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Check all elements.
       - Time: O(m*n)

    2. Row Selection + Binary Search:
       - Use last element of row to select row.
       - Then binary search in that row.
       - Time: O(m + log n)

    3. Flatten + Binary Search (Optimal):
       - Treat matrix as 1D sorted array.
       - Time: O(log(m*n)), Space: O(1)

    🔑 Conclusion:
    - Use Approach 3 in interviews/contests.
    ===========================================================
    */
    return 0;
}
