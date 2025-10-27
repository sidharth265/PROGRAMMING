#include<bits/stdc++.h>
using namespace std;

/*
Problem: Rotate Image (90° Clockwise)

Problem Statement:
Given an n x n 2D matrix representing an image, rotate the image by 90 degrees clockwise. The rotation must be done in-place.

Example:
Input:
  matrix =
  [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
  ]
Output:
  [
    [7, 4, 1],
    [8, 5, 2],
    [9, 6, 3]
  ]

Approach Overview:
- Extra Matrix (O(n^2) space): Build a new matrix ans where ans[j][n-1-i] = matrix[i][j], then copy back.
- In-place Optimal (Transpose + Reverse Rows): First transpose across the main diagonal, then reverse each row.

Complexity Overview:
- Extra Matrix: Time O(n^2), Space O(n^2).
- In-place (Recommended): Time O(n^2), Space O(1).
*/

/*
Approach 1: Using Extra Matrix (O(n^2) space)

Idea:
- For each element at (i, j), its rotated position is (j, n-1-i).
- Write into a temporary matrix and copy back.

Algorithm:
1) Create ans with same dimensions.
2) For i in [0..n-1], for j in [0..n-1]:
     ans[j][n-1-i] = matrix[i][j]
3) Copy ans back to matrix.

Time Complexity: O(n^2)
Space Complexity: O(n^2)
*/
void rotateExtra(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++) {
            ans[j][n-i-1] = matrix[i][j];
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            matrix[i][j] = ans[i][j];
        }
    }
}

/*
Approach 2: In-place (Transpose + Reverse Rows) — Recommended

Idea:
- Transpose: swap matrix[i][j] with matrix[j][i] for i<j.
- Reverse each row to complete the 90° clockwise rotation.

Algorithm:
1) For i in [0..n-2]:
     For j in [i+1..n-1]:
        swap(matrix[i][j], matrix[j][i])
2) For each i in [0..n-1]:
     reverse(matrix[i].begin(), matrix[i].end())

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
void rotateInPlace(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i=0; i<n-1; i++){
        for (int j=i+1; j<n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    for (int i=0; i<n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Choose one:
    // rotateExtra(matrix);    // Uses O(n^2) extra space
    rotateInPlace(matrix);     // In-place O(1) space

    cout << "Rotated matrix:\n";
    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = 0; j < (int)matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
