#include<bits/stdc++.h>
using namespace std;

/*
Problem: Set Matrix Zeroes

Problem Statement:
Given an m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place if possible.

Example:
Input:
  matrix = [
    [0, 1, 2, 0],
    [1, 4, 5, 1],
    [9, 3, 6, 1]
  ]
Output (one valid result):
  [
    [0, 0, 0, 0],
    [0, 4, 5, 0],
    [0, 3, 6, 0]
  ]

Approach Overview:
- Extra Space O(m+n): Track which rows and columns need zeroing using two marker arrays; then zero them in a second pass.
- Optimized O(1) Extra Space: Use the first row and first column of the matrix itself as markers; handle the first column separately with a boolean.

Complexity Overview:
- Both approaches: Time O(mn).
- Extra space approach: Space O(m+n).
- In-place optimized: Space O(1).
*/

/*
Approach 1: Extra Space O(m+n)

Idea:
- Scan matrix and record rows[i]=1 or cols[j]=1 if matrix[i][j]==0.
- Second pass: Set matrix[i][j]=0 if rows[i]==1 or cols[j]==1.

Algorithm:
1) Initialize rows[m]=0, cols[n]=0
2) For each cell (i,j), if matrix[i][j]==0: rows[i]=1, cols[j]=1
3) For each i: if rows[i]==1, set row i to 0
4) For each j: if cols[j]==1, set column j to 0

Time Complexity: O(mn)
Space Complexity: O(m+n)
*/
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> row(m, 0);
    vector<int> col(n, 0);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (matrix[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }
    for (int i=0; i<m; i++) {
        if (row[i]) {
            for (int j=0; j<n; j++) matrix[i][j] = 0;
        }
    }
    for (int j=0; j<n; j++) {
        if (col[j]) {
            for (int i=0; i<m; i++) matrix[i][j] = 0;
        }
    }
}

/*
Approach 2: In-place O(1) Extra Space (Use first row/col as markers)

Idea:
- Use matrix[i][0] and matrix[0][j] as flags to indicate zeroing row i or column j.
- Keep a separate boolean col0 to remember whether the first column should be zeroed (since matrix[0][0] is shared for first row/col).
- First pass: set markers.
- Second pass (reverse order): zero cells based on markers; handle first column with col0.

Algorithm:
1) col0=false
2) For i in [0..m-1]:
     if matrix[i][0]==0: col0=true
     For j in [1..n-1]:
        if matrix[i][j]==0: matrix[i][0]=0, matrix[0][j]=0
3) For i from m-1 down to 0:
     For j from n-1 down to 1:
        if matrix[i][0]==0 || matrix[0][j]==0: matrix[i][j]=0
     If col0: matrix[i][0]=0

Time Complexity: O(mn)
Space Complexity: O(1)
*/
void setZeroes2 (vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    bool col0 = false;

    for (int i=0; i<m; i++) {
        if (matrix[i][0] == 0) col0 = true;
        for (int j=1; j<n; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    for (int i=m-1; i>=0; i--) {
        for (int j=n-1; j>=1; j--) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
        if (col0) matrix[i][0] = 0;
    }
}

int main() {
    vector<vector<int>> matrix = {{0,1,2,0},{1,4,5,1},{9,3,6,1}};
    setZeroes2(matrix);
    for (int i=0; i<(int)matrix.size(); i++) {
        for (int j=0; j<(int)matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
