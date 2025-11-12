#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Search a 2D Matrix II
---------------------------------------------------------------
Link: https://leetcode.com/problems/search-a-2d-matrix-ii/

Given an m x n integer matrix sorted in ascending order:
- Each row is sorted left-to-right
- Each column is sorted top-to-bottom

Determine if a given target exists in the matrix.

---------------------------------------------------------------
Example:
Input: 
matrix = [[1,3,5],
          [7,9,11],
          [12,13,15]], target = 9
Output: true
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Traverse every element.
- Compare with target.

⏱ Time Complexity: O(m * n)
📦 Space Complexity: O(1)
===============================================================
*/
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[0].size(); j++) {
            if (matrix[i][j] == target) return true;
        }
    }
    return false;
}


/*
===============================================================
Approach 2: Row-wise Binary Search
---------------------------------------------------------------
💡 Idea:
- Each row sorted → apply binary search in each row.

⏱ Time Complexity: O(m * log n)
📦 Space Complexity: O(1)
===============================================================
*/
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    for (int i=0; i<m; i++) {
        int low = 0, high = n-1;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (matrix[i][mid] == target) return true;
            else if (matrix[i][mid] < target) low = mid+1;
            else high = mid-1;
        }
    }
    return false;
}


/*
===============================================================
Approach 3: Optimized Row + Binary
---------------------------------------------------------------
💡 Idea:
- Only search a row if target <= last element of that row.
- Then binary search inside.

⏱ Time Complexity: O(m * log n) (but prunes many rows)
📦 Space Complexity: O(1)
===============================================================
*/
bool searchMatrix3(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    for (int i=0; i<m; i++) {
        if (target > matrix[i][n-1]) continue; // skip this row
        int low = 0, high = n-1;
        while (low <= high) {
            int mid = low + (high-low)/2;
            if (matrix[i][mid] == target) return true;
            else if (matrix[i][mid] < target) low = mid+1;
            else high = mid-1;
        }
    }
    return false;
}


/*
===============================================================
Approach 4: Optimal Staircase Search
---------------------------------------------------------------
💡 Idea:
- Start top-right corner:
  • If target < element → move left
  • If target > element → move down
  • If equal → return true
- Why it works? Each row & column sorted ⇒
  moving left reduces values, moving down increases values.

⏱ Time Complexity: O(m + n)
📦 Space Complexity: O(1)
===============================================================
*/
bool searchMatrix4(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int row = 0, col = n-1;

    while (row < m && col >= 0) {
        if (matrix[row][col] == target) return true;
        else if (matrix[row][col] > target) col--; // move left
        else row++; // move down
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
        {1, 3, 5},
        {7, 9, 11},
        {12, 13, 15}
    };
    
    int target = 9;

    cout << "Brute Force: " << (searchMatrix(matrix, target) ? "Found" : "Not Found") << endl;
    cout << "Row-wise Binary Search: " << (searchMatrix2(matrix, target) ? "Found" : "Not Found") << endl;
    cout << "Optimized Row Binary: " << (searchMatrix3(matrix, target) ? "Found" : "Not Found") << endl;
    cout << "Staircase Search: " << (searchMatrix4(matrix, target) ? "Found" : "Not Found") << endl;

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Check all elements.
       - Time: O(m*n).

    2. Binary Search per Row:
       - Use binary search in each row.
       - Time: O(m log n).

    3. Optimized Row + Binary:
       - Skip invalid rows quickly.
       - Time: O(m log n), but faster in practice.

    4. Staircase Search (Optimal):
       - Start top-right, move left or down.
       - Time: O(m+n), Space: O(1).
       - ✅ Most efficient and typically expected in interviews.

    🔑 Conclusion:
    - Use Approach 4 in interviews/contests.
    ===========================================================
    */

    return 0;
}
