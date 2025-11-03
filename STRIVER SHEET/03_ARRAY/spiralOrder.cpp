#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Spiral Order Traversal of a Matrix

Problem Statement:
Given an m x n matrix, return all elements of the matrix in spiral order.

Example:
Input:
  matrix =
  [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
  ]
Output:
  [1, 2, 3, 6, 9, 8, 7, 4, 5]

Approach Overview:
- Use four boundaries (top, bottom, left, right) to peel the matrix layer by layer in spiral order.
- After traversing a side, move the corresponding boundary inward.
- Stop when boundaries cross.

----------------------------------------
Approach: Boundary Simulation
Approach Idea:
- Traverse the current outer layer in four steps: left→right (top row), top→bottom (right column),
  right→left (bottom row, if any), bottom→top (left column, if any).
- Increment/decrement boundaries after each side traversal.

Algorithm:
1) Initialize top=0, bottom=m-1, left=0, right=n-1; result = [].
2) While top <= bottom and left <= right:
   - For j from left to right: push matrix[top][j]; top++.
   - For i from top to bottom: push matrix[i][right]; right--.
   - If top <= bottom: for j from right to left: push matrix[bottom][j]; bottom--.
   - If left <= right: for i from bottom to top: push matrix[i][left]; left++.
3) Return result.

Time Complexity: O(m*n)
Space Complexity: O(1) extra (excluding the output vector)
*/
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;
    vector<int> result;

    while (top <= bottom && left <= right) {
        // Left -> Right (top row)
        for (int j = left; j <= right; j++) {
            result.push_back(matrix[top][j]);
        }
        top++;

        // Top -> Bottom (right column)
        for (int i = top; i <= bottom; i++) {
            result.push_back(matrix[i][right]);
        }
        right--;

        // Right -> Left (bottom row)
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                result.push_back(matrix[bottom][j]);
            }
            bottom--;
        }

        // Bottom -> Top (left column)
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                result.push_back(matrix[i][left]);
            }
            left++;
        }
    }
    return result;
}

int main() {
    vector<vector<int>> matrix = {
        {1,  2,  3},
        {4,  5,  6},
        {7,  8,  9}
    };

    vector<int> result = spiralOrder(matrix);
    for (int x : result) cout << x << " ";
    cout << "\n";
    return 0;
}
